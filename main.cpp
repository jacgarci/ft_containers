#include <iterator>
#include <vector>
#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include "utils.hpp"

#include <utility>

int main()
{
    /* std::vector<int> a;
    std::vector<int>::iterator it;
    if (typeid(std::iterator_traits<std::vector<int>::iterator>::iterator_category)==typeid(std::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator"; */
    /* std::cout << std::boolalpha;
    std::cout << "is_integral:" << std::endl;
    std::cout << "char: " << std::is_integral<char>::value << std::endl;
    std::cout << "int: " << std::is_integral<int>::value << std::endl;
    std::cout << "float: " << std::is_integral<float>::value << std::endl;
    std::cout << std::boolalpha;
    std::cout << "is_integral:" << std::endl;
    std::cout << "char: " << ft::is_integral<char>::value << std::endl;
    std::cout << "int: " << ft::is_integral<int>::value << std::endl;
    std::cout << "float: " << ft::is_integral<float>::value << std::endl; */

    /* typedef ft::iterator_traits<ft::random_access_iterator_tag> traits;
    if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator";
    return 0; */
   
    std::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef std::vector<int>::iterator iter_type;
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  ft::reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
  while (rev_from != rev_until)
    std::cout << ' ' << *rev_from++;
  std::cout << '\n';

  return 0;
}


