#include <iostream>
using namespace std;

void test()
{
	int x = 0;
	decltype(x) y = 1;	   //y->int  //类似于sizeof 推导表达式类型的大小的操作符
	decltype(x + y) z = 0; //z->int

	const int &i = x;
	decltype(i) j = y;	//j-> const int&

	const decltype(z)* p = &z;	//*p  ->  const int,	p	->	const int*
	decltype(z) *pi = &z;		//*pi ->  int,			pi	->	int*
	decltype(pi)* pp = &pi;     //*pp ->  int *,		pp	->	int**
 

	cout << "hello" << endl;
}

class Foo
{
public:
	static const int Number = 0;
	int x;
};

//规则1：标识符表达式和类访问表达式
//对于标识符表达式，decltype 的推导结果和变量的类型表达一致 
int main(void)
{
	test();
	int n = 0;
	volatile const int &x = n;

	decltype(n) a = n; //a -> int
	decltype(x) b = n; //b -> const volatile int &

	decltype(Foo::Number) c = 0; //c -> const int

	Foo foo;
	decltype(foo.x) d = 0;//d -> int 类访问表达式

	system("pause");
	return 0;
}