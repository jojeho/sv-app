#pragma once
std::chrono::system_clock::time_point to_time(long day, long time)
{
	init();

	using namespace boost::assign;

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