#include "concept_utils.h"
#include "input.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>

namespace aoc_1
{
    [[nodiscard]] std::uint64_t constexpr decode( concept_utils::Container auto scrambed_data )
    {
        return std::accumulate(
            scrambed_data.begin(), scrambed_data.end(), 0, []( std::uint64_t total, std::string const& input ) {
                auto const first_digit{ std::find_if( input.begin(), input.end(), []( unsigned char c ) { return std::isdigit( c ); } ) };
                auto const last_digit{ std::find_if( input.rbegin(), input.rend(), []( unsigned char c ) { return std::isdigit( c ); } ) };

                return total += ( *first_digit - 0x30 ) * 10 + ( *last_digit - 0x30 );
            } );
    }
}

int main()
{
    std::cout << aoc_1::decode( std::move( aoc_1::input ) ) << '\n';
}