#include <iostream>
#include <casmutils/sym/cartesian.hpp>

int main(int argc, char* argv[])
{
    std::cout<<"Get in loser, we're going shopping.\n";
    std::cout<<"Also here's an identity symmetry operation:\n";

    auto I=casmutils::sym::CartOp::identity();
    std::cout<<I.matrix<<"\n\n";

    return 0;
}
