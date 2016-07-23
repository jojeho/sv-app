#pragma once
#include "config.hpp"
#include <jeho/db/mongo.hpp>
#include "sc/depot_client.hpp"
#include <boost/hana.hpp>
#include "db.hpp"
#include "stock_code_hana.hpp"
#include "stock_base_hana.hpp"


std::list<code> kospi_200()
{
  std::cout<<"load kospi "<<std::endl;
  
  db::query q("all");
  auto s =db::selector<stock_code>(db::connection("common"), q);
  std::list<code> result;

  std::for_each(std::begin(s), std::end(s)
		,[&](auto const&v)
		{
		});
  return result;
}

void load_stock_code()
{
  
  client cl;
  auto codes =cl.select_stock_code();
  for(auto c: codes)
    {
      std::cout<<"code "<<c.code<<std::endl;
    }
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
      std::copy(std::begin(sbs) ,std::end(sbs) , it);
    }
}


