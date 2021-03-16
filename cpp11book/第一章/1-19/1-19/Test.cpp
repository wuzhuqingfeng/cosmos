#include <iostream>
#include <functional>

//std::function ��Ϊ��������
void call_when_even(int x, const std::function<void(int)>& f)
{
	if (!(x & 1))  //x % 2 == 0
	{
		f(x);
	}
}

void output(int x)
{
	std::cout << x << " ";
}


/*
	std::function ��Ϊ�ص�����
*/
class A
{
	std::function<void()> m_callBack_;
public:
	A(const std::function<void()> &f) :m_callBack_(f)
	{
	}

	void notify()
	{
		m_callBack_();//�ص����ϲ�
	}
};

class Foo
{
public:
	void operator()(void)
	{
		std::cout << __FUNCTION__ << std::endl;
	}
};

void test()
{
	Foo foo;
	A aa(foo);
	aa.notify();
}

int main(void)
{
	test();

	for (int i = 0; i < 10; ++i)
	{
		call_when_even(i, output);
	}

	std::cout << std::endl;

	system("pause");
	return 0;
}