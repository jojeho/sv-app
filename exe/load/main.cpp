#include <jeho/network/req_res.hpp>
#include <jeho/network/server.hpp>
#include "config.hpp"
using func_request = jeho::network::func_request<funcs> ;
using session = jeho::network::req_session<func_request>;
using server  = jeho::network::server<session>;
const std::string address ;
const std::string port;

int main(int argc , char* argv[])
{
  jeho::network::connection con(address , port);
  server server(con);
  return 1;
}
