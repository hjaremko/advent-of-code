#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <sstream>

constexpr int size = 200;

char grid[ size ][ size ];

void gclear()
{
    for ( int i = 0; i < size; ++i )
    {
        for ( int j = 0; j < size; ++j )
        {
            grid[ i ][ j ] = '.';
        }
    }
}

void gprint()
{
    for ( int i = 0; i < size; ++i )
    {
        for ( int j = 0; j < size; ++j )
        {
            std::cout << grid[ i ][ j ];
        }

        std::cout << std::endl;
    }
}

long long distance( const std::pair<int,int>& a, const std::pair<int, int>& b )
{
    return sqrt( ( b.first  - a.first ) * ( b.second - a.first  ) +
                 ( b.second - a.first ) * ( b.second - a.second ) );
}

int main()
{
    std::fstream inputf( "input2.txt", std::ios::in );

    std::vector<std::pair<int,int>> positions;
    std::vector<std::pair<int,int>> velocities;

    for ( std::string tmp; getline( inputf, tmp ); )
    {
        std::stringstream ss( tmp );
        std::pair<int, int> p;
        std::pair<int, int> v;

        ss >> p.first >> p.second >> v.first >> v.second;

        positions.push_back( p );
        velocities.push_back( v );
    }

    long long currmin = 9999999999;
    int second = 0;
    auto pmin = min_element( begin( positions ), end( positions ) );
    auto pmax = max_element( begin( positions ), end( positions ) );

    for ( ; ; ++second )
    {
        for ( unsigned i = 0; i < positions.size(); ++i )
        {
            positions.at( i ).first  += velocities.at( i ).first;
            positions.at( i ).second += velocities.at( i ).second;
        }

        pmin = min_element( begin( positions ), end( positions ) );
        pmax = max_element( begin( positions ), end( positions ) );
        auto current_distance = distance( *pmax, *pmin );

        if ( current_distance <= currmin )
        {
            currmin = distance( *pmax, *pmin );
        }
        else
        {
            break;
        }
    }

    std::cout << second << std::endl;

    for ( unsigned i = 0; i < positions.size(); ++i )
    {
        positions.at( i ).first  -= velocities.at( i ).first;
        positions.at( i ).second -= velocities.at( i ).second;
    }

    gclear();

    for ( auto& p : positions )
    {
        grid[ p.second ][ p.first ] = '#';
    }

    gprint();

    return 0;
}
