SECTION .data
msg db 'VigenereCipher',0xa // ������ ������	
lenm equ $ - msg // ��������� ����� ������
key db 'vine' //������ ����
lenk equ $ - key //��������� ����� �����
newLine db 0xa // ������ ������ ������

SECTION .bss
array resb lenm // ������ ������ ����� ������

SECTION .text
global _start
_start:

mov ecx,lenm  // ������ � �������� ����� ������
mov ebx,key   // ������ � �������� ����� ������
mov ebp,lenk  // ������ � �������� ����� ������

mov esi,msg   //������ ������ � �������
mov edi,array //������ ������� � �������

.cycle:       //������ �����
mov dl,[esi]  //���������� ����� ����� ������
cmp dl,'z'    // ���������� � ������ z 
ja .z         //��������	
cmp dl,'a'    //�� 
jb .h  	      //�����
sub dl,'a'    //�������� ��� ����� �	
add dl,[ebx]  //���������� � ����� ������ 
cmp dl,'z'    //���������� � z
ja .b	      //���� ���� �� ������� �� �� ����� b
;call function //����� �������
jmp .z	      // ������� �� ����� z
.b:
sub dl,'z'    // �������� ��� ����� z	
add dl,'a'    // ���������� ��� ����� �
sub dl,1      // �������� 1 
;call function //����� �������
jmp .z		// ������� �� �����  z
.h:
cmp dl,'Z'	//��������	
ja .x		//�� 
cmp dl,'A'	//������� 
jb .l		//�����
add dl,byte 20	// ��������� 20 ����
sub dl,'a'	// �������� ��� a
add dl,[ebx]	//���������� � ����� ������, �� ����. � ������
cmp dl,'z'	//���������� � z
ja .c		//���� ����� �� �������
sub dl,byte 20	//�������� 20 ����
;call function	//����� �������
jmp .z		// ������� �� ����� z
.c:
sub dl,'z'	// �������� ��� ����� z	
add dl,'a'	// ���������� ��� ����� �
sub dl,1	// �������� 1 
;call function	//����� �������

.l:
.x:
.z:
mov [edi],dl	//������ � ������
xor dl,dl	//��������� dl
inc esi		//����������� ������� �� 1 ������
inc edi		//����������� ������� �� 1 �������
call function	//����� �������
loop .cycle	//��������� ����

mov eax,4	//����� �� ����� 
mov ebx,1
mov ecx,array
mov edx,lenm
int 80h
call new	//����� ������� new

mov eax,1
xor ebx,ebx
int 80h

new:
mov eax, 4	//����� ������ 
mov ebx, 1
mov ecx, newLine
mov edx, 1
int 80h
ret
function:
dec ebp		//��������� �� 1 ����� ����� 
jnz .n		//���� �� ����� �� �� ����� n 
mov ebp,lenk	//���������� ����� �����	
mov ebx,key	//���������� ��� ����
ret
.n:
inc ebx	//����������� �� 1 ����
ret