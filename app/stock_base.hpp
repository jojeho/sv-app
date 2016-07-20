#pragma once
#include "config.hpp"
#include <boost/hana.hpp>

struct stock_base {
  BOOST_HANA_DEFINE_STRUCT(stock_base,
			   (std::string , code),
			   (long ,start_price),
			   (long, high_price),
			   (long, low_price),
			   (long, end_price),
			   (long, trading_volume),
			   (long, trading_money),
			   (ptime, time)
			   );
};



