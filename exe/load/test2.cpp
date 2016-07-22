#include <string>
#include <app/dashin/chart.hpp>
#include <app/dashin/stock_base.hpp>
#include <iostream>
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT
namespace my_namespace {

        class my_chart : public chart_empty {
        public:
                my_chart()
                {
                }

                   void select(std::string const& code ,long const& begin, long const& end) {
                    std::list<stock_base> result;
                    stock_base sb;
                    result.push_back(sb);
                    result.push_back(sb);
                    std::cout<<"helllo "<<std::endl;
                }

                ~my_chart() {
                        std::cout << "Destructing my_chart" << std::endl;
                }
        };

        // Exporting `my_namespace::plugin` variable with alias name `plugin`
        // (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
        extern "C" BOOST_SYMBOL_EXPORT my_chart  chart_plugin_t;
        my_chart chart_plugin_t;

} // namespace my_namespace

