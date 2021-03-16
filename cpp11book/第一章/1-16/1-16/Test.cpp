#include <iostream>

/*
	可调用对象：

	是一个函数指针
	是一个具有operator() 成员函数的类对象 即仿函数
	是一个可被转换为函数指针的类对象
	是一个类成员(函数)指针
*/
void func(void)
{
	//...
}
//函数对象：定义了调用操作符（）的类对象。当用该对象调用此操作符时，其表现形式如同普通函数调用一般，因此取名叫函数对象

//C++函数对象实质上是操作符重载，实现了对()操作符的重载。C++函数对象不是函数指针。但是，在程序代码中，
//它的调用方式与函数指针一样，后面加个括号就可以了。
struct Foo
{
	void operator()(void)//仿函数
	{
		//...
		std::cout << "operator()" << std::endl;
	}
};

struct Bar
{
	using fr_t = void(*)(void); //使用 using 定义函数指针 注意函数的类型

	static void func(void)
	{
		//...
		std::cout << "func()" << std::endl;
	}
	
	operator fr_t(void) // 可被转换为函数指针的类对象 重载了 fr_t 函数指针类型 void(*)(void)
	{
		std::cout << "fr_t()" << std::endl;
		return func;
	}
};

struct A
{
	int a_;

	void mem_func(void)
	{
		//...
	}
};
//仿函数(functor)，就是使一个类的使用看上去像一个函数。
//其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了
int main(void)
{
	void(*func_ptr)(void) = &func;  //函数指针
	func_ptr();

	Foo foo;  //仿函数 
	foo();

	Bar bar;  //可被转换为函数指针的类对象 重载了()
	bar();

	void(A::*mem_func_ptr)(void) = &A::mem_func;  //类成员函数指针   函数指针变量 mem_func_ptr
	int A::*mem_obj_ptr = &A::a_;  //类成员指针   ::* 是【指向数据成员的指针类型】

	A aa;
	(aa.*mem_func_ptr)();
	aa.*mem_obj_ptr = 123;

	system("pause");
	return 0;
}