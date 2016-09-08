#pragma once
#include <boost/assign.hpp>
#include <boost/optional.hpp>
#include "db.hpp"
#include "stock_code_hana.hpp"
#include "stock_hana.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_serialize.hpp>

namespace db {

  using namespace boost::assign;
  const std::string kospi_200 = "kospi_200";
  boost::optional<stock_code> find_stock_code(std::string name)
  {
    std::stringstream s;
    s<<" code = "<<name<<"";
    auto con = db::connection(common_db);
    return db::find<decltype(con),stock_code>(con , db::query(s.str()));
  }

  std::list<stock_code> select_kospi_200()
  {
    std::list<stock_code> result;
    auto con = db::connection(common_db) ;
    auto s =db::selector<stock_code>(con, db::query(" kospi_200 != 0"));
    std::copy(std::begin(s) , std::end(s) , std::back_inserter(result));
    return result;
  }

  struct code_range
  {
    std::list<stock_code> codes_;
    code_range(std::string const& type )
    {
      if(type == kospi_200)
	{
	  codes_ = select_kospi_200();
	}
      else
	{
	  auto code = find_stock_code(type);
	  if(!code)
	    {
	      std::cout<<"fail to find "<<type<<std::endl;
	    }
	  codes_.push_back(*code);
	}
    }

    std::list<stock_code> codes() const
    {
      return codes_;
    }
  };

  struct day_range
  {
    long begin;
    long end;
    day_range(int year ,int month , int day , int count)
    {
      begin = year * 10000 + month *  100  + day ;
      end   = year * 10000 + month *  100  + (day + count); 

      std::cout<<begin<< " "<<end<<std::endl;
    }

    day_range(long const& yymmdd)
    {
      begin = yymmdd;
      end   = yymmdd;
    }

    std::list<long> days() const
    {
      std::list<long> result;
      int index = 0;
      while(( begin + index) <= end)
	{
	  result += begin + index++;
	}

      //    std::cout<<"finish"<<std::endl;
      // for(auto c: result)
      //   {
      // 	std::cout<<c<<","<<std::endl;
      //   }
      return result;
    }
  
  };

  struct stock_query
  {
    std::list<stock_code> codes;
    day_range dr;
    stock_query(code_range const&c , day_range const&d):codes(c.codes())
						       ,dr(d)
    {}

    std::list<long> days() const
    {
      return dr.days();
    }

    db::query to_query(long const & day) const
    {
      //std::cout<<day<<std::endl;
      std::stringstream s;
      s<<" day =" <<day;
      return db::query(s.str());
    }
  };

  auto find_or_create = [](auto con , auto const& t )
  {
    db::query q(t.equal_str());
    using type1 = std::remove_reference_t<decltype(t)>;
    using type = std::remove_const_t<type1>;
    auto r = db::find<decltype(con),type>(con , q);
    if(r)
      {
	//std::cout<<"find"<<std::endl;
	return *r;
      }
    save(con,t);
    return t;

  };

  boost::uuids::uuid make_uuid()
  {
    return boost::uuids::random_generator()();
  }

  std::string make_uuid_string()
  {
    std::stringstream id;
    id << make_uuid();
    return id.str();
  }

  auto const make_query=[](auto const& codes , auto const&period)
  {
    std::list<db::stock_query> result;

    std::list<long> days;
    for(int begin = period.first ; begin <= period.second ;++begin)
      {
	days.push_back(begin);
      }
  
    for(auto& code : codes)
      {
	for(auto& d : days)
	  {
	    result.push_back(db::stock_query{ db::code_range(code.code) , db::day_range(d)});
	  }
      }

    return result;
  };

}
