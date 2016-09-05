#pragma once
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <cstdlib> //std::system
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/thread.hpp>
#include <thread>

namespace  plot_process{

  using namespace boost::interprocess;
  using   data_type = std::vector<std::pair<double , double> > ;

  const std::string  memory_name = "jeho_my_mem2";
  template<int Size>
  struct plot_buffer_t
  {
    //Alias a vector that uses the previous STL-like allocator so that allocates
    //its values from the segment
    plot_buffer_t():reader(0),window_type(0)
    {}

    double  x[Size];
    double  y[Size];
    int size;
    int window_type;
    interprocess_semaphore reader;
  };

  typedef plot_buffer_t<20000> plot_buffer;


  std::pair<data_type,int> read()
  {
    data_type out;
    int window_type;
    try
      {
        auto shm = shared_memory_object(open_only, memory_name.c_str(),read_write);
        //Map the whole shared memory in this process
        shm.truncate(sizeof(plot_buffer));
        auto region = mapped_region(shm,read_write);
        //get the region address
        auto addr = region.get_address();
        //Obtain the shared structure
        auto data = static_cast<plot_buffer*>(addr);
        //wait until a number gets available
        std::cout<<"wait for data"<<std::endl;
        data->reader.wait();

        int size = data->size;
	window_type = data->window_type;
        //std::cout<<"accepted size "<<size
	//<<" window type "<<window_type
	//<<std::endl;
        for(int i = 0; i < size ;++i)
          {
            out.push_back(std::make_pair(data->x[i] , data->y[i]));
          }

      }catch(boost::interprocess::interprocess_exception e)
      {
        std::cout<<e.what()<<std::endl;
      }

    return std::make_pair(out ,window_type);
  }


  void remove()
  {
    shared_memory_object::remove(memory_name.c_str());
    std::cout<<"removed previous "<<memory_name<<" memory "<<std::endl;
  }

  struct out
  {
    shared_memory_object shm ;
    mapped_region  region;
    plot_buffer *data ;
    void * addr ;

    out()
    {
      //remove();

      try
        {
          shm = shared_memory_object(open_or_create, memory_name.c_str(), read_write);
          shm.truncate(sizeof(plot_buffer));
          region = mapped_region(shm, read_write);
          addr = region.get_address();
          data = new (addr)plot_buffer;
          if(data ==nullptr)
            {
              std::cout<<" nul ptr"<<std::endl;
            }

        }catch(boost::interprocess::interprocess_exception e)
        {
          std::cout<<"error "<<e.what()<<std::endl;
          throw e;
        }
    };

    void to_draw(data_type const&d,int window_type)
    {
      data->size = d.size();
      data->window_type = window_type;

      for(int i = 0; i < d.size(); ++i)
        {
          data->x[i] =  d[i].first;
          data->y[i] =  d[i].second;
        }

      data->reader.post();
    }
  };
}
