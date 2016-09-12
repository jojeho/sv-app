#pragma once 
#include "future.hpp"


BOOST_HANA_ADAPT_STRUCT(future::minute ,
			code ,
			current_day ,
			time ,
			start_price,
			high_price,
			low_price ,
			end_price,
			volume ,
			money,
			day_end_price,
			basis,
			delta,
			gamma,
			theta
			);



BOOST_HANA_ADAPT_STRUCT(future::day ,
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
			bid_r
			);
