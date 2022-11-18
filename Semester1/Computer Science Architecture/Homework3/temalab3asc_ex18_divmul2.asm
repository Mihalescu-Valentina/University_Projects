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
    b db 3
    c dw 2
    e dd 4
    x dq 6

; our code starts here
segment code use32 class=code
    start:
        ; (a+b*c+2/c)/(2+a)+e+x    (3+3*2+1)/5+4+6=C
        mov al,[b]
        cbw
        mov cx,[c]
        imul cx ;b*c is in dx:ax
        push ax
        mov al,[a]
        cbw
        mov cx,ax
        pop ax
        add ax,cx
        adc dx,0  
        mov bx,ax
        mov cx,dx ;a+b*c in cx:bx
        push cx
        push bx
        
        mov al,2
        cbw
        cwd ;2 is in dx:ax
        mov bx,[c]
        idiv bx  ; 2/c is in ax 
        pop bx
        pop cx
        cwd
        add bx,ax
        adc cx,dx ;in cx:bx is the result of (a+b*c+2/c)
        mov dx,cx
        mov ax,bx ; in dx:ax is the result of (a+b*c+2/c)
        push dx
        push ax
        
        
        
        mov eax,0
        mov al,[a]
        add al,2
        cbw ;in ax we have a+2
        mov bx,ax
        pop ax
        pop dx
        idiv bx ;in ax we have the result of (a+b*c+2/c)/(2+a)
        cwd 
        cdq ;in edx:eax is stored the result of (a+b*c+2/c)/(2+a)
        
        mov ecx, dword[x]
        mov ebx, dword[x+4] ;x is stored in ebx:ecx because is a quad
        add ecx,[e] 
        adc ebx,0  ;x+e is stored in ebx:ecx
        add ecx,eax
        adc ebx,edx  ;the final result is stored in ebx:ecx register
        
        
        
        
        
        
        
        
        
        
       
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
