#pragma once
#include <chrono>
#include <ctime>

std::chrono::system_clock::time_point now()
{
	return std::chrono::system_clock::now();
}

std::string to_string(std::chrono::system_clock::time_point const&start)
{
	std::time_t now_c = std::chrono::system_clock::to_time_t(start);
	std::tm ptm;
	gmtime_s(&ptm, &now_c);
	std::stringstream out;
	out << ptm.tm_hour << "time:" << ptm.tm_min << " min:" << ptm.tm_sec << " sec:";
	return out.str();
}

std::chrono::system_clock::time_point to_time(long day, long time)
{
	std::tm timeinfo = std::tm();

	timeinfo.tm_year = day / 10000;
	timeinfo.tm_mon = (day / 100) % 100;
	timeinfo.tm_mday = day % 100;

	if (100 < time && time < 10000)
	{
		timeinfo.tm_hour = time / 100;
		timeinfo.tm_min = time % 100;
		timeinfo.tm_sec = 0;
	}
	else if (10000 <= time && time < 1000000)
	{
		timeinfo.tm_hour = (time / 10000);
		timeinfo.tm_min = (time / 100) % 100;
		timeinfo.tm_sec = time % 100;
	}
	else if (time < 100)
	{
		timeinfo.tm_hour = 0;
		timeinfo.tm_min = 0;
		timeinfo.tm_sec = time;
	}

	time_t tt = mktime(&timeinfo);
	return std::chrono::system_clock::from_time_t(tt);
}

long to_yymmdd(std::chrono::system_clock::time_point const&now)
{
	struct tm t;
	auto tp = now.time_since_epoch();
	auto tt = std::chrono::system_clock::to_time_t(now);
	localtime_s(&t, &tt);
	return  (t.tm_year + 1900) * 10000 + (t.tm_mon + 1) * 100 + t.tm_mday;
}

