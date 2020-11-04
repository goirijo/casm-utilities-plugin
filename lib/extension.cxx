#include "../include/casmutils/sym/extension.hpp"
#include <iostream>

namespace casmutils
{
namespace sym
{
PluginExtension::PluginExtension() { std::cout << "The symmetry extension has been constructed.\n"; }

void plugin_extension() { std::cout << "This is just the standalone function from the plugin.\n"; }

void PluginExtension::say_hello()
{
    std::cout << "Hello!\n";
    return;
}
} // namespace sym
} // namespace casmutils
