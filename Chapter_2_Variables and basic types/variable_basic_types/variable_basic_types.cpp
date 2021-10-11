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
extern double pi = 3.1416; //定义
void test_2_2_2() {
	extern int i; //声明i而非定义i
	int j; // 声明并定义J
	//extern double pi = 3.1416; 函数体内部如果试图初始化一个由extern关键字标记的变量，将引发错误
	//i = 0; // 编译器不报错，但是运行会出错
	// extern int i2 = 0; not ok
	
}

int reused = 42; // reuused拥有全局作用域
void test_2_2_4() {
	//作用域
	int unique = 0; // unique拥有块作用域
	//输出#1 使用全局变量reused； 输出42 0
	cout << reused << " " << unique << endl;
	int reused = 0; // 新建局部变量reused，覆盖了全局变量reused
	//输出#2 使用局部变量reused; 输出0 0
	cout << reused << " " << unique << endl;
	//输出#3，显示地访问全局变量reused;输出42 0
	cout << ::reused << " " << unique << endl;
}

void test_2_3() {
	//符合类型是指基于其他类型定义的类型。C++语音有几种符合类型，其中包括，引用和指针
	//一条声明语句由一个基本数据类型和紧随其后的一个声明符列表组成

}

void test_2_3_1() {
	//引用为对象起了另外一个名字，通过将声明符写成&d的形式来定义引用类型，其中d是声明的变量名
	int ival = 1024;
	int& refVal = ival; //refval指向ival(it is another name for ival)
	//int& refVal2; 报错，引用必须被初始化
	refVal = 2;
	cout << "ival: " << ival << endl; //输出2
	int ii = refVal;

	int& refVal3 = refVal;
	int i = refVal;

	int& r = i, r2 = ii; //r2是int, r是引用

}

int main()
{
	cout << "Hello variable and basic_types !" << endl;
	test_2_1_2();
	test_2_1_3();
	test_2_2_1();
	test_2_2_4();
	test_2_3_1();
	return 0;
}
