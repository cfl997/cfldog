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
	* add true Ϊ���ӣ�false Ϊ����
	*/
	std::string getTimeByType(KeyTimeType keyTimeType, int timeNums, bool add = true)
	{
		// ��ȡ��ǰϵͳʱ���ʱ���
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

		// ��ʱ���ת��Ϊtime_t����
		std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

		int timeTypeNum = getTimeNumByType(keyTimeType);

		// ��ȥtimeNums*keyTimeType������
		auto  differenceTime = (timeTypeNum * 24 * 60 * 60 * timeNums);
		if (add)
			now_time_t += differenceTime;
		else
			now_time_t -= differenceTime;

		// ��time_t����ת��Ϊ����ʱ��
		std::tm* now_local = std::localtime(&now_time_t);

		// ������ʱ���ʽ��Ϊ�ַ���
		std::ostringstream oss;
		oss << std::put_time(now_local, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	bool isHaveValid(const std::string& timeStr)
	{
		// �����ɵ�ʱ���ַ���ת��Ϊʱ���
		std::tm tm = {};
		std::istringstream iss(timeStr);
		iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
		std::time_t valid_time_t = std::mktime(&tm);


		// ��ȡ��ǰϵͳʱ���ʱ���
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		// ��ʱ���ת��Ϊtime_t����
		std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

		return now_time_t > valid_time_t;
	}

	// �����ɵ�ʱ���ַ���ת��Ϊʱ���
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
	// ������ʽƥ��TimeType���������
	std::regex re("TimeType:(\\d+)");
	std::smatch match;
	if (std::regex_search(str, match, re))
	{
		// ����ƥ�䵽������
		return std::stoi(match[1]);
	}
	else
	{
		// û��ƥ�䵽������Ĭ��ֵ0
		return 0;
	}
}

static int getKeyTimeNum(const std::string& str)
{
	// ������ʽƥ��KeyTimeNum���������
	std::regex re("KeyTimeNum:(\\d+)");
	std::smatch match;
	if (std::regex_search(str, match, re))
	{
		// ����ƥ�䵽������
		return std::stoi(match[1]);
	}
	else
	{
		// û��ƥ�䵽������Ĭ��ֵ0
		return 0;
	}
}
static std::string getKeyTimer(const std::string& str)
{
	// ������ʽƥ��KeyTimer���������ʱ��
	std::regex re("KeyTimer:(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2})");
	std::smatch match;
	if (std::regex_search(str, match, re))
	{
		// ����ƥ�䵽������ʱ��
		return match[1];
	}
	else
	{
		// û��ƥ�䵽�����ؿ��ַ���
		return "";
	}
}

#endif // !_CFLTIME_HPP_
