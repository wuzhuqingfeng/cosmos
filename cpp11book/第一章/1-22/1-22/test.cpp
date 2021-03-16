#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

class A
{
public:
	int i_ = 0;

	void output(int x, int y)
	{
		std::cout << x << " " << y << std::endl;
	}
};

int main(void)
{
	A a;

	//���Ա�����Ĳ���(this, para1, para2,...) ������  thisָ��
	//��A�ĳ�Ա���� outputָ�� �� a�󶨣���ת��Ϊ һ���º��� �洢�� fr��
	std::function<void(int, int)> fr = std::bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
	//���õ�ʱ���ڴ������
	fr(1, 2); //������� 1 2

	auto fr2 = std::bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
	fr2(22, 33);  //��� 1 2

	//��A�ĳ�Ա���� i_ �� a�󶨣���ת��Ϊ һ���º��� �洢�� fr��
	std::function<int&(void)> fr_i = std::bind(&A::i_, &a);
	auto fr_2 = std::bind(&A::i_, &a);
	fr_i() = 123;
	std::cout << a.i_ << std::endl;  //��� 123
	system("pause");
	return 0;
}