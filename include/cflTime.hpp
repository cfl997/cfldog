#ifndef _CFLTIME_HPP_
#define _CFLTIME_HPP_

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <assert.h>

#include <iostream>
#include <regex>
#include <string>
//#define KeyTimerStr "KeyTimer"
//#define HasKeyTimeStr "HasKeyTime"
static const std::string KeyTimerStr	= "KeyTimer";
static const std::string HasKeyTimeStr	= "HasKeyTime";
static const std::string KeyTimeTypeStr = "KeyTimeType";
static const std::string KeyTimeNumStr	= "KeyTimeNum";

enum class KeyTimeType
{
	KEYTIME_NULL = 0,
	KEYTIME_Week = 1,
	KEYTIME_Mouth = 2,
	KEYTIME_Year = 3,
};

class KeyTimer
{
public:
	KeyTimer() {};
	~KeyTimer() {};
	int getTimeNumByType(KeyTimeType keyTimeType)
	{
		switch (keyTimeType)
		{
		case KeyTimeType::KEYTIME_NULL:
			return 0;
			break;
		case KeyTimeType::KEYTIME_Week:
			return 7;
			break;
		case KeyTimeType::KEYTIME_Mouth:
			return 31;
			break;
		case KeyTimeType::KEYTIME_Year:
			return 365;
			break;
		default:
			break;
		}
		return 0;
	}


	/*
	* add true 为增加，false 为减少
	*/
	std::string getTimeByType(KeyTimeType keyTimeType, int timeNums, bool add = true)
	{
		// 获取当前系统时间的时间戳
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

		// 将时间戳转换为time_t类型
		std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

		int timeTypeNum = getTimeNumByType(keyTimeType);

		// 减去timeNums*keyTimeType的秒数
		auto  differenceTime = (timeTypeNum * 24 * 60 * 60 * timeNums);
		if (add)
			now_time_t += differenceTime;
		else
			now_time_t -= differenceTime;

		// 将time_t类型转换为本地时间
		std::tm* now_local = std::localtime(&now_time_t);

		// 将本地时间格式化为字符串
		std::ostringstream oss;
		oss << std::put_time(now_local, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	bool isHaveValid(const std::string& timeStr)
	{
		// 将生成的时间字符串转换为时间戳
		std::tm tm = {};
		std::istringstream iss(timeStr);
		iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
		std::time_t valid_time_t = std::mktime(&tm);


		// 获取当前系统时间的时间戳
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		// 将时间戳转换为time_t类型
		std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

		return now_time_t > valid_time_t;
	}

	// 将生成的时间字符串转换为时间戳
	std::time_t getTime_tByStr(const std::string& timeStr)
	{
		std::tm tm = {};
		std::istringstream iss(timeStr);
		iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
		std::time_t generated_time_t = std::mktime(&tm);
		return generated_time_t;
	}
private:

};



static int getTimeType(const std::string& str)
{
	// 正则表达式匹配TimeType后面的数字
	std::regex re("TimeType:(\\d+)");
	std::smatch match;
	if (std::regex_search(str, match, re))
	{
		// 返回匹配到的数字
		return std::stoi(match[1]);
	}
	else
	{
		// 没有匹配到，返回默认值0
		return 0;
	}
}

static int getKeyTimeNum(const std::string& str)
{
	// 正则表达式匹配KeyTimeNum后面的数字
	std::regex re("KeyTimeNum:(\\d+)");
	std::smatch match;
	if (std::regex_search(str, match, re))
	{
		// 返回匹配到的数字
		return std::stoi(match[1]);
	}
	else
	{
		// 没有匹配到，返回默认值0
		return 0;
	}
}
static std::string getKeyTimer(const std::string& str)
{
	// 正则表达式匹配KeyTimer后面的日期时间
	std::regex re("KeyTimer:(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2})");
	std::smatch match;
	if (std::regex_search(str, match, re))
	{
		// 返回匹配到的日期时间
		return match[1];
	}
	else
	{
		// 没有匹配到，返回空字符串
		return "";
	}
}

#endif // !_CFLTIME_HPP_
