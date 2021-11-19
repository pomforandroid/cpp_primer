// Class.cpp : Defines the entry point for the application.
//

#include "Class.h"
#include <vector>

using namespace std;


//委托构造函数
class Sales_data3 {

	//非委托构造函数使用对应的实参初始化成员
	Sales_data3(const string& s, unsigned cnt, double price) :bookNo(s),
		units_sold(cnt),
		revenue(price* cnt) {}

	//其他构造函数全部委托给另一个构造函数
	Sales_data3():Sales_data3 ("", 0, 0){}
	Sales_data3(string s) :Sales_data3(s, 0, 0){}

private:
	double avg_price() const;

	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};


class Sales_data { // struct和class的默认访问权限不一样，struct在第一个访问说明符之前的成员是public，而class则是private
public: // 添加了访问说明符
	//为Sales_data的非成员函数所做的友元声明
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend istream& read(istream&, Sales_data&);
	friend ostream& print(ostream&, const Sales_data&);

	//constructor function newly add
	//Sales_data() = default; // c++ 11 newly added
	//defind a default constructor, make it the same as a construstor which only accept a string actual para
	Sales_data(const string s = "") : bookNo(s) {}
	//Sales_data(const string& s) :bookNo(s) {}
	//construct funciton initlial list
	Sales_data(const string& s, unsigned n, double p) :bookNo(s),
		units_sold(n),
		revenue(p* n) {}
	//抑制构造函数定义的隐式转换可以将构造函数声明为explicit加以阻止
	explicit Sales_data(istream&);

	// new member: about the operator of Sales_data object
	// when call total.isbn() like calling Sales_data::isbn(&total)
	// the compiler is responsible for passing the address of 'total' to the implicit parameter 'this' of isbn
	// so when we use bookNo in isbn, it actually use this->bookNo
	// const: it's role to modify the type of implicit 'this' pointer
	// it mean that the type fot 'this' is 'sales_data * const'
	// 表示this是一个指向常量的指针，称之为常量成员函数
	string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);

private:
	double avg_price() const;
	
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

// Sale_data的非成员接口函数
Sales_data add(const Sales_data&, const Sales_data&);
ostream& print(ostream&, const Sales_data&);
istream& read(istream&, Sales_data&);


//the funciton nameed Sales_data::avg_price uses the scope operator to illustrate a fact:
//we define a function named avg_price and this function is declared in the scope of the class Sales_data
double Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

// define a function returns the 'this' object
Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

