#ifndef ARGUMENT_UTILITIES_HPP
#define ARGUMENT_UTILITIES_HPP

#include <utility>
#include <vector>
#include <tuple>

namespace cli
{

std::vector<std::string> split(const std::string &s);

void getline(std::istream &file, std::string &line);

/******************************************************************************
               TUPLE UTILITIES
 ******************************************************************************/

template<int...> struct index{};

template<int I, typename Index, typename... Types>
struct make_indexes_impl;

template<int I, int... Indexes, typename T, typename ... Types>
struct make_indexes_impl<I, index<Indexes...>, T, Types...>
{
    typedef typename make_indexes_impl<I + 1, index<Indexes..., I>, Types...>::type type;
};

template<int I, int... Indexes>
struct make_indexes_impl<I, index<Indexes...> >
{
    typedef index<Indexes...> type;
};

template<typename ... Types>
struct make_indexes : make_indexes_impl<0, index<>, Types...>
{};


template<class Ret, class... Args, int... Indexes >
Ret apply_tuple_helper( Ret (*pf)(Args...), index< Indexes... >, std::tuple<Args...>&& tup);

template<class Ret, class ... Args>
Ret apply_tuple(Ret (*pf)(Args...), const std::tuple<Args...>&  tup);

template<class Ret, class ... Args>
Ret apply_tuple(Ret (*pf)(Args...), std::tuple<Args...>&&  tup);

}

#include "utilities.hxx"

#endif /* ARGUMENT_UTILITIES_HPP */