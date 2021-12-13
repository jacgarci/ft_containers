#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
    //enable_if
    template< bool Cond, class T = void >
    struct enable_if {};

    template< class T >
    struct enable_if< true, T > {typedef T type;};
    
};

#endif