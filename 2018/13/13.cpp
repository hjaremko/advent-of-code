#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>

struct cart
{
    enum dirs
    {
        left = 0,
        straight,
        right
    };

    int id = 0;
    int x = 0;
    int y = 0;
    dirs next_dir = left;
    char direction{ '>' };

    cart() {}

    cart( int t_x, int t_y, char d )
        : x( t_x ), y( t_y ), direction( d ) {}


    void move_to( const auto& tracks, auto& carts )
    {
        switch ( direction )
        {
        case '>':
        {
            char next = tracks.at( y ).at( x + 1 );
            x++;

            if ( next == '\\' )
            {
                direction = 'v';
            }
            else if ( next == '/' )
            {
                direction = '^';
            }
            else if ( next == '+' )
            {
                switch ( next_dir )
                {
                    case left:
                        direction = '^';
                        break;
                    case right:
                        direction = 'v';
                        break;
                    case straight:
                        break;

                }

                next_dir = static_cast<dirs>( ( next_dir + 1 ) % 3 );
            }

            break;
        }
        case 'v':
        {
            char next = tracks.at( y + 1 ).at( x );
            y++;
            
            if ( next == '/' )
            {
                direction = '<';
            }
            else if ( next == '\\' )
            {
                direction = '>';
            }
            else if ( next == '+' )
            {
                switch ( next_dir )
                {
                    case left:
                        direction = '>';
                        break;
                    case right:
                        direction = '<';
                        break;
                    case straight:
                        break;
                }

                next_dir = static_cast<dirs>( ( next_dir + 1 ) % 3 );
            }

            break;
        }
        case '<':
        {
            char next = tracks.at( y ).at( x - 1 );
            x--;
            
            if ( next == '\\' )
            {
                direction = '^';
            }
            else if ( next == '/' )
            {
                direction = 'v';
            }
            else if ( next == '+' )
            {
                switch ( next_dir )
                {
                    case left:
                        direction = 'v';
                        break;
                    case right:
                        direction = '^';
                        break;
                    case straight:
                        break;
                }

                next_dir = static_cast<dirs>( ( next_dir + 1 ) % 3 );
            }

            break;
        }
        case '^':
        {
            char next = tracks.at( y - 1 ).at( x );
            y--;
            
            if ( next == '/' )
            {
                direction = '>';
            }
            else if ( next == '\\' )
            {
                direction = '<';
            }
            else if ( next == '+' )
            {
                switch ( next_dir )
                {
                    case left:
                        direction = '<';
                        break;
                    case right:
                        direction = '>';
                        break;
                    case straight:
                        break;
                }

                next_dir = static_cast<dirs>( ( next_dir + 1 ) % 3 );
            }

            break;
        }

        default:
            break;
        }
    }

    bool operator<( const cart& other )
    {
        return std::make_pair( y, x ) < std::make_pair( other.y, other.x );
    }

    bool operator==( const cart& other )
    {
        return ( x == other.x && y == other.y );
    }
};

int main()
{
    std::fstream inputf( "input.txt", std::ios::in );
    std::vector<std::vector<char>> tracks( 151, std::vector<char>( 151, '.' ) );
    std::list<cart> carts;

    for ( int i = 0; i < 150; ++i )
    {
        for ( int j = 0; j <= 150; ++j )
        {
            char c = 0;
            inputf.get( c );

            switch ( c )
            {
            case '>':
            case '<':
                tracks.at( i ).at( j ) = '-';
                carts.emplace_back( j, i, c );
                break;

            case 'v':
            case '^':
                tracks.at( i ).at( j ) = '|';
                carts.emplace_back( j, i, c );
                break;

            case '\n':
                break;

            default:
                tracks.at( i ).at( j ) = c;
            }
        }
    }


    while ( carts.size() > 1 )
    {
        carts.sort();

        for ( auto cart = std::begin( carts ); cart != std::end( carts ); ++cart )
        {
            cart->move_to( tracks, carts );

            auto tmp = cart;
            --tmp;

            if ( std::count( std::begin( carts ), std::end( carts ), *cart ) >= 2 )
            {
                auto to_erase = cart;
                carts.erase( std::remove( carts.begin(), carts.end(), *to_erase ), carts.end() );
                cart = --tmp;
            }
        }
    }

    for ( auto& cart : carts )
    {
        std::cout << cart.x << ' ' << cart.y << std::endl;
    }

    return 0;
}
