/*******************************************************
 * @FileName: StringUtils.h
 * @Author: Frodo Cheng
 * @CreatedTime: May 30 2019
 * @Description:
 *		Some std::string opeartion methods.
********************************************************/
#pragma once

#ifdef WIN32
#	include <Windows.h>
#	define	STRAPI	WINAPI
#else
#	define	STRAPI
#endif // WIN32

#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>

/**
 * @Descrition:
 *		template method, object to string.
 * @Param: t of type t, must overload operator<< const method. 
 * @Return: std::string type value.
**/
template<typename T>
std::string ObjectToString(T const& t)
{
	std::ostringstream stream;
	stream << t;
	return stream.str();
}

extern "C" int STRAPI StringSubCount(std::string const& src, std::string const& sub);

extern "C" bool STRAPI StringContains(std::string const& src, std::string const& sub);

extern "C" bool STRAPI StringHasPrefix(std::string const& src, std::string const& prefix);

extern "C" bool STRAPI StringHasSurfix(std::string const & src, std::string const & surfix);

extern "C" std::string& STRAPI StringReplaceAll(std::string & src, std::string const& orgStr, std::string const& repStr);

extern "C" bool STRAPI StringToInt64(int64_t & res, std::string const& src);

extern "C" bool STRAPI StringToDouble(double & res, std::string const& src);

extern "C" bool STRAPI StringToBool(bool & res, std::string const& src);

extern "C" bool STRAPI StringSplit(std::vector<std::string> & outVec, std::string const& src, char delim, bool skipWhiteSpace = true);

extern "C" bool STRAPI StringKeyValueToMap(std::map<std::string, std::string> & outMap, std::string const& src, char pairDelim = ';', char kvDelim = '=');

extern "C" bool STRAPI StringMapToKeyValue(std::string & res, std::map<std::string, std::string> const & m, char pairDelim = ';', char kvDelim = '=');

extern "C" std::string & STRAPI StringTrim(std::string & s);
extern "C" std::string & STRAPI StringTrimLeft(std::string & s);
extern "C" std::string & STRAPI StringTrimRight(std::string & s);

extern "C" std::string & STRAPI StringUppercase(std::string & s);
extern "C" std::string & STRAPI StringLowercase(std::string & s);

/**
 * @Description:
 *     Get GMT Time Stamp as Foramt: 2019-05-30 12:31:02.534+0000
 * @param
 *     dayHourDelim: default value " ", You can pass one your self.
 *     tzPostfix: default value "+0000", Time Zone
**/
std::string STRAPI GetTimeStampGMT(std::string const & dayHourDelim = " ", std::string const& tzPostfix = "+0000");

/**
 * @Description:
 *     Get Local Time Stamp as Foramt: 2019-05-30 20:33:47.939+0800
 * @param
 *     dayHourDelim: default value " ", You can pass one your self.
 *     tzPostfix: default value "+0800", Time Zone
**/
std::string STRAPI GetTimeStampLocal(std::string const & dayHourDelim = " ", std::string const& tzPostfix = "+0800");

/**
 * @Description:
 *     Get GMT Time Stamp as Foramt: Thu May 30 12:33:47 2019
**/
std::string STRAPI GetASCTimeStampGMT();

/**
 * @Description:
 *     Get Local Time Stamp as Foramt: Thu May 30 20:33:47 2019
**/
std::string STRAPI GetASCTimeStampLocal();

/**
 * @Description:
 *     Format string.
 * @param
 *    predictedSize: size of the formatted string you predicted,
 *        if too little, the string will be truncated.
 *        if too large, the memory cannot be alloced, return empty string.
**/
std::string STRAPI StringFormat(int predictedSize, char const* format, ...);

/// just for windows
#ifdef WIN32

#if 0

#include <atlstr.h>
#include <atlconv.h>

ATL::CString StringToCstring(std::string const& s);

std::string CStringToUTF8String(ATL::CString cstr);

#endif

#endif // WIN32


template <typename T>
void StringUtilsTest(T)
{
	std::cout << ObjectToString(std::this_thread::get_id()) << std::endl;
	std::cout << GetTimeStampGMT() << std::endl;
	std::cout << GetTimeStampLocal() << std::endl;
	std::cout << GetASCTimeStampGMT() << std::endl;
	std::cout << GetASCTimeStampLocal() << std::endl;

	std::string s = "HelloWorldHelloWorldHelloWorld";

	std::cout << std::boolalpha << StringHasPrefix(s, "Hello") << std::endl;
	std::cout << std::boolalpha << StringHasSurfix(s, "World") << std::endl;

	std::cout << StringReplaceAll(s, "Hello", "World") << std::endl;

	std::cout << "Find " << s.find("") << std::endl;
	std::cout << std::boolalpha << StringContains(s, "") << std::endl;
	std::cout << std::boolalpha << StringContains("", s) << std::endl;

	test(std::cout, "SayHello!\n");

	std::fstream f;
	f.open("out.log", std::ios::app | std::ios::binary);
	test(f, "SayHello!\n");
	f.close();

	std::cout << StringFormat(32, "%s", "StringFormat\n");
	char bf[2] = { 0 };
	//std::cout << "count " << vsnprintf(bf, 1, "%s", "HelloWorld");
	std::string src = "Hello_Hello_Hello";
	std::string subStr = "Hello";
	std::string::size_type pos = src.find(subStr), subSize = subStr.size();
	int cnt = 0;
	while (pos != std::string::npos)
	{
		cnt++;
		pos = src.find(subStr, pos + subSize);
	}
	std::cout << "count " << cnt << std::endl;
	std::cout << src << std::endl;
	std::cout << "StringSubCount: " << StringSubCount(src, subStr) << std::endl;
}