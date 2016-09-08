#pragma once
#include "config.hpp"
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace future {

  struct minute {
    code code;
    long current_day;
    long time;
    long start_price;
    long high_price;
    long low_price;
    long end_price;
    long volume;
    long money;
    long day_end_price;
    double basis;
    double delta;
    double gamma;
    double theta;

    std::string table_name() const
    {
      return "minute";
    }

    template<typename Archive>
    void serialize(Archive & ar, unsigned int version)
    {
      ar & code;
      ar & low_price;
      ar & high_price;
      ar & start_price;
      ar & end_price;
      ar & volume;
      ar & money;
      ar & current_day;
      ar & time;
      ar & day_end_price;
      ar & basis;
      ar & delta;
      ar & gamma;
      ar & theta;
    }
  };

  struct day
  {
    code code;
    long current_day;
    long start_price;
    long end_price;
    long low_price;
    long high_price;
    long volume;
    long money;
    long fixed_day;
    long fixed_r;
    long rotate;
    long bid_r;
    long last_day;


    std::string table_name() const
    {
      return "day";
    }


    
    template<typename Archive>
    void serialize(Archive & ar, unsigned int version)
    {
      ar & code;
      ar & low_price;
      ar & high_price;
      ar & start_price;
      ar & end_price;
      ar & volume;
      ar & money;
      ar & current_day;
      ar & fixed_day;
      ar & fixed_r;
      ar & rotate;
      ar & bid_r;
      ar & last_day;
    }
  };
}

BOOST_FUSION_ADAPT_STRUCT(
                          future::minute,
                          (code , code)
                          (long , current_day)
                          (long , time)
                          (long , start_price)
                          (long , high_price)
                          (long , low_price)
                          (long , end_price)
                          (long , volume)
                          (long , money)
                          (long , day_end_price)
                          )

BOOST_FUSION_ADAPT_STRUCT(
			  future::day,
			  (code, code)
			  (long, current_day)
			  (long, start_price)
			  (long, high_price)
			  (long, low_price)
			  (long, end_price)
			  (long, volume)
			  (long, money)
			  (long, fixed_day)
			  (double ,fixed_r)
			  (double ,rotate)
			  (double ,bidr_r)
			  (long, last_day)
			  )


