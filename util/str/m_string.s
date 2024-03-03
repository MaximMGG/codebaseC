extern malloc
extern free
section .data
    END_L      db  0

section .bss
    struc  str
        string:  resq    1
        len:     resd    1
    endstruc

    mal_len         resq    1
    temp_str        resq    1

section .text
    global  str_concat_a
str_concat_a:
push    rbp
mov     rbp, rsp

        mov     qword [rbp - 8], rdi
        mov     qword [rbp - 16], rsi
        xor     rax, rax
        mov     rax, [rdi + 8]
        add     rax, [rsi + 8]
        inc     rax
        mov     [mal_len], rax
        mov     rdi, [mal_len]
        call    malloc
        mov     [temp_str], rax
        mov     r10, qword [rbp - 8]
        mov     rcx, [r10 + 8]
        mov     r11, [r10]
        mov     r13, [temp_str]
    .first_loop:
        cmp     rcx, 0
        je      .first_loop_exit
        mov     rax, [r11]
        mov     byte [r13], al
        inc     r11
        inc     r13
        dec     rcx
        jmp     .first_loop
    .first_loop_exit:
        mov     rax, [rbp - 16]
        mov     r11, [rax]
        mov     rcx, [rax + 8]

    .second_loop:
        cmp     rcx, 0
        je      .second_loop_end
        mov     rax, [r11]
        mov     byte [r13], al
        inc     r11
        inc     r13
        dec     rcx
        jmp     .second_loop
    .second_loop_end:
        mov     rdi, [temp_str]
        call    strlen
        mov     [mal_len], rax

        mov     rax, 1
        mov     rdi, 1
        mov     rsi, [temp_str]
        mov     rdx, [mal_len]
        syscall
leave
ret




strlen:
push    rbp
mov     rbp, rsp
        xor         rax, rax
        pxor        xmm0, xmm0

    .loop:
        pcmpistri   xmm0, [rdi + rax], 000010000b
        add         rax, 16
        jnz         .loop        
        add         rax, rcx
        inc         rax
leave
ret
