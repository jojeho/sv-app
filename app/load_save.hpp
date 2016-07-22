#pragma once
#include "config.hpp"
#include <jeho/db/mongo.hpp>
#include "daishin\depot_client.hpp"


std::list<code> kospi_200()
{
	db::query q("all");
	auto s =db::selector(db::connection(), q);
	std::list<code> result;
	std::copy(std::begin(s), std::end(s), std::begin(result));
	return result;
}

void load_save()
{
	client cl;
	auto codes = kospi_200();
	for(auto const& code : codes)
	{
		auto in = db::inserter(db::connection(code));
		auto it = std::begin(in);
		auto sbs =cl.select_stock_base(code, begin, end);
		std::copy(std::begin(sbs), std::end(sbs), it);
	}
}


