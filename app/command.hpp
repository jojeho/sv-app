#pragma once
#include "config.hpp"
#include <jeho/db/mongo.hpp>
#include <boost/hana.hpp>

#include "sc/depot_client.hpp"
#include "db.hpp"
#include "stock_code_hana.hpp"
#include "stock_base_hana.hpp"

std::list<stock_code> kospi_200()
{
  std::list<stock_code> result;
  auto con = db::connection(common_db) ;
  auto s =db::selector<stock_code>(con, db::query(" kospi_200 != 0"));
  std::copy(std::begin(s) , std::end(s) , std::back_inserter(result));
  return result;
}

void load_stock_code()
{
  auto codes =depot::select_stock_code();
  std::cout<<" insert code size "<<codes.size()<<std::endl;
  auto con = db::connection(common_db);
  auto in  = db::inserter<stock_code>(con);
  std::copy(std::begin(codes) , std::end(codes) , std::begin(in));
}

void load_save()
{
  std::string begin ,  end;
  begin ="20150701";
  end = "20150701";
  //db::day_query(begin , end);
  
  auto codes = kospi_200();
  std::cout<<" all size "<<codes.size()<<std::endl;
  int count = 0;
  for(auto const& code : codes)
    {
      try{
	std::cout<<" current code "<<code.code<<std::endl;
	auto con = db::code_connection();
	auto in = db::inserter<stock_base>(con,code);
	auto sbs =depot::select_stock_base(code.code, begin, end);
	std::copy(std::begin(sbs) ,std::end(sbs) , std::begin(in));
	count++;
      }catch(std::exception & e)
	{
	  std::cout<<"fail to code "<<code.code<<" continue"<<std::endl;
	}
    }

  std::cout<<" total update count "<<count<<std::endl;
}



