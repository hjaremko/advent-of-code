#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    std::fstream input( "input.txt", std::ios::out | std::ios::in );
    
    vector<string> input_arr;
    string tmp;

    int two = 0;
    int three = 0;

    while ( input >> tmp )
    {
        input_arr.push_back( tmp );
    }

    //first part
    for ( auto& str : input_arr )
    {
        array<int, 26> letters{ 0 };
        
        for ( auto& letter : str )
        {
            letters.at( letter - 'a' )++;
        }

        auto pos = find( begin( letters ), end( letters ), 2 );

        if ( *pos == 2 )
        {
            two++;
        }

        pos = find( begin( letters ), end( letters ), 3 );

        if ( *pos == 3 )
        {
            three++;
        }
    }

    cout << two * three << endl;

    //second part
    for ( auto str = begin( input_arr ); str != end( input_arr ); ++str )
    {
        for ( auto str2 = str + 1; str2 != end( input_arr ); ++str2 )
        {
            string common = *str;

            for ( auto fir = begin( *str ), sec = begin( *str2 ); fir != end( *str ); ++fir, ++sec )
            {
                if ( *fir != *sec )
                {
                    common.erase( common.begin() + 1 );
                }
            }

            if ( common.size() == str->size() - 1 )
            {
                cout << common << endl;
            }
        }
    }



    return 0;
}
