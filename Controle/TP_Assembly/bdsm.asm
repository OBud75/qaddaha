section .data
    prompt db 'Entrez votre nom: ', 0
    greeting db 'Bonjour, ', 0
    newline db 10, 0

section .bss
    name resb 100

section .text
    global _start

_start:
    ; Afficher "Entrez votre nom: "
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, 17
    int 0x80

    ; Lire le nom
    mov eax, 3
    mov ebx, 0
    mov ecx, name
    mov edx, 100
    int 0x80

    ; Afficher "Bonjour, "
    mov eax, 4
    mov ebx, 1
    mov ecx, greeting
    mov edx, 9
    int 0x80

    ; Afficher le nom
    mov eax, 4
    mov ebx, 1
    mov ecx, name
    mov edx, 100
    int 0x80

    ; Afficher une nouvelle ligne
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Terminer le programme
    mov eax, 1
    xor ebx, ebx
    int 0x80