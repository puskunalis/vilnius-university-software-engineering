org 100h

%include 'yasmmac.inc'

section .text

	startas:
		macPutString 'Vilius Puskunalis 1 kursas 5 grupe 6 variantas', crlf, crlf, '$'
		macPutString 'Programa isveda tik tas eilutes, kuriose antras laukas neturi raidziu A ir B, o trecio, ketvirto ir penkto lauku sumos skaitmenu suma yra 7.', crlf, crlf, '$'
		macPutString 'Iveskite rasymo failo varda:', crlf, '$'
		
		; Issaugome rasymo failo varda
		mov al, 128         
		mov dx, rasymoFailas
		call procGetStr     
		macNewLine
		
		; Atidarome skaitymo faila
		mov dx, skaitymoFailas
		call procFOpenForReading
		jnc .rasymoFailoAtidarymas
		macPutString 'Klaida atidarant faila skaitymui!', '$'
		exit
		
		; Atidarome rasymo faila
		.rasymoFailoAtidarymas:
			mov [skaitymoDeskriptorius], bx
			mov dx, rasymoFailas
			call procFCreateOrTruncate
			jnc .rasymoFailasAtidarytas
			macPutString 'Klaida atidarant faila rasymui!', '$'
			jmp .rasymoKlaida
		
		; Saugome rasymo deskriptoriu i atminti
		.rasymoFailasAtidarytas:
			mov [rasymoDeskriptorius], bx
			
			
		; Praleidziam pirma eilute
		call procSkaitytiEilute
		
		; Pagrindinis ciklas
		.kolNeFailoPabaiga:
			call procSkaitytiEilute
			
			; Praeiname i antra stulpeli su DI - alternatyvus budas neveikiantis su paskutine eilute
			;mov al, ';'
			;repnz scasb
			
			; Praeiname i antra stulpeli su DI
			mov di, eilute
			.kolNeKabliataskis:
			cmp [di], byte ';'
			je .neKabliataskis
			inc di
			jmp .kolNeKabliataskis
			.neKabliataskis:
			inc di
			
			; Tikriname antra stulpeli
			.antrasStulpelis:
				mov al, [di]
				inc di
				
				cmp al, byte 'A'
				je .praleistiEilute
				cmp al, byte 'a'
				je .praleistiEilute
				cmp al, byte 'B'
				je .praleistiEilute
				cmp al, byte 'b'
				je .praleistiEilute
				
				cmp al, byte ';'
				jne .antrasStulpelis
			
			; Skaiciuojam skaiciu langelius
			call procSkaiciuotiSuma
			call procSkaiciuotiSkaitmenuSuma
			
			
			; Jei skaitmenu suma nelygi 7, einame i sekancia eilute
			cmp [skaitmenuSuma], word 7
			jl .praleistiEilute
			cmp [skaitmenuSuma], word 10
			jg .praleistiEilute
			
			
			; Rasome eilute i faila
			mov bx, [rasymoDeskriptorius]
			mov cx, [eilutesIlgis]
			mov dx, eilute
			mov ah, 40h
			int 21h
			
			; Jei dar nenuskaityta paskutine eilute, tesiam cikla
			.praleistiEilute:
			cmp [nuskaitytaPaskutineEilute], byte 0
			je .kolNeFailoPabaiga
		
		
		; Uzdarome failus
		.pabaiga:
			mov bx, [rasymoDeskriptorius]
			call procFClose
		
		.rasymoKlaida:
			mov bx, [skaitymoDeskriptorius]
			call procFClose
		
		exit
		
%include 'yasmlib.asm'

; void procSkaitytiEilute()
; Nuskaitome eilute i buferi adresu eilute
procSkaitytiEilute:
	push ax
	push bx
	push cx
	push si
	
	mov bx, [skaitymoDeskriptorius]
	mov si, 0


	.ciklas:
		call procFGetChar
	
		; Baigiame jei baigesi failas arba klaida
		cmp ax, 0
		je .baigesiFailas
		jc .baigesiFailas
		
		; Dedame simboli i buferi
		mov [eilute+si], cl
		inc si
	
		; Ar pasiekem \n?
		cmp cl, 0x0A
		je .baigesiEilute
	
		jmp .ciklas
		
		
	.baigesiFailas:
		mov [nuskaitytaPaskutineEilute], byte 1
	.baigesiEilute:
	
	mov [eilute+si], byte '$'
	mov [eilutesIlgis], si
	
	pop si
	pop cx
	pop bx
	pop ax
	ret
	
; Input: DI - pirmo skaiciaus langelio pradzios adresas
; Output: [skaiciuSuma] - suma
procSkaiciuotiSuma:
	push si
	push ax
	push dx
	push cx
	push bx
	
	mov [skaiciuSuma], word 0
	mov si, 0
	
	; Tris kartus kartosim ciklus
	mov ch, 3
	
	.ciklas:
		mov cl, [di]
		inc di
		
		; Ar baigesi stulpelis?
		cmp cl, byte ';'
		je .baigtiCikla
		cmp cl, byte 0x0D
		je .baigtiCikla
		cmp cl, byte '$'
		je .baigtiCikla
		
		mov byte [skaiciusString+si], cl
		mov byte [skaiciusString+si+1], 0
		inc si
		
		jmp .ciklas
		
	.baigtiCikla:
		mov dx, skaiciusString
		call procParseInt16
		add [skaiciuSuma], ax
	
	; Ar kartojam procedura?
	dec ch
	cmp ch, 0
	je .baigiamProcedura
	mov si, 0
	jmp .ciklas
	
	.baigiamProcedura:
	pop bx
	pop cx
	pop dx
	pop ax
	pop si
	ret
	
; I [skaitmenuSuma] suskaiciuoja [skaiciuSuma]
procSkaiciuotiSkaitmenuSuma:
	push ax
	push dx
	push di
	
	mov [skaitmenuSuma], word 0
	
	mov ax, [skaiciuSuma]
	mov dx, skaitmenuString
	call procInt16ToStr
	mov di, dx
	
	.ciklas:
		mov dl, [di]
		inc di
		
		; Minusas nesvarbus
		cmp dl, byte '-'
		je .ciklas
		cmp dl, byte 0
		je .baigtiCikla
		
		; ASCII i skaiciu
		add [skaitmenuSuma], dl
		sub [skaitmenuSuma], byte 0x30
	
		jmp .ciklas
	
	.baigtiCikla:
	pop di
	pop dx
	pop ax
	ret

section .data

	skaitymoFailas:
		db 'input.csv', 00
		
	skaitymoDeskriptorius:
		dw 0000
		
	rasymoFailas:
		times 128 db 00
		
	rasymoDeskriptorius:
		dw 0000
		
	nuskaitytaPaskutineEilute:
		db 00
		
	eilute:
		db 64
		times 66 db '$'
		
	eilutesIlgis:
		dw 0000
		
	skaiciusString:
		times 5 db 00
		
	skaiciuSuma:
		dw 0000
	
	skaitmenuSuma:
		dw 0000
		
	skaitmenuString:
		times 8 db 00