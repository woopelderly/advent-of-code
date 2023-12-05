#include "input.h"
#include "../utils/concept_utils.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace aoc_2
{
    struct Round
    {
        int m_red{};
        int m_green{};
        int m_blue{};
        bool m_possible{};
    };

    int constexpr s_max_red{ 12 };
    int constexpr s_max_green{ 13 };
    int constexpr s_max_blue{ 14 };

    auto constexpr s_game_id_key{ "Game " };
    int constexpr s_game_id_key_length{ 5 };
    auto constexpr s_game_data_start_key{ ": " };
    int constexpr s_game_data_start_key_length{ 2 };
    auto constexpr s_game_separation_key{ "; " };
    int constexpr s_game_separation_key_length{ 2 };
    auto constexpr s_color_separation_key{ ", " };
    int constexpr s_color_separation_key_length{ 2 };
    auto constexpr s_color_value_separation_key{ ' ' };

    [[nodiscard]] std::vector< std::string > extract_round_strings( std::string game_string )
    {
        std::vector< std::string > round_strings;
        while( game_string.contains( s_game_separation_key ) )
        {
            auto const separation_position{ game_string.find( s_game_separation_key ) };
            round_strings.emplace_back( game_string.substr( 0, separation_position ) );
            game_string = game_string.substr( separation_position + s_game_separation_key_length );
            if( !game_string.empty() && !game_string.contains( s_game_separation_key ) )
            {
                round_strings.push_back( game_string );
            }
        }
        return round_strings;
    }

    [[nodiscard]] std::vector< std::string > extract_color_strings( std::string round_string )
    {
        std::vector< std::string > colors;
        if( !round_string.contains( s_color_separation_key ) )
        {
            colors.push_back( round_string );
        }
        else
        {
            while( round_string.contains( s_color_separation_key ) )
            {
                auto const separation_position{ round_string.find( s_color_separation_key ) };
                colors.emplace_back( round_string.substr( 0, separation_position ) );
                round_string = round_string.substr( separation_position + s_color_separation_key_length );
                if( !round_string.empty() && !round_string.contains( s_color_separation_key ) )
                {
                    colors.push_back( round_string );
                }
            }
        }
        return colors;
    }

    [[nodiscard]] Round extract_round( std::vector< std::string > const& colors )
    {
        Round round{};
        for( auto color_value : colors )
        {
            auto const separation_position{ color_value.find( s_color_value_separation_key ) };
            if( std::string const color{ color_value.substr( separation_position + 1 ) };
                color == "red" )
            {
                round.m_red += std::stoi( color_value.substr( 0, separation_position ) );
            }
            else if( color == "blue" )
            {
                round.m_blue += std::stoi( color_value.substr( 0, separation_position ) );
            }
            else if( color == "green" )
            {
                round.m_green += std::stoi( color_value.substr( 0, separation_position ) );
            }
        }

        round.m_possible = ( round.m_red <= s_max_red && round.m_green <= s_max_green && round.m_blue <= s_max_blue );

        return round;
    }

    [[nodiscard]] std::vector< Round > extract_rounds( std::vector< std::string > const& round_strings )
    {
        std::vector< Round > rounds;
        std::transform( round_strings.begin(), round_strings.end(), std::back_inserter( rounds ), []( std::string round_string ) {
            auto const& colors{ extract_color_strings( round_string ) };
            return extract_round( colors );
        } );
        return rounds;
    }

    [[nodiscard]] int take_game_id( std::string& game )
    {
        auto const first_digit_position{ game.find( s_game_id_key ) + s_game_id_key_length };
        auto const last_digit_position( game.find( s_game_data_start_key ) );
        int game_id{ std::stoi( game.substr( first_digit_position, last_digit_position - first_digit_position ) ) };

        game = game.substr( last_digit_position + s_game_data_start_key_length );

        return game_id;
    }

    [[nodiscard]] bool is_invalid_game( std::vector< Round > const& rounds )
    {
        return std::any_of( rounds.cbegin(), rounds.cend(), []( Round const& round ) { return !round.m_possible; } );
    }

    [[nodiscard]] int sum_valid_game_ids( utils::Container auto game_data )
    {
        return std::accumulate( game_data.begin(), game_data.end(), 0, []( int total, std::string game ) {
            int const game_id{ take_game_id( game ) };

            auto const& round_strings{ extract_round_strings( game ) };

            auto const& rounds{ extract_rounds( round_strings ) };

            if( is_invalid_game( rounds ) )
            {
                return total;
            }

            return total += game_id;
        } );
    }
}

int main()
{
    std::cout << aoc_2::sum_valid_game_ids( std::move( aoc_2::input ) ) << '\n';
}