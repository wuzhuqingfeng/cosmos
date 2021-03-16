#include <iostream>
using namespace std;

class Foo
{
public:
	static int get(void)
	{
		std::cout << "Foo get" << endl;
		return 0;
	}
};

class Bar
{
public:
	static const char* get(void)
	{
		std::cout << "Bar get" << endl;
		return "0";
	}
};

template <class A>
void func(void)
{
	auto val = A::get();

	//...
}

int main(void)
{
	func<Foo>();
	func<Bar>();

	system("pause");
	return 0;
}