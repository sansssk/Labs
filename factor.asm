section .data
    len equ 255
    mul_sign db '*'
    one db '1'
    null db '0'

    overflow_msg db 'Вы ввели слишком большое число  '
    len_overflow_msg equ $ - overflow_msg

    correct_msg db 'Нужно ввести целое положительное число  '
    len_correct_msg equ $ - correct_msg
    
    
section .bss
    num resb len
    outp resb 1

section .text
global _start

;Функция Null выводит 0 и завершает работу программы
;условие входа:
;(1) 0 в еах 
Null:
    mov eax, 4
    mov ebx, 1
    mov ecx, null
    mov edx, 1
    int 80h

    mov eax, 1
    mov ebx, 0
    int 80h

;Функция Correct выводит сообщение и завершает работу программы
;условие входа:
;(1) в еах не положительное целое число
Correct:
    mov eax, 4
    mov ebx, 1
    mov ecx, correct_msg
    mov edx, len_correct_msg
    int 80h

    mov eax, 1
    mov ebx, 0
    int 80h

;Функция Overflow выводит сообщение и завершает работу программы
;условие входа:
;(1) OF == true
Overflow:
    mov eax, 4
    mov ebx, 1
    mov ecx, overflow_msg
    mov edx, len_overflow_msg
    int 80h

    mov eax, 1
    mov ebx, 0
    int 80h

;Функция Check проверяет корректность строки
;условие входа:
;(1) в еах длина строки
;(2) в num строка
;условие выхода:
;(1) еах == 0, т.е. строка кончилась
Check:
    push eax

    .check_digit:
        ;берем из строки посимвольно,т.е. еах-1 итератор по строке
        movzx edx, byte [num + eax - 1] 
        cmp edx, '0'
        jl Correct
        cmp edx, '9'
        jg Correct

        dec eax
        cmp eax, 0
        jne .check_digit

    pop eax
    ret

;Функция Get_digit преобразует строку в число
;условие входа:
;(1) в есх длина строки
;(2) в num строка
;условие выхода:
;(1) в еах получаем число для факторизации
Get_digit:
    xor eax, eax
    mov ebp, 10

    .digit:
        xor ebx, ebx
        mov bl, byte [num + esi] ;
        mul ebp
        jo Overflow

        sub bl, '0'
        add eax, ebx
        inc esi
        cmp esi, ecx
        jl .digit

    ret

;Функция Factorize выполняет факторизацию
;условие входа:
;(1) в еах число
;(2) в ebx фактор
;условие выхода:
;(1) в еах 1, то есть факторизация выполнена
Factorize:
    cmp eax, 1
    je .return
    mov esi, eax
    xor edx, edx

    div ebx
    cmp edx, 0
    je .true

    mov eax, esi
    inc ebx
    jmp Factorize

    .true:
        call Print_factor
        mov ebx, 2
        jmp Factorize

    .return:
        ret

;Функция Print_factor выполняет печать множителя
;условие входа:
;(1) в edx множитель
;условие выхода:
;(1) в esi 0, т.е. множитель выведен
Print_factor:
    xor esi, esi
    push eax
    xor eax, eax
    mov eax, ebx
    xor ebx, ebx

    mov ebp, esp
    xor ecx, ecx

    .factor:
        mov ebx, 10
        div ebx ;для поразрядной работы с числом
        add edx, '0'
        push edx ;кладем на стек множитель поразрядно начиная с младшего
        xor edx, edx
        inc esi
        cmp eax, 0
        jne .factor

    .output:
        pop edx
        mov [outp], dl

        mov eax, 4
        mov ebx, 1
        mov ecx, outp
        mov edx, 1
        int 80h

        dec esi
        cmp esi, 0
        jne .output

        ;выводит знак умножения
        .sign:
            mov eax, 4
            mov ebx, 1
            mov ecx, mul_sign
            mov edx, 1
            int 80h
            
        mov esp, ebp
        pop eax

        ret

_start:
    mov eax, 3 
    mov ebx, 0
    mov ecx, num
    mov edx, len
    int 80h

    dec eax ;чтобы не учитывать в длине конец строки
    call Check
    xor edx,edx

    mov ecx, eax ;сохраняем длину строки для счетчика есх
    call Get_digit

    cmp eax, 0 ;0/n = 0
    je Null

    mov ebx, 2 ;наименьший возможный множитель
    call Factorize

    mov eax, 4
    mov ebx, 1
    mov ecx, one
    mov edx, 1
    int 80h

    mov eax, 1
    mov ebx, 0
    int 80h