#include <iostream>
//c++11 ��� �б��ʼ�� ��ͳһ��ʼ���κ����Ͷ���

class Foo
{
public:
	Foo(int){}

private:
	Foo(const Foo&);
};

//�б��ʼ�� ʹ���ٺ����ķ���ֵ��
struct sTest
{
	sTest(int a, double b) 
	{
		std::cout << "a = "<< a <<"b = "<< b << std::endl;
	};
};

sTest function(void)
{
	return { 123, 11.12 };
}

int main(void)
{
	Foo a1(123);
	//Foo a2 = a1;  //error C2248: ��Foo::Foo��: �޷����� private ��Ա(�ڡ�Foo����������)
	
	Foo a3 = { 123 };
	Foo a4{ 123 };		//c++11 �����ʼ���б� c98���߱�

	int a5 = { 3 };
	int a6 { 3 };		//c++11  �����ʼ���б� c98���߱�

	int* a = new int{ 10 };
	double b = double{ 12.12 };//��������ʹ�ó�ʼ���б��,�ٽ��п�����ʼ��

	int* arr = new int[3]{ 1, 2, 3 };

	sTest sObj = function();


	system("pause");
	return 0;
}