#pragma once
#include "config.hpp"
#include <jeho/db/mongo.hpp>
#include "daishin/depot_client.hpp"
#include "daishin/time.hpp"
#include "db.hpp"


std::list<code> kospi_200()
{
  std::cout<<"load kospi "<<std::endl;
	db::query q("all");
	auto s =db::selector<stock_code_data>(db::connection("common"), q);
	std::list<code> result;

	std::for_each(std::begin(s), std::end(s)
		       ,[&](auto const&v)
		      {
			//std::cout<<v.code<<" kind "<<v.kospi_200<<std::endl;
			//if(v.kospi_200 == 1)
			  {
			    result.push_back(v.code);
			  }
		       });
	return result;
}

void load_save()
{
  std::string begin ,  end;

  begin ="20150701";
  end = "20150705";
  
  client cl;
  auto codes = kospi_200();
  for(auto const& code : codes)
    {
      db::query q("all");
      auto in = db::inserter<stock_base>(db::connection(code),q);
      auto it = std::begin(in);
      auto sbs =cl.select_stock_base(code, begin, end);
      std::list<stock_base> tfs;
      std::transform(std::begin(sbs), std::end(sbs),std::back_inserter(tfs)
		     ,[](auto const&v)
		     {
		       stock_base sb;
		       sb.time = to_time(v.day ,v.time);
		       sb.low_price = v.low_price;
		       sb.high_price = v.high_price;
		       sb.start_price = v.start_price;
		       sb.end_price = v.end_price;
		       sb.volume = v.volume;
		       sb.money = v.money;
		       return sb;
		     });
      std::copy(std::begin(tfs) ,std::end(tfs) , it);
    }
}


