#include "Range.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
using namespace detail_range;

void TestRange()
{
	cout << "Range(15):";
	for (int i : Range(15))  //[0,15)
	{
		cout << " " << i;
	}

	cout << endl;
	cout << "Range(2,6):";
	for (auto i : Range(2, 6))  //[2,6)
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(10.5, 15.5):";
	for (auto i : Range(10.5, 15.5))  //[10.5,15.5),步长为1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(35,27,-1):";
	for (int i : Range(35, 27, -1))  //(27, 35]，步长为-1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(2,8,0.5):";
	for (auto i : Range(2, 8, 0.5))  //[2,8),步长为0.5
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(8,7,-0.1):";
	for (auto i : Range(8, 7, -0.1))  //(7,8]，步长为-0.1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range('a', 'z'):";
	for (auto i : Range('a', 'z'))  //['a','z'),步长为1
	{
		cout << " " << i;
	}
	cout << endl;
}


void do_cout(int n)
{
	std::cout << n << " " << std::endl;
}
void do_cout2(std::string n)
{
	std::cout << n << " " << std::endl;
}

void test()
{
	//c++ 遍历容器的普通写法
	std::vector<int> arr = { 1,2,3,4,5 };
	std::vector < std::string > arrStr = { "hello", "wang", "li" };
	for (auto it = arr.begin(); it != arr.end(); it++)
	{
		std::cout << *it << " " << std::endl;
	}

	//使用 algorithm 中的for_each 算法
	//优点 不再关注迭代器的概念,只关注容器中的元素类型
	std::for_each(arr.begin(), arr.end(), do_cout);
	std::for_each(arrStr.begin(), arrStr.end(), do_cout2);

	//c++11 基于范围的for循环 在循环开始之前确定好了迭代器的范围
	//n 表示 arr中的一个元素，   ： 后面是需要遍历的表达式
	for (auto n : arr)//for循环将自动以表达式返回的容器为范围 进行迭代
	{
		std::cout << n << " " << std::endl;
	}
	//显示使用 变量类型 ，不使用auto 推导
	for (int n : arr)
	{
		std::cout << n << " " << std::endl;
	}

	// 冒号前的局部变量只要求能够支持容器类型的隐式转换
	for (char n : arr)
	{
		std::cout << n << " " << std::endl;
	}
	//若需要在遍历时修改容器中的值，需要使用引用
	for (auto& n : arr)
	{
		std::cout << ++n << " " << std::endl;
	}

	//若只希望遍历,不希望修改
	for (const auto& n : arrStr)
	{
		std::cout << n << " " << std::endl;
	}
}

/*
	基于范围的for循环使用细节


*/

void test2()
{
	std::map < std::string, int > mm;
	mm.insert(make_pair("1", 1));
	mm.insert(make_pair("2", 2));
	mm.insert(make_pair("3", 3));
	// val类型为 std::pair
	// auto自动推导出的类型是容器中的 value_type,不是迭代器
	for (auto& val : mm) //auto& 自动推导为 std::pair &  first是只读的 
	{
		std::cout << val.first << " -> " << val.second << std::endl;
		std::cout << val.first << " -> " << val.second++ << std::endl;
		//std::cout << val.first++< " -> " << val.second << std::endl; 
	}

	//普通for
	for (auto it = mm.begin(); it != mm.end(); it++)
	{
		std::cout << it->first << " -> " << it->second << std::endl;
	}

	//注意容器本身的约束  set中的元素  
	std::set<int> ss = { 1,2,3,4 };
	for (auto& val : ss)// auto& 自动推导为 const int&
	{
		//std::cout < val++ << std::endl;//error std::set内部元素是只读的 
	}

	for (auto& val : mm)
	{
		std::cout << val.first << " -> " << val.second << std::endl;
	}


}
/*
	基于范围的for循环对于容器的访问频率
	基于范围的for循环 冒号后面的表达式只会被执行一次
*/
std::vector<int> arr = { 1,2,3,4,5,6 };
std::vector<int>& get_range(void)
{
	std::cout << "get_range -> " << std::endl;
	return arr;
}
void test3()
{
	//基于范围的for循环 冒号后面的表达式只会被执行一次
	for (auto val : get_range())
	{
		std::cout << val << endl;
	}
	std::cout << "-------------------" << endl;
	//基于范围的for循环 是普通for循环的语法糖，在迭代时修改容器很可能引起迭代器失效

	for (auto val : arr)
	{
		std::cout << val << endl;
		arr.push_back(0);
	}
}
int main(void)
{

	//test();
	//test2();
	//test3();

	TestRange();
	system("pause");
	return 0;
}