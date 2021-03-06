// Dynamic_memory_and_samrt_points.cpp : Defines the entry point for the application.
//

#include "Dynamic_memory_and_samrt_points.h"
#include <list>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <fstream>

using namespace std;


//使用标准库:文本查询程序
//在类之间共享数据
class QueryResult; //in order to to define the return type of the function query, this definition is necessary
class TextQuery {
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> file; //输入文件
	map<string, shared_ptr<set<line_no>>> wm;
};

//The Contructor of TextQuery accept a ifstream, read input file by line
TextQuery::TextQuery(ifstream& is) : file(new vector<string>)
{
	string text;
	while (getline(is, text)) { //each line in text
		file->push_back(text); // save text in this line
		int n = file->size() - 1; // save current line number
		istringstream line(text); //Break down lines of text into words
		string word;
		while (line >> word) {
			auto& lines = wm[word]; // lines is a shared_ptr
			if (!lines) // this poiner is empty when we meet it first time
				lines.reset(new set<line_no>);
			lines->insert(n); // insert this line-number into set
		}
	}

}

class QueryResult {

friend ostream& print(ostream&, const QueryResult&);

public:
	using line_no = vector<string>::size_type;
QueryResult(string s, 
	shared_ptr<set<line_no>> p,
	shared_ptr<vector<string>> f):sought(s), lines(p), file(f){}
private:
	string sought; //search word
	shared_ptr<set<line_no>>lines; //出现的行号
	shared_ptr<vector<string>> file; //output file
};
QueryResult 
TextQuery::query(const string& sought) const {
	//if can not find out sought, then return a poiner ponited to this set
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	// using find rather than position
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file); //not find
	else
		return QueryResult(sought, loc->second, file);
}
string make_plural(size_t ctr, const string& word, const string& ending = "s") {
	return (ctr > 1) ? word + ending : word;
}

ostream& print(ostream& os, const QueryResult& qr) {
	//if we find word, print the apprear count and the position
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s") << endl;
	//print word accurs evey line
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ")"
		<< *(qr.file->begin() + num) << endl;
	return os;
}

void test_12_3_2() {
	string ifile = "D:\\test.txt";
	ifstream in(ifile);
	if (in) {
		TextQuery textQuery = TextQuery(in);
		auto ret = textQuery.query("the");
		print(cout, ret);
	}

}

//allocator类
void test_12_2_2() {
	//Generally speaking, putting memory allocation and object constructor together may cause unnecessary wasted
	//for example
	int n = 10;
	string* const p2 = new string[n]; // create n empty string
	string s;
	string* q1 = p2; //q2 point to the first string
	//but we may not need n strings

	//allocator类
	allocator<string> alloc; // Allocator object that can allocate string 
	auto const p = alloc.allocate(n); // allocate n uninitialized strings
	// allocator allocate unconstructed memory
	auto q = p;  //q points to the position  behind the final construction element
	//cout << "test_12_2_2 p: " << *p << endl; // 会报错，程序终止，未构造对象的情况下使用原始内存是错误的
	//cout << "test_12_2_2 q: " << *q << endl; // cout nothing
	alloc.construct(q++,"skankhunt");
	alloc.construct(q++, 10, 'c');
	alloc.construct(q++, "hi");
	cout << "test_12_2_2 p: " << *p << endl; // cout skankhunt ,because "alloc.construct(q++,"skankhunt");" allocate p
	//cout << "test_12_2_2 q: " << *q << endl; // 会报错，程序终止，未构造对象的情况下使用原始内存是错误的
	//cout << "test_12_2_2 q: " << *--q << endl; //cout hi
	//cout << "test_12_2_2 q: " << *q << endl; // cout hi
	while (q != p) {
		cout << "test_12_2_2 q: " << *(q-1) << endl;
		alloc.destroy(--q);
	}
	// release memory by call deallocate to complete
	alloc.deallocate(p, n);
	

	allocator<int> ialloc;
	//Algorithms for copying and filling uninitialized memory 
	vector<int> vi = vector<int>(10, 223);
	auto p5 = ialloc.allocate(vi.size() * 2);
	//uninitialized_copy will return a pointer, points to the position  behind the final construction element
	auto q6 = uninitialized_copy(vi.begin(), vi.end(), p5); //q6 is the last position after allocate by p5
	uninitialized_fill_n(q6, vi.size(), 42);
	cout << "q6 " << *q6 << endl;
	cout << "q6 is behind at " << *(q6-1) << endl; // cout 223
}

