bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 3
    b db 4
    c db 2
    d db 12

; our code starts here
segment code use32 class=code
    start:
        ; d-(a+b)-(c+c) 12-7-4=1
        mov al,[a] 
        add al,[b]   ; calculate and store the sum a+b in the al register 
        mov bl,[d]
        sub bl,al     ; calculate and store d-(a+b) in the bl register
        mov al,[c]    
        add al,[c]  ;the sum c+c is performed and stored in the al register
        sub bl,al   ;the final result is stored in the bl register        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
