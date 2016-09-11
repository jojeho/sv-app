#pragma once
#include <app/sc/serialize.hpp>
#include <app/sc/trade_client.hpp>
#include <app/order.hpp>
#include <app/stock.hpp>
#include <app/rule.hpp>

namespace bid {

  struct minute
  {
    std::map<code , std::list<stock::minute> > source;
    std::map<code ,rule> rules;

    void operator()(stock::minute const&m)
    {
      source[m.code] += m;
      auto o = rules[m.code](source[m.code]);
      if(o)
	{
	  trade_client c;
	  c.send(*o);
	}
    }
  
  };

}

bid::minute stock_bid_single;

struct bid_handler
{
  void operator()(std::vector<char> const& data)
  {
    std::string text(std::begin(data),std::end(data));
    auto result = in<stock::minute>(text);
    stock_bid_single(result);
  }
};
