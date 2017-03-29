#pragma once
#include "config.hpp"
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace stock {

  struct minute {
    std::string code;
    long current_day;
    long time;
    long start_price;
    long high_price;
    long low_price;
    long end_price;
    long volume;
    long money;
    long day_end_price;

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

    }
  };

  struct day
  {
    std::string code;
    long current_day;
    long start_price;
    long end_price;
    long low_price;
    long high_price;
    long volume;
    long money;
    long fixed_day;
    double fixed_r;
    double rotate;
    double bid_r;
    long day_end_price;
    long bid;
    long ask;

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
      ar & day_end_price;
      ar & bid;
      ar & ask;
    }
  };
}

BOOST_FUSION_ADAPT_STRUCT(
			  stock::minute,
			  (std::string, code)
			  (long, current_day)
			  (long, time)
			  (long, start_price)
			  (long, high_price)
			  (long, low_price)
			  (long, end_price)
			  (long, volume)
			  (long, money)
			  (long, day_end_price)
			  )

BOOST_FUSION_ADAPT_STRUCT(
			  stock::day,
			  (std::string, code)
			  (long, current_day)
			  (long, start_price)
			  (long, high_price)
			  (long, low_price)
			  (long, end_price)
			  (long, volume)
			  (long, money)
			  (long, fixed_day)
			  (double, fixed_r)
			  (double, rotate)
			  (double ,bidr_r)
			  (long , day_end_price)
                          (long , bid)
                          (long , ask)
			  )

// const auto bind_end_price_log=[](auto const&v)
// {
//   return std::log(v.end_price);
// };

const auto  bind_from_last_day=[](auto const& v)
{
  return (v.end_price -  v.day_end_price)/double(v.day_end_price);
};


const auto bind_end_price=[](auto const&v)
{
  return v.end_price;
};

const auto bind_low_price=[](auto const&v)
{
  return v.low_price;
};

const auto bind_high_price=[](auto const&v)
{
  return v.high_price;
};

const auto bind_start_price=[](auto const&v)
{
  return v.start_price;
};


auto get_volume =[](auto const&v)
{
  return v.volume;
};

auto lt_time =[](auto const&l , auto const&r)
{
  return l.time < r.time;
};

auto lt_time_with =[](auto const&l , auto const&r)
{
  return l.time < r;
};

auto gt_time_with =[](auto const&l , auto const&r)
{
  return l.time > r;
};

auto get_end_price =[](auto const&v)
{
  return v.end_price;
};

auto get_current_day =[](auto const&v)
{
  return v.current_day;
};



auto eq_current_day
=[](auto const& i , auto const& day)
{
  return i.current_day == day;
};

auto eq_time
=[](auto const&i , auto const& time)
{
  return i.time == time;
};