// Define class-related non-member functions
istream& read(istream& is, Sales_data& item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

ostream& print(ostream& os, const Sales_data& item) {
	os << item.isbn() << " " << item.bookNo << ""
		<< item.revenue << " " << item.avg_price();
	return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data&rhs) {
	Sales_data sum = lhs; // copy the data of member if lhs to sum
	sum.combine(rhs);
	return sum;
}

//defined the constructor function outside of class
Sales_data::Sales_data(istream & is) {
	read(is, *this);
}

//拷贝，赋值和析构
void test_7_1_5() {
	Sales_data total; //uses the defautl constructor when we didn't define any construct object
	Sales_data trans = Sales_data("skankhutn", 42, 10.24f);
	total = trans; //which is equal to 
	/**total.bookNo = trans.bookNo; //commend it case we change it to private
	total.units_sold = trans.units_sold;
	total.revenue = trans.revenue;**/
}

void use_improved_Sales_data(){
	Sales_data total; //uses the defautl constructor when we didn't define any construct object
	Sales_data transl;
	//if (read(cin, total)) {
	//	Sales_data trans;
	//	while (read(cin, trans)) {
	//		if (total.isbn() == trans.isbn())
	//			total.combine(trans);
	//		else {
	//			print(cout, total) << endl; //output result
	//			total = trans;
	//		}
	//	}
	//	print(cout, total) << endl;
	//}
	//else {
	//	cerr << "No data>!" << endl;
	//}

}

//firstly to define class Window_mgr, and declare clear function, but can't define it, because you should declare Screen before using Screen 
//secondly to defind Screen, included the declaration for clear
//finally defind clear function and now it can use Screen member

//成员定义中的普通块作用域的名字查找
int height; // 定义了一个名字，稍后在Screen中使用

//类的其他特性
class Screen {
	//把Window_mgr指定成它的友元
	friend class Window_mgr;
	// 令成员函数作为友元
	// Window_mgr::clear必须在Screen类之前被声明, 要不下面这个会报错
	//friend void Window_mgr::clear(Window_mgr::ScreenIndex);
	//函数重载和友元
	//如果一个类想把一组重载函数声明成它的友元，它需要对这组函数中每一个分别声明

public:
	typedef string::size_type pos;
	void dummy_fcn(pos height) {
		cursor = width * height; // wich height? 是参数传入的height
		cursor = width * this->height; // 成员height
		cursor = width * ::height; //wich height? 是那个全局的
	}
	void setHeight(pos);
	//using pos = string::size_type;
	Screen() = default;
	Screen(pos h, pos w, char c):height(h), width(w), contents(h*w, c){}
	void some_member() const;
	char get() const {
		return contents[cursor];
	}

	inline char get(pos h, pos w) const;
	Screen& move(pos r, pos c);

	Screen& set(char);
	Screen& set(pos, pos, char);

	Screen& display(ostream& os) {
		 do_display(os);
		 return *this;
	}
	const Screen& display(ostream& os) const {
		do_display(os);
		return *this;
	}

private:
	pos cursor = 0;
	pos height= 0;
	pos width = 0;
	string contents;
	mutable size_t access_ctr; 
	size_t non_mutable_access_ctr;

	void do_display(ostream& os) const { os << contents; }

};


Screen::pos verify(Screen::pos);
void Screen::setHeight(pos var) {
	//verify的声明位于setHeight的定义之前
	height = verify(var);
}
Screen::pos verify(Screen::pos) {
	//dosome
	Screen::pos i = 1;
	return i;
}

//类数据成员的初始值
class Window_mgr {
public:
	//every number of screen in window
	using ScreenIndex = std::vector<Screen>::size_type;
	//
	void clear(ScreenIndex);

private:
	//in default, a window_mgr included an empty Screen with a standard size 
	vector<Screen> screens{ Screen(24, 80, ' ') };
};

inline
Screen& Screen::set(char c) {
	contents[cursor] = c;
	return *this;
}

inline Screen& Screen::set(pos r, pos col, char ch)
{
	contents[r * width + col] = ch;
	return *this;
}

//令成员作为内联函数。
// 如之前所见，定义在类内部的成员函数是自动inline的
inline
Screen& Screen::move(pos r, pos c ){
	pos row = r * width; //calculate the posision of row
	cursor = row + c; // move the cursor to the specified column within the line
	return *this; //return the object with lvaule form
}

char Screen::get(pos r, pos c) const {
	pos row = r * width; //calculate the posision of row
	return contents[row + c];
}

void using_Screen() {
	Screen myscreen;
	//重载成员函数 overloaded member function
	char ch = myscreen.get(); // 调用Screen::get()
	cout << "myscreen.get() " << ch << endl;
	ch = myscreen.get(0, 0); //调用Screen::get(pos, pos)
	cout << "myscreen.get(0,0) " << ch << endl;

	//move the cursor the specified position and set the char value of this position
	myscreen.move(4, 0).set('#'); //链式调用
	//like myscreen.move(4,0); myscreen.set('#')

	Screen myScreen2(5, 3,' ');
	const Screen blank(5, 3, ' ');
	myScreen2.set('#').display(cout);
	blank.display(cout);

}
//mutable data member 
//which never be const, even if is is a member in const object
void Screen::some_member() const {
	++access_ctr;
	// ++non_mutable_access_ctr; error:C++ expression must be a modifiable lvalue
}

void Window_mgr::clear(ScreenIndex i) { //前面有Window_mgr::所以ScreenIndex就没必要加Window_mgr::
	Screen& s = screens[i];
	s.contents = string(s.height * s.width, 's');
}

//类类型
struct First {
	int memi;
	int getMem();
};

struct Second {
	int memi;
	int getMem();
};

class Screen2; // Screen2的声明，前向声明，forward declaration

// 一旦一个类的名字出现，他就被认为是声明过来。因此类允许包含指向他自身类型的引用或指针
class Link_screen {
	Screen window;
	Link_screen* next;
	Link_screen* pre;
};

//友元声明和作用域
struct X {
	friend void f() {/*友元函数可以定义在类的内部*/ }
	//X() { f(); } //错误：f还没有被声明
	void g();
	void h();
};
//void X::g() { return f(); } //错误：f还没有被声明
void f(); // 声明那个定义在X中的函数
void X::h() { return f(); } //正确：现在f的声明在作用域中了

//名字查找与类的作用域
//firstly,look ofr the statement in the block where the name is located,and  only consider the statement that appears before the use of the name
//if not find, continue to look for the outer scope
//not find finally, then program error 


typedef double Money;
string bal;
//when compiler find the statement for balance function, it will looking ofr the statement for Monkey
//compiler only consider the statement before using Monkey in Account
// cause it did not find the pair member, compiler will continue to look for it int Account 's outer scoper
// then comipler find Money ’s typedef statement
// On the other side, the body of the'balance' function is processed after the entire class is visible
class Account {
public:
	Money balance() { return bal; }
private:
	Money bal;
};

//下面这一段跟前面的构造函数效果相同，但是原来的版本初始化了它的数据成员，这个版本是赋值
/**
Sales_data::Sales_data(const string& s, unsigned cnt, double price) {
	bookNo = s;
	units_sold = cnt;
	revenue = cnt * price;
}
**/
//构造函数的初始值有时必不可少
//如果成员是const或者是引用得话，必须将其初始化
class ConstRef {
public:
	ConstRef(int ii);

private:
	int i;
	//ci和ri必须被初始化
	const int ci;
	int& ri; 
};
/**
ConstRef::ConstRef(int ii)
{
	//赋值
	i = ii; //right
	//ci = ii; //错误，不能给const赋值
	//ri = i; // 错误，ri没被初始化 references must be initialized
}
**/

ConstRef::ConstRef(int ii) :i(ii), ci(ii), ri(i) {

}

void test_7_5_1() {
	ConstRef c = ConstRef(1);
}

//成员初始化的顺序， 跟它们在类中出现的顺序一致
class X2 {
	int i; //初始化列表i 比j早初始化
	int j;
public:
	// X2(int val) :j(val), i(j) { } 未定义，i在j之前被初始化
	X2(int val) :i(val), j(val) {}
};


class NoDefault {
public:
	NoDefault(const string&);
	//There have another members,but no other constructor
};

struct A {
	NoDefault my_mem;
};
//A a; //wrong, 不能为A合成构造函数
struct B {
	//错误，不能为A合成构造函数 编译器报错no default constructor exists for class
	/**
	B(){} 
	NoDefault b_member;
	**/
};

void test_7_5_3() {
	Sales_data obj(); //正确，但是是定义了一个函数而不是对象
	//obj.isbn() 编译器报错expression must have class type ，obj是一个函数
}

//隐式的类类型转换
//converting constructor
void test_7_5_4() {
	Sales_data item;
	string null_book = "9-99-99999-9";
	//构造一个临时的Sales_data对象
	//该对象的units_sold和revenue等于0，bookNo等于null_book
	item.combine(null_book);
	//只允许一步类类型转换
	//item.combine("9999999");//报错no suitable constructor exists to convert from to
	//可以显示把字符串转换成string or sales_data
	item.combine(string("9-9999-9999"));
	item.combine(Sales_data("9-9999-9999"));

	//抑制构造函数定义的隐式转换可以将构造函数声明为explicit加以阻止
	//item.combine(cin); //no suitable user-defined conversion from to exists

	//为转换显示使用构造函数
	item.combine(Sales_data(cin));
	item.combine(static_cast<Sales_data>(cin));

	//标准库中含有显式构造函数的类
	//接受一个单参数的const char * string 不是explicit
	//接受一个容量参数的vector构造函数是explicit
}

//错误，explicit关键字只允许出现在类内的构造函数声明出
/**explicit Sales_data::Sales_data(istream& is) {
	read(is, *this);
}**/

struct Data {
	int ival;
	string s;
};

void test_7_5_5() {
	//聚合类使得用户可以直接访问其成员，并且具有特殊的初始化语法形式，当一个类满足如下条件，可以说他是聚合的
	//所以成员都是public
	//没有定义任何构造函数
	//没有类内初始值
	//没有基类，也没有virtual函数
	Data val1 = { 0, "sb" };
}

//字面值常量类
//数据成员都是字面值类型的聚合类是字面值常量类。如果一个类不是聚合类，但它符合下面要求，也是：
//数据成员必须是字面值类型
//类必须至少含有一个constexpr构造函数
//如果一个数据成员含有类内初始值，则内置类型成员的初始值必须是一条常量表达式；or如果成员属于某种类类型，初始值必须使用成员自己的constexpr构造函数
//类必须使用析构函数的默认定义，该成员负责销毁类的对象
class Debug {
public:
	constexpr Debug(bool b = true) :hw(b), io(b), other(b) {}
	constexpr Debug(bool b , bool i, bool o) : hw(b), io(b), other(b) {}
	constexpr bool any() { return hw || io || other; }

	void set_io(bool b) { io = b };
	void set_hw(bool b) { io = b };
	void set_other(bool b) { io = b };

private:
	bool hw; // hardware error
	bool io;// io error
	bool other;// other error
};

void test_7_5_5() {
	Debug io_sub(false, true, false); 
	if (io_sub.any())
		cerr << "lalalalalaal" << endl;
}

//类的静态成员
//声明静态成员：通过在成员的声明之前加上关键字static是的与类关联在一起。
//和其他成员一样，静态成员可以是public的或private的。静态数据成员的类型可以是常量，引用，指针，类类型
class Account {
public:
	void calculate() { 
		//其他成员与之前的版本一致
		amount += amount * interestRate; 
	}
	static double rate() { return interestRate; }
	static void rate(double);
	static constexpr int period2 = 30;

private:
	//静态成员的类内部初始化
	static constexpr int period = 30;
	//static constexpr int period = 30; //period是常量表达式
	//如果仅用作内部ok，但是外部要使用，比如说test_const_constexpr

	double daily_tbl[period];

	string owner;
	double amount;
	static double interestRate;
	static double initRate();
};

void test_const_constexpr(const int&) {

}

void test_7_6_1() {
	//test_const_constexpr(Account::period); //member (declared at line 495) is inaccessible
	test_const_constexpr(Account::period2);
}

//定义静态成员
void Account::rate(double newRate) {
	interestRate = newRate;
}

void test_7_6() {
	//使用类的静态成员
	double r;
	r = Account::rate(); //使用作用域运算符访问静态成员

	Account ac1;
	Account* ac2 = &ac1;
	r= ac1.rate(); //通过Accoutn的对象或引用
	r= ac2->rate(); 
}

//静态成员能用于某些场景，而普通成员不能
class Bar {
public:
private:
	static Bar mem1; //正确 静态成员可以是不完全类型
	Bar* mem2; //正确 指针成员可以是不完全类型
	//Bar mem3; //错误 数据成员必须是完全类型
};

//静态成员和普通成员的另外一个区别是我们可以使用静态成员作为默认实参
class Screen {
public :
	Screen& clear(char = bkground);

private:
	static const char bkground;
};

int main()
{
	cout << "Hello CMake." << endl;
	//test_7_5_1();
	using_Screen();

	//First obj1;
	//Second obj2 = obj1; //wrong, obj1 and obj2 are of different types

	Sales_data item1;
	//class Sales_data item1;// 一条等价的声明
	class Sales_data item2;

	//类的作用域
	Screen::pos ht = 24, wd = 80;
	Screen scr(ht, wd, ' ');
	Screen* p = &scr;
	char c = scr.get(); //访问scr对象的get成员
	c = p->get();	//访问p所指对象的get成员

	return 0;
}
