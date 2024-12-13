.global _start
.intel_syntax noprefix

_start:

  mov rax, 1
  mov rdi, 1
  lea rsi, [hello]
  mov rdx, 13
  syscall

  //Exit
  mov rax, 60
  mov rdi, 0
  syscall


hello:
  .asciz "Hello World"
