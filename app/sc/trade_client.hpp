#pragma once
#include "../order.hpp"
#include "serialize.hpp"

struct trade_client
{
  std::shared_ptr<jeho::network::connection> con;

  trade_client():con(std::make_shared<jeho::network::connection>(trade_host() , trade_port()))
  {}

  void send(order const&m)
  {
    jeho::network::dump::client c(con);
    auto result =out<order>(m);
    c.send(result);
  }
};


struct day_client
{
  std::shared_ptr<jeho::network::connection> con;

  day_client():con(std::make_shared<jeho::network::connection>(trade_host() , trade_port()))
  {}

  void send(days const&m)
  {
    jeho::network::dump::client c(con);
    auto result =out<days>(m);
    c.send(result);
  }
};
