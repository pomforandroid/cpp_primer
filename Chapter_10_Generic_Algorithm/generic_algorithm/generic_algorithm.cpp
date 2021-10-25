// generic_algorithm.cpp : Defines the entry point for the application.
//

#include "generic_algorithm.h"
#include <list>
#include <vector>
#include <numeric>
#include <string>
#include <algorithm>
#include <functional>


using namespace std;
using namespace std::placeholders;

void test_10_1() {
	//概述
	int val = 42;
	vector<int> vec{ 1, 2, 3, 4, 5 };

	auto result = find(vec.cbegin(), vec.cend(), val);

	//report result
	cout << "the value " << val
		<< (result == vec.cend() ?
			"is no present" : "is present") << endl;

	string val2 = "a value";// the value which we want to find
	list<string> lst;
	auto result2 = find(lst.cbegin(), lst.cend(), val2);

	int ia[] = { 27, 210, 12, 47, 109, 83 };
	int val3 = 83;
	int* result3 = find(begin(ia), end(ia), val3);
	cout << "result " << *result3 << endl;
}

void test_10_2_1() {
	//只读算法
	vector<int> vec{ 1, 2, 3, 4, 5 };
	int sum = accumulate(vec.cbegin(), vec.cend(), 0);

	cout << "sum " << sum << endl;

	vector<string> vctr = { "i", "am ", "boy" };
	//由于string定义了+运算符。所以可以用accumulate来把所有string元素连接起来
	string sumstr = accumulate(vctr.cbegin(), vctr.cend(), string(""));
	// 如果传递了一个字符串字面值，用于保存和的对象的类型将是const char*;
	//const char*上没有定义+运算符. 所以下面代码会报错
	//string sumstr = accumulate(vctr.cbegin(), vctr.cend(), "");

	vector<char> vchar = { 'i', 'a', 'b' };
	string sumchar = accumulate(vchar.cbegin(), vchar.cend(), "");
	cout << "sumchar " << sumchar << endl;

	cout << "sumstr " << sumstr << endl;

}

void test_10_2_2() {
	//写容器元素的算法
	vector<int> ivec = { 1, 2, 3 };
	fill_n(ivec.begin(), ivec.size(), 0);

	//back+inserter
	vector <int> ivec2;
	auto it = back_inserter(ivec2); //通过它赋值会将元素添加到vec中
	*it = 42;
	for (auto a : ivec2)
		cout << a << endl;

	vector<int> ivec3;

	fill_n(back_inserter(ivec3), 10, 0);

	//拷贝算法copy

	int a1[] = { 0,1,2,3,4,5,6,7,8,9 };
	int a2[sizeof(a1) / sizeof(*a1)]; // a2与a1的大小一样
	//ret指向拷贝到a2的尾元素之后的位置
	auto ret = copy(begin(a1), end(a1), a2);// 把a1的内容拷贝给a2
	//re指向拷贝到a2的尾元素之后的位置
	cout << "copy a1 to a2" << endl;
	for (auto a : a2)
		cout << a << endl;

}

void test_10_2_3() {
	//重排容器元素的算法
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	//按字典排序words, 以便查找重复单词
	sort(words.begin(), words.end());
	for (auto a : words)
		cout << a << endl;
	cout << "-----------------------------" << endl;
	auto end_unique = unique(words.begin(), words.end());
	for (auto a : words)
		cout << a << endl;
	cout << "-----------------------------" << endl;
	words.erase(end_unique, words.end());
	for (auto a : words)
		cout << a << endl;

}

bool isShorter(const string& str1, const string& str2) {
	return str1.size() < str2.size();
}

void elumDups(vector<string> &words) {
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}


