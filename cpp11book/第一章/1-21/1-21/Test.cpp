#include <iostream>
#include <functional>

void output(int x, int y)
{
	std::cout << "x = "<< x << " y = " << y << std::endl;
}

int main(void)
{
	//std::bind ���ص�������stl�ڲ�����ķº������ͣ�����ֱ�Ӹ�ֵ��std::function

	std::bind(output, 1, 2)();

	//std::bind �������ص���һ��stl�ڲ�����ķº���
	auto fr2 = std::bind(output, 11, 22);
	fr2();//�Ѿ��󶨺ò�����,����ֱ�ӵ��ü���

	std::bind(output, std::placeholders::_1, 2)(1);
	std::bind(output, 2, std::placeholders::_1)(1);

	//std::bind(output, 2, std::placeholders::_2)(1);  //error:����ʱû�еڶ�������

	//bind ��һ������ 2�Ѿ��󶨺���,�����ڴ���10
	std::bind(output, 2, std::placeholders::_2)(10, 2);  //��� 2 2   ����ʱ��һ���������̵���
	
	std::bind(output, std::placeholders::_1, std::placeholders::_2)(1, 2);  //��� 1 2
	//std::placeholders::_2 ָ�ĵ��ǲ���2
	std::bind(output, std::placeholders::_2, std::placeholders::_1)(1, 2);  //��� 2 1


	system("pause");
	return 0;
}