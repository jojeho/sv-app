#pragma once
#include <app/config.hpp>
#include <test/dvec.hpp>
#include <test/sell.hpp>
#include <test/buy.hpp>

struct rule
{
  dvec::machine mc;
  sell::profit_func sp;
  std::shared_ptr<classifier::base> cls;
  //buy::
  code code;
  long day ;

  bool on;
  int start_time ;
  
  boost::optional<order> operator()(std::list<stock::minute> const&m)
  {
    auto v = mc(code , day , m);
    if(v)
      {
	if((*cls)(*v))
	  {
	    start_time = mc.begin;
	    on = true;
	    return order{ bid_event::buy_order , code};
	  }
      }

    if(on)
      {
	auto s =sp(std::next(std::begin(m) , start_time) ,
	   std::end(m));

	if(s)
	  {
	    on = false;
	    start_time=0;
	    return order{ bid_event::sell_order , code};
	  }
      }

    return boost::optional<order>();
  }
};
