#pragma once
#include <jeho/db/req_mongo.hpp>

namespace db {
	struct connection : public mongo::connection
	{
		connection():mongo::connection(db_name)
	};
	
	using query = jeho::db::query;

	template<typename T>
	using inserter = mongo::req_up<mongo::insert, T , jeho::db::query>;
}