bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1,3,-2,-5,3,-8,5,0
    lg equ $-s
    d1 times lg db 0
    d2 times lg db 0
    a dd 0
; our code starts here
segment code use32 class=code
    start:
         mov ecx,lg
         mov esi,0 ;used as an index for s
         mov edi,0  ;used as an index for d1
         mov ebx,0 ;used as an index for d2
         jecxz End ;for
         eticheta:
             mov al,[s+esi]
             cmp al,0
             jg positive
                mov [d2+ebx],al
                inc ebx
                jmp tag
             positive:
             mov [d1+edi],al
             inc edi
             tag:
             inc esi
         loop eticheta ;do while
         
         
         
         End:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
