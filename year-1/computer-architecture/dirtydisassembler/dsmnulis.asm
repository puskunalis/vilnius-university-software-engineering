; Uzduotis: nuskaityti komandines eilutes argumenta (failo vardas be pletinio), 
; atidaryti atitinkama faila skaitymui, perra6yti jo turini pagal
; dizasemblerio schema 
;  
%include 'yasmmac.inc'

%macro writeln   1
    push ax
    push dx
    mov ah, 09
    mov dx, %1
    int 21h
    mov ah, 09
    mov dx, naujaEilute
    int 21h
    pop dx
    pop ax
%endmacro

%macro writeln2   1
    push ax
    push dx
    mov ah, 09
    mov dx, %1
    int 21h
    pop dx
    pop ax
%endmacro
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro readln    1
    mov ah, 0Ah
    mov dx, %1
    int 21h
    mov ah, 09
    mov dx, naujaEilute
    int 21h
%endmacro

%macro macPrintRegister   2
    push bx
	push di
	
	mov bh, 0
	mov bl, %1
	add bl, bl
	mov di, %2
	mov di, [di+bx]
	writeln2 di

	pop di
	pop bx
%endmacro

%macro macArray8ar16 0
	mov word [current_array], r_array
	cmp dl, byte argRegMem8
	je %%baigiamMacro
	cmp dl, byte argReg8
	je %%baigiamMacro
	mov word [current_array], rw_array
	cmp [bitMode32], byte 1
	jne %%baigiamMacro
	mov word [current_array], rw32_array
	%%baigiamMacro:
	cmp dl, byte argSegReg
	jne %%tikraiBaigiamMacro
	mov word [current_array], sr_array
	%%tikraiBaigiamMacro:
%endmacro

%macro macPrintStr 1
	push dx
	mov dx, %1
	call procPutStr
	pop dx
%endmacro

%macro macPrintPrefixOpJeiYra 0
	cmp [prefiksoAdresas], word 0
	je %%neraPrefikso
	macPrintStr [prefiksoAdresas]
	macPrintStr strDvitaskis
	mov [prefiksoAdresas], word 0
	%%neraPrefikso:
%endmacro

%macro macSpausdintiByteWord 0
	cmp [reikesPtr], byte 0
	je %%nereikesPtr
	cmp dl, byte argRegMem16
	je %%spausdintiWord
	cmp dl, byte argReg16
	jne %%spausdintiByte
	%%spausdintiWord:
	macPrintStr strWord
	jmp %%atspausdinomWord
	%%spausdintiByte:
	macPrintStr strByte
	%%atspausdinomWord:
	macPrintPrefixOpJeiYra
	jmp %%pabaiga
	%%nereikesPtr:
	macPrintStr strStartLauztinis
	macPrintPrefixOpJeiYra
	%%pabaiga:
%endmacro

%macro macGetChar 0
	push bx
	push ax
	mov bx, [skaitomasFailas]
	call procFGetChar
	add [ipCounter], word 1
	pop ax
	pop bx
%endmacro

%macro macSetGroupOpcode 1
	push bx
	push si
	push dx
	
	mov si, bx
	mov bx, 0
	mov bl, [abREG]
	add bl, bl
	add bx, %1
	mov dx, [bx]
	mov [si], dx
	;macPrintStr [si]
	
	pop dx
	pop si
	pop bx
%endmacro

%macro macTestAtskirasAtvejis 0
	cmp [bx], word t_opTEST
	jne %%neTest
	mov [ag2], byte argImm8
	cmp [dabartineInstrukcija], byte 0xF6
	je %%neTest
	mov [ag2], byte argImm16
	%%neTest:
%endmacro

%macro macPrintPoslinki 0
	push ax
	;mov ax, cs
	mov ax, 0734h
	call procPutHexWord
	macPrintStr strDvitaskis
	mov ax, [ipCounter]
	call procPutHexWord
	macPrintStr strTarpas
	pop ax
