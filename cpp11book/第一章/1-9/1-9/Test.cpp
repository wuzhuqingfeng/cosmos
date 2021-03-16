#include <iostream>
#include <vector>
#include <map>

// ʹ�� std::initializer_list<int> ����ʼ�����ⳤ�ȵĳ�ʼ���б�
//stl�е�������ͨ��ʹ�� std::initializer_list ��ɵ�
class Foo
{
public:
	Foo(std::initializer_list <int>){}
};

class FooVector
{
	std::vector<int> content_;

public:
	FooVector(std::initializer_list<int> list)//initializer_list ������ճ�ʼ���б�
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			content_.push_back(*it);
		}
	}
};


//map ���� pair��ʽ����ġ�map�е�Ԫ�ص�����value_type 
//typedef pair<const Key, Type> value_type;


class FooMap
{
	std::map<int, int> content_;
	using pair_t = std::map<int, int>::value_type;//������������   typedef

public:
	FooMap(std::initializer_list<pair_t> list)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			content_.insert(*it);
		}
	}
};

//ʹ�� std::initializer_list ���Զ�����������ʼ��
void test01()
{
	Foo foo = { 1,2,3,4,5 };
	FooVector foo1 = { 1, 2, 3, 4, 5 };
	FooMap foo2 = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
}

//ʹ�� std::initializer_list ����ͬ���͵�����
void func(std::initializer_list<int> list)
{
	std::cout << "size = "<<list.size() << std::endl;
	//�� std::initializer_list ����ֻ��ͨ��begin() end() ѭ������
	//��������ֻ���ģ��޷��޸�ĳһ��Ԫ�أ����������帳ֵ
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

void test02()
{
	func({});//1���ռ���
	func({ 1,2,3 });//���� { 1,2,3 }
}

/*
		std::initializer_list ���ڲ��������𱣴��ʼ���б���Ԫ�صĿ���,����
		�洢���б���Ԫ�ص����ö��ѣ������Ҫ�ٳ��ж������������֮ǰ�������
*/

//�����ʹ�÷���
std::initializer_list<int> func2(void)
{
	int a = 1, b = 2;
	return { a,b };//ab ����ʱ��û�п���
}

//��ȷ��ʹ��
std::vector<int> func3(void)
{
	int a = 1, b = 2;
	return { a,b };//ab ����ʱ��û�п���
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
	a = func2();//ֵʱ����ֵ
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