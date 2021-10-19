// generic_algorithm.cpp : Defines the entry point for the application.
//

#include "generic_algorithm.h"
#include <list>
#include <vector>
#include <numeric>

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

int main()
{
	cout << "Hello 泛型算法." << endl;
	test_10_1();
	test_10_2_1();
	return 0;
}
