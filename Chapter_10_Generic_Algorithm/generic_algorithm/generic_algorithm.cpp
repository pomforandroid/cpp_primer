// generic_algorithm.cpp : Defines the entry point for the application.
//

#include "generic_algorithm.h"
#include <list>
#include <vector>
#include <numeric>
#include <string>
#include <algorithm>

using namespace std;

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
int main()
{
	cout << "Hello 泛型算法." << endl;
	test_10_1();
	test_10_2_1();
	test_10_2_2();
	test_10_2_3();
	test_10_3_1();
	return 0;
}
