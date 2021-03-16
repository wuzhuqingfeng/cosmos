#include <iostream>
#include <functional>
/*
	std::bind
	将调用对象和其参数一起进行绑定,绑定后的结果可以使用std::function 进行保存，并延迟调用到任何需要的时候
	（1）将调用对象和其参数 一起绑定一个仿函数
	（2）将多元可调用对象转成一元或者（n-1）元可调用对象，即绑定部分参数
*/
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

void output_add_2(int x)
{
	std::cout << x + 2 << " ";
}

int main(void)
{
	{
		//std::bind 返回的类型是stl内部定义的仿函数类型，可以直接赋值给std::function
		//std::placeholders::_1 占位符，代表这个位置将在函数调用时，被传入的第一个参数所替代
		auto fr = std::bind(output, std::placeholders::_1);
		for (int i = 0; i < 10; ++i)
		{
			call_when_even(i, fr);
		}
		std::cout << std::endl;
	}

	{
		auto fr = std::bind(output_add_2, std::placeholders::_1);

		for (int i = 0; i < 10; ++i)
		{
			call_when_even(i, fr);
		}

		std::cout << std::endl;
	}

	system("pause");
	return 0;
}