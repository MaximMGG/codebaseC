extern malloc
section .data

section .bss
    str:     resq    1

section .text
    global  test_str

test_str:
push    rbp
mov     rbp, rsp
        mov     [rbp - 8], rdi
        mov     rax, [rbp - 8]
        mov     rbx, [rax]
        mov     rcx, [rax + 8]
        mov     rdi, 12
        call    malloc
        mov     [str], rax
        mov     rax, [rbp - 8]
        mov     rdi, [rax + 8]
        call    malloc
        mov     rbx, [str]
        mov     qword [rbx], rax
        mov     rax, [rbp - 8]
        mov     rcx, [rax + 8]
        mov     dword [rbx + 8], ecx

        mov     rax, str

leave
ret

