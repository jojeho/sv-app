#include "config.hpp"
#include <jeho/network/req_res.hpp>
#include <app/stock_base.hpp>

#include <jeho/db/req_mongo.hpp>

using namespace jeho::network;
namespace db =   mongo;


int main(int argc , char* argv[])
{
  jeho::network::connection n_con(load_host() , load_port());
  std::string code ;
  ptime begin,end;
  
  auto n_req =jeho::network::req_res<find_stock_base>(n_con,code,begin,end);

  db::connection db_con(db_connection_string , db_name);
  jeho::db::query q("");
  auto db_req = db::req_up<db::insert,stock_base,jeho::db::query>(db_con,q);
  auto it = std::begin(db_req);
  std::copy(std::begin(n_req),std::end(n_req), it);
  return 1;
}
