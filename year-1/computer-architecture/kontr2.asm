org 100h

%include 'yasmmac.inc'

section .text

	startas:
		macPutString 'Vilius Puskunalis 1 kursas 5 grupe 2 kontrolinis', crlf, '$'
		macPutString 'Iveskite eilute iki 100 simboliu:', crlf, '$'
		
		mov byte [eilute], 0x65
		
		mov byte [eilute+10], '$'
		
		mov ah, 0x0A
		mov dx, eilute
		int 0x21
		
		macNewLine
		
		mov bx, eilute+2
		call pirmasSkaitmuo
		
		macPutString 'Rezultatas: ', '$'
		mov ah, 0x00
		call procPutUInt16
		
		exit
		
	
	; Input: BX - eilutes, kuri baigiasi '$', pradzia
	; Output: AL - pirmo skaitmens indeksas pradedant nuo 1, jei nerasta - 0
	pirmasSkaitmuo:
		push si
		push cx
		
		; Saugome AH reiksme
		mov ch, ah
		
		; Nunuliname AX is anksto
		mov ax, 0x00
		
		; Lengvesnis budas siuo atveju pradeti cikla nuo 0
		mov si, 0xFFFF
		
		.ciklas:
			inc si
			
			; Ar baigesi string?
			cmp [bx+si], byte 0x00
			je .baigti
			
			; Ar dabartinis simbolis nera tarp 0 ir 9 simboliu?
			cmp [bx+si], byte 0x30
			jl .ciklas
			cmp [bx+si], byte 0x39
			jg .ciklas
			
			; Jei taip, i AL dedame indeksa
			mov ax, si
			inc ax
			
			; Graziname AH reiksme
			mov ah, ch
		
		.baigti:
		
		pop cx
		pop si
		ret

%include 'yasmlib.asm'

section .data
		
	eilute:
		times 102 db 0x00