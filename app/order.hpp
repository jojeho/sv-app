#pragma once

struct order
{
  int type;
  std::string code;

  template<typename Archive>
  void serialize(Archive & ar, unsigned int version)
  {
    ar & type;
    ar & code;
  }

  
};

struct days
{
	std::list<std::string> codes;

	template<typename Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar & codes;
	}
};

