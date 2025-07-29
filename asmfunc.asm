;In this file, enter your assembly code. This will then be picked up by C. (in the mainG part)


section .data
msg1 db "Hello World! TRIAL RUN",10,0

section .text
bits 64
default rel
global mainG
extern printf, scanf


mainG:
mov rbp, rsp; for correct debugging
;write your code here
sub rsp, 8*7
mov rcx, msg1
call printf

add rsp, 8*7
ret