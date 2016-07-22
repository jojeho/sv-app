#include <string>
#include <iostream>
#include <app/dashin/stock_base.hpp>
#include <list>
#include <boost/filesystem.hpp>

#include <app/dashin/stock_base.hpp>
#include <app/dashin/chart.hpp>

#include <list>


#include <boost/dll/import.hpp> // for import_alias
#include <boost/function.hpp>

namespace dll = boost::dll;
void dll_test(std::wstring path)
{
    //const wchar_t* szName = path.c_str();
    boost::filesystem::path lib_path(path);
    std::string code;
        long begin, end;
        boost::shared_ptr<chart> plugin;            // variable to hold a pointer to plugin variable
        std::cout << "Loading the plugin" << std::endl;

        plugin = dll::import<chart>(          // type of imported symbol is located between `<` and `>`
                lib_path ,                     // path to the library and library name
                "chart_plugin",                                       // name of the symbol to import
                dll::load_mode::append_decorations              // makes `libmy_plugin_sum.so` or `my_plugin_sum.dll` from `my_plugin_sum`
                );

code = "A000210";
begin = 20160701;
end  = 20160705;

        std::cout << "plugin->calculate(1.5, 1.5) call:  " << plugin->select(code , begin , end).size() << std::endl;
}

int main()
{
        std::string code = "A000210";
        long begin = 20160705;
        long end = 20160710;
        std::cout<<"hello"<<std::endl;
        std::wstring name( L"D:/dev/prj/sv2/win/exe/dashine/Debug/dashine.dll" );
        dll_test(name);
        std::cout<<"a"<<std::endl;
        return 1;
}
