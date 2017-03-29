#pragma once
#include <app/sc/serialize.hpp>
#include "../db.hpp"
#include <app/stock.hpp>
#include <app/stock_hana.hpp>
struct rtime_handler
{
  void operator()(std::vector<char> const& data)
  {
    std::string text(std::begin(data),std::end(data));
    auto result = in<stock::minute>(text);
    std::cout<<"receive "<<result.code<<" at time "<<result.time<<std::endl;

    try
      {
	auto host  =  bid_host();
	auto port  =  bid_port();
	auto con = std::make_shared<jeho::network::connection>(host , port);
	jeho::network::dump::client c(con);

	//auto t = out<stock::minute>(result);
	//std::cout<<t<<std::endl;
	//std::string new_text(std::begin(data), std::end(data));
	//std::string text = "xxxxxxxxxxxxxxx";
	//c.send(text);
      }catch(std::exception e)
      {
	//std::cout<<"fail to send bid"<<std::endl;
      }

    {
      if(result.time >= 900)
	{
          std::cout<<"insert to db "<<result.code<<" at time "<<result.time<<std::endl;
      	  auto con = db::code_connection(result.code , rtime_db);
	  auto in = db::inserter<stock::minute>(con);
	  auto it = std::begin(in);
	  *it = result;
	  it++;
	}
    }
  }
};
