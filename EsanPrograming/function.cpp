#include <iostream>
using namespace std;

int floor_(double n) {
	if (n >= 0) {
		return (int)n;
	}
	else
		return (int)n - 1;
}

int ceil_(double n) {
	if (n >= 0) {
		return (int)n + 1;
	}
	else
		return (int)n;
}


//main¹® ±¸Çö
int main() {
	cout << floor_(3.14) << endl;
	cout << ceil_(3.14) << endl;

	cout << floor_(-3.14) << endl;
	cout << ceil_(-3.14) << endl;

	return 0;
}
