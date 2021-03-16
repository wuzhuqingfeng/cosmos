#include <iostream>
#include <functional>

void output(int x, int y)
{
	std::cout << "x = "<< x << " y = " << y << std::endl;
}

int main(void)
{
	//std::bind 返回的类型是stl内部定义的仿函数类型，可以直接赋值给std::function

	std::bind(output, 1, 2)();

	//std::bind 函数返回的是一个stl内部定义的仿函数
	auto fr2 = std::bind(output, 11, 22);
	fr2();//已经绑定好参数了,在这直接调用即可

	std::bind(output, std::placeholders::_1, 2)(1);
	std::bind(output, 2, std::placeholders::_1)(1);

	//std::bind(output, 2, std::placeholders::_2)(1);  //error:调用时没有第二个参数

	//bind 第一个参数 2已经绑定好了,不会在传入10
	std::bind(output, 2, std::placeholders::_2)(10, 2);  //输出 2 2   调用时第一个参数被吞掉了
	
	std::bind(output, std::placeholders::_1, std::placeholders::_2)(1, 2);  //输出 1 2
	//std::placeholders::_2 指的的是参数2
	std::bind(output, std::placeholders::_2, std::placeholders::_1)(1, 2);  //输出 2 1


	system("pause");
	return 0;
}