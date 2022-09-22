#include <iostream>
using namespace std;
int main(){
	// ���������� �����ֲ
	int n;
	cout << "enter n";
	cin >> n;
	int** a = new int*[n];// ������� �
	int** b = new int*[n];// ������� �
	int** res = new int*[n];// ����������� �������
	cout << "eneter elements of a";
	for (int i = 0; i < n; i++){
		a[i] = new int[n];
		b[i] = new int[n];
		res[i] = new int[n];
		for (int j = 0; j < n; j++){
			cin >> a[i][j];
			b[i][j] = i + j - 1;
			res[i][j] = 0;
		}
	}
	// ²���˲��ֲ� ����������� �������
	cout << "A: "<< endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << " B: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << b[i][j] <<" ";
		}
		cout << endl;
	}
	cout << endl;
	// ���������� ������� (�������� �������� �������)
	// ��� �������� ����� �������� �� �++ 
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			__asm{
				mov edx, res// edx = res
				mov esi, i
				imul esi, 4
				add edx, esi// edx = &res[i]
				push [edx]
				pop edx// edx = res[i]
				mov esi, j
				imul esi, 4
				add edx, esi// edx = &res[i][j]
				push edx
				xor esi, esi
				mov ecx, n
			start:
				mov eax, a
				mov ebx, b
			a_to_eax:
				mov edx, i
				mov eax, [eax + 4 * edx]// eax = a[i]
				mov edx, esi
				mov eax, [eax + 4 * edx]// eax = a[i][esi]
			b_to_ebx:
				mov edx, esi
				mov ebx, [ebx + 4 * edx]// ebx = b[esi]
				mov edx, j
                mov ebx, [ebx + 4 * edx]// ebx = b[esi][j]
			end:
				pop edx
				imul eax, ebx// eax = a[i][esi]*b[esi][j]
				add [edx], eax
				push edx
				inc esi
				loop start
				pop edx
			}
		}
	}
	// ��������� ����������
	cout << " A*B: " << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << res[i][j] << " ";
		}
		cout << endl;
	}


	for (int i = 0; i < n; i++) {
		delete[]a[i];
		delete[]b[i];
		delete[]res[i];
	}
	delete[]a;
	delete[]b;
	delete[]res;

}