#pragma once
#include "config.hpp"
#include <jeho/db/mongo.hpp>
#include <boost/hana.hpp>

#include "sc/depot_client.hpp"
#include "db.hpp"
#include "stock_code_hana.hpp"
#include "stock_base_hana.hpp"


std::list<stock_code> query_kospi_200()
{
  std::cout<<"load kospi "<<std::endl;
  db::query q("all");
  auto con = std::make_shared<db::connection>("common") ;
  auto s =db::selector<stock_code>(con, q);
  std::list<stock_code> result;
  std::copy_if(std::begin(s) , std::end(s)
	       ,std::back_inserter(result)
	       ,[](auto const&v){ return v.kospi_200 != 0;});
  
  return result;
}

void load_stock_code()
{
  client cl;
  auto codes =cl.select_stock_code();
  std::cout<<" insert code size "<<codes.size()<<std::endl;
  db::query q("all");
  auto con = std::make_shared<db::connection>("common") ;
  auto in = db::inserter<stock_code>(con,q);
  auto it = std::begin(in);
  std::copy(std::begin(codes) , std::end(codes) , it);
}

void load_save()
{
  std::string begin ,  end;

  begin ="20150701";
  end = "20150701";
  client cl;
  auto codes = query_kospi_200();
  std::cout<<" all size "<<codes.size()<<std::endl;
  int count = 0;
  for(auto const& code : codes)
    {
      
      try{
	db::query q("all");
	auto con = std::make_shared<db::code_connection>();
	std::cout<<" current code "<<code.code<<std::endl;
	auto in = db::inserter<stock_base>(con,code.code,q);
	auto it = std::begin(in);
	auto sbs =cl.select_stock_base(code.code, begin, end);
	std::copy(std::begin(sbs) ,std::end(sbs) , it);
	count++;
      }catch(std::exception & e)
	{
	  std::cout<<"fail to code "<<code.code<<" continue"<<std::endl;
	}
    }

  std::cout<<" total update count "<<count<<std::endl;
}



