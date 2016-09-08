#pragma once
#include <exception>
//#include <boost/optional.hpp>

template<typename Funcs>
struct depot_handler
{
  boost::optional<std::string> operator()(std::vector<char> const& data)
  {
    auto it = std::find(data.begin(), data.end(), ':');
    if (it == data.end())
      {
	std::cout << "no func name";
	std::string message ="no func name";
	//throw std::exception(message.c_str());
      }

    std::string func_name = std::string(data.begin(), it);
    it++;
    std::string text(it, data.end());
    return Funcs()(func_name, text);
  }
};

namespace req_list {

  const std::string select_stock_min = "select_stock_min";
  const std::string select_future_min = "select_future_min";
  const std::string select_stock_code = "select_stock_code";
  const std::string select_future_code = "select_future_code";
  const std::string select_stock_day = "select_stock_day";
  const std::string select_future_day = "select_future_day";

}

	
