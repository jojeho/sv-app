#pragma once
#include <jeho/db/mongo.hpp>
#include "config.hpp"
#include "stock_code.hpp"

namespace db {

  std::shared_ptr<mongo::connection> connection(std::string db_name)
  {
    return std::make_shared<mongo::connection>(db_connection_string,db_name);
  }


  struct code_con_impl : mongo::connection 
  {
    std::string code ;
    code_con_impl(std::string db_con , std::string const& sc):mongo::connection(db_con,"stock")
							    ,code(sc)
    {}

    code_con_impl(std::string db_con , std::string const& sc , std::string db_name):mongo::connection(db_con,db_name)
							    ,code(sc)
    {}

    
    ~code_con_impl(){}
  };
  
  std::shared_ptr<code_con_impl> code_connection(stock_code const&sc)
  {
    return std::make_shared<code_con_impl>(db_connection_string , sc.code);
  }

  std::shared_ptr<code_con_impl> code_connection(stock_code const&sc,std::string db_name)
  {
    return std::make_shared<code_con_impl>(db_connection_string , sc.code,db_name);
  }

  
  std::shared_ptr<code_con_impl> code_connection(code const&sc)
  {
    return std::make_shared<code_con_impl>(db_connection_string , sc);
  }


  
  
  using query = jeho::db::query;

  template<typename T>
  struct inserter : public mongo::circle<mongo::insert, T , jeho::db::query>
  {
    typedef   mongo::circle<mongo::insert, T , jeho::db::query> base;

    inserter(std::shared_ptr<mongo::connection>  con)
    :base(con,query(""))
    {}

    inserter(std::shared_ptr<code_con_impl>  con)
      :base(con,con->code)
    {
      std::cout<<con->code<<std::endl;
    }
  };


  template<typename T>
  struct selector  : public mongo::cursor<T>
  {
    using base = mongo::cursor<T>;
    selector(std::shared_ptr<mongo::connection> con
	     ,jeho::db::query const&q):base(con , q){}
    selector(std::shared_ptr<code_con_impl> con
	     ,jeho::db::query const&q):base(con, con->code , q
					    ){}
  };


  template<typename Con ,typename T>
  boost::optional<T> find(Con con 
			  ,jeho::db::query const&q)
  {
    auto _ = selector<T>(con,q);
    auto b = std::begin(_);
    if(b == std::end(_))
      {
	return boost::optional<T>();
      }
    return *b;
  }

  template<typename Con , typename T>
  void save(Con con , T const&t)
  {
    auto i = inserter<T>(con);
    auto it = std::begin(i);
    *it = t;
    it++;
  }
  

}
