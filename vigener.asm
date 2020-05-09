SECTION .data
msg db 'VigenereCipher',0xa
lenm equ $ - msg
key db 'vine'
lenk equ $ - key
newLine db 0xa

SECTION .bss
array resb lenm

SECTION .text
global _start
_start:

mov ecx,lenm
mov ebx,key
mov ebp,lenk

mov esi,msg
mov edi,array

.cycle:
mov dl,[esi]
cmp dl,'z'
ja .z
cmp dl,'a'
jb .h
sub dl,'a'
add dl,[ebx]
cmp dl,'z'
ja .b
;call function
jmp .z
.b:
sub dl,'z'
add dl,'a'
sub dl,1
;call function
jmp .z
.h:
cmp dl,'Z'
ja .x
cmp dl,'A'
jb .l
add dl,byte 20
sub dl,'a'
add dl,[ebx]
cmp dl,'z'
ja .c
sub dl,byte 20
;call function
jmp .z
.c:
sub dl,'z'
add dl,'a'
sub dl,1
;call function

.l:
.x:
.z:
mov [edi],dl
xor dl,dl
inc esi
inc edi
call function
loop .cycle

mov eax,4
mov ebx,1
mov ecx,array
mov edx,lenm
int 80h
call new

mov eax,1
xor ebx,ebx
int 80h

new:
mov eax, 4
mov ebx, 1
mov ecx, newLine
mov edx, 1
int 80h
ret
function:
dec ebp
jnz .n
mov ebp,lenk
mov ebx,key
ret
.n:
inc ebx
ret
