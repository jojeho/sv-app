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

    auto host  =  bid_host();
    auto port  =  bid_port();
    auto con = std::make_shared<jeho::network::connection>(host , port);
    jeho::network::dump::client c(con);
    c.send(text);
    {
      auto con = db::code_connection(result.code , rtime_db);
      auto in = db::inserter<stock::minute>(con);
      auto it = std::begin(in);
      *it = result;
      it++;
    }
  }
};
