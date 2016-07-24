#pragma once
#include "../config.hpp"
#include <boost/lexical_cast.hpp>
#include <jeho/network/req.hpp>
#include "depot_handler.hpp"
#include "serialize.hpp"
#include "stock_query.hpp"


#include "../stock_base.hpp"
#include "../stock_code.hpp"

struct depot_client
{
  boost::asio::io_service is;

  template<typename Arg, typename Result>
  Result request(std::string const& func_name, Arg const& arg)
  {
    auto s = out<Arg>(arg);
    jeho::network::connection con(load_host(), load_port());
    jeho::network::req::client c(con,is);
    s = func_name +":" + s;
    auto b = c.request(s);
    return  in<Result>(b);
  }

  template<typename Result>
  Result request_no_arg(std::string const& func_name)
  {
    std::cout<<load_host()<<" "<<load_port()<<std::endl;
    jeho::network::connection con(load_host(), load_port());
    jeho::network::req::client c(con,is);
    auto s = func_name + ":" ;
    auto b = c.request(s);
    //std::cout<<"result "<<b<<std::endl;
    //std::cout<<"end result size "<<b.size()<<std::endl;
    return  in<Result>(b);
  }

  
  std::list<stock_base> select_stock_base(std::string const& code, std::string const& begin, std::string const& end)
  {
    std::cout << "select stock base run " << std::endl;
    stock_query sq;
    sq.begin = boost::lexical_cast<long>(begin);
    sq.end = boost::lexical_cast<long>(end);
    sq.code = code;

    std::cout << " query  code " << sq.code << " begin " << sq.begin << " " << sq.end << std::endl;
    return request<stock_query, std::list<stock_base>>(req_list::select_stock_base, sq);
  }

  std::list<stock_code> select_stock_code()
  {
    std::cout << "select stock code run " << std::endl;
    return request_no_arg<std::list<stock_code>>(req_list::select_stock_code);
  }
};


namespace depot {

  std::list<stock_base> select_stock_base(std::string const& code
					  ,std::string const& begin
					  ,std::string const& end)
  {
    depot_client cl;
    return cl.select_stock_base(code , begin, end);
  }

  std::list<stock_code> select_stock_code()
  {
    depot_client cl;
    return cl.select_stock_code();
  }
}
