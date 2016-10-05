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


    std::string table_name() const
    {
      return "day";
    }

    template<typename Archive>
    void serialize(Archive & ar, unsigned int version)
    {
      ar & code;
      ar & current_day;
      ar & start_price;
      ar & end_price;
      ar & low_price;
      ar & high_price;
      ar & volume;
      ar & money;
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
			  (double , basis)
			  (double , delta)
			  (double , gamma)
			  (double , theta)
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
			  )


