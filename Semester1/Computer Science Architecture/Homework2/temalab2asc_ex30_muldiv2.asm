bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
     a db 5
     e dw 12
     h dw 13

; our code starts here
segment code use32 class=code
    start:
        ;100/(e+h-3*a) 100/(25-3*5)=100/10=10=A
        mov bx,[e]
        add bx,[h]   ;the result of e+h is stored in the bx register,ax will be used further for division/multiplication
        mov cl,3      
        mov al,[a]  
        mul cl       ;the result of 3*a will be stored in ax on 16 bits
        sub bx,ax    ;the result of e+h-3*a il stored in bx register
        mov ax,100
        div bl       ;the final result is stored in al, the divident is the ax' value and the divisor is the value stored in bl
        
        
        
         
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
