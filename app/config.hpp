#pragma once
#include <chrono>
#include <string>
#include <boost/date_time.hpp>

//using ptime = std::chrono::system_clock::time_point;
using code = std::string;
using date = boost::gregorian::date;

const std::string  db_connection_string ="mongodb://localhost:27017";
const std::string  common_db = "common";


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

static std::string base_host()
{
  return  "192.168.10.101";
  //return base_host_;
}

static std::string base_port()
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





