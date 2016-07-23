#pragma once
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/list.hpp>

template<typename T>
std::string out(T const&t)
{
  std::ostringstream s;
  boost::archive::binary_oarchive ar(s);
  ar << t;
  return s.str();
}


template<typename T>
T in(std::string const& text)
{
  std::stringstream s(text);
  std::cout<<" size "<<s.str().size()<<std::endl;
  std::cout<<s.str()<<std::endl;
  boost::archive::binary_iarchive ar(s);
  
  std::cout<<text.size()<<std::endl;

  T t;
  ar >> t;
  return t;
}
