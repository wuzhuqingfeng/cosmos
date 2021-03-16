#include <memory>
#include <type_traits>
#include <iostream>
#include <string>

#if 1
/*
   shared_ptr
   是存储指向动态分配（堆）对象指针的类，用于生存期控制。 每使用一次，内部的引用计数加1，每析构一次，
   内部引用计数减1，减为0时，删除指向的堆内存

   1使用引用计数 每一个shared_ptr拷贝指向相同的内存，在最后一个shared_ptr析构的时候，内存才会被释放
*/

void test()
{

	//初始化 使用构造函数
	std::shared_ptr<int> p(new int(100));
	std::shared_ptr<int> p2 = p;

	//初始化 使用reset方法  当智能指针有值的时候，会使引用计数减1
	std::shared_ptr<int> ptr;
	ptr.reset(new int(100));
	if (ptr)
	{
		std::cout << "ptr is not null" << std::endl;
	}

	//获取原始指针 get()
	int* myp = ptr.get();

	//使用make_shared<T> 辅助方法 优先使用 更高效

	std::shared_ptr<std::string> p4 = std::make_shared<std::string>(10, '9');
	std::shared_ptr<std::string> p5 = std::make_shared<std::string>("hello");
	std::shared_ptr<std::string> p6 = std::make_shared<std::string>();

}

//删除器
void DeleteIntPtr(int* p)
{
	std::cout << " DeleteIntPtr(int* p)" << std::endl;
	delete p;
}
void test02()
{
	//指定删除器 当p1的引用计数为0 时，自动调用删除器释放对象的内存

	std::shared_ptr<int> p1(new int, DeleteIntPtr);
	std::shared_ptr<int> p2(new int, [](int* p)//使用lambda
		{
			delete p;
		});

	//使用 shared_ptr 管理动态数组时,需要指定删除器,因为 shared_ptr的默认删除不支持数组对象
	std::shared_ptr<int> p(new int[10], [](int* p) {
		delete[] p;
		});

	//std::shared_ptr<int> p3(new int[10], std::default_delete<int[]>); 编译不过

}

//使用 shared_ptr 注意事项
//错误的使用  
struct A
{
	A() { std::cout << "A()" << std::endl; }
	~A() { std::cout << "~A()" << std::endl; }
	std::shared_ptr<A> GetSelf()
	{
		return std::shared_ptr<A>(this);//err 
	}
};

//正确的使用
struct B :public std::enable_shared_from_this<B>
{
	B() { std::cout << "B()" << std::endl; }
	~B() { std::cout << "~B()" << std::endl; }
	std::shared_ptr<B> GetSelf()
	{
		return shared_from_this();//通过基类的成员函数返回this的share_ptr
	}
};

struct D;
struct C
{
	std::shared_ptr<D> m_dptr;
	C() { std::cout << "C()" << std::endl; }
	~C() { std::cout << "~C() is delete" << std::endl; }
};
struct D
{
	std::shared_ptr<C> m_dptr;
	//std::weak_ptr<C> m_dptr; //其中改为一个即能解决循环引用的问题
	D() { std::cout << "D()" << std::endl; }
	~D() { std::cout << "~D() is delete" << std::endl; }

	
};

