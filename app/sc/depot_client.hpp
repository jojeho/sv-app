#pragma once
#include "../config.hpp"
#include <boost/lexical_cast.hpp>
#include <jeho/network/req_client.hpp>
#include "../stock_base.hpp"
#include "name_request.hpp"
#include "serialize.hpp"

struct client
{
  boost::asio::io_service is;
  template<typename Arg, typename Result>
	Result request(std::string const& func_name, Arg const& arg)
	{
		auto s = out<Arg>(arg);
		jeho::network::connection con(load_host(), load_port());
		jeho::network::req_res_client c(con,is);
		auto b = c.request(s);
		return  in<Result>(b);
	}

  std::list<daishin::stock_base> select_stock_base(std::string const& code, std::string const& begin, std::string const& end)
	{
	  using namespace daishin;
		std::cout << "select stock base run " << std::endl;
		stock_query sq;
		sq.begin = boost::lexical_cast<long>(begin);
		sq.end = boost::lexical_cast<long>(end);
		sq.code = code;

		std::cout << " query  code " << sq.code << " begin " << sq.begin << " " << sq.end << std::endl;
		return request<stock_query, std::list<daishin::stock_base>>(req_list::select_stock_base, sq);
	}
};


