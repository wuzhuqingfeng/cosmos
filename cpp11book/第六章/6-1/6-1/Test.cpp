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
	记录时长 duration 表示时间间隔, 记录时间长度
	std::ratio<分子, 分母> 表示时钟周期  分子/分母
*/
void test00()
{
	
	//线程休眠3秒
	std::this_thread::sleep_for(std::chrono::seconds(3));//休眠3秒
	std::this_thread::sleep_for(std::chrono::milliseconds(100));//休眠100 毫秒
	std::cout << "*************"<<std::endl;

	//获取时间间隔的时钟周期 count()
	std::chrono::milliseconds ms{ 3 };//3 毫秒

	std::chrono::microseconds us = 2 * ms;//6000 微秒
	std::chrono::duration<double, std::ratio<1, 30>> hz30{ 3.5 };

	std::cout << "3ms = " << ms.count() << " ticks" << std::endl;
	std::cout << "6000 us = " << us.count() << " ticks" << std::endl;

	//两端时间间隔的差值
	std::chrono::minutes t1(10);
	std::chrono::seconds t2(10);
	std::chrono::seconds t3 = t1 - t2;//t3时钟周期是1s
	std::cout << t3.count() << " seconds" << std::endl;

	//duration_cast<> 将秒的时钟周期转换为分钟的时钟周期，通过count()获取转换后的时间间隔
	std::cout << std::chrono::duration_cast<std::chrono::minutes>(t3).count() 
		<< " minutes" << std::endl;

}

/*
	time point 时间点
	获取从clock的纪元开始所经过的duration和当前时间
*/
void test()
{
	//计算时间距离1970年1月1日 有多少天
	using days_type = std::chrono::duration<int, std::ratio<60 * 60 * 24>>;//表示一天
	std::chrono::time_point<std::chrono::system_clock, days_type> today =
		std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());
	std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;

	//不同的clock的time_point 不能进行算术运算
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

	Timer t; //开始计时
	fun();

	std::cout << t.elapsed_seconds() << std::endl; //打印fun函数耗时多少秒
	std::cout << t.elapsed_nano() << std::endl; //打印纳秒
	std::cout << t.elapsed_micro() << std::endl; //打印微秒
	std::cout << t.elapsed() << std::endl; //打印毫秒
	std::cout << t.elapsed_seconds() << std::endl; //打印秒
	std::cout << t.elapsed_minutes() << std::endl; //打印分钟
	std::cout << t.elapsed_hours() << std::endl; //打印小时
}


int main(void)
{
	test();
	Test();

	system("pause");
	return 0;
}