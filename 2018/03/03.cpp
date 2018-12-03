#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct box
{
    int id{ 0 };
    int x{ 0 };
    int y{ 0 };
    int width{ 0 };
    int height{ 0 };

    void read( const string& line )
    {
        sscanf( line.c_str(), "#%d @ %d,%d: %dx%d", &id, &x, &y, &width, &height );
    }

    bool is_overlapping( const box& rect2 )
    {
        int x_overlap = max( 0, min( this->x + width , rect2.x + rect2.width  ) - max( this->x, rect2.x ) );
        int y_overlap = max( 0, min( this->y + height, rect2.y + rect2.height ) - max( this->y, rect2.y ) );

        return x_overlap && y_overlap;
    }
};

int main()
{
    std::fstream input( "input.txt", std::ios::out | std::ios::in );

    unordered_map<int,int> pairs;
    vector<box> boxes;
    int area = 0;

    int** grid = new int*[ 1000 ];

    for ( int i = 0 ; i < 1000 ; ++i )
    {
        grid[ i ] = new int[ 1000 ];

        for ( int j = 0 ; j < 1000 ; ++j )
        {
            grid[ i ][ j ] = 0;
        }
    }

    for ( string tmp; getline( input, tmp ); )
    {
        box rtmp;
        rtmp.read( tmp );
        boxes.push_back( rtmp );

        for ( int i = rtmp.x; i < rtmp.x + rtmp.width; ++i )
        {
            for ( int j = rtmp.y; j < rtmp.y + rtmp.height; ++j )
            {
                grid[ i ][ j ]++;
            }
        }
    }

    //part one
    for ( int i = 0; i < 1000; ++i )
    {
        for ( int j = 0; j < 1000; ++j )
        {
            if ( grid[ i ][ j ] >= 2 )
            {
                area++;
            }
        }
    }

    cout << area << endl;

    //part two
    for ( auto box1 = begin( boxes ); box1 != end( boxes ); ++box1 )
    {
        for ( auto box2 = begin( boxes ); box2 != end( boxes ); ++box2 )
        {
            auto contains = pairs.find( box2->id );

            if ( box1->id != box2->id && contains == end( pairs ) && box1->is_overlapping( *box2 ) )
            {
                pairs.insert( { box2->id, box1->id } );
                pairs.insert( { box1->id, box2->id } );
            }
        }
    }

    for ( int i = 1; i <= 1233; ++i )
    {
        auto contains = pairs.find( i );

        if ( contains == end( pairs ) )
        {
            cout << '#' << i << endl;
            break;
        }
    }

    return 0;
}
