#pragma once
#include "config.hpp"
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct stock_base {
  code code;
  long day;
  long time;
  long start_price;
  long high_price;
  long low_price;
  long end_price;
  long volume;
  long money;
  long day_end_price;
  long last_day;

  template<typename Archive>
  void serialize(Archive & ar, unsigned int version)
  {
    ar & code ;
    ar & low_price;
    ar & high_price;
    ar & start_price;
    ar & end_price;
    ar & volume;
    ar & money;
    ar & day;
    ar & time;
    ar & day_end_price;
	ar & last_day;
  }
};

BOOST_FUSION_ADAPT_STRUCT(
			  stock_base,
			  (code , code)
			  (long , day)
			  (long , time)
			  (long , start_price)
			  (long , high_price)
			  (long , low_price)
			  (long , end_price)
			  (long , volume)
			  (long , money)
			  (long , day_end_price)
	(long , last_day)
			  )


const auto bind_end_price_log=[](auto const&v)
{
  return std::log(v.end_price);
};

const auto bind_end_price=[](auto const&v)
{
  return v.end_price;
};
