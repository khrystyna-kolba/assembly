#include <iostream>
using namespace std;
int main() {
	int a, b, c;
	cin >> a >> b >> c;
	if (a < 0 || b < 0 || c < 0) {
		cout << "there is a negative num" << endl;
		return 0;
	}
	int res;
	__asm {
		mov eax, a //записуємо в регістр eax a
		add eax, b //додаємо до вмістимого еах b (в еах а+b)
		add eax, c //додаємо до вмістимого еах b (в еах а+b+c)
		mov ebx, 3 //записуємо в регістр ebx 3

		cdq //розширюємо регістр еах

		div ebx //ділимо вмістиме еах на вмістиме ebx( (a+b+c)/3)
        //ціла частина в еах, остача в edx

		mov res, eax //записуємо в змінну res цілу частину від поділу з еах
	}
	cout << res << endl; //виводимо результат
	return 0;
}


