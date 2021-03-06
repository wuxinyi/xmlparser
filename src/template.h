 
//----------------------------------------------------------------------
// 此文件由工具自动生成，请勿修改 
// this file is generated by xmltool, so don't change by yourself
//----------------------------------------------------------------------
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "tinyxml2.h"
#include "attribute_parser.h"
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
using namespace tinyxml2;


namespace xml {
  //XML-->CPP STRUCT
  //this class can load xmlfiles to cpp struct and load them into computer memory
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
    

    std::string version;
    struct TEST1
    {
      std::string t3v;
      int t1v;
      int t2v;
      bool parse(const XMLElement* child)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("t3v");
        if (attri)
        {
          this->t3v= Attribute_Parser<std::string>()(attri->Value());
        }

        attri = child->FindAttribute("t1v");
        if (attri)
        {
          this->t1v= Attribute_Parser<int>()(attri->Value());
        }

        attri = child->FindAttribute("t2v");
        if (attri)
        {
          this->t2v= Attribute_Parser<int>()(attri->Value());
        }

        return true;
      }
    };
    std::map<int,struct TEST1> test1;
    typedef std::map<int,struct TEST1>::iterator TEST1_It;
    typedef std::map<int,struct TEST1>::const_iterator TEST1_ConstIt;

    struct TEST2
    {
      int id;
      std::string name;
      struct TESTN
      {
        int id;
        std::string name;
        bool parse(const XMLElement* child)
        {
          if (!child) return false;
          const XMLAttribute* attri = NULL;
          attri = child->FindAttribute("id");
          if (attri)
          {
            this->id= Attribute_Parser<int>()(attri->Value());
          }

          attri = child->FindAttribute("name");
          if (attri)
          {
            this->name= Attribute_Parser<std::string>()(attri->Value());
          }

          return true;
        }
      };
      std::map<int,struct TESTN> testn;
      typedef std::map<int,struct TESTN>::iterator TESTN_It;
      typedef std::map<int,struct TESTN>::const_iterator TESTN_ConstIt;

      bool parse(const XMLElement* child)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("id");
        if (attri)
        {
          this->id= Attribute_Parser<int>()(attri->Value());
        }

        attri = child->FindAttribute("name");
        if (attri)
        {
          this->name= Attribute_Parser<std::string>()(attri->Value());
        }

        {
          const XMLElement *ele_begin = NULL;
          const XMLElement *ele_end = NULL;
          ele_begin = child->FirstChildElement("testn");
          ele_end   = child->LastChildElement("testn");
          while(ele_begin)
          {
            if (strcmp(ele_begin->Name(),"testn") != 0) {
              ele_begin = ele_begin->NextSiblingElement();
              continue;
            }
            struct TESTN temp_;
            if (temp_.parse(ele_begin))
            {
              this->testn.insert(std::pair<int, struct TESTN>(temp_.id, temp_));
            }
            if (ele_begin == ele_end) {
              break;
            }
            ele_begin = ele_begin->NextSiblingElement();
          }
        }

        return true;
      }
    };
    std::vector<struct TEST2> test2;
    typedef std::vector<struct TEST2>::iterator TEST2_It;
    typedef std::vector<struct TEST2>::const_iterator TEST2_ConstIt;

    struct TEST3
    {
      int num1;
      long num2;
      std::string num3;
      struct TEST3N
      {
        int id;
        bool parse(const XMLElement* child)
        {
          if (!child) return false;
          const XMLAttribute* attri = NULL;
          attri = child->FindAttribute("id");
          if (attri)
          {
            this->id= Attribute_Parser<int>()(attri->Value());
          }

          return true;
        }
      };
      std::vector<struct TEST3N> test3n;
      typedef std::vector<struct TEST3N>::iterator TEST3N_It;
      typedef std::vector<struct TEST3N>::const_iterator TEST3N_ConstIt;

      bool parse(const XMLElement* child)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("num1");
        if (attri)
        {
          this->num1= Attribute_Parser<int>()(attri->Value());
        }

        attri = child->FindAttribute("num2");
        if (attri)
        {
          this->num2= Attribute_Parser<long>()(attri->Value());
        }

        attri = child->FindAttribute("num3");
        if (attri)
        {
          this->num3= Attribute_Parser<std::string>()(attri->Value());
        }

        {
          const XMLElement *ele_begin = NULL;
          const XMLElement *ele_end = NULL;
          ele_begin = child->FirstChildElement("test3n");
          ele_end   = child->LastChildElement("test3n");
          while(ele_begin)
          {
            if (strcmp(ele_begin->Name(),"test3n") != 0) {
              ele_begin = ele_begin->NextSiblingElement();
              continue;
            }
            struct TEST3N temp_;
            if (temp_.parse(ele_begin))
            {
              this->test3n.push_back(temp_);
            }
            if (ele_begin == ele_end) {
              break;
            }
            ele_begin = ele_begin->NextSiblingElement();
          }
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
        this->version= Attribute_Parser<std::string>()(attri->Value());
      }

      {
        const XMLElement *ele_begin = NULL;
        const XMLElement *ele_end = NULL;
        ele_begin = child->FirstChildElement("test1");
        ele_end   = child->LastChildElement("test1");
        while(ele_begin)
        {
          if (strcmp(ele_begin->Name(),"test1") != 0) {
            ele_begin = ele_begin->NextSiblingElement();
            continue;
          }
          struct TEST1 temp_;
          if (temp_.parse(ele_begin))
          {
            this->test1.insert(std::pair<int, struct TEST1>(temp_.t1v, temp_));
          }
          if (ele_begin == ele_end) {
            break;
          }
          ele_begin = ele_begin->NextSiblingElement();
        }
      }

      {
        const XMLElement *ele_begin = NULL;
        const XMLElement *ele_end = NULL;
        ele_begin = child->FirstChildElement("test2");
        ele_end   = child->LastChildElement("test2");
        while(ele_begin)
        {
          if (strcmp(ele_begin->Name(),"test2") != 0) {
            ele_begin = ele_begin->NextSiblingElement();
            continue;
          }
          struct TEST2 temp_;
          if (temp_.parse(ele_begin))
          {
            this->test2.push_back(temp_);
          }
          if (ele_begin == ele_end) {
            break;
          }
          ele_begin = ele_begin->NextSiblingElement();
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

  //XML-->LUATABLE
  //this class load xml file into LuaState, we can use config for example "xml.ta.tb.tc" in lua files
  struct LUA_XMLPARSER
  {
    void doLoad2luaState(lua_State * L)
    {
      if (NULL == L)
      {
        return;
      }
      this->currL = L;
      this->load();
    }

    bool load()
    {
      XMLDocument doc;
      int ret = 0;
      if((ret = doc.LoadFile("./xml/template.xml")) != XML_SUCCESS) {
        return false;
      }
      bool ret_ = false;
      XMLElement *ele = NULL;
      ele = doc.FirstChildElement("xmlparser");
      if (!ele) return false;
      lua_getglobal(this->currL, "xml");
      if (!lua_istable(this->currL, -1))
      {
        lua_pop(this->currL, 1);
        lua_newtable(this->currL);
        lua_setglobal(this->currL, "xml");
        lua_getglobal(this->currL, "xml");
        if (!lua_istable(this->currL,-1))
        {
          lua_pop(this->currL,1);
          return false;
        }
      }
      lua_pushstring(this->currL,"xmlparser");
      lua_newtable(this->currL);
      ret_ = this->parse(ele, this->currL);
      lua_settable(this->currL, -3);
      lua_pop(this->currL, 1);
      return ret_;
    }

    bool parse(const XMLElement* child, lua_State * const L)
    {
      if (!child) return false;
      const XMLAttribute* attri = NULL;
      attri = child->FindAttribute("version");
      if (attri)
      {
        lua_pushstring(L,"version");
        lua_pushstring(L, Attribute_Parser<std::string>()(attri->Value()).c_str());
        lua_settable(L,-3);
      }

      {
        const XMLElement *ele_begin = NULL;
        const XMLElement *ele_end = NULL;
        ele_begin = child->FirstChildElement("test1");
        ele_end   = child->LastChildElement("test1");
        int id = 0;
        while(ele_begin)
        {
          if (strcmp(ele_begin->Name(),"test1") != 0) {
            ele_begin = ele_begin->NextSiblingElement();
            continue;
          }
          if (id == 0) {
            lua_pushstring(L,"test1");
            lua_newtable(L);
          }
          attri = ele_begin->FindAttribute("t1v");
          if (attri) {
            lua_pushinteger(L, Attribute_Parser<int>()(attri->Value()));
            lua_newtable(L);
            //recursive parse lua table!
            this->test1.parse(ele_begin, L);
            lua_settable(L, -3);
          }
          if (ele_begin == ele_end) {
            lua_settable(L,-3);
            break;
          }
          ele_begin = ele_begin->NextSiblingElement();
          ++ id;
        }
      }

      {
        const XMLElement *ele_begin = NULL;
        const XMLElement *ele_end = NULL;
        ele_begin = child->FirstChildElement("test2");
        ele_end   = child->LastChildElement("test2");
        int id = 0;
        while(ele_begin)
        {
          if (strcmp(ele_begin->Name(),"test2") != 0) {
            ele_begin = ele_begin->NextSiblingElement();
            continue;
          }
          if (id == 0) {
            lua_pushstring(L,"test2");
            lua_newtable(L);
          }
          lua_pushinteger(L,id+1);
          lua_newtable(L);
          //recursive parse lua table!
          this->test2.parse(ele_begin, L);
          lua_settable(L, -3);
          if (ele_begin == ele_end) {
            lua_settable(L,-3);
            break;
          }
          ele_begin = ele_begin->NextSiblingElement();
          ++ id;
        }
      }

      {
        const XMLElement *ele_begin = NULL;
        ele_begin = child->FirstChildElement("test3");
        if (ele_begin)
        {
            lua_pushstring(L,"test3");
            lua_newtable(L);
            this->test3.parse(ele_begin, L);
            lua_settable(L,-3);
        }
      }

      return true;
    }

    struct LUA_TEST1
    {
      bool parse(const XMLElement* child, lua_State * const L)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("t3v");
        if (attri)
        {
          lua_pushstring(L,"t3v");
          lua_pushstring(L, Attribute_Parser<std::string>()(attri->Value()).c_str());
          lua_settable(L,-3);
        }

        attri = child->FindAttribute("t1v");
        if (attri)
        {
          lua_pushstring(L,"t1v");
          lua_pushinteger(L, Attribute_Parser<int>()(attri->Value()));
          lua_settable(L,-3);
        }

        attri = child->FindAttribute("t2v");
        if (attri)
        {
          lua_pushstring(L,"t2v");
          lua_pushinteger(L, Attribute_Parser<int>()(attri->Value()));
          lua_settable(L,-3);
        }

        return true;
      }

    };
    struct LUA_TEST1 test1;

    struct LUA_TEST2
    {
      bool parse(const XMLElement* child, lua_State * const L)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("id");
        if (attri)
        {
          lua_pushstring(L,"id");
          lua_pushinteger(L, Attribute_Parser<int>()(attri->Value()));
          lua_settable(L,-3);
        }

        attri = child->FindAttribute("name");
        if (attri)
        {
          lua_pushstring(L,"name");
          lua_pushstring(L, Attribute_Parser<std::string>()(attri->Value()).c_str());
          lua_settable(L,-3);
        }

        {
          const XMLElement *ele_begin = NULL;
          const XMLElement *ele_end = NULL;
          ele_begin = child->FirstChildElement("testn");
          ele_end   = child->LastChildElement("testn");
          int id = 0;
          while(ele_begin)
          {
            if (strcmp(ele_begin->Name(),"testn") != 0) {
              ele_begin = ele_begin->NextSiblingElement();
              continue;
            }
            if (id == 0) {
              lua_pushstring(L,"testn");
              lua_newtable(L);
            }
            attri = ele_begin->FindAttribute("id");
            if (attri) {
              lua_pushinteger(L, Attribute_Parser<int>()(attri->Value()));
              lua_newtable(L);
              //recursive parse lua table!
              this->testn.parse(ele_begin, L);
              lua_settable(L, -3);
            }
            if (ele_begin == ele_end) {
              lua_settable(L,-3);
              break;
            }
            ele_begin = ele_begin->NextSiblingElement();
            ++ id;
          }
        }

        return true;
      }

      struct LUA_TESTN
      {
        bool parse(const XMLElement* child, lua_State * const L)
        {
          if (!child) return false;
          const XMLAttribute* attri = NULL;
          attri = child->FindAttribute("id");
          if (attri)
          {
            lua_pushstring(L,"id");
            lua_pushinteger(L, Attribute_Parser<int>()(attri->Value()));
            lua_settable(L,-3);
          }

          attri = child->FindAttribute("name");
          if (attri)
          {
            lua_pushstring(L,"name");
            lua_pushstring(L, Attribute_Parser<std::string>()(attri->Value()).c_str());
            lua_settable(L,-3);
          }

          return true;
        }

      };
      struct LUA_TESTN testn;

    };
    struct LUA_TEST2 test2;

    struct LUA_TEST3
    {
      bool parse(const XMLElement* child, lua_State * const L)
      {
        if (!child) return false;
        const XMLAttribute* attri = NULL;
        attri = child->FindAttribute("num1");
        if (attri)
        {
          lua_pushstring(L,"num1");
          lua_pushinteger(L, Attribute_Parser<int>()(attri->Value()));
          lua_settable(L,-3);
        }

        attri = child->FindAttribute("num2");
        if (attri)
        {
          lua_pushstring(L,"num2");
          lua_pushinteger(L, Attribute_Parser<long>()(attri->Value()));
          lua_settable(L,-3);
        }

        attri = child->FindAttribute("num3");
        if (attri)
        {
          lua_pushstring(L,"num3");
          lua_pushstring(L, Attribute_Parser<std::string>()(attri->Value()).c_str());
          lua_settable(L,-3);
        }

        {
          const XMLElement *ele_begin = NULL;
          const XMLElement *ele_end = NULL;
          ele_begin = child->FirstChildElement("test3n");
          ele_end   = child->LastChildElement("test3n");
          int id = 0;
          while(ele_begin)
          {
            if (strcmp(ele_begin->Name(),"test3n") != 0) {
              ele_begin = ele_begin->NextSiblingElement();
              continue;
            }
            if (id == 0) {
              lua_pushstring(L,"test3n");
              lua_newtable(L);
            }
            lua_pushinteger(L,id+1);
            lua_newtable(L);
            //recursive parse lua table!
            this->test3n.parse(ele_begin, L);
            lua_settable(L, -3);
            if (ele_begin == ele_end) {
              lua_settable(L,-3);
              break;
            }
            ele_begin = ele_begin->NextSiblingElement();
            ++ id;
          }
        }

        return true;
      }

      struct LUA_TEST3N
      {
        bool parse(const XMLElement* child, lua_State * const L)
        {
          if (!child) return false;
          const XMLAttribute* attri = NULL;
          attri = child->FindAttribute("id");
          if (attri)
          {
            lua_pushstring(L,"id");
            lua_pushinteger(L, Attribute_Parser<int>()(attri->Value()));
            lua_settable(L,-3);
          }

          return true;
        }

      };
      struct LUA_TEST3N test3n;

    };
    struct LUA_TEST3 test3;

    lua_State *currL;
  };
  static struct LUA_XMLPARSER lua_xmlparser;
}
