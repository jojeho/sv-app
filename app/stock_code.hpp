#pragma noce
#include <string>
#include "config.hpp"
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


struct stock_code
{
  std::string code ;
  std::string  full_code;
  int  market;
  int  kospi_200;
};

BOOST_FUSION_ADAPT_STRUCT(
			  stock_code ,
			  (code , code)
			  (std::string , code)
			  (std::string , full_code)
			  (int , market)
			  (int , kospi_200)
			  )

