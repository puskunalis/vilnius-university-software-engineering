org 100h

%include 'yasmmac.inc'

section .text

	startas:
		macPutString 'Vilius Puskunalis 1 kursas 5 grupe', crlf, '$'
		macPutString 'Iveskite teksto eilute nuo 8 iki 80 simboliu:', crlf, '$'
		
		; Ivedame eilute
		mov ah, 0Ah
		mov dx, buferisIvedimui
		int 21h
		
		macNewLine
		
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
		
		macPutString 'Sutvarkyta teksto eilute:', crlf, '$'
		
		; Koreguojame buferi
		mov bx, 0
		mov bl, [buferisIvedimui+1]         
		mov byte [buferisIvedimui+bx+3], 0Ah ; Pridedame LF
		mov byte [buferisIvedimui+bx+4], '$' ; Pridedame galo simboli
		
		mov [eilutesIlgis], bx
		
		; Kopijuojame sutvarkyta pradine eilute antram uzdaviniui
		add bx, 4
		mov cx, bx
		ciklas1:
			mov bx, cx
			mov dl, [buferisIvedimui+bx]
			mov [pradineEilute+bx], dl
			dec cx
			jnz ciklas1
		
		; Apkeiciame pirma ir penkta simbolius vietomis
		mov al, [buferisIvedimui+2]
		mov ah, [buferisIvedimui+6]
		mov [buferisIvedimui+2], ah
		mov [buferisIvedimui+6], al
		
		; Ketvirta simboli pakeiciame i '*'
		mov byte [buferisIvedimui+5], '*'
		
		; Spausdiname sutvarkyta teksto eilute
		mov ah, 09h
		mov dx, buferisIvedimui+2
		int 21h
		
		mov cl, 0
		ciklas2:
			inc cl
			mov bl, cl
			
			mov dl, [pradineEilute+bx+1]
			
			; Imame paskutinio bito liekana, shiftiname ir sumuojame
			mov ah, 0
			mov al, dl
			mov ch, 2
			div ch
			add [bituSuma], ah
			
			shr dl, 3
			
			mov ah, 0
			mov al, dl
			mov ch, 2
			div ch
			add [bituSuma], ah
			
			shr dl, 1
			
			mov ah, 0
			mov al, dl
			mov ch, 2
			div ch
			add [bituSuma], ah
			
			cmp cl, [eilutesIlgis]
			jne ciklas2
			
		macPutString 'Pradines teksto eilutes nulinio, treciojo ir ketvirtojo bitu suma:', crlf, '$'
		mov ax, [bituSuma]
		call procPutUInt16
		
		macNewLine
		
		; Atliekame veiksmus su skaiciais
		mov dx, 0
		mov ax, [skaicius1]
		mov bx, 3
		div bx
		mov [skaicius1], ax
		
		mov dx, 0
		mov ax, [skaicius2]
		mov bx, 2
		div bx
		inc ax
		mov [skaicius2], ax
		
		mov dx, 0
		mov ax, [skaicius3]
		mov bx, 200
		div bx
		mov ax, dx
		mov [skaicius3], dx
		
		; Lyginame sutvarkytus skaicius
		mov dx, [skaicius2]
		cmp dx, 17h
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
		
		macPutString 'Reiskinio min(a / 3, c % 200, max(b / 2 + 1, 23)) reiksme:', crlf, '$'
		mov ax, [maziausiasSkaicius]
		call procPutUInt16
		
		mov ah, 4Ch
		int 21h
		
	cmp1:
		mov byte [skaicius2], 17h
		jmp cmp1Back
		
	cmp2:
		mov [maziausiasSkaicius], dx
		jmp cmp2Back
		
	cmp3:
		mov [maziausiasSkaicius], dx
		jmp cmp3Back

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
		
	skaicius2:
		dw 00
		
	skaicius3:
		dw 00
		
	maziausiasSkaicius:
		dw 00
		
	bituSuma:
		dw 00