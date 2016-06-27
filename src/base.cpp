#include "base.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	const char *v = "-123.0";

	Attribute_Parser<std::string> str_p;
	std::string r = str_p(v);
	std::cout << r << std::endl; 

	Attribute_Parser<int> int_p;
	int r_ = int_p(v);
	std::cout << r_ << std::endl; 

	Attribute_Parser<unsigned int> uint_p;
	unsigned int ur_ = uint_p(v);
	std::cout << ur_ << std::endl; 

	Attribute_Parser<long> lint_p;
	long l_ = lint_p(v);
	std::cout << l_ << std::endl; 

	Attribute_Parser<unsigned long> ulint_p;
	unsigned long ul_ = ulint_p(v);
	std::cout << ul_ << std::endl; 

	Attribute_Parser<float> lf_p;
	float f_ = lf_p(v);
	std::cout << f_ << std::endl; 

	Attribute_Parser<double> ld_p;
	double ld_ = ld_p(v);
	std::cout << ld_ << std::endl; 

	return 0;
}
