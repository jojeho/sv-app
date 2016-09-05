#include "config.hpp"
#include <app/command.hpp>

const auto equal_day = [](auto const& l , auto const& r)
			{
			  return l.day == r.day && l.time == r.time;
			};

const auto sort_day = [](auto const& l , auto const&r)
		      {
			if(l.day == r.day)
			  {
			    return l.time < r.time;
			  }

			return l.day  < r.day ;
		      };

const std::string temp_code_db = "stock";

void copy()
{
  auto codes = db::select_kospi_200();
  for(auto code : codes)
    {
      auto con = db::code_connection(code , "stock2");
      std::stringstream s;
      s<<" code = "<<code.code;
      std::cout<<s.str()<<std::endl;
      auto _ = db::selector<stock_base>(con , db::query(s.str()));
      std::vector<stock_base> all;
      std::copy(std::begin(_) ,std::end(_) , std::back_inserter(all));
      std::cout<<"source size "<<all.size()<<" ";
      std::sort(std::begin(all) ,std::end(all), sort_day);
      auto last = std::unique(std::begin(all) ,std::end(all) , equal_day);
      all.erase(last , std::end(all));
      std::cout<<"unique size "<<all.size()<<std::endl;
      auto con2 = db::code_connection(code,temp_code_db);
      auto in = db::inserter<stock_base>(con2);
      std::copy(std::begin(all) ,std::end(all) , std::begin(in));
    }
}

int main(int argc , char* argv[])
{
  copy();
  //load_save();

  //select_stock_base();
  //load_stock_code();
  return 0;
}


