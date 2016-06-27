#include "xmlstruct.h"
#include "tinyxml2.h"
#include <iostream>

namespace xml
{
	TEST test; 
}



namespace xml {
	bool TEST::parse(const char *filename)
	{
		XMLDocument doc;
		int ret = 0;
		if((ret = doc.LoadFile(filename)) != XML_SUCCESS) {
			std::cout << "加载失败:" << ret <<std::endl;
			return false;
		}
		XMLElement *ele = NULL;
		ele = doc.FirstChildElement("xmlparser");
		if (!ele) return false;
	  xmlparser.parse(ele); 

    return true;
	} 

	bool TEST::XMLPARSER::parse(const XMLElement* child)
	{
		if (!child) return false;
		int ret = 0;

		//先解析属性
		const XMLAttribute* attri = NULL;
		attri = child->FindAttribute("version");
		if (attri) {
			version = attri->Value();
		} 

		//再解析节点
		const XMLElement *ele_begin = NULL;
    const XMLElement *ele_end   = NULL;
		ele_begin = child->FirstChildElement("test1");
		ele_end   = child->LastChildElement("test1");
		if (!ele_begin || !ele_end) return false;
		while(ele_begin <= ele_end)
		{
			TEST1 temp_;
			if (temp_.parse(ele_begin)) {
				test1.insert(std::make_pair<int, TEST1>(temp_.t1v, temp_));  
			}
			++ ele_begin;
		}
		return true;
	}

	bool TEST::XMLPARSER::TEST1::parse(const XMLElement* child)
	{
		if (!child) return false;
		int ret = 0;

		//先解析属性
		const XMLAttribute* attri = NULL;
		attri = child->FindAttribute("t1v");
		if (attri) {
			t1v = (int)atoi(attri->Value());
		}  

		attri = child->FindAttribute("t2v");
		if (attri) {
			t2v = (int)atoi(attri->Value());
		}  

		attri = child->FindAttribute("t3v");
		if (attri) {
			t3v = (int)atoi(attri->Value());
		} 

		return true; 
	}
}
