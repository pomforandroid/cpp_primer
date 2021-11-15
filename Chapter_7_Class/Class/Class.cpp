// Class.cpp : Defines the entry point for the application.
//

#include "Class.h"

using namespace std;

struct Sales_data {
	// new member: about the operator of Sales_data object
	// when call total.isbn() like calling Sales_data::isbn(&total)
	// the compiler is responsible for passing the address of 'total' to the implicit parameter 'this' of isbn
	// so when we use bookNo in isbn, it actually use this->bookNo
	// const: it's role to modify the type of implicit 'this' pointer
	// it mean that the type fot 'this' is 'sales_data * const'
	// 表示this是一个指向常量的指针，称之为常量成员函数
	string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
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





void use_improved_Sales_data(){
	Sales_data total;
	if (read(cin, total)) {
		Sales_data trans;
		while (read(cin, trans)) {
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else {
				print(cout, total) << endl; //output result
				total = trans;
			}
		}
		print(cout, total) << endl;
	}
	else {
		cerr << "No data>!" << endl;
	}

}

int main()
{
	cout << "Hello CMake." << endl;
	return 0;
}
