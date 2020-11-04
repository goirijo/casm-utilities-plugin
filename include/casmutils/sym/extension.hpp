#ifndef CASMUTILS_SYM_PLUGIN_EXTENSION_EXAMPLE_HH
#define CASMUTILS_SYM_SYM_PLUGIN_EXTENSION_EXAMPLE_HH

#include <iostream>

namespace casmutils
{
    namespace sym
    {
        class PluginExtension
        {
            public:
                PluginExtension();

                void say_hello();

                void say_hello_again()
                {
                    std::cout<<"HELLOOOO!\n";
                    return;
                }
        };

        void plugin_extension();
    }
}


#endif
