#include <memory>
#include <type_traits>
#include <iostream>
#include <string>

#if 1
/*
   shared_ptr
   �Ǵ洢ָ��̬���䣨�ѣ�����ָ����࣬���������ڿ��ơ� ÿʹ��һ�Σ��ڲ������ü�����1��ÿ����һ�Σ�
   �ڲ����ü�����1����Ϊ0ʱ��ɾ��ָ��Ķ��ڴ�

   1ʹ�����ü��� ÿһ��shared_ptr����ָ����ͬ���ڴ棬�����һ��shared_ptr������ʱ���ڴ�Żᱻ�ͷ�
*/

void test()
{

	//��ʼ�� ʹ�ù��캯��
	std::shared_ptr<int> p(new int(100));
	std::shared_ptr<int> p2 = p;

	//��ʼ�� ʹ��reset����  ������ָ����ֵ��ʱ�򣬻�ʹ���ü�����1
	std::shared_ptr<int> ptr;
	ptr.reset(new int(100));
	if (ptr)
	{
		std::cout << "ptr is not null" << std::endl;
	}

	//��ȡԭʼָ�� get()
	int* myp = ptr.get();

	//ʹ��make_shared<T> �������� ����ʹ�� ����Ч

	std::shared_ptr<std::string> p4 = std::make_shared<std::string>(10, '9');
	std::shared_ptr<std::string> p5 = std::make_shared<std::string>("hello");
	std::shared_ptr<std::string> p6 = std::make_shared<std::string>();

}

//ɾ����
void DeleteIntPtr(int* p)
{
	std::cout << " DeleteIntPtr(int* p)" << std::endl;
	delete p;
}
void test02()
{
	//ָ��ɾ���� ��p1�����ü���Ϊ0 ʱ���Զ�����ɾ�����ͷŶ�����ڴ�

	std::shared_ptr<int> p1(new int, DeleteIntPtr);
	std::shared_ptr<int> p2(new int, [](int* p)//ʹ��lambda
		{
			delete p;
		});

	//ʹ�� shared_ptr ����̬����ʱ,��Ҫָ��ɾ����,��Ϊ shared_ptr��Ĭ��ɾ����֧���������
	std::shared_ptr<int> p(new int[10], [](int* p) {
		delete[] p;
		});

	//std::shared_ptr<int> p3(new int[10], std::default_delete<int[]>); ���벻��

}

//ʹ�� shared_ptr ע������
//�����ʹ��  
struct A
{
	A() { std::cout << "A()" << std::endl; }
	~A() { std::cout << "~A()" << std::endl; }
	std::shared_ptr<A> GetSelf()
	{
		return std::shared_ptr<A>(this);//err 
	}
};

