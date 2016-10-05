#pragma once
#include <string>
#include "config.hpp"
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


struct stock_code
{
  std::string code ;
  std::string  full_code;
  std::string name;
  int  market;
  int  kospi_200;
  
  template<typename Archive>
  void serialize(Archive & ar, unsigned int version)
  {
	  ar & code;
	  ar & full_code;
	  ar & name;
	  ar & market;
	  ar & kospi_200;
  }
};

auto bind_code =[](auto c)
		{
		  return c.code;
		};


auto bind_f_code =[](auto c)
		{
		  return  "F" + c.code;
		};


BOOST_FUSION_ADAPT_STRUCT(
			  stock_code ,
			  (code , code)
			  (std::string , full_code)
			  (std::string , name)
			  (int , market)
			  (int , kospi_200)
			  )

