// variable_basic_types.cpp : Defines the entry point for the application.
//

#include "variable_basic_types.h"

using namespace std;

void test_2_1_2() {
	bool b = 42; // b为真
	int i = b; // i的值为1
	i = 3.14; //i的值为3
	double pi = i; // pi的值为3.0
	unsigned char c = -1;; // 假设char占8比特，c的值为255
	signed char c2 = 256; // 假设char占8比特，c2的值是未定义的
	cout << "c: " << c << " c2: " << c2 << endl; // 输出空白，why? 后面找到原因了更新

	//含有无符号类型的表达式
	unsigned u = 10;
	int i2 = -42;
	cout << i2 + i2 << endl; // 输出-84
	cout << u + i2 << endl; // 如果int占32位，输出4294967264
}

void test_2_1_3() {
	//字面值常量
	20; /*十进制*/
	024; /*八进制*/
	0x14; /*十六进制*/
	cout << "2e2: " << 2e2 << endl;
	3.14159;
	cout << "3.14159E0: " << 3.14159E0 << endl;
	'a'; //字符字面值
	"Hello World"; //字符串字面值
	cout << "\tHi! \n";
	//指定字面值的类型
	L'a'; //宽字符型字面值，类型是wchar_t
	u8"hi!"; //utf-8字符串字面值
	42ULL;// unsigned long long
	1E-3F; // float
	3.14159L;// long double
	//布尔字面值和指针字面值
	bool test = false; // true和false是布尔类型的字面值
	nullptr; //指针字面值
}

void test_2_2_1() {
	//变量定义
	int sum = 0, value,
		units_sold = 0;
	string book("0-201-78345-X"); // book通过一个string字面值初始化

	//初始化, 注意在C++，初始化和赋值是两个完全不同的操作
	double price = 109.99, discount = price * 0.16;

	//列表初始化
	int units_sold1 = 0;
	int units_sold2 = { 0 };
	int units_sold3{ 0 }; // c++ 11 new
	int units_sold4(0);

	//如果使用列表初始化且初始值存在丢失信息的风险，则编译器降报错
	long double ld = 3.1415926536;
	//int a{ ld }, b = { ld }; // 错误 conversion from 'long double' to 'int', possible loss of data
	int c(ld), d = ld; // ok
	// 默认初始化
	string empty; // 非显示地初始化成一个空串

}



int main()
{
	cout << "Hello variable and basic_types !" << endl;
	test_2_1_2();
	test_2_1_3();
	test_2_2_1();
	return 0;
}
