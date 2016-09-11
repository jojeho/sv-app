#pragma once
#include <app/sc/serialize.hpp>


struct trade_handler
{
  void operator()(std::vector<char> const& data)
  {
    std::string text(std::begin(data),std::end(data));
    auto result = in<stock::minute>(text);

  }
};
