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
	int operator()(int a)//仿函数
	{
		std::cout << __FUNCTION__ << "(" << a << ") ->: ";
		return a;
	}
};

/*
	std::function 可调用对象包装器,是一个类模板，可以容纳除了类成员(函数)指针之外的所有
	可调用对象。通过指定它的模板参数，就可以用统一的处理方式处理函数、函数对象、函数指针，
	并允许保存和延迟使用它们
*/
int main(void)
{
	std::function<void(void)> fr1 = func;//绑定一个普通函数
	fr1();

	//绑定一个类的静态成员函数
	std::function<int(int)> fr2 = Foo::foo_func;
	std::cout << fr2(123) << std::endl;

	Bar bar;
	fr2 = bar;//绑定一个仿函数
	std::cout << fr2(123) << std::endl;

	system("pause");
	return 0;
}