#include <iostream>
using namespace std;

class Set {
	char p[26]; // ���� ���ҵ��� ����� �迭
	int size; // ������ ����
public:
	Set() { size = 0; }
	Set(const char* s);
	friend ostream& operator << (ostream& out, Set s); //Set ��ü ����� ������  
	Set operator+(char newElement);//���� �߰� 
	Set operator| (Set op2); //������ 
	Set operator&(Set op2); //������ 
	friend bool operator <=(Set op1, Set op2); //op1�� op2�� �κ��������� ��
	friend Set operator~(Set s); // ������(��ü ���� = �ҹ��� ��ü)
	friend Set operator-(Set op1, Set op2); //������
};

ostream& operator << (ostream& out, Set s) { //Set ��ü ����� ������ 
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


// �������Լ��� ������ ������ �Լ� ����
Set::Set(const char* s) {//�������Լ� �ߺ� (�̰� �ʹ� ������� �̷��� �ϴ°� �¾ƿ�? �� ª�� ����� �ֳ���?) 
	size = 0;//������� �ʱ�ȭ

	for (int i = 0; s[i] != NULL; i++) {//s���ڿ��� NULL���϶����� �ݺ��� ����
		int j = 0;
		for (; j < size; j++) {//�ְ����ϴ� ���Ұ� p�迭�� ���� �����ϴ��� Ȯ���ϴ� �ݺ���
			if (p[j] == s[i])//���� �����Ͻ� break
				break;
		}
		if (j == size) {//�ٸ� �����Ͻ� j�� size�� ���� �����Ƿ� �̷��� �����϶�
			p[size] = s[i];//���ο� ���� �߰� ��
			size++;//size +1
		}
	}
}

Set Set::operator+(char newElement) {//���� �߰� 
	for (int i = 0; i < size; i++) {//���ο� ���Ұ� ������ ���տ� �����ϴ��� Ȯ��
		if (p[i] == newElement)//���� ���� ���Ұ� �����Ѵٸ�
			return *this;//�ڱ��ڽ��� ��ȯ
	}
	//�ݺ����� ���������� �� �Լ��� ��������ʾҴٸ� ���ο� ���Ұ� ������ ���տ� �������� �����Ƿ�
	p[size] = newElement;//���ο� ���Ҹ� �߰��� ��
	size++;//size�� +1 �� �� 
	return *this;//�ڱ��ڽ��� ��ȯ
}

Set Set::operator| (Set op2) {//������
	Set tmp;

	for (int i = 0; i < size; i++) {
		tmp = tmp + p[i];
	}
	for (int j = 0; j < op2.size; j++) {
		tmp = tmp + op2.p[j];
	}
	return tmp;
}

Set Set::operator&(Set op2) {//������
	Set tmp;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < op2.size; j++) {
			if (p[i] == op2.p[j]) {
				tmp = tmp + p[i];
			}
		}
	}

	return tmp;

	/* �����ƴٴϴ� �ڵ��ε� �� �̷��� §���� ���ش� �Ȱ��ϴ�  �׳�...�б�Ⱦ ���� § �ڵ�� �� �������� �ɱ��...
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


//������ �Լ� ����
bool operator <=(Set op1, Set op2) { //op1�� op2�� �κ��������� ��
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

Set operator~(Set s) {// ������(��ü ���� = �ҹ��� ��ü)
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

Set operator-(Set op1, Set op2) {//������
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

//main�� ����
int main() {
	Set s1, s2("mathematics"), s3, s4;

	s3 = s3 + 't' + 'e' + 's' + 't' + 'i' + 'n' + 'g'; //���� ����
	cout << "s1 = " << s1 << "\ns2 = " << s2 << "\ns3 = " << s3 << "\n\n";

	s1 = s2 & s3;//������
	cout << s2 << " �� " << s3 << " = " << s1 << "\n\n";

	s1 = s2 | s3;//������
	cout << s2 << " �� " << s3 << " = " << s1 << "\n\n";

	s4 = s1 - s3;//������
	cout << s1 << " - " << s3 << " = " << s4 << "\n\n";

	s4 = ~s1; //������
	cout << "~" << s1 << " = " << s4 << "\n\n";

	if (s2 <= s1)//�κ��������� �˻�
		cout << s2 << " �� " << s1 << "\n\n";

	if (!(s2 <= s3))
		cout << s2 << " is not susbset of " << s3 << "\n\n";

	return 0;
}