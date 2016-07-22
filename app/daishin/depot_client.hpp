#pragma once
#include <boost/lexical_cast.hpp>
#include <jeho/network/req_client.hpp>
#include "stock_base.hpp"
#include "name_request.hpp"
#include "serialize.hpp"

struct client
{
	template<typename Arg, typename Result>
	Result request(std::string const& func_name, Arg const& arg)
	{
		auto s = in<Arg>(arg);
		jeho::network::conection con(load_host(), load_port());
		jeho::network::req_res_client c(con);
		auto b = c.request(s);
		return  out<Result>(b);
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
};


