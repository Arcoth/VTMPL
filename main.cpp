#include "index_list.hxx"
#include "const_string.hxx"
#include "algorithms.hxx"

#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{
	using namespace vtmpl;

	using list = transform<make_index_list<4>::type, functions::square>;

	std::copy( std::begin(list::arr), std::end(list::arr), std::ostream_iterator<vtmpl::index_type>(std::cout, ", ") );

	std::cout << "\nString literal: " << STRING("ABCDEFGHIJ")::nt_arr << '\n';
}
