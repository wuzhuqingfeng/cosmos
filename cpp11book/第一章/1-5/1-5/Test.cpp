#include <iostream>
#include <vector>
#include <map>
using namespace std;

template <class ContainerT>
class Foo
{
	//typename ContainerT::iterator it_;  //���Ͷ������������
	//typename ContainerT::const_iterator it_;

	//������ const ContainerT ��ͨ��������ʹ������it_���壺
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
	typedef const std::vector<int> container_t;  //������const���ԣ�����ᱨһ��Ѵ�����Ϣ

	typedef std::map< std::string, int> map_int_t;
	container_t arr;

	Foo<container_t> foo;
	foo.func(arr);

	system("pause");
	return 0;
}

//ģ��ı���

//��1��д��
typedef std::map< std::string, int> map_int_t0;
typedef std::map< std::string, std::string> map_str_t0;


//��2��д�� c++98/03
template<typename T>
struct str_map {
	typedef std::map< std::string, T> type;
};

str_map<int>::type map_int_t1;
str_map<std::string>::type map_str_t1;

//��3��д�� c++11
template<typename T>
using str_map_t = std::map<std::string, T>;

str_map_t<int> map_int_t2;
str_map_t<std::string> map_str_t2;

/*
	using �ı����÷�������typedef��ȫ������

*/

typedef unsigned int uint_t0;	//��ͨ�����ض���
using uint_t1 = unsigned int;   //using �����ض���

//typedef std::map < std::string, int > map_int_t;//��ͨ�����ض���
using map_int_t1 = std::map < std::string, int >;

//typedef void(*fun_t)(int, int);//���¶���һ������ָ�� ,�����˴�����Ķ��Ѷ�
using fun_t2 = void(*)(int, int);//using �﷨ͨ����ֵ��������� ��typedef�ĵȼ���

//����ģ�����
//c++98/03
template<typename T>
struct fun_t
{
	typedef void (*typeFunc)(T, T);
};
//ʹ�� func_t ģ��
fun_t<int>::typeFunc xx_1;

//c++11 
template<typename T>
using func_t2 = void(*)(T, T); //func_t2 ��ģ����� �����Ǻ���ģ�壨����ģ��ʵ��������һ��������
//ʹ�� func_t2 ģ��
func_t2<int> xx_2;//xx_2 ������һ������ģ��ʵ��������࣬���� void(*)(int, int)�� ����


template<typename T>
using type_t = T;
type_t<int> i;//  type_t<int> �ȼ��� int 

