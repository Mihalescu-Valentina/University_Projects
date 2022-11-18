bits 32 ; assembling for the 32 bits architecture
global rapidconv
segment data use32 class=data
    number resd 1
    result resb 8
segment code use32 class=code
rapidconv:
    
    mov eax, [esp+4]  ;eax= 9A837F02
    mov [number],eax
    
    mov edi,result
    cld ;in order to take the result from left to right
    
    mov ecx, 8  ;because we have 8 hexadigits in a doubleword
    maskk:
        mov eax,[number]  ;eax= 027F839A 
        and eax,0Fh        ;eax= A, eax= 9, eax= 3 ... eax= 0
        shr dword [number], 4   ;in order to keep the mask as it is and always to work with the al part of eax we shift to the right with 4 positions after the first shr number will be 39 f8 27 00 in the memory we get rid of A
        
        cmp eax,0     ;we have one hexa digit in eax which will be converted into a character part of the string result
        jl skip       
        cmp eax,9    ;if the hexa digit is greater than 9,then we are interested to see if it is equal to A,B,C,D,E or F(>15)
        jg letter
        ; 0-9
            add eax,48 ;'0'-'9'
        jmp skip
        letter:
        cmp eax,15
        jg skip
        ;10-15
            sub eax,10 ;0-5   
            add eax,'A' ;'A'+0/1/2/3/4/5
        skip:
        stosb
    loop maskk
    
    mov edx,[result+4]  ;edx='0' '2' '7' 'F' because of the mov
    mov eax,[result]    ;eax='8' '3' '9' 'A' because of the mov -double little endian
    ret