#include <iostream>
using namespace std;
int a, x;
int values[11]; // масив для збереження у(х)
int main() {
	a = -3;
	__asm {
		mov eax, offset values
		push eax // заштовхуємо у стек адресу початку масиву
		mov cx, 11 // кількість проходів циклу 
	start: // початок циклу
		mov eax, 6 // для обчислення x = 6 - сх 
		sub ax, cx // отримуємо поточне значення х
		cwde // розширюємо ax до eax

		mov ebx, eax // записуємо x в ebx

		mov edx, ebx // записуємо x в edx

	getabs://кусочок для знаходження |x|
		neg edx 
		js getabs

        cmp edx, 3 // порівнюємо |х| з 3
		jl lless // якщо |х| менше 3, переходимо до мітки lless
					  // якщо |х| >= 3:
        mov eax, a //переміщуємо а в еах
		add eax, ebx //в еах= а+х
		jmp secpart
	lless :
		mov eax, ebx //переміщуємо х в еах
		neg eax // -x
		add eax, 4 // -x+4
		jmp secpart

	secpart:
		add eax, 2 //+2
		test edx, 1 //тестуємо з одиничкою для перевірки на парність(останній символ в двійковому поданні)
		jz result //if x is even jump, if not continue
		mov ebx, a // стала а
		add eax, ebx //+a
		jmp result

	result :
		pop ebx // виштовхуємо зі стеку адресу масиву
		mov[ebx], eax // записуємо результат за поточною адресою
		add ebx, 4 // зсуваємо вказівник масиву
		push ebx // заштовхуємо в стек нову адресу
		loop start // кінець циклу
		pop ebx //коректно очищаємо стек      
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