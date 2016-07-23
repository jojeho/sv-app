#pragma once

#include <boost/optional.hpp>


		template<typename Funcs>
		struct name_request
		{
			boost::optional<std::string> operator()(std::vector<char> const& data)
			{
				auto it = std::find(data.begin(), data.end(), ':');
				std::string func_name = std::string(data.begin(), it);
				it++;
				std::string text(it, data.end());
				return Funcs()(func_name, text);
			}
		};

		namespace req_list {

			const std::string select_stock_base = "select_stock_base";
			const std::string select_stock_code = "seelct_stock_code";

	}

	