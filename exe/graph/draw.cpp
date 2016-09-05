#include <boost/bind.hpp>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <slope/chart.h>
#include <string>


#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include "inter.hpp"
#include <boost/lexical_cast.hpp>

void new_window(std::pair<plot_process::data_type,int> const& d)
{
  //std::cout<<"new window pos:"<<d.second<<std::endl;
  /* Secure glib */
  if( ! g_thread_supported() )
    g_thread_init( NULL );

  /* Secure gtk */
  gdk_threads_init();

  /* Obtain gtk's global lock */
  gdk_threads_enter();

  double x[d.first.size()];
  double y[d.first.size()];

  for(int i = 0 ; i < d.first.size(); ++i)
    {
      x[i] = d.first[i].first;
      y[i] = d.first[i].second;
      //std::cout<<" aa " <<x[i]<<" "<<y[i]<<std::endl;
    }


  auto pw = slope_chart_new2("Cossine Curive" ,d.second);
  _slope_chart  * chart = pw;
  slope_chart_plot (chart, x, y, d.first.size(), "Random scatter", "bag");
  slope_chart_show(chart);
  gtk_main();

  /* Release gtk's global lock */
  gdk_threads_leave();
}


int main (int argc, char *argv[])
{
  plot_process::data_type out;
  gtk_init( &argc, &argv );

  bool first = true;

  while(true){
  
    auto d = plot_process::read();

    if(!first)
      {
        gtk_main_quit();
        first = false;
      }

    boost::thread t(boost::bind(&new_window ,d));
  }
  return 0;
}
