#pragma once
#include <app/sc/serialize.hpp>
#include <app/sc/trade_client.hpp>
#include <app/order.hpp>
#include <app/stock.hpp>
#include <app/rule.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
namespace bid {

  struct minute
  {
    std::map<code , std::list<stock::minute> > source;
    std::map<code ,rule> rules;
    boost::mutex receive_mtx;
    void operator()(stock::minute const&m)
    {
      boost::lock_guard<boost::mutex> guard(receive_mtx);
      if(m.time >= 900)
	{
	  source[m.code] += m;
	  std::cout<<m.code<<" "<<m.time<<std::endl;
	  auto o = rules[m.code](source[m.code]);
	  if(o)
	    {
	      trade_client c;
	      c.send(*o);
	    }
	}
      else
	{
	  std::cout<<"bfore time "<<m.time<<std::endl;
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
    std::cout<<result.code<<std::endl;
    stock_bid_single(result);
  }
};
