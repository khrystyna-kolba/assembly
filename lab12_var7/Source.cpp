#include <iostream>
#include <cmath>
using namespace std;
const int n = 5;
// кількість значень змінної а
const float four = 4;
float c;
float d;
float a[n];// значення змінної
float y[n];// значення виразу
void calculateASM() {
	__asm {
		// заповнення регістрів
		lea esi, a// адреса початку масиву a
		lea edi, y// адреса початку масиву y
		mov ecx, n// розмір масиву
		finit// ініціалізація співпроцесора

	iteration :// початок циклу
		fld c
		fmul four//4c s0
		fldln2 //log2(e)
		fld d  // log2(e) d
		fdiv four// log2(e) d/4
		fyl2x //ln(d/4)
        fsub //s0 = 4c-lnd4
	
		fld [esi]// значення a в стек співпроцесора
		fld[esi]// значення a в стек співпроцесора
		fmul// ai^2
		fld1
		fsub
		fdiv

		fstp[edi]// запис значення виразу в масив
		// перехід до наступних елементів масивів
		add esi, 4
		add edi, 4
			loop iteration// кінець циклу
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