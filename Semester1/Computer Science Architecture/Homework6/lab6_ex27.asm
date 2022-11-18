bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
     s dw 3456h,1122h,1125h,1128h,1120h,1127h,2345h,3455h
     len equ ($-s)/2
     fin times len dw 0
     lenmax db 0
     startmax db 0
     lencrt db 0
     startcrt db 1
     i db 0
; our code starts here
segment code use32 class=code
    start:
        cld
        mov ecx,len
        mov esi,s
        mov edi,0
        ;mov [lenmax],0
        ;mov [startmax],0
        ;mov [lencrt],0
        ;mov [startcrt],1
        ;mov i,2
        ;mov [edi+0],[s+0]
        ;add esi,2
        ;add [pos],1
        jecxz end_loop
        longest_substr_asc:
        ;cmpsw ;<=> cmp esi,edi; add esi,2 ;add edi,2
        cmp [i+esi],[i+esi-2]
        jg ascending
        cmp lencrt,lenmax
        jnle maxnotfound:
        mov startmax,startcrt
        sub lencrt,1
        mov [lenmx],[lencrt]
        jmp final
        maxnotfound:
        mov [startcrt],[i]
        mov [lencrt],1
        jmp final
        ;dec [lend1]
        ;mov [ind1],[pos]
        ascending:
           add [lencrt],1
           ;inc word[find1]
           ;add esi,2
           ;add [pos],1
        final:
        add [i],2
        loop longest_substr_asc
        
        end_loop:
        
        mov ecx,[lenmax]
        mov [i],startmax
        jecxz fin_build
        fin_string:
        mov [fin+edi],[esi+i]
        add [i],2
        add edi,2
        loop fin_string
        fin_build:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
