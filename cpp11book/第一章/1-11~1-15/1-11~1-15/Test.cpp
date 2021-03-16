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
	for (auto i : Range(10.5, 15.5))  //[10.5,15.5),����Ϊ1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(35,27,-1):";
	for (int i : Range(35, 27, -1))  //(27, 35]������Ϊ-1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(2,8,0.5):";
	for (auto i : Range(2, 8, 0.5))  //[2,8),����Ϊ0.5
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(8,7,-0.1):";
	for (auto i : Range(8, 7, -0.1))  //(7,8]������Ϊ-0.1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range('a', 'z'):";
	for (auto i : Range('a', 'z'))  //['a','z'),����Ϊ1
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
	//c++ ������������ͨд��
	std::vector<int> arr = { 1,2,3,4,5 };
	std::vector < std::string > arrStr = { "hello", "wang", "li" };
	for (auto it = arr.begin(); it != arr.end(); it++)
	{
		std::cout << *it << " " << std::endl;
	}

	//ʹ�� algorithm �е�for_each �㷨
	//�ŵ� ���ٹ�ע�������ĸ���,ֻ��ע�����е�Ԫ������
	std::for_each(arr.begin(), arr.end(), do_cout);
	std::for_each(arrStr.begin(), arrStr.end(), do_cout2);

	//c++11 ���ڷ�Χ��forѭ�� ��ѭ����ʼ֮ǰȷ�����˵������ķ�Χ
	//n ��ʾ arr�е�һ��Ԫ�أ�   �� ��������Ҫ�����ı��ʽ
	for (auto n : arr)//forѭ�����Զ��Ա��ʽ���ص�����Ϊ��Χ ���е���
	{
		std::cout << n << " " << std::endl;
	}
	//��ʾʹ�� �������� ����ʹ��auto �Ƶ�
	for (int n : arr)
	{
		std::cout << n << " " << std::endl;
	}

	// ð��ǰ�ľֲ�����ֻҪ���ܹ�֧���������͵���ʽת��
	for (char n : arr)
	{
		std::cout << n << " " << std::endl;
	}
	//����Ҫ�ڱ���ʱ�޸������е�ֵ����Ҫʹ������
	for (auto& n : arr)
	{
		std::cout << ++n << " " << std::endl;
	}

	//��ֻϣ������,��ϣ���޸�
	for (const auto& n : arrStr)
	{
		std::cout << n << " " << std::endl;
	}
}

/*
	���ڷ�Χ��forѭ��ʹ��ϸ��


*/

void test2()
{
	std::map < std::string, int > mm;
	mm.insert(make_pair("1", 1));
	mm.insert(make_pair("2", 2));
	mm.insert(make_pair("3", 3));
	// val����Ϊ std::pair
	// auto�Զ��Ƶ����������������е� value_type,���ǵ�����
	for (auto& val : mm) //auto& �Զ��Ƶ�Ϊ std::pair &  first��ֻ���� 
	{
		std::cout << val.first << " -> " << val.second << std::endl;
		std::cout << val.first << " -> " << val.second++ << std::endl;
		//std::cout << val.first++< " -> " << val.second << std::endl; 
	}

	//��ͨfor
	for (auto it = mm.begin(); it != mm.end(); it++)
	{
		std::cout << it->first << " -> " << it->second << std::endl;
	}

	//ע�����������Լ��  set�е�Ԫ��  
	std::set<int> ss = { 1,2,3,4 };
	for (auto& val : ss)// auto& �Զ��Ƶ�Ϊ const int&
	{
		//std::cout < val++ << std::endl;//error std::set�ڲ�Ԫ����ֻ���� 
	}

	for (auto& val : mm)
	{
		std::cout << val.first << " -> " << val.second << std::endl;
	}


}
/*
	���ڷ�Χ��forѭ�����������ķ���Ƶ��
	���ڷ�Χ��forѭ�� ð�ź���ı��ʽֻ�ᱻִ��һ��
*/
std::vector<int> arr = { 1,2,3,4,5,6 };
std::vector<int>& get_range(void)
{
	std::cout << "get_range -> " << std::endl;
	return arr;
}
void test3()
{
	//���ڷ�Χ��forѭ�� ð�ź���ı��ʽֻ�ᱻִ��һ��
	for (auto val : get_range())
	{
		std::cout << val << endl;
	}
	std::cout << "-------------------" << endl;
	//���ڷ�Χ��forѭ�� ����ͨforѭ�����﷨�ǣ��ڵ���ʱ�޸������ܿ������������ʧЧ

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