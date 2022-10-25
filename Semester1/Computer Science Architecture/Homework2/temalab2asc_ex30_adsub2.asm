bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 8
    b dw 5
    c dw 6
    d dw 4

; our code starts here
segment code use32 class=code
    start:
        ;a-b+(c-d+a) 8-5+(6-4+8)=3+10=13=D
        mov ax,[c]  
        sub ax,[d]   ;ax stores the result of c-d(because both c and d are words-they need a register of 16 bits)
        add ax,[a]   ; ax stores the result of c-d+a
        mov bx,[a]   
        sub bx,[b]   ;bx stores the result of the subtraction a-b
        add bx,ax    ;the final result is stored in the bx register  
       
       
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
