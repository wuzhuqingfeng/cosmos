#include <iostream>
//��ֹ������խ�������������ݷ����仯�򾫶ȶ�ʧ����ʽ����ת��
struct point {
	int x;
	int y;
	point(int _x = 0, int _y = 0) : x(_x), y(_y) 
	{
		printf("(this, x, y) = (%p, %d, %d)\n", this, x, y);
	}
};

/*
	c++11 ͨ���б��ʼ������鼰��ֹ������խ
*/
int main(void)
{

	struct point po1(5, 6);
	printf("(&po1, x, y) = (%p, %d, %d)\n", &po1, po1.x, po1.y);

	int a = 1.1;  
	//int b = { 1.1 };  //error   c++11 ͨ���б��ʼ�������

	float fa = 1e40;
	//float fb = { 1e40 };  //error c++11 ͨ���б��ʼ�������

	float fc = (unsigned long long)-1;
	//float fd = { (unsigned long long)-1 };  //error c++11 ͨ���б��ʼ�������
	float fe = (unsigned long long)1;
	float ff = { (unsigned long long)1 };  //OK

	const int x = 1024;
	const int y = 1;//��ȥ��const �޶���,����� f��Ϊ������խ������

	char c = x;
	//char d = { x };  //error
	char e = y;
	char f = { y };

	system("pause");
	return 0;
}