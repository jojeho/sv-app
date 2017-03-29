#pragma once
#include "config.hpp"
#include <jeho/db/mongo.hpp>
#include <boost/hana.hpp>
#include <thread>
#include "sc/depot_client.hpp"
#include "db.hpp"
#include "stock_code_hana.hpp"
#include "stock_hana.hpp"
#include "future_hana.hpp"
#include "db_command.hpp"


void load_stock_code()
{
  auto codes =depot::select_stock_code();
  std::cout<<" insert code size "<<codes.size()<<std::endl;
  auto con = db::connection(common_db);
  auto in  = db::inserter<stock_code>(con);
  std::copy(std::begin(codes) , std::end(codes) , std::begin(in));
}

std::list<stock_code> load_future_code()
{
  auto codes =depot::select_future_code();
  std::cout<<" insert code size "<<codes.size()<<std::endl;

  for(auto c : codes)
    {
      std::cout<<c.code<<" "<<c.name
	       <<" "<<c.full_code
	       <<std::endl;
    }
  
  return codes;
}

std::list<std::string> load_future_code_only()
{
  auto all_codes = load_future_code();
  std::list<std::string> codes;
  std::transform(std::begin(all_codes)
		 ,std::end(all_codes)
		 ,std::back_inserter(codes)
		 ,bind_code);
  return codes;
}

auto const load_stock_day=[](auto db_name , std::list<std::pair<std::string,std::string>> const& days )
{
  //auto codes=db::select_kospi_200_only_code();
  auto codes=db::select_all_only_code();
  codes.push_back(KOSPI_CODE);//KOSPI_CODE;);
  for(auto code : codes)
    {
      auto f_day = std::begin(days);
      while(f_day != std::end(days))
	{
	  auto begin = (f_day->first);
	  auto end   = (f_day->second);
	  try{

	    std::cout<<"current code "<<code
		     <<" day "<<begin<<" "<<end
		     <<std::endl;
	    	    
            
	    auto sbs =depot::select_stock_day(code, begin, end);
	    auto con = db::code_connection(code,db_name);
	    db::inserter<stock::day> in(con);

	    for(auto b :sbs)
	      {
		std::cout<<b.current_day<<",";
	      }

	    std::cout<<std::endl<<std::endl;
	    std::copy(std::rbegin(sbs) ,std::rend(sbs) , std::begin(in));
	  }catch(std::exception & e)
	    {
	      std::cout<<"fail to code "<<code<<" continue"<<std::endl;
	      using namespace std::chrono_literals;
	      std::this_thread::sleep_for(3s);
	    }

	  using namespace std::chrono_literals;
	  std::this_thread::sleep_for(3s);
	  //count++;
	  f_day++;

	}
    }
};

auto const load_future_day=[](std::string db_name
			      ,std::list<std::pair<std::string,std::string>> const& days
			      )
{
  auto all_codes = load_future_code_only();
  for(auto code : all_codes)
    {
      auto f_code = "F" + code;
      auto f_day = std::begin(days);
      while(f_day != std::end(days))
	{
	  auto begin = (f_day->first);
	  auto end   = (f_day->second);
	  try{

	    std::cout<<"current code "<<code
		     <<" day "<<begin<<" "<<end
		     <<std::endl;
	    	    
	    auto sbs =depot::select_future_day(code, begin, end);

	    for(auto & b : sbs)
	      {
		b.code = f_code;
	      }

	    auto con = db::code_connection(f_code,db_name);
	    db::inserter<future::day> in(con);
	    std::copy(std::rbegin(sbs) ,std::rend(sbs) , std::begin(in));
	    using namespace std::chrono_literals;
	    std::this_thread::sleep_for(1s);
	    //count++;
	  }catch(std::exception & e)
	    {
	      std::cout<<"fail to code "<<code<<" continue"<<std::endl;
	      using namespace std::chrono_literals;
	      std::this_thread::sleep_for(1s);
	    }

	  f_day++;
	}
    }

};

