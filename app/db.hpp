#pragma once
#include <jeho/db/req_mongo.hpp>
#include "config.hpp"

namespace db {

  struct connection : public mongo::connection
  {
    connection()
      :mongo::connection(db_connection_string
			 ,"test"){}
	  
    connection(std::string const& db)
      :mongo::connection(db_connection_string
			 ,db){}
  };

  struct code_connection : public mongo::connection
  {
    code_connection()
      :mongo::connection(db_connection_string
			 ,"stock"){}
  };


  using query = jeho::db::query;

  template<typename T>
  using inserter = mongo::req_up<mongo::insert, T , jeho::db::query>;

  template<typename T>
  using selector  = mongo::cursor<T> ;
}
