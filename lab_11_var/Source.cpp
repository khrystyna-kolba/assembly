#include <iostream>
using namespace std;

void multiplying_square_matrixes(int** res, int** first, int** sec, int siz) {
	// АСЕМБЛЕРНА ВСТАВКА (алгоритм множення матриць)
	// Для зручності цикли записано на С++ 
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
	// Для зручності цикли записано на С++ 
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
	// ФОРМУВАННЯ МАТРИЦІ
	int n,m;
	cout << "enter n"<<"\n";
	cin >> n;
	cout << "enter m"<<"\n";
	cin >> m;
	int** a = new int* [n];// матриця А
	int** a2 = new int* [n];// матриця А^2
	int** res = new int* [n];// результуюча матриця для проміжних результатів
	int** resclear = new int* [n];// результуюча матриця для проміжних результатів
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
	//отже ми ввели матрицю .а. і створили матрицю для .результату. і .матриці піднесеної
	//до квадрату.
	// ВІЗУАЛІЗАЦІЯ А
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
	//множення щоб отримати А^2
	multiplying_square_matrixes(a2, a, a, n);
	cout << "SLID A^2: " << slid(a2, n) << endl;
	cout << endl;
	// ВИВЕДЕННЯ РЕЗУЛЬТАТУ A^2
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
	// Цикл для знаходження матриць до A^m
	for (int k = 3; k < m + 1; k++) {
		int num_to_mult;
		num_to_mult = (k / 2) - 1;
		for (int s = 0; s < num_to_mult; s++) {
			//множення A^2 на res=A^2 задану кількість разів
			//результат зберігаємо в resclear i копіюємо до res
			multiplying_square_matrixes(resclear, res, a2, n);
			// B проміжний res ставимо resclear
			//resclear наповняєм нулями
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					res[i][j] = resclear[i][j];
					resclear[i][j] = 0;
				}
			}
		}
		//якщо непарний степінь
		//домножуємо ще на A
		if (k % 2 != 0) {
			//множення res на А
			multiplying_square_matrixes(resclear, res,a,n);
			// B проміжний res ставимо resclear
			//resclear наповняєм нулями
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
				res[i][j] = a2[i][j]; //знову робимо res=A^2
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