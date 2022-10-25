bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
     a db 4
     b db 2
     c db 5
     d dw 9

; our code starts here
segment code use32 class=code
    start:
        ;[(a-b)*5+d]-2*c [(4-2)*5+9]-2*5=2*5+9-10=19-10=9
         mov al,[a] 
         
         sub al,[b]   ;the subtraction between a and b is stored in the al register
         mov bl,5    
         
         mul bl      ;the mul instruction will multiply the 5 from the bl register with the result of(a-b) which is stored in al
         ;the final result of the multiplication is stored in ax which is a register of 16 bits: 8(bl)+8(al)
         
         add ax,[d]   ;this addition can be performed because both operands have a size of 16 bits
         
         mov bx,ax     ;I moved the data from ax to bx because in order to perform the next multiplication i need the register  al to be filled only with the value of c and also the result previously stored in ax needs to be used further in the programme
         
         mov cl,2
         mov al,[c]
         
         mul cl ;this mul instruction will multiply the 2 from cl with the c from al and will store the result on 16 bits-ax register(changing the ah value as well)
         
         sub bx,ax   ; the final result is stored in the bx register
         
         
         
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
