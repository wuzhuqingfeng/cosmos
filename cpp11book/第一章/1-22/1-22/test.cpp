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

	//类成员函数的参数(this, para1, para2,...) 隐藏了  this指针
	//将A的成员函数 output指针 和 a绑定，并转换为 一个仿函数 存储到 fr中
	std::function<void(int, int)> fr = std::bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
	//调用的时候在传入参数
	fr(1, 2); //参数输出 1 2

	auto fr2 = std::bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
	fr2(22, 33);  //输出 1 2

	//将A的成员变量 i_ 和 a绑定，并转换为 一个仿函数 存储到 fr中
	std::function<int&(void)> fr_i = std::bind(&A::i_, &a);
	auto fr_2 = std::bind(&A::i_, &a);
	fr_i() = 123;
	std::cout << a.i_ << std::endl;  //输出 123
	system("pause");
	return 0;
}