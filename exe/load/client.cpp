#include "config.hpp"
#include <app/command.hpp>

const auto equal_day = [](auto const& l , auto const& r)
			{
			  return l.current_day == r.current_day && l.time == r.time;
			};


const auto sort_day = [](auto const& l , auto const&r)
		      {
			if(l.current_day == r.current_day)
			  {
			    return l.time < r.time;
			  }

			return l.current_day  < r.current_day ;
		      };

const std::string temp_code_db = "stock2";

void backup()
{
  auto codes = db::select_kospi_200();
  //auto codes = load_future_code();
  for(auto code : codes)
    {
      auto con = db::code_connection(code , stock_db);
      std::stringstream s;
      //s<<"all"<<code.code;
      std::cout<<s.str()<<std::endl;
      auto _ = db::selector<stock::minute>(con , db::query("all"));
      std::vector<stock::minute> all;
      std::copy(std::begin(_) ,std::end(_) , std::back_inserter(all));
      std::cout<<"source size "<<all.size()<<" ";

            //std::sort(std::begin(all) ,std::end(all), sort_day);
      //auto last = std::unique(std::begin(all) ,std::end(all) , equal_day);
      //all.erase(last , std::end(all));
      //std::cout<<"unique size "<<all.size()<<std::endl;

      auto con2 = db::code_connection(code,temp_code_db);
      db::remove_table<stock::minute>(con2);
      auto in = db::inserter<stock::minute>(con2);
      std::copy(std::begin(all) ,std::end(all) , std::begin(in));
    }
}

void check()
{

  auto codes = db::select_kospi_200();
  long day = 20160801;
  for(auto code : codes)
    {
      auto con = db::code_connection(code , stock_db);
      std::stringstream s;
      s<<" code = "<<code.code;
	//<<" & current_day = "<<day;
      std::cout<<s.str()<<std::endl;
      auto _ = db::selector<stock::day>(con , db::query(s.str()));
      std::vector<stock::day> all;
      std::copy(std::begin(_) ,std::end(_) , std::back_inserter(all));
      int source_size = all.size();
      std::cout<<"source size "<<all.size()<<" ";

      for(auto b : all)
	{
	  std::cout<<b.current_day<<",";
	}

       std::cout<<std::endl;
      
      //std::sort(std::begin(all) ,std::end(all), sort_day);
      //auto last = std::unique(std::begin(all) ,std::end(all) , equal_day);
      //all.erase(last , std::end(all));

      // if(source_size != all.size())
      // 	{
      // 	  std::cout<<"unique size "<<all.size()<<std::endl;
      // 	}
    }
}

auto split_days =[](std::string begin , std::string end, int size = 5)
{
  std::list<std::pair<std::string,std::string>> result;
  using namespace boost::gregorian;
  using namespace boost::assign;

  //std::cout<<begin<<" "<<end<<std::endl;
  auto first = day_iterator(boost::gregorian::from_undelimited_string(begin));
  auto last  = day_iterator(boost::gregorian::from_undelimited_string(end));
  //++last;
  size =size - 1;

  while(true)
    {
      auto c_first = first;
      for(int i =0 ; i < size ; ++i)
	{
	  if(*first == *last)
	    {
	      break;
	    }

	  ++first;
	}
      result += std::make_pair(to_iso_string(*c_first)
			       ,to_iso_string(*first));

      if(*first == *last)
	{
	  break;
	}

      ++first;
    }

  for(auto b : result)
    {
      std::cout<<b.first<<" "<<b.second<<std::endl;
    }
  return result;
};

int main(int argc , char* argv[])
{
  //load_kospi200();
  //std::string db_name = "test";
  std::string begin = "20160101";
  std::string end   = "20160930";

  auto days = split_days(begin, end,100);

  //remove_stock_table();
  //load_stock_day(stock_db , days);

  
  //remove_future_table();
  load_future_day(future_db , days );


  //load_day(db_name, begin , end);
  //load_future_save(db_name , begin,end);
  //load_day_futrue();

  //check();

  /////backup();
  //load_minute();
  //select_stock_base();
  //load_stock_code();
  return 0;
}