void test03()
{

	//1 不要用一个原始指针初始化多个 shared_ptr
	int* ptr = new int(1000);
	std::shared_ptr<int> p1(ptr);
	std::shared_ptr<int> p2(ptr);//logic error 因为  p1 和 p2  不共享 引用计数各自为1
	//2 不要再函数实参中创建 shared_ptr
	//function(shared_ptr<int>(new int), g()); //错误做法 函数参数的计算顺序可能不一样 若先new  再调用g(),若g()异常，则int 内存泄漏

	//正确做法 先创建智能指针 
	std::shared_ptr<int> p(new int(200));
	//f(p, g());
	//3 通过 shared_from_this() 返回this指针。不要将this指针作为  shared_ptr 返回出来,因为this指针
	//本质是一个裸指针,这样可能会重复导致析构
	{
		std::shared_ptr<A> sp1(new(A));
		//std::shared_ptr<A> sp2 = sp1->GetSelf();//使用this指针 构造出的 sp1和 sp2 没有任何关系,离开作用域后，各自析构,导致重复析构
	}
	std::cout << "------shared_from_this()---------" << std::endl;
	{
		std::shared_ptr<B> sp3(new(B));
		std::shared_ptr<B> sp4 = sp3->GetSelf();//OK
	}
	std::cout << "-------测试循环引用--------" << std::endl;
	//4避免循环引用 导致内存泄露
	{
		std::shared_ptr<C> Cp(new C);
		std::shared_ptr<D> Dp(new D);
		Cp->m_dptr = Dp;
		Dp->m_dptr = Cp;
	}//object should be destroyed
	//循环引用导致cp和dp的引用计数都为2，离开作用域后，二者引用计数都为1，并不减为0，导致两个
	//指针都不会析构，产生内存泄漏
}
#endif

#if 0
/*
	std::auto_ptr
	不推荐使用,c11已经废除
	原因
	1、auto_ptr指针在c++11标准中就被废除了，可以使用unique_ptr来替代，
	功能上是相同的，unique_ptr相比较auto_ptr而言，	提升了安全性（没有浅拷贝），
	增加了特性（delete析构）和对数组的支持
	2、auto_ptr 对象拥有其内部指针的所有权。这意味着auto_ptr对其内部指针的
	释放负责，即当自身被释放时，会在析构函数中自动的调用delete，从而释放内部指针的内存。
	3、正因如此，不能有两个auto_ptr 对象拥有同一个内部指针的所有权，因为有可能在某个时机，
	两者均会尝试析构这个内部指针。
    当两个auto_ptr对象之间发生赋值操作时，内部指针被拥有的所有权会发生转移，这意味着这个
	赋值的右者对象会丧失该所有权，不在指向这个内部指针（其会被设置成null指针）
	4、auto_ptr的构造的参数可以是一个指针，或者是另外一个auto_ptr对象。
	当一个新的auto_ptr获取了内部指针的所有权后，之前的拥有者会释放其所有权。
	5、调用release，从而放弃其内部指针的使用权，但是同样这么做违背了智能指针的初衷。
	6、调用reset来重新分配指针的所有权，reset中会先释放原来的内部指针的内存，然后分配新的内部指针。

*/

//aptr放弃内部指针的所有权,即不会调用析构
void foo_release()
{
	//释放
	int* pNew = new int(3);
	{
		std::auto_ptr<int> aptr(pNew);
		int* P = aptr.release();//aptr不会delete 掉pNew,只是将自身置empty 
	}

	{
		int* pNew2 = new int(3);
		int *p2 = new int(5);
		{
			std::auto_ptr<int> aptr(pNew2);
			aptr.reset(p2);//将pNew2 释放,指向p2
		}
	}
	/*
	当出了块作用域之后，aptr对象会自动调用析构，然后在析构中会自动的delete其内部指针，
	也就是出了这个作用域后，其内部指针就被释放了

	这种写法是不推荐的，因为我们这里本质上就是希望不去管理指针的释放工作，这种写法就又需要程序员自己操心指针的问题，
	也就是使用**智能指针要避免出现指针的直接使用
*/
}

void foo_assign()
{
	std::auto_ptr<int> p1;
	std::auto_ptr<int> p2;

	p1 = std::auto_ptr<int>(new int(3));
	*p1 = 4;
	p2 = p1;//p1释放了所有权,交给p2
}


