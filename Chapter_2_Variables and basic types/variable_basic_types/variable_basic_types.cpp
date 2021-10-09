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



int main()
{
	cout << "Hello variable and basic_types !" << endl;
	test_2_1_2();
	test_2_1_3();
	return 0;
}
