// Dynamic_memory_and_samrt_points.cpp : Defines the entry point for the application.
//

#include "Dynamic_memory_and_samrt_points.h"
#include <list>
#include <vector>

using namespace std;

void test_12_1_2() {
	//默认情况下，动态分配的对象是默认初始化
	int* pi = new int; // piz指向一个动态分配，为初始化的无名对象
	string* ps = new string; // 初始化为空string

	//直接初始化方式来初始化一个动态分配的对象
	int* pi_1 = new int(1024); // pi指向的对象的值是1024
	string* ps_2 = new string(10, '9');
	vector<int>* pv = new vector<int>{ 1, 2, 3, 4, 5, 6 };

	string* s1 = new string; // 默认初始化
	string* s2 = new string(); // 值初始化

	int* pi1 = new int; // 默认初始化， 未定义
	int* pi2 = new int(); // 值初始化， 0
	
	//仅有单一初始化器才可以使用auto
	auto p1_a = new int(1024);
	//auto p2_a = new int(10, 1);

	//动态分配的const对象
	//合法的
	const int* pci = new int(1024);
	const string* pcstr = new string;

	//内存耗尽
	int* p1 = new int; // if 分配 failed, new抛出std::bad_alloc
	int* p2 = new(nothrow) int; // if 分配失败，new返回一个空指针

	//释放动态内存。通过delete表达式来将动态内存归还给系统
	delete p2; 

	int i, * pi_i1 = &i, * pi_i2 = nullptr;
	double* pd = new double(33), * pd2 = pd;

	//delete i; // wrong. expression must be a pointer to complete object type
	delete pi_i1; // undifine, pi_i1 point to local var
	delete pd; // right
	delete pd2; //undifint, pd2 指向的内存已经释放了
	delete pi_i2; //right ,释放一个空指针总是没有错误的

	//delte之后重置指针值
	int* pp(new int(42)); //pp指向动态内存
	auto q = pp; //p和q指向相同的内存
	delete pp;
	pp = nullptr; 
	//we delete this memory and then set p to nullptr, indicating that it no longer points  any object
	//but resetting p has no effect to q, when we release the memory pointed to by p, q becomes invalid
}

//动态对象的生存期直到被释放为止
template <typename Foo, typename T>
Foo* factory(T arg) {
	//handle arg as appropriate
	return new Foo(arg);
}

//局部变量p被销毁，但是此变量是一个内置指针，而不是一个智能指针，p left his scope, nothing happen
template <typename Foo, typename T>
void use_factory(T arg) {
	Foo* p = factory(arg);
	//use p but didn't release it
}//p left his scope, but the memory he pointed to was not released

template <typename Foo, typename T>
void use_factory2(T arg) {
	Foo* p = factory(arg);
	delete p; // remember to release memory ,we don't need anymore
}

void test_12_1_1() {
	shared_ptr<string> p1; // shared_ptr, 可以指向string
	shared_ptr<list<int>> p2;  //shared_ptr, 可以指向int的list

	if (p1 && p1->empty())
		*p1 = "sb";

	//最安全的分配和使用动态内存的方法是调用一个名为make-shared的标准库函数
	shared_ptr<int> p3 = make_shared<int>(42);
	shared_ptr<string> p4 = make_shared<string>(10, '9');
	shared_ptr<int> p5 = make_shared<int>(); // 值初始化
	//auto
	auto p6 = make_shared<vector<string>>();
	//shared_ptr的拷贝和赋值
	auto p = make_shared<int>(42); // P指向的对象只有p一个引用者
	auto q(p); // p和q指向相同对象，此对象有两个引用者

	auto r = make_shared<int>(42);
	r = q; // 给r赋值，令它指向另一个地址
			//递增q指向的对象的引用计数
			//递减r原来指向的对象的引用计数
			//r原来指向的对象已没有引用者，会自动释放

	//shared_ptr自动销毁所管理的对象
	//通过析构函数完成销毁工作
	//shared_ptr还会自动释放相关联的内存
}

template <typename Foo, typename T>
shared_ptr<Foo> factory(T arg) {
	return make_shared<Foo>(arg);
}

template <typename Foo, typename T>
void use_factory(T arg)
{
	shared_ptr<Foo> p = factory(arg);
	//use p
} // p离开了作用域，它指向的内存会被自动释放掉

//但是如果有其他shared_ptr也指向这块内存，它就不会被释放掉
template <typename Foo, typename T>
shared_ptr<Foo> use_factory(T arg) {
	shared_ptr<Foo> p = factory(arg);
	// use p do something
	return p; // when we return p, 引用计数进行了递增操作
}// p离开了作用域，但它指向的内存不会被释放掉


class StrBlob {
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); };
	//add and remove element
	void push_back(const string& t) { data->push_back(t); };
	void pop_back();
	//元素访问
	string& front();
	string& back();
private:
	shared_ptr<vector<string>> data;
	//如果data[i]不合法，抛出一个异常
	void check(size_type i, const string& msg) const;
};

StrBlob::StrBlob():data(make_shared<vector<string>>()){}

StrBlob::StrBlob(initializer_list<string> il):
	data(make_shared<vector<string>>(il)){}

void StrBlob::check(size_type i, const string& msg) const {
	if (i > data->size())
		throw out_of_range(msg);
}

string& StrBlob::front(){
	check(0, "front on empty StrBlob");
	return data->front();
}

string& StrBlob::back(){
	check(0, "back on empty StrBlob");
	return data->back();
}


void StrBlob::pop_back(){
	check(0, "pop_back on empty StrBlob");
	return data->pop_back();
}


int main()
{
	cout << "Hello Dynamic memory and smart points !." << endl;

	test_12_1_2();
	return 0;
}
