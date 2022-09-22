#include <iostream>
using namespace std;
__int16 my_arr[5] = { 42017, 18434, 0, 0, 37 };
int count_pos = 3;
int result = 0;
//correct work with array
//mov ebx, offset my_arr
//add ebx, type my_arr
//mov ax, [ebx]
//cwde
//mov result, eax
int main() {
	//1010 0100 0010 0001 42017
	//0100 1000 0000 0010 18434
	//0000 0000 0000 0000 0
	//0000 0000 0000 0000 0
	//0000 0000 0010 0101 37
	// answer: 3, 6, 18, 21,75, 78 - 6
	__asm {

		mov cx, 5 //������� ���� ����������� �����(�� ��������� ������)
		//�������� ������ 32 ���� �����
		mov ebx, offset my_arr //�������� ������ ������� ������ � ������
	array_loop:
		mov eax, count_pos //�������� ����� ������� � ������ ���
		mov edi, 16 //�������� 16 � ������
		xor edx, edx //������� ������
		div edi // ������ ������������ ������ ������� ������� �� 16

		mov edi, edx //�������� ������ �� ������
		xor eax, eax //������� ��� 
		mov ax, [ebx]//����� � �� ��� �������� 
			//������� �[i] - 32����� �����

	zsuv_loop:
        cmp edi, 3 //���� ������ ������ 1 ��� 2, �� ��������� �� �� 3
			//� �� �� ������
	    jl less_three
		jmp three
	less_three:
		cmp edi, 2 
		jne is_one
		shl ax, 2 //���� �� 2
		jnc not_inc_res
		inc result
		jmp not_three
	is_one:
		shl ax, 1 //���� �� 1
		jnc not_inc_res
		inc result
		jmp not_three
	three: //���� �� 3, ���� ������ ����� ��� ������� 3
        shl ax, 3
		jnc not_inc_res
        inc result
	not_three:
    not_inc_res:
        add edi, 3
		cmp edi, 16
    jl zsuv_loop 
			//���� ������� ����� �� 16, ���������� �� ���������� ����� �� �����

        mov count_pos, edi
		add ebx, type my_arr //��������� �� �����

    loop array_loop

	}
	cout << result << endl; //�������� ��������� �� �������
	return 0;
}

//mov ebx, offset my_arr
//mov ax, [ebx]
////cwde
//shl ax, 3
//mov dx, 1 //mask?
//and ax, dx
//jz not_inc_res
//inc result
//not_inc_res :


/*
mov ax, 42017
shl ax, 3
//shl ax, 1
mov dx, 1 //mask?
//and ax, dx
jnc not_inc_res
inc result
not_inc_res :
*/