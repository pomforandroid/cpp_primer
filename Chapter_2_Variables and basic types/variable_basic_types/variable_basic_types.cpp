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
	int* p3;
	int*& r2 = p3; //r 是一个对指针P的引用

	r2 = &i2; // r2引用了一个指针，因此给r2赋值就是令p3指向i2
	*r2 = 0; // 解引用r2得到i2, 也就是p2指向的对象，将i2的值改为0
	//要理解r2的类型到底是什么，最简单的方法是从由右向左阅读r2的定义，离变量名最近的符号是&(例子是&r2)对变量的类型有最直接的影响
	//因此r2是一个引用
	//声明符的其余部分用以确定r2引用得类型是什么，例子是*说明r2引用得是一个指针
	//最后声明的基本数据类型部分指出r2引用得是一个int指针
}

const int get_size() {
	return 1024;
}
void test_2_4() {
	//const限定符
	const int bufSize = 512; // 输入缓冲区大小

	//bufSize = 512; // 错误：试图向const对象写值 C++ expression must be a modifiable lvalue
	const int i2 = get_size();
	const int j = 42;
	//const int k; 错误：k是一个未经初始化的常量

	int i = 42;
	const int ci = i; // 正确，i的值被拷贝给了ci
	int k = ci; // 正确：ci的值被拷贝给了k

	//某些时候有这样一种const变量，它的初始值不是一个常量表达式，但是有必要在文件间共享
	// file_1.cpp定义并初始化了一个常量，该常量能被其他文件访问
	//extern const int bufSize = fcn();
	//file_1.h 头文件
	//extern const int bufsize; 


}


void test_2_4_1() {
	//const的引用
	//可以把引用绑定到const对象上，就想绑定到其他对象上一样，我们称之为对常量的引用。
	//与普通引用不同的是，对常量的引用不能被用作修改它所绑定的对象

	const int ci = 1024;
	const int& r = ci; //正确：引用及其对应的对象都是常量
	//r1 = 42; // 错误:r1是对常量的引用
	//int& r2 = ci; //错误：试图让一个非常量引用指向一个常量对象

	//初始化对const的引用
	int i = 42;
	const int& r1 = i; //允许将const int& 绑定到一个普通的int对象上
	const int& r2 = 42; //正确：r1是一个常量引用
	const int& r3 = r1 * 2; //正确
	//int& r4 = r1 * 2; // 错误：r4是一个普通的非常量引用

	//对const的引用可能引用一个并非const的对象
	int& r4 = i;
	//r1 = 0; // not ok
	r4 = 0;
}


void test_2_4_2() {
	//指针和const
	//与引用一样，也可以令指针指向向量或非常量
	//类似于常量引用，指向常量的指针不能用于改变所指对象的值
	//要想存放常量对象的地址，只能使用指向常量的指针
	const double pi = 3.14;
	//double* ptr = &pi; // 错误，ptr是一个普通指针，C++ a value of type cannot be used to initialize an entity of type
	const double* cptr = &pi; //正确， cptr可以指向一个双精度常量
	//*cptr = 42; // 错误不能给*cptr赋值
	double dval = 3.14;
	cptr = &dval;  //正确，但是不能通过cptr改变dval的值
	cout << "cptr: " <<  *cptr << endl;
	
	//const指针
	//常量指针必须初始化，而且一旦初始化完成后，它的值（也就是存放在指针中的那个地址）就不能再改变了
	//把*放在const关键字之前用以说明指针是一个常量
	//这样的书写形式隐含着一层意味，即不变的是指针本身的值而非指向的那个值：
	int errNumb = 0;
	int* const curErr = &errNumb; // curErr将一直指向errNumb
	const double pi2 = 3.14159;
	const double* const pip = &pi2; //pip是一个指向常量对象的常量指针

	//搞清楚这些声明最行之有效的办法是从右向左阅读
	//1.离curErr最近的符号是const, 意味着curErr本身是一个常量对象
	//2.对象的类型由声明符的其余部分确定。声明符中的下一个符号是*，意思是curErr是一个常量指针
	//3.最后该声明语句的基本数据类型部分确定了常量指针指向的是一个int对象

	//*pip = 2.72; //错误：pip是一个指向常量的指针

	if (*curErr) {
		*curErr = 0;// 正确: 把curErr所指的对象的值重置
		//curErr = &pi; //错误
	}
}

void test_2_4_3() {
	//顶层const
	//指针本身是不是常量以及指针所指的是不是一个常量就是两个互相独立的问题
	//用名词顶层const 表示指针本身就是个常量
	//而用名词底层const表示指针所指的对象是一个常量

	//更一般的，顶层const可以表示任意的对象是常量，这一点对任何数据类型都适用
	//指针类型既可以是顶层const也可以是底层const
	int i = 0;
	int* const p1 = &i; // 不能改变p1的值，这是一个顶层const
	const int ci = 42; //不能改变ci的值，这是一个顶层const
	const int* p2 = &ci; //允许改变p2的值，这是一个底层const

	const int* const p3 = p2; //靠右的是顶层const，靠左的是底层const
	const int& r = ci; //用于声明引用得都是底层const

	i = ci; // 正确，拷贝ci的值，ci是一个顶层const，对此操作无影响
	p2 = p3; //正确，p2和p3指向的对象类型相同，p3顶层const的部分不影响

	//另一方面，底层const的限制却不能忽视。
	//当执行对象的拷贝时，拷入和拷出的对象必须具有相同的底层const资格。
	//或者两个对象的数据类型必须能够转换
	//一般来说，非常量可以转换成常量，反之不行
	//int* p = p3; //错误p3包含底层const的定义，而p没有
	p2 = p3; // 正确，p2和p3都是底层const
	p2 = &i; //正确 int*能转换成const int*
	//int& r = ci; // 错误普通的int&不能绑定到int常量上
	const int& r2 = i; // 正确：const int&可以绑定到一个普通int上

}

constexpr int size() {
	return 1024;
}

int get_size2() {
	return 11;
}

void test_2_4_4() {
	//constexpr和常量表达式
	const int max_files = 20; //max_files是常量表达式
	const int limit = max_files + 1; // limit是常量表达式
	int staff_size = 27; 

	const int sz = get_size2(); 

	//constexpr变量，c++11规定允许将变量声明为constexpr类型以便由编译器来验证变量的值是否是一个常量表达式

	constexpr int mf = 20;
	constexpr int lmit = mf + 1;
	constexpr int sz2 = size();

	//字面值类型
	//算术类型、引用和指针都属于字面值类型
	//尽管指针和引用都定义成constexpr,但是他们的初始值却受到严格限制，一个constexpr指针的初始值必须是nullptr或者0
	//或者是存储在某个固定地址中的对象

	//指针和constexpr
	const int* p = nullptr; // p是一个指向整型常量的指针
	constexpr int* q = nullptr; // q是一个指向整数的常量指针
	//其中关键在于constexpr把它所定义的对象置为了顶层const




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
	test_2_4();
	test_2_4_2();
	return 0;
}