void biggies(vector<string>& words, vector<string>::size_type sz) {
	elumDups(words); // 将words按字典排序，删除重复单词
	stable_sort(words.begin(), words.end(), isShorter);
	//获取一个迭代器，指向第一个满足size()>=sz的元素
	auto wc = find_if(words.begin(), words.end(), 
		[sz](const string& str) 
		{return str.size() >= sz;});
	//计算满足size>=sz的元素的数目
	auto count = words.end() - wc;
	cout << count << " " << count << endl;

	//打印长度大于等于给定值的单词，每个单词后面接一个空格

	for_each(wc, words.end(),
		[](const string& s) {cout << s << "";});
	cout << endl;
}

void test_10_3_2() {
	//lambda表达式
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	biggies(words, 5);
}


void test_10_3_1() {
	//定制操作
	//向算法传递函数
	//谓词
	vector<string> vecs{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	sort(vecs.begin(), vecs.end(), isShorter); // isShorter就是谓词参数

	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	elumDups(words);
	stable_sort(words.begin(), words.end(), isShorter);
	for (const auto& s : words)
		cout << s << " ";
	cout << endl;

}

void test_10_3_3(vector<string>::size_type sz, ostream &os) {
	//lambda捕获和返回
	//当向一个函数传递一个lambda时，同时定义了一个新类型和该类型的一个对象：传递的参数就是此编译器生成的类类型的未命名对象

	//值捕获
	size_t v1 = 42; //local var
	// 将v1拷贝到名为f的可调用对象
	auto f = [v1] {return v1;};
	v1 = 0;
	auto j = f();
	cout << "j = " << j <<endl;

	//引用捕获
	size_t v2 = 42; //局部变量
	auto f2 = [&v2] {return v2;};
	v2 = 0;
	auto j2 = f2(); //f2保存v2的引用
	cout << "j2 = " << j2 <<endl;

	//隐私捕获
	//为了指示编译器推断捕获列表，应在捕获列表中写一个&或=
	//&表示采用捕获引用方式
	//=表示采用值捕获方式
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	auto wc = find_if(words.begin(), words.end(),
		[=](const string& s)
		{return s.size() >= sz;});

	//混合使用，捕获列表参数第一个必须是&或者=
	//sz显示捕获，值捕获方式，os隐式捕获
	for_each(words.begin(), words.end(),
		[&, sz](const string& s) {os << s << sz;});

	//os显示捕获，引用捕获方式，sz隐式捕获
	for_each(words.begin(), words.end(),
		[=, &os](const string& s) {os << s << sz;});

	//可变lambda
	size_t v3 = 42;
	auto f3 = [v3]() mutable {return ++v3;};
	v3 = 0;
	auto j3 = f3();
	cout << "j3 " << j3 << endl;
	//指定lambda返回类型

	vector<int> ivec = { -1, -2, -3, -6,-8 };
	//下面的正确，不用指定返回类型，编译器能推断出来
	transform(ivec.begin(), ivec.end(), ivec.begin(), 
		[](int i) {return i < 0 ? -i : i;});
	//书上说这个会错误，但是好像这里编译器也能推断出了
	transform(ivec.begin(), ivec.end(), ivec.begin(),
		[](int i) {if (i < 0) return -i; else return i;});

	//显示指定
	transform(ivec.begin(), ivec.end(), ivec.begin(),
		[](int i) -> int
		{if (i < 0) return -i; else return i;});
		
}

bool check_size(const string& s, string::size_type sz) {
	return s.size() >= sz;
}

void testBindPara(int a, int b, int c, int d, int e) {
	cout << a << " " << b << " " << c << " " << d << " " << e <<" "<< endl;
}

ostream& print(ostream& os, const string& s, char c) {
	return os << s << c;
}

void test_10_3_4() {
	//参数绑定
	//标准库bind函数
	auto check6 = bind(check_size, _1 , 6);
	string s = "hello";
	bool b1 = check6(s); //check6会调用check_size(s, 6)
	cout << "check6 " << b1 << endl;

	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	vector<string> words2{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	string::size_type sz = 6;
	auto wc = find_if(words.begin(), words.end(),
		[=](const string& s)
		{return s.size() >= sz;});
	cout << "wc1" << endl;
	for_each(wc, words.end(),
		[](const string& s) {cout << s << " ";});

	cout << endl;
	auto wc2 = find_if(words2.begin(), words2.end(),
		bind(check_size, _1, sz));

	cout << "wc2" << endl;
	for_each(wc2, words2.end(),
		[](const string& s) {cout << s << " ";});

	//bind的参数
	//if testBindPara is callable object ,it has 5 para
	int a = 1;
	int b = 2;
	int c = 3;
	//用bind重排参数顺序
	auto g = bind(testBindPara, a, b, _2, c, _1);

	// 实际的调用g(_1, _2); 映射为testBindPare(a, b, _2, c, _1)

	g(111, 222); //实际上调了testBindPara(a, b, 222, c, 111);

	//绑定引用参数
	//for_each(words.begin(), words.end(), bind(print, cout, _1, ' '));

	for_each(words.begin(), words.end(),
		bind(print, ref(cout), _1, ' '));

}

void test_10_4_1() {
	//插入迭代器
	list<int> lst = { 1,2,3,4 };
	list<int> lst2, lst3; // empty list

	//
	copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
	for (auto l : lst2)
		cout << l << " " << endl;

	//copy(lst.cbegin(), lst.cend(), lst3); 会报错
	copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));

	for (auto l : lst3)
		cout << l << " " << endl;
}

