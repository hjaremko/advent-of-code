#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

int react( string& s )
{
    //original brute solution
    // do
    // {
    //     deleted = false;
    //     for ( auto s = begin( input ); s != end( input ) - 1; ++s )
    //     {
    //         if ( ( *s >= 'A' && *s <= 'Z' && *( s + 1 ) == *s + 32 ) ||
    //              ( *s >= 'a' && *s <= 'z' && *( s + 1 ) == *s - 32 ) )
    //         {
    //             *s = '0';
    //             *( s + 1 ) = '0';
    //             deleted = true;
    //         }
    //     }
    //
    //     input.erase( std::remove( input.begin(), input.end(), '0' ), input.end() );
    // } while ( deleted );
    //
    // return input.size();

    string q;

    for ( auto& c : s )
    {
        char last = q.back();

        if ( abs( last - c ) == abs( 'A' - 'a' ) )
        {
            q.pop_back();
        }
        else
        {
            q.push_back( c );
        }
    }

    return q.size();
}

int main()
{
    std::fstream inputf( "input.txt", std::ios::in );
    string input;

    inputf >> input;
    inputf.close();

    string old = input;

    cout << react( input ) << endl;

    int best = input.size();

    for ( char c = 'a'; c <= 'z'; ++c )
    {
        input = old;
        input.erase( std::remove( input.begin(), input.end(), c ), input.end() );
        input.erase( std::remove( input.begin(), input.end(), c - 32 ), input.end() );

        int result = react( input );
        
        if ( result < best )
        {
            best = result;
        }
    }

    cout << best;

    return 0;
}
