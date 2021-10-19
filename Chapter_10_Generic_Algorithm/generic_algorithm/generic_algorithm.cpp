// generic_algorithm.cpp : Defines the entry point for the application.
//

#include "generic_algorithm.h"
#include <list>
#include <vector>

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

int main()
{
	cout << "Hello 泛型算法." << endl;
	test_10_1();
	return 0;
}
