#include <iostream>
#include <functional>

/*
	lambda是一个匿名函数
	[捕获列表](参数列表) mutable(可选) 异常属性 -> 返回类型 {
		// 函数体
	}

	[ caputrue ] ( params ) opt -> ret { body; };


	[] 不捕获任何变量
	[=] 捕获外部作用域所有变量,按值捕获 默认添加this
	[&] 捕获外部作用域所有变量,按引用捕获 默认添加this
	[=, &foo] 按值捕获外部作用域的所有变量, 并按引用捕获foo
	[bar] 按值捕获bar,同时不捕获其他变量
	[this] 捕获当前类中的this 指针,让lambda 表达式拥有和当前类成员函数同样的访问权限
*/
class A
{
	int i_ = 0;

	void func(int x, int y)
	{
		//auto x1 = []{return i_; };			//error,没有捕获外部变量 [] 不捕获任何变量
		
		auto x2 = [=]{return i_ + x + y; };		//[=] 捕获外部作用域所有变量,按值捕获 默认添加this
		auto x3 = [&]{return i_ + x + y; };		//[&] 捕获外部作用域所有变量,按引用捕获 默认添加this
		auto x4 = [this]{return i_; };          //[this]捕获当前类中的this指针
		
		//auto x5 = [this]{return i_ + x + y; };  //error,没有捕获x和y
		auto x6 = [this, x, y]{return i_ + x + y; };//里面有成员变量

		auto x7 = [this]{return i_++; };
	}
};

/*
	lambda
*/
int main(void)
{
	{
		int a = 0;
		int b = 1;
		//auto f1 = []{return a; };  //error,没有捕获外部变量 
		auto f2 = [&]{return a++; };

		//在捕获的一瞬间,a的值已经诶复制到lambda 中了
		auto f3 = [=]{return a; };
		std::cout << "a = " << a<< std::endl;//a = 0
		a += 10;
		std::cout << "a = " << f3() << std::endl;//a = 0
		
		//按值捕获无法修改捕获的外部变量
		//修改按值捕获的外部变量 使用 mutable
		//auto f4 = [=]{return a++; };  //error,a是以复制方式捕获的，无法修改
		auto f4 = [=]()mutable {return a++; };//
		std::cout << "a = " << f4() << std::endl;// a = 0

		//auto f5 = [a]{return a + b; };  //error,没有捕获变量b
		auto f6 = [a, &b]{return a + (b++); };//a 按值捕获, b按引用捕获
		auto f7 = [=, &b]{return a + (b++); };//= 其他按值捕获  b按引用捕获
	}

	{
		/*
		    可以认为lambda 是一个带有operator()的类，即仿函数
			lambda 表达式中的 operator()默认是const的,一个const成员函数无法修改成员函数的值.
			返回值自动推导
			mutable的作用就是取消 operator()中的const
		*/

		//std::function 存储 lambda
		int a = 100;
		std::function<int(int)> f1 = [](int a) {return a; };//因为 返回值是int ,自动推导
		std::cout << f1(10) << std::endl;//10
		
		//std::function 操作 lambda
		std::function<int()> f2 = std::bind([](int a) {return a; }, 123);
		std::cout << f2() << std::endl;//123
	}
	
	{
		//没有捕获变量的 lambda 可以直接转换为函数指针
		//捕获变量的 lambda 不能转换为函数指针
		typedef void (*pFun)(int*);
		pFun p = [](int*p) {delete p; };
		//pFun p1 = [&](int* p) {delete p; };
	}

	system("pause");
	return 0;
}