#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include<string>

class CountEven
{
	int& count_;

public:
	CountEven(int& count) : count_(count){}

	void operator()(int val)
	{
		if (!(val & 1))  //val % 2 == 0
		{
			++count_;
			std::cout <<" "<<count_ << std::endl;
		}
	}
};

void test01()
{
	std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
	int even_count = 0;

	std::for_each(v.begin(), v.end(), CountEven(even_count));//仿函数
	std::cout << "The number of even is " << even_count << std::endl;

	//使用lambda 使用真正的闭包概念
	std::for_each(v.begin(), v.end(), [&even_count](int val) {
		if (!(val & 1))  //val % 2 == 0
		{
			++even_count;
			std::cout << " " << even_count << std::endl;
		}
		});
	std::cout << "The number of even is " << even_count << std::endl;

	int count = std::count_if(v.begin(), v.end(), [](int x) {return x > 4 && x < 6; });
	std::cout << count << std::endl;

}

//tuple 元组 是一个固定大小的不同类型值得集合
void test02()
{
	
	int x = 1;
	int y = 2;
	std::string s = "aa";
	auto tp2 = std::tie(x, s, y);
	//tp的类型为 std::tuple<int&, string &, int&>

	std::tuple<const char*, int> tp = std::make_tuple("hello", 33);
	
	//法1 获取元组的值
	const char* data = std::get<0>(tp);
	int len = std::get<1>(tp);

	//法2 使用tie 解包 tuple
	const char* data2;
	int len2;
	std::tie(data2, len2) = tp;
	std::cout << "data2 = "<<data2 << " " << "len2 = " << len2 << std::endl;

	//只想解析某个位置的值 std::ignore 占位符表示不解某个位置的值
	int len3;
	std::tie(std::ignore, len3) = tp;//只想解第2个值
	std::cout << "len3 = " << len3 << std::endl;

	std::tuple<int, double, std::string> t(64, 128.0, "Caroline");
	std::tuple<std::string, std::string, int> t2 = std::make_tuple("Caroline", "Wendy", 1992);

	//返回元素个数  
	size_t num = std::tuple_size<decltype(t)>::value;
	std::cout << "num = " << num << std::endl;

	//获取第1个值的元素类型  
	std::tuple_element<1, decltype(t)>::type cnt = std::get<1>(t);
	std::cout << "cnt = " << cnt << std::endl;

	//比较  
	std::tuple<int, int> ti(24, 48);
	std::tuple<double, double> td(28.0, 56.0);
	bool b = (ti < td);
	std::cout << "b = " << b << std::endl;


}

int main(void)
{
	

	test01();
	test02();
	system("pause");
	return 0;
}