%endmacro
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
org 100h   
section .text
    main:
       ; pradzioje ds ir es rodo i PSP;
       ; PSP+80h -> kiek baitu uzima komandine eilute (be programos pavadinimo)
       ; 
       call skaitykArgumenta
       jnc .rasykArgumenta
       writeln klaidosPranesimas
       jmp .Ok

       .rasykArgumenta: 
       mov dx, komEilutesArgumentas      
       call writeASCIIZ 
       
       ;Atidarome faila
       mov dx, komEilutesArgumentas      
       call atverkFaila
       jnc .skaitomeFaila
       writeln klaidosApieFailoAtidarymaPranesimas
       jmp .Ok

       .skaitomeFaila:
       mov bx, [skaitomasFailas]          
       mov dx, nuskaitytas          
       call skaitomeFaila
       jnc .failoUzdarymas
       writeln klaidosApieFailoSkaitymaPranesimas
       ;jmp .Ok

       .failoUzdarymas:
       mov bx, [skaitomasFailas]          
       call uzdarykFaila
       .Ok:
       mov ah,     4ch                            ; baigimo funkcijos numeris
       int 21h
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  atverkFaila:  
        ; dx - failo vardo adresas
        ; CF yra 1 jeigu klaida 
        push ax
        push dx

        mov ah, 3Dh
        mov al, 00h       ; skaitymui
        int 21h

        jc .pab
        mov [skaitomasFailas], ax

        .pab:  
        pop dx
        pop ax
        ret   

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  uzdarykFaila:  
        ; dx - failo vardo adresas
        ; CF yra 1 jeigu klaida 
        push ax
        push bx

        mov ah, 3Eh
        int 21h

        .pab:  
        pop dx
        pop ax
        ret     


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    rasykSimboli:  
        ; al - simbolis 
        push ax
        push dx
        mov dl, al
        mov ah, 02h
        int 21h
        pop dx
        pop ax
        ret   
  
  

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   konvertuokI16taine:  
        ; al - baitas
        ; ax - rezultatas
        mov ah, al
        and ah, 0F0h
        times 4 shr ah, 1
        and al, 0Fh

        cmp al, 09
        jle .plius0
        sub al, 10
        add al, 'A'
        jmp .AH
        .plius0:
        add al, '0'
        .AH:
             
        cmp ah, 09
        jle .darplius0
        sub ah, 10
        add ah, 'A'
        jmp .pab
        .darplius0:
        add ah, '0'
        .pab:
        xchg ah, al 
        ret     
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    analizuokKoda:  
		; INPUT: 
		;    al - nuskaitytas baitas
		;    bx - failo deskriptorius - cia nenaudojas, bet potencialiai reikalingas  :)
		
		mov [dabartineInstrukcija], al
		
		cmp [spausdinamIP], byte 0
		je .nespausdinamIP
		macPrintPoslinki
		.nespausdinamIP:
		mov [spausdinamIP], byte 1
		
		push bx
		push ax
		push cx
		push dx
		push si
		push di
		push bp
		
		; BX bus naudojamas strukturoms adresuoti, padauginam is 5
		mov ah, 0
		mov bx, op00
		times 5 add bx, ax
		
		; Jei neegzistuoja
		cmp [bx+tipas], byte kEmpty
		je .tiesiogDB
		
		; Jei 32bitPrefix
		cmp [bx+tipas], byte k32bitPrefix
		jne .ne32Bitu
		mov [bitMode32], byte 1
		mov [spausdinamIP], byte 0
		jmp .pabBeCRLF
		.ne32Bitu:
		
		; Jei kPrefix
		cmp [bx+tipas], byte kPrefix
		jne .nePrefix
		push ax
		mov ax, [bx+pavadinimas]
		mov [prefiksoAdresas], ax
		pop ax
		mov [spausdinamIP], byte 0
		jmp .pabBeCRLF
		.nePrefix:
		
		; Jei kPrefixOp
		cmp [bx+tipas], byte kPrefixOp
		jne .nePrefixOp
		macPrintStr [bx] ; Komandos pavadinima printinam
		mov [spausdinamIP], byte 0
		jmp .pabBeCRLF
		.nePrefixOp:
		
		; Saugom argumentus i atminti
		push ax
		mov ah, 0
		mov al, [bx+arg1]
		mov [ag1], al
		mov al, [bx+arg2]
		mov [ag2], al
		pop ax
		
		; Jei kUseless
		cmp [bx+tipas], byte kUseless
		jne .neUseless
		macGetChar
		macPrintStr [bx] ; Komandos pavadinima printinam
		cmp [ag2], byte argUseless
		jne .pab
		macGetChar
		jmp .pab
		.neUseless:
		
		; Jei visiskai neturi argumentu
		cmp [ag1], byte argNone
		je .argNone
		
		; Nuskaitom adresavimo baita jei toks yra
		cmp [bx+arg1], byte argRegMem8
		jl .galABAntrameArgumente
		jmp .skaitytiAB
		.galABAntrameArgumente:
		cmp [bx+arg2], byte argRegMem8
		jl .neraAdresavimoBaito
		.skaitytiAB:
		call skaitytiAdresavimoBaita
		
		; Jei kExtraOpk
		cmp [bx+tipas], byte kExtraOpk
		jne .dirbamSuAB
		cmp al, byte 0x84
		jg .ne84
		macSetGroupOpcode grp1
		jmp .dirbamSuExtraOpk
		.ne84:
		cmp al, byte 0xD4
		jg .neD4
		macSetGroupOpcode grp2
		jmp .dirbamSuExtraOpk
		.neD4:
		cmp al, byte 0xF8
		jg .neF8
		macSetGroupOpcode grp3
		jmp .dirbamSuExtraOpk
		.neF8:
		cmp al, byte 0xFE
		jne .neFE
		macSetGroupOpcode grp4
		jmp .dirbamSuExtraOpk
		.neFE:
		cmp al, byte 0xFF
		jne .dirbamSuAB
		macSetGroupOpcode grp5
		
		.dirbamSuExtraOpk:
		call procArReikesPtr
		macPrintStr [bx] ; Komandos pavadinima printinam
		
		macTestAtskirasAtvejis ; Test ilgesne uz kitas komandas F6, F7
		
		call darbasSuExtraOpk
		jmp .pab
		.nerExtraOpk:
		
		; Darbas su adresavimo baitu
		;;;;;;;;;;;;;;;;;;;;;
		.dirbamSuAB:
		
		call procArReikesPtr
		
		; SegReg not used opcode atvejis
		cmp [ag1], byte argSegReg
		je .segRegNotUsedAtvejis
		cmp [ag2], byte argSegReg
		je .segRegNotUsedAtvejis
		jmp .neraSegReg
		.segRegNotUsedAtvejis:
		cmp [abREG], byte 100b
		jl .neraSegReg
		mov al, [dabartineInstrukcija]
		call konvertuokI16taine
		mov [nuskaitytas], ax
		writeln2 strDB
		macNewLine
		macPrintPoslinki
		mov al, [ab]
		call konvertuokI16taine
		mov [nuskaitytas], ax
		writeln2 strDB
		jmp .pab
		.neraSegReg:
		
		macPrintStr [bx] ; Komandos pavadinima printinam
		
		mov dl, [ag1]
		mov dh, [abRM]
		mov [ag], dl
		
		; Esc atskiras atvejis
		cmp al, byte 0xD8
		jl .neraEsc
		cmp al, byte 0xDF
		jg .neraEsc
		call procEscAtskirasAtvejis
		jmp .praleidziamPoEsc
		.neraEsc:
		
		call spausdintiAdresa
		call procArReikesPtr
		.praleidziamPoEsc:
		
		mov dl, [ag2]
		cmp dl, argNone
		je .pab
		
		macPrintStr strKablelis
		mov dh, [abREG]
		
		cmp dl, argFar
		jg .neNeadresuojamas
		mov dl, [ag2]
		mov [ag], dl
		call printArgument
		jmp .pab
		.neNeadresuojamas:
		
		; Esc atskiras atvejis
		cmp al, byte 0xD8
		jl .neraEsc2
		cmp al, byte 0xDF
		jg .neraEsc2
		jmp .pab
		.neraEsc2:
		
		call spausdintiAdresa
		
		jmp .pab
		; Baigiam darba su adresavimo baitu
		;;;;;;;;;;;;;;;;;;;;;
		.neraAdresavimoBaito:
		macPrintStr [bx] ; Komandos pavadinima printinam
		
		mov al, [ag1]
		mov [ag], al
		call printArgument
		
		cmp [ag2], byte 0 ; argNone
		je .pab
		
		macPrintStr strKablelis
		
		mov al, [ag2]
		mov [ag], al
		call printArgument
		
		jmp .pab
		
		.tiesiogDB:
		call konvertuokI16taine                 ; DB
		mov [nuskaitytas],  ax
		writeln2 strDB
		jmp .pab
		
		.argNone:
		macPrintStr [bx] ; Komandos pavadinima printinam
		.pab:
		macNewLine
		mov [bitMode32], byte 0
		.pabBeCRLF:
		pop bp
		pop di
		pop si
		pop dx
		pop cx
		pop ax
		pop bx
		ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; Adresavimo baito reiksmes nuskaitomos i [abMOD], [abREG], [abRM]
	skaitytiAdresavimoBaita:
		push ax
		push bx
		push cx
		
		macGetChar
		mov byte [ab], cl
		
		mov ch, cl
		times 6 shr ch, 1
		mov [abMOD], ch
		
		mov ch, cl
		times 5 shl ch, 1
		times 5 shr ch, 1
		mov [abRM], ch
		
		mov ch, cl
		times 2 shl ch, 1
		times 5 shr ch, 1
		mov [abREG], ch
		
		pop cx
		pop bx
		pop ax
		ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; dl - argumentas
	; dh - "dabartinis RM"
	spausdintiAdresa:
		push cx
		push ax
		; Pradedam nuo mod11
		cmp [abMOD], byte 11b
		je .mod11
		
		cmp [abMOD], byte 00b
		jne .praleistiDA
		cmp [abRM], byte 110b
		jne .praleistiDA
		
		call directAddress
		jmp .ret
		
		.praleistiDA:
		.mod00:
			cmp dl, argRegMem16
			jg .printinamRegistra
			
			; Printinam adresa
			mov word [current_array], rm_array
			macSpausdintiByteWord
			macPrintRegister [abRM], [current_array]
			
			; Jei nebeskaitysim baitu, nes mod is tikro nebuvo 00
			cmp [abMOD], byte 00b
			jne .mod01
			macPrintStr strEndLauztinis
			jmp .ret
			
			.printinamRegistra:
			call printinamRegistra
			jmp .ret
			
		.mod01:
			macPrintStr strPliusas
			
			; Nuskaitom baita
			mov ah, 0
			macGetChar
			mov al, cl
			
			; Ar skaitom dar viena baita?
			cmp [abMOD], byte 10b
			je .mod10
			
			call procPutHexWord
			macPrintStr strEndLauztinis
			jmp .ret
			
		.mod10:
			; Nuskaitom baita
			macGetChar
			mov ah, cl
			
			call procPutHexWord
			macPrintStr strEndLauztinis
			jmp .ret
		
		.mod11:
			macArray8ar16
			macPrintRegister dh, [current_array]
		
		.ret:
		pop ax
		pop cx
		ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;		
	printinamRegistra:
		macArray8ar16
		macPrintRegister [abREG], [current_array]
		ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; dl - vis dar argumentas
	directAddress:
		push ax
		push bx
		push cx
		push dx
		
		macArray8ar16
		
		cmp dl, byte argRegMem16
		jg .spausdinamRegistra
		
		macSpausdintiByteWord
		macGetChar
		mov al, cl
		macGetChar
		mov ah, cl
		call procPutHexWord
		macPrintStr strEndLauztinis
		jmp .baigiamDA
		
		.spausdinamRegistra:
			macArray8ar16
			macPrintRegister [abREG], [current_array]
		
		.baigiamDA:
		pop dx
		pop cx
		pop bx
		pop ax
		ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	printArgument:
		push bx
		push ax
		push cx
		push dx
		push si
		
		cmp [ag], byte argDS
		jg .neRegistras
		mov bx, registru_array
		cmp [bitMode32], byte 1
		jne .ne32Bitu
		mov bx, reg32_array
		.ne32Bitu:
		times 2 add bl, [ag]
		macPrintStr [bx]
		jmp .pab
		.neRegistras:
		
		cmp [ag], byte argConst1
		jg .ne1
		macPrintStr strVienas
		jmp .pab
		.ne1:
		
		cmp [ag], byte argConst3
		jg .ne3
		macPrintStr strTrys
		jmp .pab
		.ne3:
		
		cmp [ag], byte argEImm8
		jg .neImm8
		macGetChar
		mov ax, cx
		call procPutHexWord
		jmp .pab
		.neImm8:
		
		cmp [ag], byte argShort
		jg .neShort
		macGetChar
		mov ah, 0
		mov al, cl
		cbw
		add ax, [ipCounter]
		inc ax
		call procPutHexWord
		jmp .pab
		.neShort:
		
		cmp [ag], byte argOffs8
		jg .neOffs8
		.Offs8:
		macGetChar
		mov al, cl
		macGetChar
		mov ah, cl
		macPrintStr strStartLauztinis
		macPrintPrefixOpJeiYra
		call procPutHexWord
		macPrintStr strEndLauztinis
		jmp .pab
		.neOffs8:
		
		cmp [ag], byte argImm16
		jg .neImm16
		macGetChar
		mov al, cl
		macGetChar
		mov ah, cl
		cmp [bitMode32], byte 1
		jne .ne32bit
		mov si, ax
		macGetChar
		mov al, cl
		macGetChar
		mov ah, cl
		call procPutHexWordVisada
		mov ax, si
		.ne32bit:
		call procPutHexWordVisada
		jmp .pab
		.neImm16:
		
		cmp [ag], byte argOffs16
		jg .neOffs16
		jmp .Offs8
		.neOffs16:
		
		cmp [ag], byte argNear
		jg .neArgNear
		macGetChar
		mov al, cl
		macGetChar
		mov ah, cl
		add ax, [ipCounter]
		inc ax
		call procPutHexWord
		jmp .pab
		.neArgNear:
		
		cmp [ag], byte argFar
		macGetChar
		mov dl, cl
		macGetChar
		mov dh, cl
		macGetChar
		mov bl, cl
		macGetChar
		mov bh, cl
		mov ax, bx
		call procPutHexWord
		macPrintStr strDvitaskis
		mov ax, dx
		call procPutHexWord
		
		.pab:
		pop si
		pop dx
		pop cx
		pop ax
		pop bx
		ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	darbasSuExtraOpk:
		push dx
		
		mov dl, [ag1]
		mov dh, [abRM]
		call spausdintiAdresa
		
		cmp [ag2], byte argNone
		je .pab
		
		macPrintStr strKablelis
	
		mov al, [ag2]
		mov [ag], al
		call printArgument
		
		.pab:
		pop dx
		ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	procEscAtskirasAtvejis:
		push ax
		
		mov ah, 0
		mov al, [dabartineInstrukcija]
		sub al, 0xD8
		times 3 shl al, 1
		add al, [abREG]
		call procPutHexWord
		
		macPrintStr strKablelis
		
		cmp [abMOD], byte 11b
		je .printinamRegistra
		mov dl, [ag1]
		mov dh, [abRM]
		call spausdintiAdresa
		jmp .ret
		
		.printinamRegistra:
		macPrintRegister byte [abRM], r_array
		
		.ret:
		pop ax
		ret
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	procArReikesPtr:
		mov [reikesPtr], byte 0
		
		cmp [ag1], byte argImm8
		je .reikes
		cmp [ag2], byte argImm8
		je .reikes
		cmp [ag1], byte argEImm8
		je .reikes
		cmp [ag2], byte argEImm8
		je .reikes
		cmp [ag1], byte argImm16
		je .reikes
		cmp [ag2], byte argImm16
		je .reikes
		cmp [ag1], byte argFar
		je .reikes
		cmp [ag2], byte argConst1
		je .reikes
		cmp [ag2], byte argConst3
		je .reikes
		cmp [ag2], byte argCL
		je .reikes
		cmp [ag1], byte argSegReg
		je .reikes
		cmp [ag2], byte argSegReg
		je .reikes
		
		cmp [ag2], byte argNone
		jne .ret
		cmp [ag1], byte argRegMem8
		je .reikes
		cmp [ag1], byte argRegMem16
		je .reikes
		
		jmp .ret
		.reikes:
		mov [reikesPtr], byte 1
		jmp .ret
	
		.ret:
		ret
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    skaitykArgumenta:  
         ; nuskaito ir paruosia argumenta
         ; jeigu jo nerasta, tai CF <- 1, prisingu atveju - 0

         push bx
         push di
         push si 
         push ax

         xor bx, bx
         xor si, si
         xor di, di

         mov bl, [80h]         ;
         mov [komEilIlgis], bl
         mov si, 0081h  
         mov di, komEilutesArgumentas
         push cx
         mov cx, bx
         mov ah,00
         cmp cx, 0000
         jne .pagalVisus
         stc 
         jmp .pab
   
         .pagalVisus:
         mov al, [si]     ;
         cmp al, ' '
         je .toliau
         cmp al, 0Dh
         je .toliau
         cmp al, 0Ah
         je .toliau
         mov [di],al
         ; call rasykSimboli  
         mov ah, 01                  ; ah - pozymis, kad buvo bent vienas "netarpas"
         inc di     
         jmp .kitasZingsnis
         .toliau:
         cmp ah, 01                  ; gal jau buvo "netarpu"?  
         je .isejimas 
         .kitasZingsnis:
         inc si
     
         loop .pagalVisus
         .isejimas: 
         cmp ah, 01                  ; ar buvo "netarpu"?  
         je .pridetCOM
         stc                         ; klaida!   
         jmp .pab 
         .pridetCOM:
         mov [di], byte '.'
         mov [di+1], byte 'C'
         mov [di+2], byte 'O'
         mov [di+3], byte 'M'
         clc                         ; klaidos nerasta
         .pab:
         pop cx
         pop ax
         pop si
         pop di 
         pop dx
         ret
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    skaitomeFaila:  
        ; skaitome faila po viena baita 
        ; bx - failo deskriptorius
        ; dx - buferis 
        push ax
        push dx
        push bx
        push cx
        push si
                
        mov si, dx 
        .kartok:
        mov cx, 01
        mov ah, 3Fh 
        int 21h
        jc .isejimas           ; skaitymo klaida
        cmp ax, 00
        je .isejimas           ; skaitymo pabaiga

        mov al,[si]            ; is buferio
        
        call analizuokKoda     ; bandome dekoduoti
		add [ipCounter], word 1

        jmp .kartok
        
        .isejimas:
        pop si
        pop cx
        pop bx
        pop dx
        pop ax
        ret   
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    writeASCIIZ:  
         ; spausdina eilute su nuline pabaiga, dx - jos adresas
         ; 

         push si
         push ax
         push dx
 
         mov  si, dx
 
         .pagalVisus:
         mov dl, [si]  ; krauname simboli
         cmp dl, 00             ; gal jau eilutes pabaiga?
         je .pab

         mov ah, 02
         int 21h
         inc si
         jmp .pagalVisus
         .pab:
         
         writeln naujaEilute
  
         pop dx
         pop ax
         pop si
         ret
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include 'yasmlib.asm'
%include 'struktai.inc'

