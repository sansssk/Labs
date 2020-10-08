SECTION .data
msg db '{ILoveSLEEP=andEat}',0xa
lenm equ $ - msg
key db 'vine'
lenk equ $ - key
newLine db 0xa

SECTION .bss
array resb lenm

SECTION .text
global _start

_start:
    mov ecx,(lenm - 1)
    mov ebx,key
    mov ebp,lenk
    mov esi,msg
    mov edi,array 

;посимвольная обработка шифруемого текста
.letter:
    mov dl,[esi] 
    cmp dl,'z' ;если символ не является буквой
    ja .save_notletter 

    cmp dl,'a' ;если символ-заглавная буква
    jb .capital 

    call encrypt
    jmp .save

    .capital: 
        cmp dl,'Z' ;если символ не явл.буквой
        ja .save_notletter

        cmp dl,'A'
        jb .save_notletter
        
        add dl,20h ;A-Z -> a-z
        call encrypt
        sub dl,20h ;a-z -> A-Z
        jmp .save

    .save_notletter:
        mov [edi],dl
        xor dl,dl
        inc esi ;"переключаемся" на следующую букву текста
        inc edi 
        loop .letter
        jmp .output

    .save:
        mov [edi],dl
        xor dl,dl
        inc esi ;"переключаемся" на следующую букву текста
        inc edi 
        call get_letter_key
        loop .letter
        jmp .output
        
    .output:
        mov eax,4
        mov ebx,1
        mov ecx,array
        mov edx,lenm
        int 80h

        mov eax, 4
        mov ebx, 1
        mov ecx, newLine
        mov edx, 1
        int 80h

        mov eax,1
        xor ebx,ebx
        int 80h
        ret

;функция encrypt выполняет алгоритм шифра Виженера:
;буква шифртекста = (буква текста + буква шифра)%26
;
;условие входа:
;(1) символ буквы текста в dl
;(2) ключ шифрования в ebx
encrypt:
    sub dl,'a' 
    add dl,[ebx]

    cmp dl,'z'
    ja .make_letter
    ret

    ;обработка по mod 26
    .make_letter:
        sub dl,'z'
        add dl,'a'
        sub dl,1
        ret

;функция get_letter_key переключает значение буквы ключа
;
;условие входа:
;(1) текущая длина ключа в ebp
;(2) ключ в ebx
;
;условие выхода:
;(1) длина ключа > 0
;(2) ebx != 0
get_letter_key:
    dec ebp 
    jnz .update_key
    mov ebp,lenk 
    mov ebx,key
    ret

    .update_key:
        inc ebx 
        ret