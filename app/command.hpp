#pragma once
#include "config.hpp"
#include <jeho/db/mongo.hpp>
#include <boost/hana.hpp>
#include <thread>
#include "sc/depot_client.hpp"
#include "db.hpp"
#include "stock_code_hana.hpp"
#include "stock_base_hana.hpp"
#include "db_command.hpp"


void load_stock_code()
{
  auto codes =depot::select_stock_code();
  std::cout<<" insert code size "<<codes.size()<<std::endl;
  //auto con = db::connection(common_db);
  //auto in  = db::inserter<stock_code>(con);
  //std::copy(std::begin(codes) , std::end(codes) , std::begin(in));
}


////A0033920 20160801

auto const load=[](auto begin  , auto end,auto code)
{
  try{
    std::cout<<"current code "<<code.code
	     <<" day "<<begin<<" "<<end
	     <<std::endl;
    auto sbs =depot::select_stock_base(code.code, begin, end);
    auto con = db::code_connection(code);
    db::inserter<stock_base> in(con);
    std::copy(std::begin(sbs) ,std::end(sbs) , std::begin(in));
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    //count++;
  }catch(std::exception & e)
    {
      std::cout<<"fail to code "<<code.code<<" continue"<<std::endl;
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(3s);
    }

};

auto const load_day=[](auto begin  , auto end,auto code)
{
  try{
    std::cout<<"current code "<<code.code
	     <<" day "<<begin<<" "<<end
	     <<std::endl;
    auto sbs =depot::select_stock_base_day(code.code, begin, end);
    auto con = db::code_connection(code);
    db::inserter<stock_base> in(con);
    std::copy(std::begin(sbs) ,std::end(sbs) , std::begin(in));
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    //count++;
  }catch(std::exception & e)
    {
      std::cout<<"fail to code "<<code.code<<" continue"<<std::endl;
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(3s);
    }

};

auto load_code=[](auto f_day, auto codes)
{
  int size = 5;
  for(auto const& code : codes)
    {
      auto day = f_day;
      for(int i = 0 ; i < 6 ; ++i)
	{
	  auto begin = std::to_string(day);
	  auto end   = std::to_string(day+size);
	  std::cout<<begin<<" "<<end<<std::endl;
	  load(begin  , end  , code);
	  day = day+size+1;
	}

    }
};

void load_save()
{
  std::string begin ,  end;
  ///begin ="20160701";
  //end  = "20160731";
  //db::day_query(begin , end);
  auto codes = db::select_kospi_200();

  //auto f = std::find_if(std::begin(codes) ,std::end(codes) , [](auto const&v){ return v.code == "A033920";});
  //yef++;
  //codes.erase(std::begin(codes) , f);
  //std::cout<<std::begin(codes)->code<<std::endl;
  //exit(0);
  
  std::cout<<"all size "<<codes.size()<<std::endl;
  int count = 0;
  std::vector<int> days(31);
  std::iota(std::begin(days) , std::end(days) , 20160601);

  long f_day = 20160801;
  int size = 30;

  auto first = std::begin(codes);
  auto next   = std::next(first, size);

  int sum =0;
  while(first != std::end(codes))
    {
      decltype(codes) t_codes;
      std::copy(first , next  , std::back_inserter(t_codes));

      std::cout<<t_codes.size()<<std::endl;

      sum += t_codes.size();

      f_day = 20160601;
      load_code(f_day ,t_codes);

      f_day = 20160701;

      load_code(f_day ,t_codes);

      f_day = 20160801;

      load_code(f_day ,t_codes);

      first = next;

      if(first == std::end(codes))
	{
	  break;
	}
      
      if(std::distance(first , std::end(codes)) > size)
	{
	  next = std::end(codes);
	}
      else
	{
	  next = std::next(first , size);
	}
    }

  std::cout<<" total update count "<<sum<<std::endl;
}

//std::list<stock_base> select_stock_base(stock_code  const& sc, long day)
std::list<stock_base> select_stock_base()
{
  auto codes = db::select_kospi_200();
  int count = 0;
  std::list<stock_base> result;
  for(auto sc : codes)
  {
    //std::cout<<sc.code<<std::endl;
    auto con = db::code_connection(sc);
    auto _ = db::selector<stock_base>(con ,db::query( ""));
    int c = 0;
    std::for_each(std::begin(_) , std::end(_) , [&](auto const&v)
		  {
		    //std::cout<<v.start_price<<std::endl;
		    c++;
		  });
    if(c != 0)
      {
	count++;
      }
    else
      {
	std::cout<<" no code "<<std::endl;
      }
  }

  std::cout<<"leave "<<std::endl;
  return result;
}

auto print = [](stock_base sv)
{
  
};

#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
void test()
{
  auto codes = db::select_kospi_200();
  auto sc = *std::begin(codes);
  auto con = db::code_connection(sc);
  auto select = db::selector<stock_base>(con ,db::query( ""));
  using namespace boost;
  using namespace boost::range;
  auto end = boost::end(select);
  //  using namespace boost::adaptors;
  for(auto c : select)
    {
      
    }
}
