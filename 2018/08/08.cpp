#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>

struct node
{
    std::vector<node*> children;
    std::vector<int> metadata;
};

node* read( std::istream& o, int& sum )
{
    int children = 0;
    int metadata_count = 0;
    node* new_node = new node;

    if ( o.good() )
    {
        o >> children >> metadata_count;

        for ( int i = 0; i < children; ++i )
        {
            new_node->children.push_back( read( o, sum ) );
        }

        for ( int i = 0; i < metadata_count; ++i )
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
            catch ( ... )
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
    std::fstream inputf( "input.txt", std::ios::in );

    node* root = new node;
    int root_value = 0;
    int sum = 0;

    root = read( inputf, sum );
    root_value = get_value( root );

    std::cout << sum << std::endl;
    std::cout << root_value << std::endl;

    return 0;
}
