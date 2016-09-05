#pragma once
#include <fstream>
#include "inter.hpp"
plot_process::out oo;
#include <boost/assign.hpp>

namespace data {
  using one = std::vector<double> ;
  using pair = plot_process::data_type;
}

using namespace boost::assign;

void draw(plot_process::data_type dt , int pos=0)
{
  if(pos != 0)
    {
      boost::thread th(boost::bind(&system , "../graph/myd"));
    }
  else
    {
      std::string command = "../graph/myd " + std::to_string(pos);
      boost::thread th(boost::bind(&system , command.c_str()));
    }
  
  oo.to_draw(dt,pos);
}

void draw(plot_process::data_type dt,std::string const& path,int pos)
{
  const char * p = path.c_str();
  boost::thread th(boost::bind(&system , p));
  oo.to_draw(dt,pos);
}

void draw(data::one  t,int pos)
{
  plot_process::data_type dt;
  int index =0;
  for(auto v : t)
    {
      dt += std::make_pair(index++ , v);
    }

  //std::cout<<pos<<std::endl;
  draw(dt,pos);
}

void draw(data::one t, std::string const&path ,int window_pos)
{
  plot_process::data_type dt;
  int index =0;
  for(auto v : t)
    {
      dt += std::make_pair(index++ , v);
    }

  draw(dt,path,window_pos);
}


