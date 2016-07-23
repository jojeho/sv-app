#pragma once
#include "stock_code.hpp"

BOOST_HANA_ADAPT_STRUCT(stock_code ,
			code,
			full_code,
                        name,
			market,
			kospi_200);