void test_10_4_2() {
	istream_iterator<int> in_iter(cin); //从cin读取int
	istream_iterator<int> eof; //尾后迭代器
	vector<int> vec;
	while (in_iter != eof)
		vec.push_back(*in_iter++);
	for (auto v : vec)
		cout << v << " " << endl;
	//vector<int> vec2(in_iter, eof); it is the same result like vec
}

void test_10_4_2_2() {

	//使用算法操作流迭代器

	istream_iterator<int> in(cin), eof2;
	cout << accumulate(in, eof2, 0) << endl;
}

void test_10_4_2_3() {
	//ostream_iterator操作
	vector<int> vec = { 1, 2, 3, 4, 5 };
	ostream_iterator<int> out_iter(cout, " link_string ");
	for (auto e : vec)
		*out_iter++ = e;
	cout << endl;

	//上下两种写法都可以
	//推荐上面的，因为格式跟其他迭代器一样的话好替换
	for (auto e : vec)
		out_iter = e; // 赋值语句将元素写到cout
	cout << endl;

	//通过copy打印
	copy(vec.begin(), vec.end(), out_iter);
	cout << endl;
}

void test_10_4_3() {
	//反向迭代器
	vector<int> vec = { 0, 1, 2, 11, 4, 5, 6, 7, 8, 9 };
	for (auto r_iter = vec.crbegin();
		r_iter != vec.crend();
		++r_iter) //实际上是递减，移动到前一个元素
		cout << *r_iter << endl;

	sort(vec.begin(), vec.end()); 

	cout << "正序" << endl;

	for (auto a : vec)
		cout << a << endl;

	cout << "倒序" << endl;

	sort(vec.rbegin(), vec.rend());
	for (auto a : vec)
		cout << a << endl;
	string line = "my,name,is,fable";
	auto comma = find(line.cbegin(), line.cend(), ',');
	cout << string(line.cbegin(), comma) << endl;

	//if you want to print the last word
	auto rcomma = find(line.crbegin(), line.crend(), ',');
	cout << string(line.crbegin(), rcomma) << endl; // 打出来elbaf 而不是fable
	//right solution
	cout << string(rcomma.base(), line.cend()) << endl;

}



int main()
{
	cout << "Hello 泛型算法." << endl;
	test_10_1();
	test_10_2_1();
	test_10_2_2();
	test_10_2_3();
	test_10_3_1();
	test_10_3_2();
	test_10_3_3(3, cout);
	test_10_3_4();

	test_10_4_1();
	//test_10_4_2();
	//test_10_4_2_2();
	test_10_4_2_3();
	test_10_4_3();
	return 0;
}
