#include <iostream>
using namespace std;
int a, x;
int values[11]; // ����� ��� ���������� �(�)
int main() {
	a = -3;
	__asm {
		mov eax, offset values
		push eax // ���������� � ���� ������ ������� ������
		mov cx, 11 // ������� ������� ����� 
	start: // ������� �����
		mov eax, 6 // ��� ���������� x = 6 - �� 
		sub ax, cx // �������� ������� �������� �
		cwde // ���������� ax �� eax

		mov ebx, eax // �������� x � ebx

		mov edx, ebx // �������� x � edx

	getabs://������� ��� ����������� |x|
		neg edx 
		js getabs

        cmp edx, 3 // ��������� |�| � 3
		jl lless // ���� |�| ����� 3, ���������� �� ���� lless
					  // ���� |�| >= 3:
        mov eax, a //��������� � � ���
		add eax, ebx //� ���= �+�
		jmp secpart
	lless :
		mov eax, ebx //��������� � � ���
		neg eax // -x
		add eax, 4 // -x+4
		jmp secpart

	secpart:
		add eax, 2 //+2
		test edx, 1 //������� � ��������� ��� �������� �� �������(������� ������ � ��������� ������)
		jz result //if x is even jump, if not continue
		mov ebx, a // ����� �
		add eax, ebx //+a
		jmp result

	result :
		pop ebx // ���������� � ����� ������ ������
		mov[ebx], eax // �������� ��������� �� �������� �������
		add ebx, 4 // ������� �������� ������
		push ebx // ���������� � ���� ���� ������
		loop start // ����� �����
		pop ebx //�������� ������� ����      
	}
	int diap = -5;
	cout << "a= " << a << endl;
	cout << "x\tc++      " << "asm " << endl;
	for (int i = 0; i < 11; i++) {
		int res;
		if (abs(diap) >= 3) {
			res = diap + a;
		}
		else {
			res = 4 - diap;
		}

		if (diap % 2 == 0) {
			res += 2;
		}
		else {
			res += a + 2;
		}
		cout <<diap << "\t" << res <<"\t"<<values[i] << endl;
		diap++;
	}

}