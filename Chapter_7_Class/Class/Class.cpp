// Class.cpp : Defines the entry point for the application.
//

#include "Class.h"
#include <vector>

using namespace std;

class Sales_data { // struct和class的默认访问权限不一样，struct在第一个访问说明符之前的成员是public，而class则是private
public: // 添加了访问说明符
	//为Sales_data的非成员函数所做的友元声明
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend istream& read(istream&, Sales_data&);
	friend ostream& print(ostream&, const Sales_data&);

	//constructor function newly add
	Sales_data() = default; // c++ 11 newly added
	Sales_data(const string& s) :bookNo(s) {}
	//construct funciton initlial list
	Sales_data(const string& s, unsigned n, double p) :bookNo(s),
		units_sold(n),
		revenue(p* n) {}
	Sales_data(istream&);

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


//类的其他特性
class Screen {
public:
	typedef string::size_type pos;
	//using pos = string::size_type;
	Screen() = default;
	Screen(pos h, pos w, char c):height(h), width(w), contents(h*w, c){}
	void some_member() const;
	char get() const {
		return contents[cursor];
	}

	inline char get(pos h, pos w) const;
	Screen& move(pos r, pos c);

private:
	pos cursor = 0;
	pos height= 0;
	pos width = 0;
	string contents;
	mutable size_t access_ctr; 
	size_t non_mutable_access_ctr;

};

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
}
//mutable data member 
//which never be const, even if is is a member in const object
void Screen::some_member() const {
	++access_ctr;
	// ++non_mutable_access_ctr; error:C++ expression must be a modifiable lvalue
}

//类数据成员的初始值
class Window_mgr {
private:
	//in default, a window_mgr included an empty Screen with a standard size 
	vector<Screen> screens{ Screen(24, 80, ' ') };
};

int main()
{
	cout << "Hello CMake." << endl;
	using_Screen();
	return 0;
}
