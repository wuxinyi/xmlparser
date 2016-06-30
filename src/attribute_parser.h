#ifndef _BASE_H_
#define _BASE_H_

#include  <string>
#include	<stdlib.h>

using namespace std;

template <typename T>
struct Attribute_Parser
{
	T emptyV()
	{
		return T(0);
	}

	inline T operator()(const char *strValue)
	{
		return emptyV();
	}
};  


// 特化处理  const char*
	template <>
const char * Attribute_Parser<const char *>::emptyV()
{
	return "";
}

	template <>
const char * Attribute_Parser<const char *>::operator()(const char *strValue)
{
	if (strValue == NULL)
		return emptyV();
	return strValue;
}


// std::string
	template <>
std::string Attribute_Parser<std::string>::emptyV()
{
	return "";
}

	template <>
std::string Attribute_Parser<std::string>::operator()(const char *strValue)
{
	if (strValue == NULL)
		return emptyV();
	return strValue;
}

// int, long, unsigned int, unsigned long
	template<>
int Attribute_Parser<int>::operator()(const char *strValue)
{
	return atoi(strValue);
}

	template <>
unsigned int Attribute_Parser<unsigned int>::operator()(const char *strValue)
{
	return atoi(strValue);
}

	template<>
long Attribute_Parser<long>::operator()(const char *strValue)
{
	return atol(strValue);
}

	template <>
unsigned long Attribute_Parser<unsigned long>::operator()(const char *strValue)
{
	return atol(strValue);
}

//float double
	template<>
float Attribute_Parser<float>::operator()(const char *strValue)
{
	return atof(strValue);
}

	template<>
double Attribute_Parser<double>::operator()(const char *strValue)
{
	return atof(strValue);
}

#endif
