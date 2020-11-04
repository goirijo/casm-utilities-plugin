#include <pybind11/pybind11.h>
#include <pybind11/stl.h>     

#include "casmutils/sym/extension.hpp"

namespace cu=casmutils;
namespace py=pybind11;


PYBIND11_MODULE(utilsplugin, m) {

    py::class_<cu::sym::PluginExtension>(m, "PluginExtension")
        .def("say_hello", &cu::sym::PluginExtension::say_hello)
        .def("say_hello_again", &cu::sym::PluginExtension::say_hello_again);

    m.def("plug_extension", &cu::sym::plugin_extension);
}
