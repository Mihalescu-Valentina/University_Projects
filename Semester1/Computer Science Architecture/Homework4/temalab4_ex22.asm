bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 01010100000000011111100000000110b
    b dw 1001101110111110b
    c dw 0   ;c=0001 0011 1111 1111b
             ;c= 1  3  F F-> little endian: FF 13 in memory

; our code starts here
 ;We have a doubleword A and a word B. You have to form the word C that:
 ;the bits 0-4 of C are reversed compared to the bits 20-24 of A
 ;the bits 5-8 of C are 1
 ;the bits 9-12 of C are identical with the bits 12-15 of B
 ;the bits 13-15 of C are the bits 7-9 of A
segment code use32 class=code
    start:
        mov bx,0  ;in bx register is stored the word c, the final result
        
        mov eax,[a]     
        not eax   ;i inverted the bits of a
        and eax,00000001111100000000000000000000b  ; i isolated the bits from positions 20-24
        mov cl,20
        ror eax,cl    ; i rotated the bits from positions 20-24 with 20 positions to the right
        or  bx,ax     ;i put the bits into the result
        
        or  bx, 0000000111100000b   ;the bits from positions 5-8 become 1
        
        mov ax,[b] 
        and ax,1111000000000000b    ;i isolated the bits from positions 12-15
        mov cl,3 
        ror ax,cl       ;i rotated the bits from positions 12-15 with 3 positions to the right
        or  bx,ax        ;i put the bits into the result
        
        mov eax,[a]   
        and eax,00000000000000000000001110000000b ; i isolated the bits from positions 7-9
        mov cl,6
        rol ax,cl     ;i rotated the bits from positions 7-9 with 6 positions to the left 
        or  bx,ax    
        mov [c],bx  ;i move the result from the register to the result variable
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
