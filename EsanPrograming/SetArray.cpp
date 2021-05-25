#include <iostream>
using namespace std;

class Set {
	char p[26]; // 실제 원소들이 저장될 배열
	int size; // 원소의 개수
public:
	Set() { size = 0; }
	Set(const char* s);
	friend ostream& operator << (ostream& out, Set s); //Set 객체 출력을 연산자  
	Set operator+(char newElement);//원소 추가 
	Set operator| (Set op2); //합집합 
	Set operator&(Set op2); //교집합 
	friend bool operator <=(Set op1, Set op2); //op1이 op2의 부분집합인지 평가
	friend Set operator~(Set s); // 여집합(전체 집합 = 소문자 전체)
	friend Set operator-(Set op1, Set op2); //차집합
};

ostream& operator << (ostream& out, Set s) { //Set 객체 출력을 연산자 
	if (!s.size) {
		cout << "{ }";
		return out;
	}
	out << "{";
	for (int i = 0; i < s.size; i++)
		out << s.p[i] << ", ";
	out << "\b\b}";
	return out;
}


// 생성자함수와 나머지 연산자 함수 정의
Set::Set(const char* s) {//생성자함수 중복 (이거 너무 어려워요 이렇게 하는거 맞아요? 더 짧은 방법이 있나요?) 
	size = 0;//멤버변수 초기화

	for (int i = 0; s[i] != NULL; i++) {//s문자열이 NULL값일때까지 반복문 실행
		int j = 0;
		for (; j < size; j++) {//넣고자하는 원소가 p배열에 원래 존재하는지 확인하는 반복문
			if (p[j] == s[i])//같은 원소일시 break
				break;
		}
		if (j == size) {//다른 원소일시 j와 size의 값이 같으므로 이러한 조건일때
			p[size] = s[i];//새로운 원소 추가 후
			size++;//size +1
		}
	}
}

Set Set::operator+(char newElement) {//원소 추가 
	for (int i = 0; i < size; i++) {//새로운 원소가 기존의 집합에 존재하는지 확인
		if (p[i] == newElement)//만약 같은 원소가 존재한다면
			return *this;//자기자신을 반환
	}
	//반복문이 끝날때까지 이 함수가 종료되지않았다면 새로운 원소가 기존의 집합에 존재하지 않으므로
	p[size] = newElement;//새로운 원소를 추가한 후
	size++;//size를 +1 한 후 
	return *this;//자기자신을 반환
}

Set Set::operator| (Set op2) {//합집합
	Set tmp;

	for (int i = 0; i < size; i++) {
		tmp = tmp + p[i];
	}
	for (int j = 0; j < op2.size; j++) {
		tmp = tmp + op2.p[j];
	}
	return tmp;
}

Set Set::operator&(Set op2) {//교집합
	Set tmp;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < op2.size; j++) {
			if (p[i] == op2.p[j]) {
				tmp = tmp + p[i];
			}
		}
	}

	return tmp;

	/* 떠돌아다니는 코드인데 왜 이렇게 짠건지 이해는 안갑니다  그냥...읽기싫어서 남이 짠 코드는 잘 안읽히는 걸까요...
	int count = 0;
	while (count < size) tmp.p[count] = p[count++];
	for (int i = 0; i < op2.size; i++) {
		int j = 0;
		for (; j < count; j++) {
			if (tmp.p[j] == op2.p[i]) break;
		}
		if (j == count) tmp.p[count++] = op2.p[i];
	}
	tmp.size = count;
	*/
}


//프렌드 함수 구현
bool operator <=(Set op1, Set op2) { //op1이 op2의 부분집합인지 평가
	if (op2.size < op1.size)
		return false;

	for (int i = 0; i < op1.size; i++) {
		int j = 0;
		for (; j < op2.size; j++) {
			if (op1.p[i] == op2.p[j])
				break;
		}
		if (j == op2.size)
			return false;
	}
	return true;
}

Set operator~(Set s) {// 여집합(전체 집합 = 소문자 전체)
	Set tmp("abcdefghijklnmopqrstuvwxyz"), ref;

	for (int i = 0; i < 26; i++) {
		int j = 0;
		for (; j < s.size; j++) {
			if (tmp.p[i] == s.p[j])
				break;
		}
		if (j == s.size) {
			ref = ref + tmp.p[i];
		}
	}

	return ref;
}

Set operator-(Set op1, Set op2) {//차집합
	Set tmp, ref;
	ref = op1 & op2;

	for (int i = 0; i < op1.size; i++) {
		int j = 0;
		for (; j < ref.size; j++) {
			if (op1.p[i] == ref.p[j])
				break;
		}
		if (j == ref.size) {
			tmp = tmp + op1.p[i];
		}
	}
	return tmp;
}

//main문 구현
int main() {
	Set s1, s2("mathematics"), s3, s4;

	s3 = s3 + 't' + 'e' + 's' + 't' + 'i' + 'n' + 'g'; //원소 삽입
	cout << "s1 = " << s1 << "\ns2 = " << s2 << "\ns3 = " << s3 << "\n\n";

	s1 = s2 & s3;//교집합
	cout << s2 << " ∩ " << s3 << " = " << s1 << "\n\n";

	s1 = s2 | s3;//합집합
	cout << s2 << " ∪ " << s3 << " = " << s1 << "\n\n";

	s4 = s1 - s3;//차집합
	cout << s1 << " - " << s3 << " = " << s4 << "\n\n";

	s4 = ~s1; //여집합
	cout << "~" << s1 << " = " << s4 << "\n\n";

	if (s2 <= s1)//부분집합인지 검사
		cout << s2 << " ⊆ " << s1 << "\n\n";

	if (!(s2 <= s3))
		cout << s2 << " is not susbset of " << s3 << "\n\n";

	return 0;
}