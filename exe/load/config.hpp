#pragma once
#include <app/config.hpp>
#include <app/stock_base.hpp>
#include <list>

struct find_stock_base
{
  using result = std::list<stock_base>;
  using args =  boost::hana::tuple<code ,ptime,ptime>;
  result operator()(code const&c
		    ,ptime const&begin
		    ,ptime const& end)
  {
    result r;
    return r;
  }
};


using funcs = boost::hana::tuple<find_stock_base>;
