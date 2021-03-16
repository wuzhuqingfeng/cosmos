#include <iostream>
#include <vector>
#include <map>
using namespace std;

template <class ContainerT>
class Foo
{
	//typename ContainerT::iterator it_;  //类型定义可能有问题
	//typename ContainerT::const_iterator it_;

	//若想在 const ContainerT 下通过编译请使用下面it_定义：
	decltype(std::declval<ContainerT>().begin()) it_;
public:
	void func(ContainerT& container)
	{
		it_ = container.begin();
	}

	//...
};

int main(void)
{
	typedef const std::vector<int> container_t;  //这里有const属性，编译会报一大堆错误信息

	typedef std::map< std::string, int> map_int_t;
	container_t arr;

	Foo<container_t> foo;
	foo.func(arr);

	system("pause");
	return 0;
}

//模板的别名

//第1种写法
typedef std::map< std::string, int> map_int_t0;
typedef std::map< std::string, std::string> map_str_t0;


//第2种写法 c++98/03
template<typename T>
struct str_map {
	typedef std::map< std::string, T> type;
};

str_map<int>::type map_int_t1;
str_map<std::string>::type map_str_t1;

//第3种写法 c++11
template<typename T>
using str_map_t = std::map<std::string, T>;

str_map_t<int> map_int_t2;
str_map_t<std::string> map_str_t2;

/*
	using 的别名用法覆盖了typedef的全部功能

*/

typedef unsigned int uint_t0;	//普通类型重定义
using uint_t1 = unsigned int;   //using 别名重定义

//typedef std::map < std::string, int > map_int_t;//普通类型重定义
using map_int_t1 = std::map < std::string, int >;

//typedef void(*fun_t)(int, int);//重新定义一个函数指针 ,增加了代码的阅读难度
using fun_t2 = void(*)(int, int);//using 语法通过赋值来定义别名 是typedef的等价物

//定义模板别名
//c++98/03
template<typename T>
struct fun_t
{
	typedef void (*typeFunc)(T, T);
};
//使用 func_t 模板
fun_t<int>::typeFunc xx_1;

//c++11 
template<typename T>
using func_t2 = void(*)(T, T); //func_t2 是模板别名 ，不是函数模板（函数模板实例化后是一个函数）
//使用 func_t2 模板
func_t2<int> xx_2;//xx_2 并不是一个由类模板实例化后的类，而是 void(*)(int, int)的 别名


template<typename T>
using type_t = T;
type_t<int> i;//  type_t<int> 等价于 int 

