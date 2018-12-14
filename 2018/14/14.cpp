#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string recipes;
    std::string input = "939601";
    bool part_one = false;
    bool part_two = false;

    recipes.push_back( '3' );
    recipes.push_back( '7' );

    int elf_one = 0;
    int elf_two = 1;

    while ( true )
    {
        if ( !part_one && recipes.size() >= stoi( input ) + 10 )
        {
            std::cout << recipes.substr( stoi( input ), 10 ) << std::endl;
            part_one = true;
        }

        std::string new_receipe = std::to_string( ( recipes[ elf_one ] - '0' ) + ( recipes[ elf_two ] - '0' ) );

        for ( auto& c : new_receipe )
        {
            recipes.push_back( c );

            if ( recipes.size() >= input.size() )
            {
                auto s = recipes.find( input, recipes.size() - input.size() );
                    
                if ( s != std::string::npos )
                {
                    std::cout << s << std::endl;
                    part_two = true;
                    break;
                }
            }
        }

        if ( part_two )
            break;

        elf_one = ( ( elf_one + ( recipes[ elf_one ] - '0' ) + 1 ) % recipes.size() );
        elf_two = ( ( elf_two + ( recipes[ elf_two ] - '0' ) + 1 ) % recipes.size() );
    }

    return 0;
}
