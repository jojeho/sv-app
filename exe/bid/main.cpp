#include <boost/assign.hpp>
using namespace boost::assign;
#include <jeho/network/server.hpp>
#include <jeho/network/dump.hpp>
#include <app/config.hpp>
#include <app/sc/bid_handler.hpp>
#include <app/rule.hpp>


using handler = bid_handler;
using session = jeho::network::dump::session<handler> ;
using server = jeho::network::server<session>;
using connection = jeho::network::connection;


std::map<code , rule> make_rules()
{
  std::map<code,rule> result;

  auto con = db::connection(rule_db);

  auto _ = db::selector<classifier::interval>(con , db::query("all"));

  auto first = std::begin(_);

  auto codes = db::select_kospi_200();
  
  if(first != std::end(_))
    {
      for(auto code : codes)
	{
	  rule r ;
	  r.code = code.code;
	  r.sp = sell::make_policy(property_out(sell::property::simple{ "simple"}));
	  r.cls = std::make_shared<classifier::interval>(*first);
	  result += std::make_pair(code.code , r);
	}
      
    }
  
  std::cout<<"rule size "<<result.size()<<std::endl;
  return result;
}


int main()
{
  stock_bid_single.rules = make_rules();
  auto host = bid_host();
  auto port = bid_port();
  jeho::network::connection con(host , port);
  server s(con);
  return 1;
}
