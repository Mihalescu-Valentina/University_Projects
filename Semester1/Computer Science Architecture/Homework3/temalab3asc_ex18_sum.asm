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
    c dd 1020h
    d dq 1122334455667788h
    
    

; our code starts here
segment code use32 class=code
    start:
        ;(d-b)-a-(b-c)
        mov ecx, dword[d+0] ;my quadword d is stored in ebx:ecx
        mov ebx, dword[d+4]
        clc
        
        mov ax,[b]
        cwde
        cdq     
        sub ecx,eax
        sbb ebx,edx  ;(d-b) is stored in ebx:ecx
        
        mov al,[a]
        cbw
        cwde
        cdq
        sub ecx,eax
        sbb ebx,edx  ;(d-b)-a is stored in ebx:ecx
        
        mov dx,[b]
        cwde
        sub edx,[c]
        
        mov eax,edx
        cdq          ;(b-c) is stored in edx:eax
        sub ecx,eax
        sbb ebx,edx
        
        
        
                
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