void test()
{
	std::auto_ptr<int> aptr(new int(3));
	std::cout << aptr.get() << " " << *aptr << std::endl;
	//这样会编译出错，因为auto_ptr的构造有关键字explicit
	//explicit关键字表示调用构造函数时不能使用隐式赋值，而必须是显示调用
	//std::auto_ptr<int> aptr2 = new int(3); //error C2440: 'initializing': cannot convert from 'int *' to 'std::auto_ptr<int>

	//可以用其他的auto_ptr指针进行初始化
	std::auto_ptr<int> aptr2 = aptr;//将原aprt释放了 aptr = null
	printf("aptr2 %p : %d\r\n", aptr2.get(), *aptr2);

	//但是这么内存访问出错，直接0xc05,因为aptr已经释放了其所有权。
	//*aptr = 4;
	printf("aptr %p\r\n", aptr.get());

	foo_release();
	foo_assign();
}
/*
auto_ptr存在的问题
为什么11标准会不让使用auto_ptr，原因是其使用有问题。
1. 作为参数传递会存在问题。
	因为有拷贝构造和赋值的情况下，会释放原有的对象的内部指针，所以当有函数使用的是auto_ptr时，
	调用后会导致原来的内部指针释放。
2.不能使用vector数组
*/

void foo_test(std::auto_ptr<int> p)
{
	printf("%d\r\n", *p);
}

void foo_ary()
{
	/*
	std::vector<std::auto_ptr<int>> Ary;//err
	std::auto_ptr<int> p(new int(3));
	Ary.push_back(p);

	printf("%d\r\n", *p);
	*/
	//编译就不通过
}

void test05()
{
	std::auto_ptr<int> p1 = std::auto_ptr<int>(new int(3));
	foo_test(p1);

	//这里的调用就会出错，因为拷贝构造函数的存在，p1实际上已经释放了其内部指针的所有权了
	printf("%d\r\n", *p1);

}
#endif

#if 0
/*
	unique_ptr 独占型的智能指针
	1构造函数 实际上是没有类似auto_ptr的那种拷贝构造(避免了auto_ptr的问题)

*/
void foo_constuct()
{
	//这样构造是可以的
	std::unique_ptr<int> p(new int(3));

	//空构造
	std::unique_ptr<int> p4;

	//下面三种写法会报错 从根源上杜绝了auto_ptr作为参数传递的写法
	//std::unique_ptr<int> p2 = p;//err  不可复制
	//std::unique_ptr<int> p3(p);//err
	//p4 = p;//err
	std::unique_ptr<int> p5 = std::move(p);//可以移动
	
}

// reset的用法和auto_ptr是一致的：
void foo_reset()
{
	//释放
	int* pNew = new int(3);
	int* p = new int(5);
	{
		std::unique_ptr<int> uptr(pNew);
		uptr.reset(p);//将 pNew 释放,

	}
}

//release不会释放原来的内部指针，只是简单的将自身置空(放弃所有权)。
void foo_release()
{
	//释放
	int* pNew = new int(3);
	int* p = NULL;
	{
		std::unique_ptr<int> uptr(pNew);
		p = uptr.release();//将 uptr 设置为 empty,放弃所有权
	}
}


void test()
{
	foo_constuct();
	foo_reset();
	foo_release();
}

#endif



//支持普通指针
template <class T, class... Args> inline
typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
make_unique(Args&&...args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

//支持动态数组
template <class T> inline
typename std::enable_if<std::is_array<T>::value&& std::extent<T>::value == 0, std::unique_ptr<T>>::type
make_unique(size_t size)
{
	typedef typename std::remove_extent<T>::type U;
	return std::unique_ptr<T>(new U[size]());
}

//过滤掉定长数组的情况
template <class T, class... Args>
typename std::enable_if<std::extent<T>::value != 0, void>::type
make_unique(Args&&...) = delete;

int main(void)
{

	test();
	system("pause");
	auto unique = make_unique<int>(100);
	std::cout << *unique << std::endl;

	auto unique2 = make_unique<int[]>(10);

	for (int i = 0; i < 10; i++)
	{
		unique2[i] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << unique2[i] << " ";
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}