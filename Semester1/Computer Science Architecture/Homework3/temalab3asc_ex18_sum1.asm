bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
     a db 12h
     b dw 1234h
     c dd 2345678h
     d dq 1122334455667788h
    

; our code starts here
segment code use32 class=code
    start:
        ; (d+d)-a-b-c
        mov eax, dword[d+0]  ;separating the quadword in 2 doublewords
        mov edx, dword[d+4]
        
        clc
        add eax,eax  ;eax:AACCEF10
        adc edx,edx  ;the result of d+d is stored in edx:eax registers edx:22446688
        
        
        mov ecx,0
        mov cl,[a]
        mov ebx,0 ;a is stored in ebx:ecx
        sub eax,ecx  ;eax:AACCEEFE
        sbb edx,ebx   ;(d+d)-a is stored in edx:eax registers  edx:22446688
        
        mov ebx,0
        mov ecx,0
        mov cx,[b]   ;b is stored in ebx:ecx
        sub eax,ecx   ;eax:AACCDCCA
        sbb edx,ebx   ;(d+d)-a-b is stored in edx:eax registers  edx:22446688
        
        mov ebx,0
        mov ecx,[c]
        sub eax,ecx  ;eax:A8988652
        sbb edx,ebx  ;the final result is stored in edx:eax registers edx:22446688
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
