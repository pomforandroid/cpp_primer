// Dynamic_memory_and_samrt_points.cpp : Defines the entry point for the application.
//

#include "Dynamic_memory_and_samrt_points.h"
#include <list>
#include <vector>

using namespace std;

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
	void push_back(const string& t) { data->push_back(t) };
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
	cout << "Hello CMake." << endl;
	return 0;
}
