#include <iostream>
#include <vector>
#include <map>

// 使用 std::initializer_list<int> 来初始化任意长度的初始化列表
//stl中的容器是通过使用 std::initializer_list 完成的
class Foo
{
public:
	Foo(std::initializer_list <int>){}
};

class FooVector
{
	std::vector<int> content_;

public:
	FooVector(std::initializer_list<int> list)//initializer_list 负责接收初始化列表
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			content_.push_back(*it);
		}
	}
};


//map 是以 pair形式插入的。map中的元素的类型value_type 
//typedef pair<const Key, Type> value_type;


class FooMap
{
	std::map<int, int> content_;
	using pair_t = std::map<int, int>::value_type;//重新命名类型   typedef

public:
	FooMap(std::initializer_list<pair_t> list)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			content_.insert(*it);
		}
	}
};

//使用 std::initializer_list 给自定义类型做初始化
void test01()
{
	Foo foo = { 1,2,3,4,5 };
	FooVector foo1 = { 1, 2, 3, 4, 5 };
	FooMap foo2 = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
}

//使用 std::initializer_list 传递同类型的数据
void func(std::initializer_list<int> list)
{
	std::cout << "size = "<<list.size() << std::endl;
	//对 std::initializer_list 访问只能通过begin() end() 循环遍历
	//迭代器是只读的，无法修改某一个元素，但可以整体赋值
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

void test02()
{
	func({});//1个空集合
	func({ 1,2,3 });//传递 { 1,2,3 }
}

/*
		std::initializer_list 的内部并不负责保存初始化列表中元素的拷贝,仅仅
		存储了列表中元素的引用而已，因此需要再持有对象的生存周期之前传递完毕
*/

//错误的使用方法
std::initializer_list<int> func2(void)
{
	int a = 1, b = 2;
	return { a,b };//ab 返回时并没有拷贝
}

//正确的使用
std::vector<int> func3(void)
{
	int a = 1, b = 2;
	return { a,b };//ab 返回时并没有拷贝
}

void test03()
{
	std::initializer_list<int> myList;
	size_t n = myList.size();
	myList = { 1,2,3,4,5,6 };
	n = myList.size();
	myList = { 11,22};
	n = myList.size();

	std::vector<int> a;
	a = func2();//值时乱码值
	a = func3();

}

int main(void)
{
	test01();
	test02();
	test03();
	system("pause");
	return 0;
}