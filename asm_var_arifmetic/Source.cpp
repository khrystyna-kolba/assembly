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
		mov eax, a //�������� � ������ eax a
		add eax, b //������ �� ��������� ��� b (� ��� �+b)
		add eax, c //������ �� ��������� ��� b (� ��� �+b+c)
		mov ebx, 3 //�������� � ������ ebx 3

		cdq //���������� ������ ���

		div ebx //����� ������� ��� �� ������� ebx( (a+b+c)/3)
        //���� ������� � ���, ������ � edx

		mov res, eax //�������� � ����� res ���� ������� �� ����� � ���
	}
	cout << res << endl; //�������� ���������
	return 0;
}


