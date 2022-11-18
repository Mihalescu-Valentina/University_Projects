bits 32
global _cnt_word_letters
extern _printf
segment data public data use32
    message db "Number of letters in word: %d",10,0
segment code public code use32
_cnt_word_letters:
	push ebp    ;a new stack frame is created
	mov ebp,esp  
    
    mov esi,[ebp+8] ; address of s-the first and only parameter of the function
    
    xor ecx,ecx ; counts the number of letters in a word
    parse_sentence:
        lodsb   ; al = current char
        cmp al,0
        je done_parsing
        
        cmp al,'A'
        jb not_letter
        
        cmp al,'z'
        ja not_letter
        
        cmp al,'a'
        jae is_letter
        
        cmp al,'Z'
        jbe is_letter
        
        is_letter:
            inc ecx
        jmp over_not_letter
        not_letter:
            cmp ecx,0
            je cont
                push ecx
                push dword message
                call _printf
                add esp,4*2
            cont:
            xor ecx,ecx
        over_not_letter:
    jmp parse_sentence  ;because we can't know how many words we have in a sentence i cannot work with a loop so i have to use jmp
    
    done_parsing:
    
    mov esp, ebp  ;remaking the stackframe
    pop ebp
    ret