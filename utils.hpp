#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
    // enable_if
    template< bool Cond, class T = void >
    struct enable_if {};

    template< class T >
    struct enable_if< true, T > {typedef T type;};
    
    // is_integral
    template < class T, T v >
	struct integral_constant
	{
	    static const    T  value = v;
	    typedef         T  value_type;
	    typedef integral_constant type;
	};

    template <class T, T v>
    const T integral_constant< T, v >::value;

    #define _BOOL_CONSTANT(b) integral_constant<bool,(b)>
    typedef _BOOL_CONSTANT(true) true_type;
    typedef _BOOL_CONSTANT(false) false_type;

	template < class T> struct is_integral_type                     : public false_type {};
	template <> struct is_integral_type < bool >					: public true_type {};
	template <> struct is_integral_type < char >					: public true_type {};
	template <> struct is_integral_type < char16_t >				: public true_type {};
	template <> struct is_integral_type < char32_t >				: public true_type {};
	template <> struct is_integral_type < wchar_t >					: public true_type {};
	template <> struct is_integral_type < signed char >				: public true_type {};
	template <> struct is_integral_type < short int >				: public true_type {};
	template <> struct is_integral_type < int >						: public true_type {};
	template <> struct is_integral_type < long int >				: public true_type {};
	template <> struct is_integral_type < long long int >			: public true_type {};
	template <> struct is_integral_type < unsigned char >			: public true_type {};
	template <> struct is_integral_type < unsigned short int >		: public true_type {};
	template <> struct is_integral_type < unsigned int >			: public true_type {};
	template <> struct is_integral_type < unsigned long int >		: public true_type {};
	template <> struct is_integral_type < unsigned long long int >	: public true_type {};

	template <typename T>
		struct is_integral : public is_integral_type<T> {};
    
    // iterator_traits
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
	template<class Iterator>
	struct iterator_traits
	{
   		typedef typename Iterator::difference_type	difference_type;
    	typedef typename Iterator::value_type	value_type;
    	typedef typename Iterator::pointer	pointer;
    	typedef typename Iterator::reference	reference;
    	typedef typename Iterator::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
    	typedef ptrdiff_t	difference_type;
    	typedef T	value_type;
    	typedef T*	pointer;
    	typedef T&	reference;
    	typedef random_access_iterator_tag	iterator_category;
	};

	template< class T>
	struct iterator_traits < const T * >
	{
		typedef ptrdiff_t	difference_type;
		typedef T	value_type;
		typedef T const *	pointer;
		typedef T const &	reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	// iterator template
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
    	typedef T         value_type;
    	typedef Distance  difference_type;
    	typedef Pointer   pointer;
    	typedef Reference reference;
    	typedef Category  iterator_category;
	};

	// reverse_iterator
	template <class Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference>
	{
	protected:
    	Iterator current;
	public:
    	typedef Iterator                                            iterator_type;
    	typedef typename iterator_traits<Iterator>::difference_type difference_type;
    	typedef typename iterator_traits<Iterator>::reference       reference;
    	typedef typename iterator_traits<Iterator>::pointer         pointer;

    	reverse_iterator() : current() {}
    	explicit reverse_iterator(Iterator x) : current(x) {}
    	template <class U> reverse_iterator(const reverse_iterator<U>& u) : current(u.base()) {}
    	template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u) {current = u.base; return (*this);}
    	Iterator base() const {return (current);}
    	reference operator*() const {Iterator tmp = current; return (*--tmp);}
    	pointer   operator->() const {return &(operator*());}
    	reverse_iterator& operator++() {--current; return (current);}
    	reverse_iterator  operator++(int) {reverse_iterator tmp(*this); --current; return tmp;}
    	reverse_iterator& operator--() {++current; return *this;}
    	reverse_iterator  operator--(int) {reverse_iterator tmp(*this); ++current; return tmp;}
    	reverse_iterator  operator+ (difference_type n) const {return reverse_iterator(current - n);}
    	reverse_iterator& operator+=(difference_type n) {current -= n; return *this;}
    	reverse_iterator  operator- (difference_type n) const {return reverse_iterator(current + n);}
    	reverse_iterator& operator-=(difference_type n) {current += n; return *this;}
    	reference         operator[](difference_type n) const {return *(*this + n);}
	};

	template <class Iterator1, class Iterator2>
	bool	operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
	{
		return (x.base() == y.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
	{
		return x.base() > y.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
	{
		return x.base() != y.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
	{
		return x.base() < y.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
	{
		return x.base() <= y.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
	{
		return x.base() >= y.base();
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
	{
	    return y.base() - x.base();
	}   

	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x)
	{
	    return reverse_iterator<Iterator>(x.base() - n);
	}

	// equal
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
    	for (; first1 != last1; ++first1, ++first2) 	
        	if (!(*first1 == *first2)) 
			   	return false;
    	return true;
	}

	template<class InputIt1, class InputIt2, class BinaryPredicate>	
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
    	for (; first1 != last1; ++first1, ++first2)
        	if (!p(*first1, *first2))
            	return false;
    	return true;
	}

	// lexicographical_compare
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
    	for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
        	if (*first1 < *first2) return true;
        	if (*first2 < *first1) return false;
    	}
    	return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
    	for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
        	if (comp(*first1, *first2)) return true;
        	if (comp(*first2, *first1)) return false;
    	}
    	return (first1 == last1) && (first2 != last2);
	}

	// pair
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		T1	first;
		T2	second;

		pair() : first(), second() {}
		pair(first_type const &a, second_type const &b) : first(a), second(b) {}
		pair(pair<_U1, _U2> const &p) : first(p.first), second(p.second) {}
	};
};

#endif