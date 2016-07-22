#pragma once
#include <chrono>
#include <string>

struct stock_base
{
	long low_price;
	long high_price;
	long start_price;
	long end_price;
	long volume;
	long money;
	long day;
	long time;

	template<typename Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar & low_price;
		ar & high_price;
		ar & start_price;
		ar & end_price;
		ar & volume;
		ar & money;
		ar & day;
		ar & time;
	}

};

struct stock_query
{
	std::string code;
	long begin;
	long end;
	template<typename Archive>
	void serialize(Archive &ar, unsigned int version)
	{
		ar & code;
		ar & begin;
		ar & end;
	}
};
