#pragma once 
#include "stock_base.hpp"


BOOST_HANA_ADAPT_STRUCT(stock_base ,
			code ,
			day ,
			time ,
			start_price,
			high_price,
			low_price ,
			end_price,
			volume ,
			money);
