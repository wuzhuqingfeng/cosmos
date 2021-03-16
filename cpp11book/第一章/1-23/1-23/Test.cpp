#include <iostream>
#include <functional>

/*
	lambda��һ����������
	[�����б�](�����б�) mutable(��ѡ) �쳣���� -> �������� {
		// ������
	}

	[ caputrue ] ( params ) opt -> ret { body; };


	[] �������κα���
	[=] �����ⲿ���������б���,��ֵ���� Ĭ�����this
	[&] �����ⲿ���������б���,�����ò��� Ĭ�����this
	[=, &foo] ��ֵ�����ⲿ����������б���, �������ò���foo
	[bar] ��ֵ����bar,ͬʱ��������������
	[this] ����ǰ���е�this ָ��,��lambda ���ʽӵ�к͵�ǰ���Ա����ͬ���ķ���Ȩ��
*/
class A
{
	int i_ = 0;

	void func(int x, int y)
	{
		//auto x1 = []{return i_; };			//error,û�в����ⲿ���� [] �������κα���
		
		auto x2 = [=]{return i_ + x + y; };		//[=] �����ⲿ���������б���,��ֵ���� Ĭ�����this
		auto x3 = [&]{return i_ + x + y; };		//[&] �����ⲿ���������б���,�����ò��� Ĭ�����this
		auto x4 = [this]{return i_; };          //[this]����ǰ���е�thisָ��
		
		//auto x5 = [this]{return i_ + x + y; };  //error,û�в���x��y
		auto x6 = [this, x, y]{return i_ + x + y; };//�����г�Ա����

		auto x7 = [this]{return i_++; };
	}
};

/*
	lambda
*/
int main(void)
{
	{
		int a = 0;
		int b = 1;
		//auto f1 = []{return a; };  //error,û�в����ⲿ���� 
		auto f2 = [&]{return a++; };

		//�ڲ����һ˲��,a��ֵ�Ѿ������Ƶ�lambda ����
		auto f3 = [=]{return a; };
		std::cout << "a = " << a<< std::endl;//a = 0
		a += 10;
		std::cout << "a = " << f3() << std::endl;//a = 0
		
		//��ֵ�����޷��޸Ĳ�����ⲿ����
		//�޸İ�ֵ������ⲿ���� ʹ�� mutable
		//auto f4 = [=]{return a++; };  //error,a���Ը��Ʒ�ʽ����ģ��޷��޸�
		auto f4 = [=]()mutable {return a++; };//
		std::cout << "a = " << f4() << std::endl;// a = 0

		//auto f5 = [a]{return a + b; };  //error,û�в������b
		auto f6 = [a, &b]{return a + (b++); };//a ��ֵ����, b�����ò���
		auto f7 = [=, &b]{return a + (b++); };//= ������ֵ����  b�����ò���
	}

	{
		/*
		    ������Ϊlambda ��һ������operator()���࣬���º���
			lambda ���ʽ�е� operator()Ĭ����const��,һ��const��Ա�����޷��޸ĳ�Ա������ֵ.
			����ֵ�Զ��Ƶ�
			mutable�����þ���ȡ�� operator()�е�const
		*/

		//std::function �洢 lambda
		int a = 100;
		std::function<int(int)> f1 = [](int a) {return a; };//��Ϊ ����ֵ��int ,�Զ��Ƶ�
		std::cout << f1(10) << std::endl;//10
		
		//std::function ���� lambda
		std::function<int()> f2 = std::bind([](int a) {return a; }, 123);
		std::cout << f2() << std::endl;//123
	}
	
	{
		//û�в�������� lambda ����ֱ��ת��Ϊ����ָ��
		//��������� lambda ����ת��Ϊ����ָ��
		typedef void (*pFun)(int*);
		pFun p = [](int*p) {delete p; };
		//pFun p1 = [&](int* p) {delete p; };
	}

	system("pause");
	return 0;
}