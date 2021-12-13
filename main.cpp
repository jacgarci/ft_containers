#include <iterator>
#include <vector>
#include <type_traits>
#include <iostream>
#include "utils.hpp"

int main()
{
    ft::enable_if<0, char>::type k;

    k = 65;
    std::cout <<  k << std::endl;
    return (0);
}


