#pragma once 
#include "stock.hpp"


BOOST_HANA_ADAPT_STRUCT(stock::minute ,
			code ,
			current_day ,
			time ,
			start_price,
			high_price,
			low_price ,
			end_price,
			volume ,
			money,
			day_end_price
			);



BOOST_HANA_ADAPT_STRUCT(stock::day ,
			code ,
			current_day ,
			start_price,
			high_price,
			low_price ,
			end_price,
			volume ,
			money,
			fixed_day,
			fixed_r,
			rotate,
			bid_r,
			last_day
			);