void load_stock_minute(std::list<std::pair<std::string,std::string>> const& days)
{
  auto codes = db::select_kospi_200_only_code();
  //codes.clear();
  codes.push_back(KOSPI_CODE);
  //codes.resize(30);
  
  int count = 0;
  int sum =0;
  auto first = std::begin(codes);
  while(first != std::end(codes))
    {
      auto code = *first;
      auto f_day = std::begin(days);
      while(f_day != std::end(days))
	{
	  auto begin = (f_day->first);
	  auto end   = (f_day->second);
	  
	  try{
	    std::cout<<"current code "<<code
		     <<" day "<<begin<<" "<<end
		     <<std::endl;
	    auto sbs =depot::select_stock_min(code, begin, end);
	    auto con = db::code_connection(code,minute_db);
	    db::inserter<stock::minute> in(con);
            if(sbs.size() !=0)
              {
                sum++;
              }
	    std::copy(std::rbegin(sbs) ,std::rend(sbs) , std::begin(in));
	    using namespace std::chrono_literals;
	    std::this_thread::sleep_for(1s);
	    //count++;
	  }catch(std::exception & e)
	    {
	      std::cout<<"fail to code "<<code<<" continue"<<std::endl;
	      using namespace std::chrono_literals;
	      std::this_thread::sleep_for(1s);
	    }
	  f_day++;	  
	}

      first++;
    }

  std::cout<<" total update stock count "<<sum<<std::endl;
}


void load_future_minute(std::string db_name
			,std::list<std::pair<std::string,std::string>>const& days
			)
{
  auto codes = load_future_code_only();
  std::cout<<"all size "<<codes.size()<<std::endl;

  for(auto const& code : codes)
    {
      auto  f_day = std::begin(days);
      auto  l_day = std::end(days);
      while(f_day != l_day)
	{
	  auto begin = f_day->first;
	  auto end   = f_day->second;
	  std::cout<<begin<<" "<<end<<std::endl;
	  
	  try{
	    std::cout<<"current code "<<code
		     <<" day "<<begin<<" "<<end
		     <<std::endl;
	    auto sbs =depot::select_future_min(code, begin, end);
	    auto f_code = "F" + code;
	    auto con = db::code_connection(f_code,db_name);
	    for(auto b :sbs)
	      {
		std::cout<<b.time<<",";
	      }

	    std::cout<<std::endl<<std::endl;
	    std::cout<<"load size "<<sbs.size()<<std::endl;
	    db::inserter<future::minute> in(con);
	    std::copy(std::rbegin(sbs) ,std::rend(sbs) , std::begin(in));
	    using namespace std::chrono_literals;
	    std::this_thread::sleep_for(1s);
	    //count++;
	  }catch(std::exception & e)
	    {
	      std::cout<<"fail to code "<<code<<" continue"<<std::endl;
	      using namespace std::chrono_literals;
	      std::this_thread::sleep_for(1s);
	    }

	  f_day++;
	}
    }
}

void remove_stock_table()
{
  auto all_codes=db::select_kospi_200_only_code();
  for(auto code : all_codes)
    {
      auto con = db::code_connection(code,stock_db);
      try
	{
	  db::remove_table<stock::day>(con);

	}catch(std::exception & e)
	{
	  std::cout<<"no remove"<<std::endl;
	}
    }

}

void remove_future_table()
{
  auto all_codes = load_future_code_only();
  for(auto code : all_codes)
    {
      auto f_code = "F" +code;
      auto con = db::code_connection(f_code,future_db);

      try
	{
	  db::remove_table<future::day>(con);

	}catch(std::exception & e)
	{
	  std::cout<<"no remove"<<std::endl;
	}

    }
}


#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
void test()
{
  auto codes = db::select_kospi_200();
  auto sc = *std::begin(codes);
  auto con = db::code_connection(sc,stock_db);
  auto select = db::selector<stock::minute>(con ,db::query( ""));
  using namespace boost;
  using namespace boost::range;
  auto end = boost::end(select);
  //  using namespace boost::adaptors;
  for(auto c : select)
    {
      
    }
}
