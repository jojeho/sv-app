#include <boost/assign.hpp>
using namespace boost::assign;
#include <jeho/network/server.hpp>
#include <jeho/network/dump.hpp>
#include <app/config.hpp>
#include <app/order.hpp>
#include  <app/sc/trade_client.hpp>
int main()
{
  auto host = bid_host();
  auto port = bid_port();
  //auto codes = db::kospi();

  // auto v = day_vec(name);
  // auto m = classifier(name);
  // buy_codes ;

  // trade_clients ;
  
  // for(code  : codes)
  //   {
  //     auto vv = v(current_day);
  //     if(m(vv))
  //       {
  //         trad_clines += code
  //       }
  //   }

  std::list<std::string> cs;
  cs += "A000210";
  cs += "A000660";
  
  day_client ds;
  ds.send(days{cs});

  return 1;
    
}
