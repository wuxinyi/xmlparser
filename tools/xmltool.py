#!/usr/bin/env python
# -*- coding: utf-8 -*-

from xml.dom import minidom as xmlparser
import os

TemplateHead = """ 
//--------------------------------------------------- 
// 此文件由工具自动生成，请勿修改 
//---------------------------------------------

#include <vector>
#include <string>
#include <map>
#include <utility>
#include "../tinyxml2/tinyxml2.h"
using namespace tinyxml2;

"""
XML_Dir = './xml/'

class XmlParser:
	""" this class will be used to parse xml template, then generator c++ source code for loading xml file into memory (or LuaState)"""
	def __init__(self, xmldirname, cppdirname):
		self.dirname_  = xmldirname
		self.xmlfiles_ = []
		self.cppdir    = cppdirname
		self.currxmlpath = ''
		self.curr_template_path = ''

	def get_xml_files(self, path):
		"""get xml files in a folser"""
		fielnum = 0
		list_ = os.listdir(self.dirname_)  #列出目录下的所有文件和目录
		for line in list_:
			filepath = os.path.join(path,line)
			# 如果是目录则递归遍历
			if os.path.isdir(filepath):
				self.get_xml_files(filepath)
				continue
   
			if line.endswith(".xml"):
				filepath = os.path.join(path,line)
				self.xmlfiles_.append(filepath)

	def dump(self):
		for line in self.xmlfiles_:
			print(line)			

	def dump_str2cppfile(self,cppfile,blank,content):
		"""write content to cppfile with format of n blank ahead""" 
		ct = ''
		while blank > 0:
			ct += ' '
			blank -= 1
		ct += content + '\n'
	 	try:	
			cppfile.write(ct)
		except:
			assert(0)

	def parse_label(self, label):
		"""parse key word of xml template"""
		label = label.strip() #remove blank 
		# types map 
		values = {
			'string':'std::string ',
			'int':'int',
			'unsigned int':'unsigned int',
			'long':'long',
			'unsigned long':'unsigned long',
			'long long int': 'long long int',
			'unsigned long long int':'unsigned long long int',
			'float':'float',
			'double':'double',
		}	 

		if values.has_key(label):
			return values[label]
		else:
			return ""

	def parse_value(self, v, vtype):
		vtype = vtype.strip()
		values = {
  	'string':'std::string(',
  	'int':'(int)atoi(',
  	'unsigned int':'(unsigned int)atoi(',
  	'long':'(long)atol(',
  	'unsigned long':'(unsigned long)atol(',
  	'long long int': '(long long int)atol(',
  	'unsigned long long int':'(unsigned long long int)atol(',
  	'float':'(float)atof(',
  	'double':'(double)atof(',
		}

		if values.has_key(vtype):
			temp_content = 'this->' + v + ' = ' + values[vtype] + 'attri->Value());'
			return temp_content
		else:
			return '' 

	def parse_and_generator_cppfiles(self,templatepath,cppdirpath):
		"""parse xml and generator cpp files"""
		path_slice = templatepath.split('/')
		path_slice = path_slice[-1]
		if not path_slice.endswith('.xml'):
			print("error file name:" + path_slice)
			return
		filename = path_slice     #name of the xml file	
	 	idx = path_slice.find('.xml')
		path_slice = path_slice[0:idx]

		self.currxmlpath = XML_Dir + filename #the path of xml file
		self.curr_template_path = templatepath
		print(self.currxmlpath)
	
		doc   = xmlparser.parse(templatepath) 
		root  = doc.documentElement
		blank = 0
		cppfilename = cppdirpath + path_slice + '.h' 
		cppfile = open(cppfilename,'w')	

		# for node in root.childNodes:
		#	if node.nodeType == node.ELEMENT_NODE:
		self.dump_str2cppfile(cppfile,blank,TemplateHead)
		self.dump_str2cppfile(cppfile,blank, 'namespace xml {')
		self.parse_node(root, cppfile, blank+2, 1)					
		self.dump_str2cppfile(cppfile,blank,'static struct ' + root.nodeName.upper() + ' ' + root.nodeName + ';')
		self.dump_str2cppfile(cppfile,blank,'}')
		cppfile.close()

	def parse_node_generator_parsefunc(self,node,cppfile,blank):
		"""generator ::parse(node *) function for every xml struct"""
		node_name = node.nodeName
		self.dump_str2cppfile(cppfile, blank, 'bool parse(const XMLElement* child)')
		self.dump_str2cppfile(cppfile, blank,'{')
		self.dump_str2cppfile(cppfile, blank+2,'if (!child) return false;')
		self.dump_str2cppfile(cppfile, blank+2, 'const XMLAttribute* attri = NULL;')
	  #parse attribute firstly 	
		attribute_keys = node.attributes.keys()
		for attribute_key in attribute_keys:
			attribute      = node.attributes[attribute_key]
			attribute_name  = attribute.name.strip() 
			attribute_value = attribute.value.strip() 
			if attribute_name == 'container_' or attribute_name == 'key_':
				continue
			temp_content = 'attri = child->FindAttribute("' + attribute_name + '");'
			self.dump_str2cppfile(cppfile, blank+2, temp_content)
			self.dump_str2cppfile(cppfile, blank+2, 'if (attri)')
			self.dump_str2cppfile(cppfile, blank+2, '{')	
			temp_content = self.parse_value(attribute_name, attribute_value)
			self.dump_str2cppfile(cppfile, blank+4,temp_content)
			self.dump_str2cppfile(cppfile, blank+2, '}\n') 

		#then parse children nodes
		for subnode in node.childNodes:
		#recursive parse
			if subnode.nodeType != subnode.ELEMENT_NODE:
				continue
			container_type = subnode.getAttribute('container_')
			if container_type == 'map':
				container_name       = subnode.nodeName.strip()
				container_key_name   = subnode.getAttribute('key_')
				container_key_type   = subnode.getAttribute(container_key_name)
					
				self.dump_str2cppfile(cppfile, blank+2, '{')		
				self.dump_str2cppfile(cppfile, blank+4,'const XMLElement *ele_begin = NULL;')
				self.dump_str2cppfile(cppfile, blank+4,'const XMLElement *ele_end = NULL;')
				temp_content = 'ele_begin = child->FirstChildElement("'+ subnode.nodeName + '");'
				self.dump_str2cppfile(cppfile, blank+4, temp_content)
				temp_content = 'ele_end   = child->LastChildElement("' + subnode.nodeName + '");'
				self.dump_str2cppfile(cppfile, blank+4, temp_content)				
 				self.dump_str2cppfile(cppfile, blank+4, 'while(ele_begin <= ele_end)')
				self.dump_str2cppfile(cppfile, blank+4, '{')
				temp_content = 'struct ' + container_name.upper() + ' temp_;';
				self.dump_str2cppfile(cppfile, blank+6, temp_content)			
				self.dump_str2cppfile(cppfile, blank+6, 'if (temp_.parse(ele_begin))')
				self.dump_str2cppfile(cppfile, blank+6, '{')
				temp_content = 'this->'+subnode.nodeName+'.insert(std::pair<' + self.parse_label(container_key_type) + ', struct ' + container_name.upper() + '>(' + 'temp_.'+ container_key_name + ', temp_));'
				self.dump_str2cppfile(cppfile, blank+8, temp_content)
				self.dump_str2cppfile(cppfile, blank+6, '}')					 
				self.dump_str2cppfile(cppfile, blank+6, '++ ele_begin;')	
				self.dump_str2cppfile(cppfile, blank+4, '}')
				self.dump_str2cppfile(cppfile, blank+2, '}\n') 
			elif container_type == 'vector':
				container_name = subnode.nodeName.strip()
				self.dump_str2cppfile(cppfile, blank+2, '{')		
				self.dump_str2cppfile(cppfile, blank+4,'const XMLElement *ele_begin = NULL;')
				self.dump_str2cppfile(cppfile, blank+4,'const XMLElement *ele_end = NULL;')
				temp_content = 'ele_begin = child->FirstChildElement("'+ subnode.nodeName + '");'
				self.dump_str2cppfile(cppfile, blank+4, temp_content)
				temp_content = 'ele_end   = child->LastChildElement("' + subnode.nodeName + '");'
				self.dump_str2cppfile(cppfile, blank+4, temp_content)				
 				self.dump_str2cppfile(cppfile, blank+4, 'while(ele_begin <= ele_end)')
				self.dump_str2cppfile(cppfile, blank+4, '{')
				temp_content = 'struct ' + container_name.upper() + ' temp_;';
				self.dump_str2cppfile(cppfile, blank+6, temp_content)			
				self.dump_str2cppfile(cppfile, blank+6, 'if (temp_.parse(ele_begin))')
				self.dump_str2cppfile(cppfile, blank+6, '{')
				temp_content = 'this->'+subnode.nodeName+'.push_back(temp_);'
				self.dump_str2cppfile(cppfile, blank+8, temp_content)
				self.dump_str2cppfile(cppfile, blank+6, '}')					 
				self.dump_str2cppfile(cppfile, blank+6, '++ ele_begin;')	
				self.dump_str2cppfile(cppfile, blank+4, '}')
				self.dump_str2cppfile(cppfile, blank+2, '}\n') 
			else:
				container_name = subnode.nodeName.strip()
				self.dump_str2cppfile(cppfile, blank+2, '{')
				self.dump_str2cppfile(cppfile, blank+4,'const XMLElement *ele_begin = NULL;')
				temp_content = 'ele_begin = child->FirstChildElement("'+ subnode.nodeName + '");'
				self.dump_str2cppfile(cppfile, blank+4, temp_content)
				self.dump_str2cppfile(cppfile, blank+4, 'if (ele_begin)')
				self.dump_str2cppfile(cppfile, blank+4, '{')
				temp_content  = 'this->'+container_name + '.parse(ele_begin);'
				self.dump_str2cppfile(cppfile, blank+6, temp_content)
				self.dump_str2cppfile(cppfile, blank+4, '}')
				self.dump_str2cppfile(cppfile, blank+2, '}\n')

		self.dump_str2cppfile(cppfile, blank+2, 'return true;')
		self.dump_str2cppfile(cppfile, blank, '}')
		
	def generate_load_function(self, cppfile, filepath, nodename, blank):
		temp_content = 'bool load()'
		self.dump_str2cppfile(cppfile, blank, temp_content)
		self.dump_str2cppfile(cppfile,blank,'{')
		self.dump_str2cppfile(cppfile,blank+2,'XMLDocument doc;')
		self.dump_str2cppfile(cppfile,blank+2,'int ret = 0;')
		temp_content = 'if((ret = doc.LoadFile("' + filepath + '")) != XML_SUCCESS) {'
		self.dump_str2cppfile(cppfile, blank+2, temp_content)	
		self.dump_str2cppfile(cppfile, blank+4, 'return false;')
		self.dump_str2cppfile(cppfile,blank+2,'}')
		self.dump_str2cppfile(cppfile, blank+2, 'XMLElement *ele = NULL;')
		self.dump_str2cppfile(cppfile, blank+2,'ele = doc.FirstChildElement("' + nodename + '");')
		self.dump_str2cppfile(cppfile, blank+2, 'if (!ele) return false;')
		self.dump_str2cppfile(cppfile, blank+2, 'return this->parse(ele);')
		self.dump_str2cppfile(cppfile,blank,'}')
		self.dump_str2cppfile(cppfile,blank,'\n')
		
	def parse_node(self, node, cppfile, blank, isroot = 0):
		"""parse xml node: parse attribute first, then children nodes"""
		#dump struct name
		node_name = node.nodeName
		self.dump_str2cppfile(cppfile, blank, 'struct ' + node_name.upper());	 	 			
		self.dump_str2cppfile(cppfile, blank, '{')

    # if root node, generate load function
		if isroot == 1:
			if self.currxmlpath == "":
				return
			self.generate_load_function(cppfile, self.currxmlpath, node_name, blank + 2)

    # parse attribute first
		attribute_keys = node.attributes.keys()
		for attribute_key in attribute_keys:
			attribute      = node.attributes[attribute_key]
			attribute_name = attribute.name.strip()  
			if attribute_name == 'container_' or attribute_name == 'key_':
				continue
			prefix = self.parse_label(attribute.value) + ' ' + attribute.name + ';'  	
			self.dump_str2cppfile(cppfile, blank + 2, prefix)

   # parse nodes
		for subnode in node.childNodes:
		#recursive parse
			if subnode.nodeType != subnode.ELEMENT_NODE:
				continue
			self.parse_node(subnode,cppfile,blank+2)
	 		 # if it's a container, then generator container variable, otherwise normal variable
			container_type = subnode.getAttribute('container_')
			if container_type == 'map':
				container_key_name   = subnode.getAttribute('key_')
				container_key_name = container_key_name.strip()
				container_key_type   = subnode.getAttribute(container_key_name)
				container_value_type = 'struct ' + subnode.nodeName.upper()	
				final_label = 'std::map<' + self.parse_label(container_key_type) + ',' + container_value_type + '> ' + subnode.nodeName + ';\n'
				self.dump_str2cppfile(cppfile, blank+2, final_label)
			elif container_type == 'vector':
				container_value_type = 'struct ' + subnode.nodeName.upper()
				final_label = 'std::vector<' + container_value_type + '> ' + subnode.nodeName + ';\n'
				self.dump_str2cppfile(cppfile, blank+2, final_label)
			else:
				container_value_type = 'struct ' + subnode.nodeName.upper()
				final_label = container_value_type + ' ' + subnode.nodeName + ';\n'
				self.dump_str2cppfile(cppfile, blank+2, final_label)				

		self.parse_node_generator_parsefunc(node,cppfile,blank+2)
		self.dump_str2cppfile(cppfile, blank, '};')
	
if __name__ == '__main__':
	dirname = '../xml/template/'
	parser = XmlParser(dirname,"./")
	parser.get_xml_files(dirname)
	parser.dump()

	for line in parser.xmlfiles_:
		parser.parse_and_generator_cppfiles(line,'../src/')

