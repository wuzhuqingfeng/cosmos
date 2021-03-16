#include <iostream>
//防止类型收窄：导致数据内容发生变化或精度丢失的隐式类型转换
struct point {
	int x;
	int y;
	point(int _x = 0, int _y = 0) : x(_x), y(_y) 
	{
		printf("(this, x, y) = (%p, %d, %d)\n", this, x, y);
	}
};

/*
	c++11 通过列表初始化来检查及防止类型收窄
*/
int main(void)
{

	struct point po1(5, 6);
	printf("(&po1, x, y) = (%p, %d, %d)\n", &po1, po1.x, po1.y);

	int a = 1.1;  
	//int b = { 1.1 };  //error   c++11 通过列表初始化来检查

	float fa = 1e40;
	//float fb = { 1e40 };  //error c++11 通过列表初始化来检查

	float fc = (unsigned long long)-1;
	//float fd = { (unsigned long long)-1 };  //error c++11 通过列表初始化来检查
	float fe = (unsigned long long)1;
	float ff = { (unsigned long long)1 };  //OK

	const int x = 1024;
	const int y = 1;//若去掉const 限定符,则变量 f因为类型收窄而报错

	char c = x;
	//char d = { x };  //error
	char e = y;
	char f = { y };

	system("pause");
	return 0;
}