#include "tinyxml2.h"
#include "template.h"
#include <stdio.h>
#include <iostream>
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
using namespace std;
using namespace tinyxml2;

int main()
{
	if (!xml::xmlparser.load())
	{
		std::cout << "加载失败" << std::endl;
		return 1;
	}

	std::cout << "------------------------- C++ ------------------------------------" << std::endl;
	for (auto &v : xml::xmlparser.test1)
	{
		std::cout << v.second.t1v << " " <<  v.second.t2v << " " << v.second.t3v << std::endl;
	}

	for (auto &v : xml::xmlparser.test2)
	{
		std::cout << v.id << " " <<  v.name << std::endl;
    std::cout << "------" << std::endl;
		for(xml::XMLPARSER::TEST2::TESTN_ConstIt it = v.testn.cbegin(); it != v.testn.cend(); ++it)
		{
			std::cout << it->second.id << " " << it->second.name << std::endl << std::endl;
		}
	}
	std::cout << xml::xmlparser.test3.num1 << " " << xml::xmlparser.test3.num2 << " " << xml::xmlparser.test3.num3 << std::endl;

	std::cout << "----------------------------LUA---------------------------------------" << std::endl;
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
  xml::lua_xmlparser.doLoad2luaState(L);	
	luaL_dofile(L, "./luadir/test.lua");

	/*XMLDocument doc;
	int ret = 0;
	if((ret = doc.LoadFile("./xml/template.xml")) != XML_SUCCESS) {
		std::cout << "error" << std::endl;
		return false;
	}

	const XMLElement *ele = NULL;
	ele = doc.FirstChildElement("xmlparser");
	const XMLAttribute* attri = NULL;
  attri = ele->FindAttribute("version"); 
	std::cout << attri->Value() << std::endl;

	const XMLElement *node=ele->FirstChildElement("test2"); 
	const XMLElement *node_end=ele->LastChildElement("test2");
	while(true)
	{
		if (strcmp(node->Name(), "test2") != 0) 
		{
			node = node->NextSiblingElement();
			continue;
		}
		std::cout << node->Name() << std::endl;
		const XMLAttribute* attri = NULL;
		attri = node->FindAttribute("id"); 
		std::cout << attri->Value() << std::endl;
		attri = node->FindAttribute("name"); 
		std::cout << attri->Value() << std::endl;
		if (node == node_end) break;
		node = node->NextSiblingElement();
	}*/

	return 0;
}
