#pragma once
#include "serialize.hpp"

struct rtime_client
{
  std::shared_ptr<jeho::network::connection> con
  rtime_client():con(std::make_shared<jeho::network::connection>(base_host() , base_port()))
  {}

  void send(stock::minute const&m)
  {
    jeho::network::dump::clinet c(con);
    auto result =out<stock::minute>(m);
    c.send(result);
  }
};
