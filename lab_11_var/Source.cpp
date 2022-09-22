#include <iostream>
using namespace std;

void multiplying_square_matrixes(int** res, int** first, int** sec, int siz) {
	// ���������� ������� (�������� �������� �������)
	// ��� �������� ����� �������� �� �++ 
	for (int i = 0; i < siz; i++) {
		for (int j = 0; j < siz; j++) {
			res[i][j] = 0;
		}
	}
	for (int i = 0; i <siz; i++) {
		for (int j = 0; j < siz; j++) {
			__asm {
				mov edx, res// edx = res
				mov esi, i
				imul esi, 4
				add edx, esi// edx = &res[i]
				push[edx]
				pop edx// edx = res[i]
				mov esi, j
				imul esi, 4
				add edx, esi// edx = &res[i][j]
				push edx
				xor esi, esi
				mov ecx, siz
			start:
				mov eax, first
				mov ebx, sec
			a_to_eax:
				mov edx, i
				mov eax, [eax + 4 * edx]// eax = first[i]
				mov edx, esi
				mov eax, [eax + 4 * edx]// eax = first[i][esi]
			b_to_ebx:
				mov edx, esi
				mov ebx, [ebx + 4 * edx]// ebx = sec[esi]
				mov edx, j
				mov ebx, [ebx + 4 * edx]// ebx = sec[esi][j]
			end:
				pop edx
				imul eax, ebx// eax = first[i][esi]*sec[esi][j]
				add[edx], eax
				push edx
				inc esi
				loop start
				pop edx
			}
		}
	}

}

int slid(int** matrix, int n) {
	int res=0;
	// ��� �������� ����� �������� �� �++ 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//res[i][j] = 0;
		}
	}
			__asm {
				mov ecx, n
				xor esi, esi
			start :
				mov eax, matrix

			matrix_to_eax :
				mov edx, esi
				mov eax, [eax + 4 * edx]// eax = matrix[esi]
				mov eax, [eax + 4 * edx]// eax = matrix[esi][esi]
			end:
				add res, eax// res+=eax
				inc esi
				loop start
			}
			return res;
}

int main() {
	// ���������� �����ֲ
	int n,m;
	cout << "enter n"<<"\n";
	cin >> n;
	cout << "enter m"<<"\n";
	cin >> m;
	int** a = new int* [n];// ������� �
	int** a2 = new int* [n];// ������� �^2
	int** res = new int* [n];// ����������� ������� ��� �������� ����������
	int** resclear = new int* [n];// ����������� ������� ��� �������� ����������
	cout << "enter elements of a"<<"\n";
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
		a2[i] = new int[n];
		res[i] = new int[n];
		resclear[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			res[i][j] = 0;
			resclear[i][j] = 0;
			a2[i][j] = 0;
		}
	}
	//���� �� ����� ������� .�. � �������� ������� ��� .����������. � .������� ��������
	//�� ��������.
	// ²���˲��ֲ� �
	cout << "SLID A: " << slid(a, n) << endl;
	cout << endl;
	cout << " A: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	//�������� ��� �������� �^2
	multiplying_square_matrixes(a2, a, a, n);
	cout << "SLID A^2: " << slid(a2, n) << endl;
	cout << endl;
	// ��������� ���������� A^2
	cout << " A^2: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a2[i][j] << " ";
			res[i][j] = a2[i][j];
		}
		cout << endl;
	}
	cout << endl;

	cout << endl;
	// ���� ��� ����������� ������� �� A^m
	for (int k = 3; k < m + 1; k++) {
		int num_to_mult;
		num_to_mult = (k / 2) - 1;
		for (int s = 0; s < num_to_mult; s++) {
			//�������� A^2 �� res=A^2 ������ ������� ����
			//��������� �������� � resclear i ������� �� res
			multiplying_square_matrixes(resclear, res, a2, n);
			// B �������� res ������� resclear
			//resclear ��������� ������
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					res[i][j] = resclear[i][j];
					resclear[i][j] = 0;
				}
			}
		}
		//���� �������� ������
		//��������� �� �� A
		if (k % 2 != 0) {
			//�������� res �� �
			multiplying_square_matrixes(resclear, res,a,n);
			// B �������� res ������� resclear
			//resclear ��������� ������
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					res[i][j] = resclear[i][j];
					resclear[i][j] = 0;
				}
			}
		}
		cout << "SLID " << "A^" << k << ": " << slid(res, n) << endl;
		cout << endl;
		cout << "A^" << k <<": "<< endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << res[i][j] << " ";
				res[i][j] = a2[i][j]; //����� ������ res=A^2
			}
			cout << endl;
		}
		cout << endl;
	}


	for (int i = 0; i < n; i++) {
		delete[]a[i];
		delete[]a2[i];
		delete[]res[i];
		delete[]resclear[i];
	}
	delete[]a;
	delete[]a2;
	delete[]res;
	delete[]resclear;

}