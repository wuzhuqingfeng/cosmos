#include <iostream>

/*
	�ɵ��ö���

	��һ������ָ��
	��һ������operator() ��Ա����������� ���º���
	��һ���ɱ�ת��Ϊ����ָ��������
	��һ�����Ա(����)ָ��
*/
void func(void)
{
	//...
}
//�������󣺶����˵��ò���������������󡣵��øö�����ô˲�����ʱ���������ʽ��ͬ��ͨ��������һ�㣬���ȡ���к�������

//C++��������ʵ�����ǲ��������أ�ʵ���˶�()�����������ء�C++���������Ǻ���ָ�롣���ǣ��ڳ�������У�
//���ĵ��÷�ʽ�뺯��ָ��һ��������Ӹ����žͿ����ˡ�
struct Foo
{
	void operator()(void)//�º���
	{
		//...
		std::cout << "operator()" << std::endl;
	}
};

struct Bar
{
	using fr_t = void(*)(void); //ʹ�� using ���庯��ָ�� ע�⺯��������

	static void func(void)
	{
		//...
		std::cout << "func()" << std::endl;
	}
	
	operator fr_t(void) // �ɱ�ת��Ϊ����ָ�������� ������ fr_t ����ָ������ void(*)(void)
	{
		std::cout << "fr_t()" << std::endl;
		return func;
	}
};

struct A
{
	int a_;

	void mem_func(void)
	{
		//...
	}
};
//�º���(functor)������ʹһ�����ʹ�ÿ���ȥ��һ��������
//��ʵ�־�������ʵ��һ��operator()���������������ƺ�������Ϊ������һ���º�������
int main(void)
{
	void(*func_ptr)(void) = &func;  //����ָ��
	func_ptr();

	Foo foo;  //�º��� 
	foo();

	Bar bar;  //�ɱ�ת��Ϊ����ָ�������� ������()
	bar();

	void(A::*mem_func_ptr)(void) = &A::mem_func;  //���Ա����ָ��   ����ָ����� mem_func_ptr
	int A::*mem_obj_ptr = &A::a_;  //���Աָ��   ::* �ǡ�ָ�����ݳ�Ա��ָ�����͡�

	A aa;
	(aa.*mem_func_ptr)();
	aa.*mem_obj_ptr = 123;

	system("pause");
	return 0;
}