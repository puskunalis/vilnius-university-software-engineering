org 100h

%include 'yasmmac.inc'

section .text

	startas:
		macPutString 'Vilius Puskunalis 1 kursas 5 grupe', crlf, '$'
		macPutString 'Iveskite teksto eilute nuo 8 iki 80 simboliu:', crlf, '$'
		
		eilutesIvedimas:
			mov ah, 0Ah
			mov dx, buferisIvedimui
			int 21h
		
		macNewLine
		
		; Koreguojame buferi
		mov bx, 0
		mov bl, [buferisIvedimui+1]         
		mov byte [buferisIvedimui+bx+3], 0Ah ; Pridedame LF
		mov byte [buferisIvedimui+bx+4], '$' ; Pridedame galo simboli
		mov [eilutesIlgis], bx
		
		cmp bx, 8
		jnb tinkamaEilute
		
		macPutString 'Eilute per trumpa!', crlf, '$'
		jmp eilutesIvedimas
		
		tinkamaEilute:
		
		macPutString 'Iveskite skaiciu a:', crlf, '$'
		call procGetUInt16
		mov [skaicius1], ax
		macNewLine
		
		macPutString 'Iveskite skaiciu b:', crlf, '$'
		call procGetUInt16
		mov [skaicius2], ax
		macNewLine
		
		macPutString 'Iveskite skaiciu c:', crlf, '$'
		call procGetUInt16
		mov [skaicius3], ax
		macNewLine
		
		mov ax, [skaicius1]
		mov [pradinisSkaicius1], ax
		
		; Skaiciu a keliame i c
		;mov al, [skaicius1]
		;mov [skaicius3], al
		
		macPutString 'Trecias ir sestas simboliai apkeisti vietomis, antras simbolis "-":', crlf, '$'
		
		; Kopijuojame sutvarkyta pradine eilute antram uzdaviniui
		add bx, 4
		mov cx, bx
		ciklas1:
			mov bx, cx
			mov dl, [buferisIvedimui+bx]
			mov [pradineEilute+bx], dl
			dec cx
			jnz ciklas1
		
		; Apkeiciame trecia ir sesta simbolius vietomis
		mov al, [buferisIvedimui+4]
		mov ah, [buferisIvedimui+7]
		mov [buferisIvedimui+4], ah
		mov [buferisIvedimui+7], al
		
		; Antra simboli pakeiciame i '-'
		mov byte [buferisIvedimui+3], '-'
		
		; Spausdiname sutvarkyta teksto eilute
		mov ah, 09h
		mov dx, buferisIvedimui+2
		int 21h
		
		macPutString 'Pradines teksto eilutes baitu antro, trecio ir priespaskutinio bitu sumos:', crlf, '$'
		
		mov bl, 0
		ciklas2:
			mov cl, 0
			inc bl
			
			mov dl, [pradineEilute+bx+1]
			
			shr dl, 2
			
			; Imame liekanas, shiftiname, sumuojame
			mov ah, 0
			mov al, dl
			mov ch, 2
			div ch
			add cl, ah
			add [bituSuma], ah
			
			shr dl, 1
			
			mov ah, 0
			mov al, dl
			mov ch, 2
			div ch
			add cl, ah
			add [bituSuma], ah
			
			shr dl, 3
			
			mov ah, 0
			mov al, dl
			mov ch, 2
			div ch
			add cl, ah
			add [bituSuma], ah
			
			mov ah, 0
			mov al, cl
			call procPutUInt16
			
			cmp bl, [eilutesIlgis]
			jne ciklas2
			
		macNewLine
			
		macPutString 'Bendra suma:', crlf, '$'
		mov ax, [bituSuma]
		call procPutUInt16
		
		macNewLine
		
		mov ah, [skaicius1]
		cmp ah, 0
		je dalybaIsNulio
		
		; Atliekame veiksmus su skaiciais
		mov dx, 0
		mov ax, 1000
		mov bx, [skaicius1]
		div bx
		mov [skaicius1], ax
		
		mov dx, 0
		mov ax, [skaicius2]
		mov bx, 50
		div bx
		add dx, [skaicius3]
		mov [skaicius2], dx
		
		mov dx, 0
		mov ax, [pradinisSkaicius1]
		mov bx, 2
		div bx
		mov [skaicius3], ax
		
		; Lyginame sutvarkytus skaicius
		mov dx, [skaicius3]
		cmp dx, 23
		jb cmp1
		cmp1Back:
		
		mov dx, [skaicius2]
		cmp dx, [skaicius3]
		jb cmp2
		mov dx, [skaicius3]
		mov [maziausiasSkaicius], dx
		cmp2Back:
		
		mov dx, [skaicius1]
		cmp dx, [maziausiasSkaicius]
		jb cmp3
		cmp3Back:
		
		macPutString 'Reiskinio min(1000 / a, b % 50 + c, max(a / 2 + 1, 23)) reiksme:', crlf, '$'
		mov ax, [maziausiasSkaicius]
		call procPutUInt16
		
		exit
		
	cmp1:
		mov byte [skaicius3], 23
		jmp cmp1Back
		
	cmp2:
		mov [maziausiasSkaicius], dx
		jmp cmp2Back
		
	cmp3:
		mov [maziausiasSkaicius], dx
		jmp cmp3Back
	
	dalybaIsNulio:
		macPutString 'Dalyba is nulio!', crlf, '$'
		exit

%include 'yasmlib.asm'

section .data
		
	eilutesIlgis:
		dw 00
		
	buferisIvedimui:
		db 51h, 00h, '******************************************************************************************'
	
	pradineEilute:
		db 51h, 00h, '******************************************************************************************'
		
	skaicius1:
		dw 00
		
	pradinisSkaicius1:
		dw 00
		
	skaicius2:
		dw 00
		
	skaicius3:
		dw 00
		
	maziausiasSkaicius:
		dw 00
		
	bituSuma:
		dw 00
