#include <jeho/network/server.hpp>
#include <jeho/network/dump.hpp>
#include <app/config.hpp>
#include <app/sc/rtime_handler.hpp>
using handler = rtime_handler;
using session = jeho::network::dump::session<handler> ;
using server = jeho::network::server<session>;
using connection = jeho::network::connection;

int main()
{
  auto host = rtime_host();
  auto port = rtime_port();
  jeho::network::connection con(host , port);
  server s(con);
  return 1;
}
