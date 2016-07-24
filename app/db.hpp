#pragma once
#include <jeho/db/mongo.hpp>
#include "config.hpp"
#include "stock_code.hpp"
namespace db {

  std::shared_ptr<mongo::connection> connection(std::string db_name)
  {
    return std::make_shared<mongo::connection>(db_connection_string,db_name);
  }

  std::shared_ptr<mongo::connection> code_connection()
  {
    return std::make_shared<mongo::connection>(db_connection_string,"stock");
  }

  using query = jeho::db::query;

  template<typename T>
  struct inserter : public mongo::circle<mongo::insert, T , jeho::db::query>
  {
    typedef   mongo::circle<mongo::insert, T , jeho::db::query> base;
    inserter(std::shared_ptr<mongo::connection> const& con)
      :base(con,query(""))
    {}

    inserter(std::shared_ptr<mongo::connection> const& con , stock_code const&c)
      :base(con,c.code,query(""))
    {}

  };


  template<typename T>
  using selector  = mongo::cursor<T> ;
}
