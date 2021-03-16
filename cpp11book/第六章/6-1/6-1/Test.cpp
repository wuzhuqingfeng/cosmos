#define _CRT_SECURE_NO_WARNINGS

#include "Timer.hpp"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>
#include <chrono>

void fun()
{
	std::cout << "hello world" << std::endl;
}

/*
	��¼ʱ�� duration ��ʾʱ����, ��¼ʱ�䳤��
	std::ratio<����, ��ĸ> ��ʾʱ������  ����/��ĸ
*/
void test00()
{
	
	//�߳�����3��
	std::this_thread::sleep_for(std::chrono::seconds(3));//����3��
	std::this_thread::sleep_for(std::chrono::milliseconds(100));//����100 ����
	std::cout << "*************"<<std::endl;

	//��ȡʱ������ʱ������ count()
	std::chrono::milliseconds ms{ 3 };//3 ����

	std::chrono::microseconds us = 2 * ms;//6000 ΢��
	std::chrono::duration<double, std::ratio<1, 30>> hz30{ 3.5 };

	std::cout << "3ms = " << ms.count() << " ticks" << std::endl;
	std::cout << "6000 us = " << us.count() << " ticks" << std::endl;

	//����ʱ�����Ĳ�ֵ
	std::chrono::minutes t1(10);
	std::chrono::seconds t2(10);
	std::chrono::seconds t3 = t1 - t2;//t3ʱ��������1s
	std::cout << t3.count() << " seconds" << std::endl;

	//duration_cast<> �����ʱ������ת��Ϊ���ӵ�ʱ�����ڣ�ͨ��count()��ȡת�����ʱ����
	std::cout << std::chrono::duration_cast<std::chrono::minutes>(t3).count() 
		<< " minutes" << std::endl;

}

/*
	time point ʱ���
	��ȡ��clock�ļ�Ԫ��ʼ��������duration�͵�ǰʱ��
*/
void test()
{
	//����ʱ�����1970��1��1�� �ж�����
	using days_type = std::chrono::duration<int, std::ratio<60 * 60 * 24>>;//��ʾһ��
	std::chrono::time_point<std::chrono::system_clock, days_type> today =
		std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());
	std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;

	//��ͬ��clock��time_point ���ܽ�����������
	using namespace std::chrono;
	system_clock::time_point now = system_clock::now();
	std::time_t last = system_clock::to_time_t(now - hours(24));
	std::time_t next = system_clock::to_time_t(now + hours(24));

	std::cout << "one days ago: time was "<< std::put_time(std::localtime(&last),"%F %T")<<std::endl;
	std::cout << "next days: time was " << std::put_time(std::localtime(&next), "%F %T") << std::endl;
}

void Test()
{
	std::cout << "\nTest()\n";

	Timer t; //��ʼ��ʱ
	fun();

	std::cout << t.elapsed_seconds() << std::endl; //��ӡfun������ʱ������
	std::cout << t.elapsed_nano() << std::endl; //��ӡ����
	std::cout << t.elapsed_micro() << std::endl; //��ӡ΢��
	std::cout << t.elapsed() << std::endl; //��ӡ����
	std::cout << t.elapsed_seconds() << std::endl; //��ӡ��
	std::cout << t.elapsed_minutes() << std::endl; //��ӡ����
	std::cout << t.elapsed_hours() << std::endl; //��ӡСʱ
}


int main(void)
{
	test();
	Test();

	system("pause");
	return 0;
}