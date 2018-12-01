#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

int main()
{
    std::fstream input( "input.txt", std::ios::out | std::ios::in );

    int frequency = 0;
    int delta = 0;

    std::vector<int> input_arr;
    std::unordered_map<int, int> frequencies;

    while ( input >> delta )
    {
        input_arr.push_back( delta );
    }

    for ( int i = 0; true; ++i )
    {
        frequency += input_arr.at( i % input_arr.size() );

        auto result = frequencies.find( frequency );

        if ( result != std::end( frequencies ) ) 
        {
            std::cout << result->first << std::endl;
            break;
        }
        else
        {
            frequencies.insert( {frequency, frequency} );
        }
    }

    input.close();

    return 0;
}
