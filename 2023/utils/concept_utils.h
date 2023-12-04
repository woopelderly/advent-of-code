#pragma once

#include <concepts>
#include <iterator>

namespace utils
{
    // https://stackoverflow.com/a/70543294
    template< typename ContainerType_t >
    concept Container =
        requires( ContainerType_t a, const ContainerType_t b ) {
            requires std::regular< ContainerType_t >;
            requires std::swappable< ContainerType_t >;
            requires std::destructible< typename ContainerType_t::value_type >;
            requires std::same_as< typename ContainerType_t::reference, typename ContainerType_t::value_type& >;
            requires std::same_as< typename ContainerType_t::const_reference, const typename ContainerType_t::value_type& >;
            requires std::forward_iterator< typename ContainerType_t::iterator >;
            requires std::forward_iterator< typename ContainerType_t::const_iterator >;
            requires std::signed_integral< typename ContainerType_t::difference_type >;
            requires std::same_as< typename ContainerType_t::difference_type, typename std::iterator_traits< typename ContainerType_t::iterator >::difference_type >;
            requires std::same_as< typename ContainerType_t::difference_type, typename std::iterator_traits< typename ContainerType_t::const_iterator >::difference_type >;
            {
                a.begin()
                } -> std::same_as< typename ContainerType_t::iterator >;
            {
                a.end()
                } -> std::same_as< typename ContainerType_t::iterator >;
            {
                b.begin()
                } -> std::same_as< typename ContainerType_t::const_iterator >;
            {
                b.end()
                } -> std::same_as< typename ContainerType_t::const_iterator >;
            {
                a.cbegin()
                } -> std::same_as< typename ContainerType_t::const_iterator >;
            {
                a.cend()
                } -> std::same_as< typename ContainerType_t::const_iterator >;
            {
                a.size()
                } -> std::same_as< typename ContainerType_t::size_type >;
            {
                a.max_size()
                } -> std::same_as< typename ContainerType_t::size_type >;
            {
                a.empty()
                } -> std::same_as< bool >;
        };
}