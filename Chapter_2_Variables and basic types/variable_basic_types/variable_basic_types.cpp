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

void test_2_3_2() {

	//1. 指针本身就是一个对象，允许对指针赋值和拷贝，在指针的生命周期内它可以先后指向几个不同的对象
	//2. 指针无须在定义时赋值。

	int* ip1, * ip2; // ip1和ip2都是指向int型对象的指针
	double dp, * dp2; //dp2是指向double型对象的指针，dp是double型对象

	int ival = 42; 
	//指针存放某个对象的地址，要想获取该地址，需要使用取地址符（操作符&)
	int* p = &ival; 
	//利用指针访问对象 ，如果指针指向了一个对象，则允许使用解引用符（操作符*）来访问该对象
	cout << *p; // 由符号*得到指针p所指的对象，输出42
	*p = 0; //由符号*得到指针p所指的对象，即可经由p为变量ival赋值
	cout << *p; 

	//某些符号有多重含义
	int i = 42;
	int& r = i; // &紧随类型名出现，因此是声明的一部分，r是一个引用
	int* p2; // *紧随类型名出现，因此是声明的一部分，p2是一个指针
	p2 = &i; // & 出现在表达式中，是一个取地址符
	*p2 = i; // *出现在表达式中，是一个解引用符
	int& r2 = *p2;

	//空指针
	int* p1 = nullptr; // 等价于int *p1 = 0;
	int* p3 = 0;
	//需要首先#include cstdlib
	//int* p3 = NULL;// 等价于int *p3 = 0;

	//赋值和指针
	//一旦定义了引用，就无法令其再绑定到另外的对象
	//给指针赋值就是令他存放一个新的地址，从而指向一个新的对象
	int i42 = 42;
	int* pi = 0;
	int* pi2 = &i42;
	int* pi3;
	pi3 = pi2; // pi3和pi2指向同一个对象i42
	pi2 = 0;//现在pi2不指向任何对象了

	//记住赋值永远改变的是等号左侧的对象
	pi = &ival; //pi的值被改变，现在pi指向了ival
	*pi = 0; //ival的值被改变，指针pi并没有改变


	//void指针  void*是一种特殊的指针类型，可用于存放任意对象的地址
	double obj = 3.14, * pd = &obj;
	void* pv = &obj;
	pv = pd;
}

void test_2_3_3() {
	//理解复合类型的声明
	//i是一个int类型的数，p是一个int型指针，r是一个int型引用
	int i = 1024, * p = &i, & r = i;
	//基本数据类型是int而非int*,*仅仅是修饰了p而已
	int* p1, p2; //p1是指向int的指针，p2是int

	//指向指针的指针
	int ival = 1024;
	int* pi = &ival; // pi指向一个int型的数
	int** ppi = &pi; //ppi指向一个int型的指针

	cout << "the value of ival\n"
		<< "direct value: " << ival << "\n"
		<< "indirect value: " << *pi << "\n"
		<< "doubly indirect value: " << **ppi
		<< endl;

	//指向指针的引用
	int i2 = 42;
	int* p; 
	int*& r2 = p; //r 是一个对指针P的引用

	r2 = &i2; // r2引用了一个指针，因此给r2赋值就是令p指向i2
	*r2 = 0; // 解引用r2得到i2, 也就是p指向的对象，将i2的值改为0
	//要理解r2的类型到底是什么，最简单的方法是从由右向左阅读r2的定义，离变量名最近的符号是&(例子是&r2)对变量的类型有最直接的影响
	//因此r2是一个引用
	//声明符的其余部分用以确定r2引用得类型是什么，例子是*说明r2引用得是一个指针
	//最后声明的基本数据类型部分指出r2引用得是一个int指针
}

int main()
{
	cout << "Hello variable and basic_types !" << endl;
	test_2_1_2();
	test_2_1_3();
	test_2_2_1();
	test_2_2_4();
	test_2_3_1();
	test_2_3_2();
	test_2_3_3();

	return 0;
}
