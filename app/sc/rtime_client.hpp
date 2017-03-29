#pragma once
#include "serialize.hpp"
#include <jeho/network/connection.hpp>
#include <jeho/network/dump.hpp>
struct rtime_client
{
	std::shared_ptr<jeho::network::connection> con;
  rtime_client():con(std::make_shared<jeho::network::connection>(rtime_host() , rtime_port()))
  {}

  void send(stock::minute const&m)
  {
    jeho::network::dump::client c(con);
    auto result =out<stock::minute>(m);
    c.send(result);
  }
};
