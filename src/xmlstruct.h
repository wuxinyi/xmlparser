#ifndef _XMLSTRUCT_H_
#define _XMLSTRUCT_H_

#include <map>
#include <vector>
#include <string>
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace xml 
{
  // test 配置
	struct TEST {
		struct XMLPARSER
		{
			struct TEST1
			{
				int t1v;
				int t2v;
				int t3v;
				bool parse(const XMLElement *child);
			};  

			std::map<int, TEST1> test1;
      std::string version;     

			bool parse(const XMLElement* child);      
		}xmlparser;
		bool parse(const char *filename);
	};
  extern TEST test;
}

#endif
