#include <app/db_command.hpp>
#include "../graph/graph.hpp"


#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/variance.hpp>

using namespace boost::accumulators;
namespace tags =  boost::accumulators::tag;
using acc_type = accumulator_set<double, stats<tags::mean,tags::variance > > ;


struct gap
{
  long s;
  long e;
  double profit;
};

BOOST_HANA_ADAPT_STRUCT(gap , s , e , profit);

struct gp
{
  code code;
  long day;
  std::vector<gap> gaps;
};

BOOST_HANA_ADAPT_STRUCT(gp , code , day , gaps);

int limit_size =50;
double min_gap = 0.015;
int warmup = 30;

void out(gp const& r , std::vector<stock_base> const&v = std::vector<stock_base>(0))
{
  std::cout<<r.code<<"  count "<<r.gaps.size()<<std::endl;
  for(auto b : r.gaps)
    {
      std::cout<<"{"<<b.s<<"~"<<b.e<<" "<<b.profit<<"}";
	std::cout<<std::endl;
    }

  if(v.size() != 0)
    {
      data::one r ;
      std::transform(std::begin(v), std::end(v) , std::back_inserter(r),
		     [](auto const&v)
		     {
		       return std::log(v.end_price);
		     });
      draw(r,1);
      std::string msg;
      std::cin>>msg;
    }
  std::cout<<std::endl;
}

using namespace boost::assign;

void insert()
{
  auto codes = db::select_kospi_200();
  auto days = std::make_pair(20160705 , 20160730);
  auto qs = db::make_query(codes , days);

  for(auto q : qs)
    {
      for(auto code : q.codes)
	{
	  auto con = db::code_connection(code);
	  auto con2 = db::connection(common_db);
	  for(auto day : q.days())
	    {
	      std::vector<stock_base> sbs;
	      auto _ = db::selector<stock_base>(con ,q.to_query(day));
	      std::copy(std::begin(_) ,std::end(_) , std::back_inserter(sbs));
	      std::sort(std::begin(sbs),std::end(sbs),[](auto const&l , auto const&r)
			{
			  return l.time < r.time;
			});

	      auto start = std::begin(sbs);
	      auto end = std::end(sbs);
	      auto dis = std::distance(start ,end);

	      if(start == end|| dis < warmup)
		{
		  continue;
		}

	      auto r = gp{ code.code , day};
	      start =std::next(start, warmup);
	      while(start != end)
		{
		  auto next = start;
		  next++;

		  std::pair<long,double> max_gap;
		  max_gap.first = 0;
		  max_gap.second = 0;
		  
		  for(int i = 0; i < limit_size; i++)
		    {
		      if(next == end)
			{
			  break;
			}
		      
		      double gap = (next->end_price - start->end_price)/(double)start->end_price;
		      if(gap > max_gap.second)
			{
			  max_gap.first  = next->time;
			  max_gap.second = gap;
			}
		      next++;
		    }

		  if( max_gap.second > min_gap )
		    {
		      r.gaps += gap { start->time , max_gap.first , max_gap.second};
		    }

		  start++;
		}
	      
	      if(r.gaps.size() != 0)
		{
		  out(r,sbs);
		  db::save(con2 , r);
		}
	    }
	}
    }
}

auto const o = [](auto const&v
		  ,int &count)
{
  out(v);
  auto con = db::code_connection(v.code);
  std::stringstream ss;
  ss<<" day = "<<v.day;
  auto _ = db::selector<stock_base>(con ,db::query(ss.str()));
  data::one eps;
  std::transform(std::begin(_), std::end(_) , std::back_inserter(eps)
		 ,[](auto const&v)
  {
    return v.end_price;
  });

  draw(eps,1);
  std::string msg;
  std::cin>>msg;
  count++;
};

void show()
{
  auto con = db::connection(common_db);
  db::query q("");
  auto _ = db::selector<gp>(con, q);
  int count = 0;
  std::for_each(std::begin(_) , std::end(_) ,std::bind(o , std::placeholders::_1 , std::ref(count)));
  std::cout<<"total count "<<count<<std::endl;
}


  const auto look=[](auto  action)
  {
    auto codes = db::select_kospi_200();
    auto days = std::make_pair(20160705 , 20160730);
    auto qs = db::make_query(codes , days);

    for(auto q : qs)
      {
	for(auto code : q.codes)
	  {
	    auto con = db::code_connection(code);
	    auto con2 = db::connection(common_db);
	    for(auto day : q.days())
	      {
		std::vector<stock_base> sbs;
		auto _ = db::selector<stock_base>(con ,q.to_query(day));
		std::copy(std::begin(_) ,std::end(_) , std::back_inserter(sbs));
		std::sort(std::begin(sbs),std::end(sbs),[](auto const&l , auto const&r)
			  {
			    return l.time < r.time;
			  });
		if(std::begin(sbs) != std::end(sbs))
		  action(sbs);
	      }
	  }
      }
  };

const auto volume =[](std::vector<stock_base> const&sv)
{
  auto begin = std::begin(sv);
  auto next  = std::begin(sv);
  next++;
  auto end = std::end(sv);
  acc_type acc;
  data::one esp;
  esp += std::log(begin->end_price);
  std::for_each(next ,end ,[&](auto const&v)
  {
    auto gap = std::abs((v.end_price - begin->end_price)/(double)begin->end_price);
    acc(gap);
    esp +=std::log((v.end_price + v.start_price)/(double)2);
    begin++;
    //std::cout<<v.end_price<<std::endl;
  });

  auto mm = std::minmax_element(std::begin(sv) , std::end(sv)
				,[](auto const& l
				    ,auto const&r)
  {
    return l.end_price < r.end_price;
  });
  
  double total_gap = (mm.second->end_price  - mm.first->end_price)/double(mm.first->end_price);
  
  std::cout<<"total gap "<<total_gap<<" mean "<<mean(acc)
  <<" margin "<<(mean(acc)/total_gap)
  <<std::endl;

  draw(esp,1);
  std::string msg;
  std::cin>>msg;
};
  
int main(int argc , char* argv[])
{
  look(volume);
  //insert();
  //show();
  return 1;
}
