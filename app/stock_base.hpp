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
			  (long , money))
