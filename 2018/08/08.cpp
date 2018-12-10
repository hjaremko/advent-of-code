#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <list>
#include <map>
#include <queue>
#include <array>

using namespace std;

struct node
{
    vector<node*> children;
    vector<int> metadata;
};

node* read( istream& o, int& sum )
{
    int children = 0;
    int metadata_c = 0;
    node* new_node = new node;

    if ( o.good() )
    {
        o >> children >> metadata_c;

        for ( int i = 0; i < children; ++i )
        {
            new_node->children.push_back( read( o, sum ) );
        }

        for ( int i = 0; i < metadata_c; ++i )
        {
            int tmp = 0;
            o >> tmp;
            sum += tmp;
            new_node->metadata.push_back( tmp );
        }

        return new_node;
    }
    else
    {
        return nullptr;
    }
}

int get_value( node* root )
{
    int sum = 0;

    if ( root->children.size() != 0 )
    {
        for ( auto e : root->metadata )
        {
            try
            {
                sum += get_value( root->children.at( e - 1 ) );
            }
            catch (...)
            {
                // sum += 0;
            }
        }
    }
    else
    {
        for ( auto e : root->metadata )
        {
            sum += e;
        }
    }

    return sum;
}

int main()
{
    // std::fstream inputf( "test.txt", std::ios::in );
    std::fstream inputf( "input.txt", std::ios::in );

    node* root = new node;
    int root_value = 0;
    int sum = 0;

    root = read( inputf, sum );
    root_value = get_value( root );

    cout << sum << endl;
    cout << root_value << endl;

    return 0;
}
