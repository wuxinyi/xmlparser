#include "tinyxml2.h"
#include "template.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace tinyxml2;

extern int example_4();
extern int example_3();

int main()
{
	if (!xml::xmlparser.load())
	{
		std::cout << "加载失败" << std::endl;
		return 1;
	}

	for (auto &v : xml::xmlparser.test1)
	{
		std::cout << v.second.t1v << " " <<  v.second.t2v << " " << v.second.t3v << std::endl;
	}

	for (auto &v : xml::xmlparser.test2)
	{
		std::cout << v.id << " " <<  v.name << std::endl;
	}

  std::cout << xml::xmlparser.test3.num1 << " " << xml::xmlparser.test3.num2 << " " << xml::xmlparser.test3.num3 << std::endl;
}
