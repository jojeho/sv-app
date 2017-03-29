#pragma once
#include <chrono>
#include <string>
#include <boost/date_time.hpp>

//using ptime = std::chrono::system_clock::time_point;
//using code = std::string;
//using date = boost::gregorian::date;

const std::string  db_connection_string ="mongodb://localhost:27017";
const std::string  common_db = "common";
const std::string  stock_db = "stock";
const std::string  minute_db = "minute";
const std::string  future_db = "future";
const std::string  rtime_db = "rtime";
const std::string  rule_db = "rule";
const std::string  vec_db = "vec";
const std::string  stats_db = "stats";
const std::string  KOSP_FUTURE_CODE = "F10100";
const std::string  KOSPI_CODE ="U001";

enum bid_event{ buy_order , sell_order};

static std::string load_host()  
{
  return  "192.168.10.100";
  // return load_host_;
}

static std::string load_port()
{
  return "10001";
  // return load_port_;
}

static std::string rtime_host()
{
  return  "192.168.10.101";
  //return base_host_;
}

static std::string rtime_port()
{
  return "10000";
  //return base_port_;
}


static std::string trade_host()
{
  return  "192.168.10.100";
  //return base_host_;
}

static std::string trade_port()
{
  return "12001";
  //return base_port_;
}


static std::string bid_host()
{
  return  "192.168.10.101";
  //return base_host_;
}

static std::string bid_port()
{
  return "9000";
  //return base_port_;
}


struct period
{
  long first;
  long second;
  period(long b, long e):first(b) ,second(e)
  {}
};

std::ostream& operator<<(std::ostream& os , period const&p)
{
  os<<p.first<<" "<<p.second;
  return os;
}


