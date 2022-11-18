bits 32

global start        
extern exit
extern rapidconv
extern printf
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data
;21. It is given a number in base 2 represented on 32 bits. Write to the console the number in base 16. (use the quick conversion)
    a dd 0010011111111000001110011010b
    ;a dd 101010111100110111101111b
    checking_format db "checked hexa with %%x is: %x",10,0
    result_format db "result hexa from module is: %s",10,0
    result resb 9
; our code starts here
segment code use32 class=code
    start:
    push dword [a]
    call rapidconv
    add esp,4*1
    
    mov edi,result
    add edi,7  
    std  ;there is need of setting the direction flag and adding 7 to edi in order to perform the stosb instruction correctly for our string; if it were just mov edi,result and cdf the string would have been stored in result in reverse order 
    mov ecx,4
    loop1:
        stosb
        shr eax,8
    loop loop1
    ;after loop1 eax is 0 and the second part of the result is stored in the right order in the result: 00 00 00 00 38 33 39 41
    mov eax,edx
    mov ecx,4
    loop2:
        stosb
        shr eax,8
    loop loop2
    ;result-> 30 32 37 46 38 33 39 41
    push dword [a]
    push checking_format
    call [printf]    
    add esp, 4*2
    
    push dword result
    push result_format
    call [printf]    
    add esp, 4*2

        push    dword 0
        call    [exit]
