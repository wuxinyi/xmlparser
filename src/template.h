 
//--------------------------------------------------- 
// 此文件由工具自动生成，请勿修改 
//---------------------------------------------

#include <vector>
#include <string>
#include <map>
#include <utility>
#include "../tinyxml2/tinyxml2.h"
using namespace tinyxml2;


namespace xml {
  struct XMLPARSER
  {
    bool load()
    {
      XMLDocument doc;
      int ret = 0;
      if((ret = doc.LoadFile("./xml/template.xml")) != XML_SUCCESS) {
        return false;
      }
      XMLElement *ele = NULL;
      ele = doc.FirstChildElement("xmlparser");
      if (!ele) return false;
      return this->parse(ele);
    }
    

    std::string  version;
    struct TEST1
    {
      std::string  t3v;
      int t1v;
      int t2v;
      bool parse(const XMLElement* child)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("t3v");
        if (attri)
        {
          this->t3v = std::string(attri->Value());
        }

        attri = child->FindAttribute("t1v");
        if (attri)
        {
          this->t1v = (int)atoi(attri->Value());
        }

        attri = child->FindAttribute("t2v");
        if (attri)
        {
          this->t2v = (int)atoi(attri->Value());
        }

        return true;
      }
    };
    std::map<int,struct TEST1> test1;

    struct TEST2
    {
      int id;
      std::string  name;
      bool parse(const XMLElement* child)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("id");
        if (attri)
        {
          this->id = (int)atoi(attri->Value());
        }

        attri = child->FindAttribute("name");
        if (attri)
        {
          this->name = std::string(attri->Value());
        }

        return true;
      }
    };
    std::vector<struct TEST2> test2;

    struct TEST3
    {
      int num1;
      long num2;
      std::string  num3;
      bool parse(const XMLElement* child)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("num1");
        if (attri)
        {
          this->num1 = (int)atoi(attri->Value());
        }

        attri = child->FindAttribute("num2");
        if (attri)
        {
          this->num2 = (long)atol(attri->Value());
        }

        attri = child->FindAttribute("num3");
        if (attri)
        {
          this->num3 = std::string(attri->Value());
        }

        return true;
      }
    };
    struct TEST3 test3;

    bool parse(const XMLElement* child)
    {
      if (!child) return false;
      const XMLAttribute* attri = NULL;
      attri = child->FindAttribute("version");
      if (attri)
      {
        this->version = std::string(attri->Value());
      }

      {
        const XMLElement *ele_begin = NULL;
        const XMLElement *ele_end = NULL;
        ele_begin = child->FirstChildElement("test1");
        ele_end   = child->LastChildElement("test1");
        while(ele_begin <= ele_end)
        {
          struct TEST1 temp_;
          if (temp_.parse(ele_begin))
          {
            this->test1.insert(std::pair<int, struct TEST1>(temp_.t1v, temp_));
          }
          ++ ele_begin;
        }
      }

      {
        const XMLElement *ele_begin = NULL;
        const XMLElement *ele_end = NULL;
        ele_begin = child->FirstChildElement("test2");
        ele_end   = child->LastChildElement("test2");
        while(ele_begin <= ele_end)
        {
          struct TEST2 temp_;
          if (temp_.parse(ele_begin))
          {
            this->test2.push_back(temp_);
          }
          ++ ele_begin;
        }
      }

      {
        const XMLElement *ele_begin = NULL;
        ele_begin = child->FirstChildElement("test3");
        if (ele_begin)
        {
          this->test3.parse(ele_begin);
        }
      }

      return true;
    }
  };
static struct XMLPARSER xmlparser;
}
