#include <iostream> 
#include <string>
using namespace std;

void combination(string s, int r); //combination 출력
void permutation(string s); //permutation 출력
int com(int n, int r); //combination 계산
int per(int n); //permutation 계산
void swap(int* a, int* b);


int main() {
	int menu, r;
	string str;

	while (true) {
		cout << "메뉴를 입력하세요. (1: 조합, 2: 순열, 3: 종료)" << endl << "메뉴: ";
		cin >> menu;

		if (menu != 1 && menu != 2 && menu != 3) {//1,2,3이 아닐때, 즉 0이 들어오면
			cout << "잘못입력하셨습니다. 다시 입력해주세요." << endl;
			continue;
		}

		switch (menu) {
		case 1:
			cout << endl << "문자열과 조합을 위해 선택할 문자의 개수 r를 입력하세요." << endl << "문자열: ";
			cin >> str;
			cout << "문자의 개수: ";
			cin >> r;

			if (str.size() < r) {
				cout << "문자의 개수를 잘못 입력하셨습니다." << endl;
				break;
			}
			combination(str, r);
			break;
		case 2:
			cout << endl << "문자열을 입력하세요" << endl << "문자열: ";
			cin >> str;
			permutation(str);
			break;
		case 3:
			cout << "종료합니다." << endl;
			break;
		}
		if (menu == 3)
			return 0;
		cout << endl;
	}
}

void combination(string str, int r) {
	int* num = new int[r];

	for (int i = 0; i < r; i++) {
		num[i] = i;
		cout << str[num[i]];
	}
	cout << endl;

	for (int i = 1; i < com(str.size(), r); i++) {
		int m = r - 1, max = str.size() - 1;

		while (num[m] == max) {
			m--; max--;
		}
		num[m] = num[m] + 1;

		for (int j = m + 1; j < r; j++) {
			num[j] = num[j - 1] + 1;
		}

		for (int i = 0; i < r; i++) {//i번째 조합을 출력
			cout << str[num[i]];
		}
		cout << endl;
	}
	delete[] num;
}

void permutation(string str) {
	int n = str.size(), m, k, p, q;
	int* num = new int[n];  

	for (int i = 0; i < n; i++) {
		num[i] = i;
		cout << str[num[i]];
	}
	cout << endl;

	for (int i = 1; i < per(n); i++) {
		m = n - 2;

		while (num[m] > num[m + 1])
			m = m - 1;
		k = n - 1;

		while (num[m] > num[k])
			k = k - 1;

		swap(num[m], num[k]);
		p = m + 1;
		q = n - 1;

		while (p < q) {
			swap(num[p], num[q]);
			p = p + 1;
			q = q - 1;
		}

		for (int i = 0; i < n; i++)
			cout << str[num[i]];
		cout << endl;
	}
	delete[] num;
}

int com(int n, int r) {
	int mol = 1, den = 1;
	for (int i = n; i > r; i--) {
		mol *= i;
	}
	for (int i = r - 1; i > 1; i--) {
		den *= i;
	}
	return mol / den;
}

int per(int n) {
	int val = 1;
	for (int i = 1; i <= n; i++) {
		val *= i;
	}
	return val;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
