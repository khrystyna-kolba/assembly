#include <iostream>
#include <cmath>
using namespace std;
const int n = 5;
// ������� ������� ����� �
const float four = 4;
float c;
float d;
float a[n];// �������� �����
float y[n];// �������� ������
void calculateASM() {
	__asm {
		// ���������� �������
		lea esi, a// ������ ������� ������ a
		lea edi, y// ������ ������� ������ y
		mov ecx, n// ����� ������
		finit// ����������� ������������

	iteration :// ������� �����
		fld c
		fmul four//4c s0
		fldln2 //log2(e)
		fld d  // log2(e) d
		fdiv four// log2(e) d/4
		fyl2x //ln(d/4)
        fsub //s0 = 4c-lnd4
	
		fld [esi]// �������� a � ���� ������������
		fld[esi]// �������� a � ���� ������������
		fmul// ai^2
		fld1
		fsub
		fdiv

		fstp[edi]// ����� �������� ������ � �����
		// ������� �� ��������� �������� ������
		add esi, 4
		add edi, 4
			loop iteration// ����� �����
	}
}

void enteringData() {
	cout << " enter c (c>d): ";
	cin >> c;
	cout << " enter d (c>d): ";
	cin >> d;
	cout << " enter a[i] :" << endl;
	for (int i = 0; i < n; ++i) {
		cout << " a[" << i << "] = ";
		cin >> a[i];
	}
}

void printRes(const char* sym) {
	cout << " calculated in " << sym << endl;
	for (int i = 0; i < n; ++i) {
		cout << " result: [" << i + 1 << "] = " << y[i] << endl;
	}
}

void calculateCpp() {
	for (int i = 0; i < n; i++) {
		y[i] = (4*c-log(d/4))/(a[i]*a[i]-1);
	}
}

int main() {
	enteringData();
	calculateASM();
	printRes("ASM");
	calculateCpp();
	printRes("C++");
}