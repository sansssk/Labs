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

;������������ ��������� ���������� ������
.letter:
    mov dl,[esi] 
    cmp dl,'z' ;���� ������ �� �������� ������
    ja .save_notletter 

    cmp dl,'a' ;���� ������-��������� �����
    jb .capital 

    call encrypt
    jmp .save

    .capital: 
        cmp dl,'Z' ;���� ������ �� ���.������
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
        inc esi ;"�������������" �� ��������� ����� ������
        inc edi 
        loop .letter
        jmp .output

    .save:
        mov [edi],dl
        xor dl,dl
        inc esi ;"�������������" �� ��������� ����� ������
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

;������� encrypt ��������� �������� ����� ��������:
;����� ���������� = (����� ������ + ����� �����)%26
;
;������� �����:
;(1) ������ ����� ������ � dl
;(2) ���� ���������� � ebx
encrypt:
    sub dl,'a' 
    add dl,[ebx]

    cmp dl,'z'
    ja .make_letter
    ret

    ;��������� �� mod 26
    .make_letter:
        sub dl,'z'
        add dl,'a'
        sub dl,1
        ret

;������� get_letter_key ����������� �������� ����� �����
;
;������� �����:
;(1) ������� ����� ����� � ebp
;(2) ���� � ebx
;
;������� ������:
;(1) ����� ����� > 0
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