#include <iostream>
using namespace std;

class BitSet {
	int BitMap;
public:
	BitSet() { BitMap = 0; }
	BitSet(const char s[]);
	friend ostream& operator<<(ostream& out, BitSet s);
	BitSet operator+(char newElement); //원소 추가	 
	BitSet operator|(BitSet op2); //합집합
	BitSet operator&(BitSet op2); //교집합
	friend bool operator <=(BitSet op1, BitSet op2); //op1이 op2의 부분집합인지 평가
	friend BitSet operator~(BitSet s); // 여집합(전체 집합 = 소문자 전체)
	friend BitSet operator-(BitSet op1, BitSet op2); //차집합	 
};

ostream& operator<<(ostream& out, BitSet s) {
	if (!s.BitMap) {
		out << "{ }";
		return out;
	}
	int temp = s.BitMap;
	out << "{";
	for (int i = 0; i < 26; i++) {
		if (temp & 1)
			out << (char)('a' + i) << ", ";
		temp >>= 1;
	}
	out << "\b\b}";
	return out;
}


// 생성자함수와 나머지 연산자 함수 정의
BitSet::BitSet(const char s[]) {
	BitMap = 0;//이 코드..고작 한줄 안적어서 한시간이 넘게 무엇이 틀렸는지 고민했습니다....하....

	for (int i = 0; s[i] != NULL; i++) {
		BitMap |= (1 << (s[i] - 'a'));
	}
}

BitSet BitSet::operator+(char newElement) { //원소 추가
	int num = (int)(newElement - 'a');
	BitMap |= (1 << num);//솔직히 잘 모르겠습니다
	return *this;
}


BitSet BitSet::operator|(BitSet op2) {//합집합
	BitSet tmp;
	tmp.BitMap = BitMap | op2.BitMap;
	return tmp;
}

BitSet BitSet::operator&(BitSet op2) { //교집합
	BitSet tmp;
	tmp.BitMap = BitMap & op2.BitMap;
	return tmp;
}

bool operator <=(BitSet op1, BitSet op2) { //op1이 op2의 부분집합인지 평가
	if (op2.BitMap < op1.BitMap)
		return false;

	int temp = op1.BitMap, con = op2.BitMap;

	for (int i = 0; i < 26; i++) {//a부터 끝까지 검사
		if (temp & 1) {// op1에 원소가 존재할 때
			if (!(con & 1))//op2에 원소가 존재하지 않는다면
				return false;
		}// 그짓!
		temp >>= 1;
		con >>= 1;
	}
}

BitSet operator~(BitSet s) { // 여집합(전체 집합 = 소문자 전체)
	BitSet tmp;
	tmp.BitMap = ~(s.BitMap);
	return tmp;
}

BitSet operator-(BitSet op1, BitSet op2) {//차집합
	BitSet tmp;
	tmp.BitMap = op1.BitMap & (~op2.BitMap);
	return tmp;
}


//main문 구현
int main() {
	BitSet s1, s2("mathematics"), s3, s4;

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