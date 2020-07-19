SECTION .data
msg db 'VigenereCipher',0xa // создаю строку	
lenm equ $ - msg // записываю длину строки
key db 'vine' //создаю ключ
lenk equ $ - key // записываю длину ключа
newLine db 0xa // создаю пустую строку

SECTION .bss
array resb lenm // создаю массив длины строки

SECTION .text
global _start
_start:

mov ecx,lenm  // запись в регистры наших данных
mov ebx,key   // запись в регистры наших данных
mov ebp,lenk  // запись в регистры наших данных

mov esi,msg   // запись строки в регистр
mov edi,array // запись массива в регистр

.cycle:       // начало цикла
mov dl,[esi]  // записываем адрес нашей строки
cmp dl,'z'    // сравниваем с буквой z 
ja .z         // проверка	
cmp dl,'a'    // на 
jb .h  	      // букву
sub dl,'a'    // отнимаем код буквы а	
add dl,[ebx]  // складываем с нашим ключом 
cmp dl,'z'    // сравниваем с z
ja .b	      // если ушли за алфавит то на метку b
;call function // вызов функции
jmp .z	      // прыгаем на метку z
.b:
sub dl,'z'    // отнимаем код буквы z	
add dl,'a'    // прибавляем код буквы а
sub dl,1      // отнимаем 1 
;call function // вызов функции
jmp .z		// прыгаем на метку  z
.h:
cmp dl,'Z'	// проверка	
ja .x		// на 
cmp dl,'A'	// большие 
jb .l		// буквы
add dl,byte 20	// добавляем 20 байт
sub dl,'a'	// отнимаем код a
add dl,[ebx]	// складываем с нашим ключом, со знач. в адресе
cmp dl,'z'	// сравниваем с z
ja .c		// если вышли за алфавит
sub dl,byte 20	// отнимаем 20 байт
;call function	// вызов функции
jmp .z		// прыгаем на метку z
.c:
sub dl,'z'	// отнимаем код буквы z	
add dl,'a'	// прибавляем код буквы а
sub dl,1	// отнимаем 1 
;call function	// вызов функции

.l:
.x:
.z:
mov [edi],dl	// запись в массив
xor dl,dl	// обнуление dl
inc esi		// увеличиваем счетчик на 1 строки
inc edi		// увеличиваем счетчик на 1 массива
call function	// вызов функции
loop .cycle	// повторяем цикл

mov eax,4	// вывод на экран 
mov ebx,1
mov ecx,array
mov edx,lenm
int 80h
call new	// вызов функции new

mov eax,1
xor ebx,ebx
int 80h

new:
mov eax, 4	// вывод строки 
mov ebx, 1
mov ecx, newLine
mov edx, 1
int 80h
ret
function:
dec ebp		// уменьшаем на 1 длину ключа 
jnz .n		// если не равно то на метку n 
mov ebp,lenk	// записываем длину ключа	
mov ebx,key	// записываем сам ключ
ret
.n:
inc ebx	// увеличиваем на 1 ключ
ret
