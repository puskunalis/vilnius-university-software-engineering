org 100h

section .text
	
	startas:
		
		;cmc
		;std
		;movsb
		;movsw
		;cmpsb
		;cmpsw
		;scasb
		;scasw
		;lodsb
		;lodsw
		;stosb
		;stosw
		;push ax
		;push cx
		;push dx
		;push bx
		;push sp
		;push bp
		;push si
		;push di
		;pop ax
		;pop cx
		;pop dx
		;pop bx
		;pop sp
		;pop bp
		;pop si
		;pop di
		;push es
		;push cs
		;push ss
		;push ds
		;pop es
		;pop ss
		;pop ds
		
;add al, bh
;add cl, bl
;add dh, ch
;add cl, byte [bx+si+1]
;add byte [bx+si+9000], cl
;add cx, word [ds:1234]
;add word [1234], cx
;add byte [4546], al
;add al, byte [4546]
;add si, word [5]
;add dx, bx
;add ax, si
;add bp, di
;mov al, [ss:1234]
;mov ax, [es:9876]
;mov [ds:4568], al
;mov [cs:6668], ax
;add al, 56
;add ax, 4564
;repne movsb
;repnz lodsb
;rep scasb
;repe scasw
;repz lodsw
;jmp 1541:8778
;shr ah, 1
;add dl, 3
;push es
;pop es
;push cs
;adc cl, cl
;pop ss
;push ds
;and byte [ss:1234], ch
;int 3
;int 1
;int 3
;mov ss, [ds:1354+bx+di]
;mov [cs:7894+si+bx], ds
;mov ss, [cs:bp]
;mov ds, [bp]
;call procedura
;push word [ds:bx+si+9876]
;pop word [ds:bx+si+9876]
;mov ds, ax
;mov ax, ds
;mov word [cs:bx+si+39321], 30855
mov [bp], word 39000
mov [bp+20], word 37000
mov [bp+35000], word 36000
lea di, word [ss:bx+di+32101]
les sp, word [es:si+2]
lds si, word [bp]
xchg ax, ax
nop
xchg ax, cx
xchg bp, ax
xchg ax, di
cbw
cwd
aam
aad
aam
mov dh, byte [bp+9876]
push word [1]
inc word [1]
les ax, word [cs:bx+si+1234]
xor cl, byte [bp+9999]
call 7777:8888
jmp 8888:7777
shr al, 1
int 3
shr dh, 1
test dh, 45
not dh
test dx, 30000
not dx
inc word [bp+5]
dec word [ds:bx+si+3]
call ax
call word [es:bp+si+32000]
jmp ax
jmp word [es:bp+si+32000]
push word [es:bp+si+32000]
db 0x8C
db 0x21
mov word [ds:bx+di+3], cs
mov es, word [ds:bx+di+4]
jmp .label
.label:

mov eax, 12345678h
mov eax, 0FFFFFFFh
mov eax, 00001000h
mov eax, 00010000h
mov ebx, 98765432h
mov ecx, 45000450h
mov edx, 60000036h
mov esp, 45651000h
mov edi, 00000001h
mov esi, 10000000h
mov ebp, 00000000h
mul eax
mul edx
imul ecx
imul ebx
div ecx
div ebx
idiv ecx
idiv edx

aad 7
aam 8

mov ah, 0x4C
int 0x21

procedura:
	pushf
	popf
	ret