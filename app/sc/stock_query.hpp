#pragma once
#include <chrono>
#include <string>


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

