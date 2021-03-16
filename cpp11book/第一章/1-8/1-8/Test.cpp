#include <iostream>
//c++11 提出 列表初始化 来统一初始化任何类型对象

class Foo
{
public:
	Foo(int){}

private:
	Foo(const Foo&);
};

//列表初始化 使用再函数的返回值上
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
	//Foo a2 = a1;  //error C2248: “Foo::Foo”: 无法访问 private 成员(在“Foo”类中声明)
	
	Foo a3 = { 123 };
	Foo a4{ 123 };		//c++11 对象初始化列表 c98不具备

	int a5 = { 3 };
	int a6 { 3 };		//c++11  对象初始化列表 c98不具备

	int* a = new int{ 10 };
	double b = double{ 12.12 };//匿名对象使用初始化列表后,再进行拷贝初始化

	int* arr = new int[3]{ 1, 2, 3 };

	sTest sObj = function();


	system("pause");
	return 0;
}