//动态数组

int get_size() {
	return 0;
}
void test_12_2_1() {
	//call get_size to confirm  how many ints are allocated
	int* pia = new int[get_size()];
	//Type alias
	typedef int arrT[42];
	int* p = new arrT;// assign an array of 42 ints; p pointed to the first int

	//initialize an array of dynamically allocate objects
	// in default, object allocated by new, whether in a single allocate or in an array, are initialized by default

	int* pia1 = new int[10]; //undefined, ten uninitialized int
	int* pia2 = new int[10](); //10 int value initialized to 0
	string* psa = new string[10];//10 empty string
	string* psa2 = new string[10](); //10 empty string

	//new standard, using Initializer
	int* pia3 = new int[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// it is legal to allocate an empty array
	int* p_empty = new int[0];
	cout << "p-empty " << *p_empty << endl;

	//释放动态数组
	delete[]p;// Square brackets are required
	//smart point and Dynamic array
	unique_ptr<int[]> up(new int[10]);
	//up.release();// Automatically use delete[] to destory its pointer
	//when an unique_ptr point to an array instead of a single object, we can not use dot and arrow member operators
	for (size_t i = 0; i != 10; i++)
		up[i] = i;// assign an new value to each element
	// it is difference between unique_ptr and shared_ptr, shared_ptr does not directly support the management of dynamic arrays
	// if you want, you must offer the deleter defined by yourself
	// must provide your owner deleter
	shared_ptr<int[]> sp(new int[10], [](int* p) {delete[]p;});
	sp.reset();
}

//weak ptr
void test_12_1_6() {
	// weak ptr 是一种不控制所指向对象的智能指针，它指向一个shared_ptr管理的对象
	//binding a weak_ptr to a shared_ptr will not change the reference count of shared_ptr

	//it need a share_ptr to init
	auto p = make_shared<int>(42);
	weak_ptr<int> wp(p);  // wp weakly share p1, the reference count of p has not change
	//because obj maybe not exist, we cannot use weak_ptr to directly visit obj
	//must use lock
	if (shared_ptr<int> np = wp.lock()) {
		//np share object with p in the scope
	}
}

//unique_ptr
void test_12_1_5() {
	//一个unique“拥有”它所指向的对象。与shared_ptr不同，某个时刻智能有一个unique_ptr指向一个给定对象。
	unique_ptr<double> p1;
	unique_ptr<int> pi1(new int(42));
	//由于一个unique“拥有”它所指向的对象，因此unique不支持普通的拷贝或者赋值操作
	unique_ptr<string> pstr1(new string("Stsfasfasfas"));
	//unique_ptr<string> p2(pstr1); // unique does not support copy
	unique_ptr<string> p3;
	//p3 = p2; // wrong: unique_ptr does not support assignment
	//Although we cannot copy or allocate a unique_ptr, we can call release or reset to transfer the ownership of the pointer from a (non-const) unique_ptr to another unique
	
	unique_ptr<string> p2(pstr1.release()); //releae set p1 to null
	cout << "p2: " << *p2 << endl; // cout Stsfasfasfas
	unique_ptr<string> p5(new string("skankhunt"));
	//transfer ownership of p5 to p2
	p2.reset(p5.release()); //reset release the memory originally pointed to by p2
	cout << "p2: " << *p2 << endl; //cout skankhunt
}

//传递unique_ptr参数和返回unique_ptr
unique_ptr<int> clone(int p ) {
	//correct, create a unique_ptr from int *
	return unique_ptr<int>(new int(p));
}
//or return a local var 's copy
unique_ptr<int> clone2(int p) {
	//correct, create a unique_ptr from int *
	auto ret = unique_ptr<int>(new int(p));
	return ret;
}


//智能指针和异常
void test_12_1_4() {
	shared_ptr<int> sp(new int(1024)); // allocate a new obj
	// this code throw a error, and it did not caught by 
}// methoed ends with shared_ptr auto release memory

// 使用我们自己的释放操作
struct destination;
struct connection {};
connection connect(destination*);
void disconnect(connection) {

}

void end_connection(connection* p) {
	disconnect(*p);
}
void f2(destination& d) {
	//get a connection ,remember to close it when it end
	/** connection c = connect(&d);
	shared_ptr<connection> p(&c, end_connection);
	**/
	// even if error happens and crash exit, connection will be close correctly
}

//pass deleter to unique_ptr
void f(destination& d) {
	/**connection c = connect(&d);
	unique_ptr<connection, decltype(end_connection)*>
		p(&c, end_connection);
	**/
}

void process(shared_ptr<int> ptr) {
	// use ptr
}//ptr leaf his scope and is destroyed
//shared_ptr和new结合使用
void test_12_1_3() {
	shared_ptr<double> p1; // share_ptr可以指向一个double
	shared_ptr<int> p2(new int(42)); // p2指向一个值为42的int
	// the smart pointer construcotr is explicit, so the direct initialization form must be used
	//shared_ptr<int> pi1 = new int(42); //the direct initialization form must be used 
	shared_ptr<int> pi2(new int(42));

	//不要混合使用普通指针和智能指针 don't mix ordinay pointers and smart pointers

	shared_ptr<int> p(new int(42));
	process(p); // 拷贝p会递增他的引用计数，在process中引用计数值为2
	// copying p will increment its reference cont, and the reference count value in process is 2
	int i = *p; // correct: the reference cout value is 1

	//也不要使用get初始化另一个智能指针或为智能指针赋值
	shared_ptr<int> p_1(new int(42));// reference count is 1
	int* q_1 = p_1.get(); // 正确，但是使用q时要注意，不要让它管理的指针被释放
	{
		shared_ptr<int>(q_1);
	}// The programe scope ends , q is destoryed, the memory it points to has been released
	int foo = *p_1; // 未定义，p指向的内存已经被释放了
	cout << "foo: " << foo << endl;

	//其他shared_ptr操作
	//p = new int(1024); // 不能将一个指针赋予shared_ptr;
	p.reset(new int(1024));
	cout << "p: " << *p << endl;
	//reset 经常与unique一起使用
	if (!p.unique())
		p.reset(new int(*p)); // we are not the only user; assign a new copy
	//*p += newvall //Now we know that we are the only user and can change the value of the object

}


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

	//int* pi1 = new int; // 默认初始化， 未定义
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
	//delete pi_i1; // undifine, pi_i1 point to local var
	delete pd; // right
	//delete pd2; //undifint, pd2 指向的内存已经释放了
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
void use_factory2(T arg) {
	Foo* p = factory(arg);
	//use p but didn't release it
}//p left his scope, but the memory he pointed to was not released

template <typename Foo, typename T>
void use_factory3(T arg) {
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


// StrBlobStr throw a error when trying to visit an unexisted element

class StrBlobStr;
class StrBlob {
	friend class StrBlobStr;
	StrBlobStr begin();
	StrBlobStr end();
	/** StrBlobStr begin() {
		return StrBlobStr(*this);
	}

	StrBlobStr end() {
		auto ret = StrBlobStr(*this, data->size());
		return ret;
	}**/
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

class StrBlobStr {
public:
	StrBlobStr() :curr(0) {}
	StrBlobStr(StrBlob& a, size_t sz = 0) :
		wptr(a.data), curr(sz) {}
	string deref() const;
	StrBlobStr& incr(); //前缀递增

private:
	//if check sucess, 'check' return a shared_ptr pointed to vector
	shared_ptr<vector<string>> check(size_t, const string&) const;
	//save a weak_ptr, which means the underlying vector will be destroyed
	weak_ptr<vector<string>> wptr;
	size_t curr; // current position in array
};

shared_ptr<vector<string>>
StrBlobStr::check(size_t i, const string& msg) const {
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBlobStr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;
}
string StrBlobStr::deref() const {
	auto p = check(curr, "derefence past and end");
	return (*p)[curr];
}

StrBlobStr& StrBlobStr::incr() {
	auto p = check(curr, "increament past end of StrBlobPtr");
	++curr;// 推进当前位置
	return *this;
}

StrBlobStr StrBlob::begin() {
	return StrBlobStr(*this);
}

StrBlobStr StrBlob:: end() {
	auto ret = StrBlobStr(*this, data->size());
	return ret;
}


int main()
{
	cout << "Hello Dynamic memory and smart points !." << endl;
	/**test_12_2_2();
	test_12_2_1();
	test_12_1_5();
	test_12_1_2();
	test_12_1_3();**/
	test_12_3_2();
	return 0;
}
