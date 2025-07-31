section .text
bits 64
default rel
global mainG
extern printf, scanf


mainG:
    ; RCX: x1
    ; RDX: x2
    ; R8:  y1
    ; R9:  y2
    ; [rsp+40]: z (output)
    ; [rsp+48]: n
    
    push rsi
    push rdi
    push rbx
    
    mov rsi, rcx        ; x1
    mov rdi, rdx        ; x2
    mov rbx, r8         ; y1
    mov r10, r9         ; y2
    mov r11, [rsp+64]   ; z (40 + 24 for pushes)
    mov r12, [rsp+72]   ; n (48 + 24 for pushes)
    
    xor ecx, ecx        ; i = 0

.loop:
    cmp ecx, r12d
    jge .end
    
    ; Calculate distance
    movss xmm0, [rsi + rcx*4]   ; x1[i]
    subss xmm0, [rdi + rcx*4]    ; dx
    mulss xmm0, xmm0              ; dx²
    
    movss xmm1, [rbx + rcx*4]    ; y1[i]
    subss xmm1, [r10 + rcx*4]    ; dy
    mulss xmm1, xmm1              ; dy²
    
    addss xmm0, xmm1              ; dx² + dy²
    sqrtss xmm0, xmm0             ; sqrt(...)
    
    ; Store result
    movss [r11 + rcx*4], xmm0    ; z[i] = result
    
    inc ecx
    jmp .loop

.end:
    pop rbx
    pop rdi
    pop rsi
    ret