section .data                   ; duomenys
  
    dabartineInstrukcija: db 00
	
	ipCounter: dw 0100h
	
	ag: db 00
	ag1: db 00
	ag2: db 00
	
	ab: db 00
	abMOD: db 00
	abREG: db 00
	abRM: db 00
	
	strKablelis: db ',', 00
	strStartLauztinis: db '[', 00
	strEndLauztinis: db ']', 00
	strPliusas: db '+', 00
	strWord: db 'WORD PTR [', 00
	strByte: db 'BYTE PTR [', 00
	strDvitaskis: db ':', 00
	strVienas: db '1', 00
	strTrys: db '3', 00
	strTarpas: db ' ', 00
	
	spausdinamIP: db 01
	reikesPtr: db 00
	
	bitMode32: db 00
	
	prefiksoAdresas: dw 0000
	
	current_array: dw 0000
	
	segmentPrefixPointer: dw 0000
    
    strDB: db 'DB      ' 
    nuskaitytas: db 00, 00, '$'
   
    klaidosPranesimas: db 'Klaida skaitant argumenta $'

    klaidosApieFailoAtidarymaPranesimas: db 'Klaida atidarant faila $'

    klaidosApieFailoSkaitymaPranesimas: db 'Klaida skaitant faila $'

    labas: db 'Labas', 0x0D, 0x0A, '$'

    naujaEilute:    db 0x0D, 0x0A, '$'  ; tekstas ant ekrano
 
    komEilIlgis: db 00
    komEilutesArgumentas:
       times 255 db 00
    skaitomasFailas:
       dw 0FFFh
