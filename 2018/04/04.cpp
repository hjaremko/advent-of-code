#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

int get_id( string os ) //-1 asleep, -2 wakes up
{
    int id = 0;

    istringstream ss( os );
    string tmp;
    getline( ss, os, ']' );
    ss >> tmp;

    if ( tmp == "Guard" )
    {
        ss >> tmp;
        sscanf( tmp.c_str(), "#%d", &id );
        return id;
    }
    else if ( tmp == "falls" )
    {
        return -1;
    }
    else if ( tmp == "wakes" )
    {
        return -2;
    }

    return 0;
}

int main()
{
    std::fstream input( "input.txt", std::ios::in );

    map<string, int> times;
    int minutes_asleep[ 4000 ] = { 0 };
    int minutes_guard [ 4000 ][ 60 ];

    for ( int q = 0; q < 4000; ++q )
    {
        for ( int i = 0; i < 60; ++i )
        {
            minutes_guard[ q ][i ] = 0;
        }
    }

    for ( string tmp; getline( input, tmp ); )
    {
        times.insert( { tmp, get_id( tmp ) } );
    }

    //part one
    int current  = 0;
    int curaslep = 0;
    int curwake  = 0;
    int tmp = 0;

    for ( auto& e : times )
    {
        if ( e.second == -1 )
        {
            sscanf( e.first.c_str(), "[%d-%d-%d %d:%d]", &tmp, &tmp, &tmp, &tmp, &curaslep );
        }
        else if ( e.second == -2 )
        {
            sscanf( e.first.c_str(), "[%d-%d-%d %d:%d]", &tmp, &tmp, &tmp, &tmp, &curwake );
            minutes_asleep[ current ] += curwake - curaslep;

            for ( int i = curaslep; i < curwake; ++i )
            {
                minutes_guard[ current ][ i ]++;
            }
        }
        else
        {
            current = e.second;
        }
    }

    int* m = max_element( minutes_asleep, minutes_asleep + 4000 );
    int  best = distance( minutes_asleep, m );
    // cout << best << endl;

    int* mm = max_element( minutes_guard[ best ],  minutes_guard[ best ] + 60 );
    cout << best * distance( minutes_guard[ best ], mm ) << endl << endl;

    //part two
    int maxtimes = 0;
    int idg = 0;

    for ( int i = 0; i < 60; ++i )
    {
        for ( int g = 0; g < 4000; ++g )
        {
            if ( minutes_guard[ g ][ i ] > minutes_guard[ idg ][ maxtimes ] )
            {
                maxtimes = i;
                idg = g;
            }
        }
    }

    // cout << maxtimes << ' ' << idg << endl;
    cout << maxtimes * idg << endl;

    return 0;
}