//��ȷ��ʹ��
struct B :public std::enable_shared_from_this<B>
{
	B() { std::cout << "B()" << std::endl; }
	~B() { std::cout << "~B()" << std::endl; }
	std::shared_ptr<B> GetSelf()
	{
		return shared_from_this();//ͨ������ĳ�Ա��������this��share_ptr
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
	//std::weak_ptr<C> m_dptr; //���и�Ϊһ�����ܽ��ѭ�����õ�����
	D() { std::cout << "D()" << std::endl; }
	~D() { std::cout << "~D() is delete" << std::endl; }

	
};

void test03()
{

	//1 ��Ҫ��һ��ԭʼָ���ʼ����� shared_ptr
	int* ptr = new int(1000);
	std::shared_ptr<int> p1(ptr);
	std::shared_ptr<int> p2(ptr);//logic error ��Ϊ  p1 �� p2  ������ ���ü�������Ϊ1
	//2 ��Ҫ�ٺ���ʵ���д��� shared_ptr
	//function(shared_ptr<int>(new int), g()); //�������� ���������ļ���˳����ܲ�һ�� ����new  �ٵ���g(),��g()�쳣����int �ڴ�й©

	//��ȷ���� �ȴ�������ָ�� 
	std::shared_ptr<int> p(new int(200));
	//f(p, g());
	//3 ͨ�� shared_from_this() ����thisָ�롣��Ҫ��thisָ����Ϊ  shared_ptr ���س���,��Ϊthisָ��
	//������һ����ָ��,�������ܻ��ظ���������
	{
		std::shared_ptr<A> sp1(new(A));
		//std::shared_ptr<A> sp2 = sp1->GetSelf();//ʹ��thisָ�� ������� sp1�� sp2 û���κι�ϵ,�뿪������󣬸�������,�����ظ�����
	}
	std::cout << "------shared_from_this()---------" << std::endl;
	{
		std::shared_ptr<B> sp3(new(B));
		std::shared_ptr<B> sp4 = sp3->GetSelf();//OK
	}
	std::cout << "-------����ѭ������--------" << std::endl;
	//4����ѭ������ �����ڴ�й¶
	{
		std::shared_ptr<C> Cp(new C);
		std::shared_ptr<D> Dp(new D);
		Cp->m_dptr = Dp;
		Dp->m_dptr = Cp;
	}//object should be destroyed
	//ѭ�����õ���cp��dp�����ü�����Ϊ2���뿪������󣬶������ü�����Ϊ1��������Ϊ0����������
	//ָ�붼���������������ڴ�й©
}
#endif

#if 0
/*
	std::auto_ptr
	���Ƽ�ʹ��,c11�Ѿ��ϳ�
	ԭ��
	1��auto_ptrָ����c++11��׼�оͱ��ϳ��ˣ�����ʹ��unique_ptr�������
	����������ͬ�ģ�unique_ptr��Ƚ�auto_ptr���ԣ�	�����˰�ȫ�ԣ�û��ǳ��������
	���������ԣ�delete�������Ͷ������֧��
	2��auto_ptr ����ӵ�����ڲ�ָ�������Ȩ������ζ��auto_ptr�����ڲ�ָ���
	�ͷŸ��𣬼��������ͷ�ʱ�����������������Զ��ĵ���delete���Ӷ��ͷ��ڲ�ָ����ڴ档
	3��������ˣ�����������auto_ptr ����ӵ��ͬһ���ڲ�ָ�������Ȩ����Ϊ�п�����ĳ��ʱ����
	���߾��᳢����������ڲ�ָ�롣
    ������auto_ptr����֮�䷢����ֵ����ʱ���ڲ�ָ�뱻ӵ�е�����Ȩ�ᷢ��ת�ƣ�����ζ�����
	��ֵ�����߶����ɥʧ������Ȩ������ָ������ڲ�ָ�루��ᱻ���ó�nullָ�룩
	4��auto_ptr�Ĺ���Ĳ���������һ��ָ�룬����������һ��auto_ptr����
	��һ���µ�auto_ptr��ȡ���ڲ�ָ�������Ȩ��֮ǰ��ӵ���߻��ͷ�������Ȩ��
	5������release���Ӷ��������ڲ�ָ���ʹ��Ȩ������ͬ����ô��Υ��������ָ��ĳ��ԡ�
	6������reset�����·���ָ�������Ȩ��reset�л����ͷ�ԭ�����ڲ�ָ����ڴ棬Ȼ������µ��ڲ�ָ�롣

*/

//aptr�����ڲ�ָ�������Ȩ,�������������
void foo_release()
{
	//�ͷ�
	int* pNew = new int(3);
	{
		std::auto_ptr<int> aptr(pNew);
		int* P = aptr.release();//aptr����delete ��pNew,ֻ�ǽ�������empty 
	}

	{
		int* pNew2 = new int(3);
		int *p2 = new int(5);
		{
			std::auto_ptr<int> aptr(pNew2);
			aptr.reset(p2);//��pNew2 �ͷ�,ָ��p2
		}
	}
	/*
	�����˿�������֮��aptr������Զ�����������Ȼ���������л��Զ���delete���ڲ�ָ�룬
	Ҳ���ǳ����������������ڲ�ָ��ͱ��ͷ���

	����д���ǲ��Ƽ��ģ���Ϊ�������ﱾ���Ͼ���ϣ����ȥ����ָ����ͷŹ���������д��������Ҫ����Ա�Լ�����ָ������⣬
	Ҳ����ʹ��**����ָ��Ҫ�������ָ���ֱ��ʹ��
*/
}

void foo_assign()
{
	std::auto_ptr<int> p1;
	std::auto_ptr<int> p2;

	p1 = std::auto_ptr<int>(new int(3));
	*p1 = 4;
	p2 = p1;//p1�ͷ�������Ȩ,����p2
}


void test()
{
	std::auto_ptr<int> aptr(new int(3));
	std::cout << aptr.get() << " " << *aptr << std::endl;
	//��������������Ϊauto_ptr�Ĺ����йؼ���explicit
	//explicit�ؼ��ֱ�ʾ���ù��캯��ʱ����ʹ����ʽ��ֵ������������ʾ����
	//std::auto_ptr<int> aptr2 = new int(3); //error C2440: 'initializing': cannot convert from 'int *' to 'std::auto_ptr<int>

	//������������auto_ptrָ����г�ʼ��
	std::auto_ptr<int> aptr2 = aptr;//��ԭaprt�ͷ��� aptr = null
	printf("aptr2 %p : %d\r\n", aptr2.get(), *aptr2);

	//������ô�ڴ���ʳ���ֱ��0xc05,��Ϊaptr�Ѿ��ͷ���������Ȩ��
	//*aptr = 4;
	printf("aptr %p\r\n", aptr.get());

	foo_release();
	foo_assign();
}
/*
auto_ptr���ڵ�����
Ϊʲô11��׼�᲻��ʹ��auto_ptr��ԭ������ʹ�������⡣
1. ��Ϊ�������ݻ�������⡣
	��Ϊ�п�������͸�ֵ������£����ͷ�ԭ�еĶ�����ڲ�ָ�룬���Ե��к���ʹ�õ���auto_ptrʱ��
	���ú�ᵼ��ԭ�����ڲ�ָ���ͷš�
2.����ʹ��vector����
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
	//����Ͳ�ͨ��
}

void test05()
{
	std::auto_ptr<int> p1 = std::auto_ptr<int>(new int(3));
	foo_test(p1);

	//����ĵ��þͻ������Ϊ�������캯���Ĵ��ڣ�p1ʵ�����Ѿ��ͷ������ڲ�ָ�������Ȩ��
	printf("%d\r\n", *p1);

}
#endif

#if 0
/*
	unique_ptr ��ռ�͵�����ָ��
	1���캯�� ʵ������û������auto_ptr�����ֿ�������(������auto_ptr������)

*/
void foo_constuct()
{
	//���������ǿ��Ե�
	std::unique_ptr<int> p(new int(3));

	//�չ���
	std::unique_ptr<int> p4;

	//��������д���ᱨ�� �Ӹ�Դ�϶ž���auto_ptr��Ϊ�������ݵ�д��
	//std::unique_ptr<int> p2 = p;//err  ���ɸ���
	//std::unique_ptr<int> p3(p);//err
	//p4 = p;//err
	std::unique_ptr<int> p5 = std::move(p);//�����ƶ�
	
}

// reset���÷���auto_ptr��һ�µģ�
void foo_reset()
{
	//�ͷ�
	int* pNew = new int(3);
	int* p = new int(5);
	{
		std::unique_ptr<int> uptr(pNew);
		uptr.reset(p);//�� pNew �ͷ�,

	}
}

//release�����ͷ�ԭ�����ڲ�ָ�룬ֻ�Ǽ򵥵Ľ������ÿ�(��������Ȩ)��
void foo_release()
{
	//�ͷ�
	int* pNew = new int(3);
	int* p = NULL;
	{
		std::unique_ptr<int> uptr(pNew);
		p = uptr.release();//�� uptr ����Ϊ empty,��������Ȩ
	}
}


void test()
{
	foo_constuct();
	foo_reset();
	foo_release();
}

#endif



//֧����ָͨ��
template <class T, class... Args> inline
typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
make_unique(Args&&...args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

//֧�ֶ�̬����
template <class T> inline
typename std::enable_if<std::is_array<T>::value&& std::extent<T>::value == 0, std::unique_ptr<T>>::type
make_unique(size_t size)
{
	typedef typename std::remove_extent<T>::type U;
	return std::unique_ptr<T>(new U[size]());
}

//���˵�������������
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