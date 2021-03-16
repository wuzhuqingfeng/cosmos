#include <iostream>
#include <functional>

void func(void)
{
	std::cout << __FUNCTION__ << std::endl;
}

class Foo
{
public:
	static int foo_func(int a)
	{
		std::cout << __FUNCTION__ << "(" << a << ") ->: ";
		return a;
	}
};

class Bar
{
public:
	int operator()(int a)//�º���
	{
		std::cout << __FUNCTION__ << "(" << a << ") ->: ";
		return a;
	}
};

/*
	std::function �ɵ��ö����װ��,��һ����ģ�壬�������ɳ������Ա(����)ָ��֮�������
	�ɵ��ö���ͨ��ָ������ģ��������Ϳ�����ͳһ�Ĵ���ʽ���������������󡢺���ָ�룬
	����������ӳ�ʹ������
*/
int main(void)
{
	std::function<void(void)> fr1 = func;//��һ����ͨ����
	fr1();

	//��һ����ľ�̬��Ա����
	std::function<int(int)> fr2 = Foo::foo_func;
	std::cout << fr2(123) << std::endl;

	Bar bar;
	fr2 = bar;//��һ���º���
	std::cout << fr2(123) << std::endl;

	system("pause");
	return 0;
}