#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <queue>

struct graph
{
    int vertices = 0;
    std::list<int> *adj;

    graph( int v )
    {
        vertices = v;
        adj = new std::list<int>[ v ];
    }

    void add_edge( int v, int w )
    {
        adj[ v ].push_back( w );
    }

    template<int Part>
    std::string topo_sort()
    {
        std::vector<int> in_degree( vertices, 0 );

        for ( int u = 0; u < vertices; ++u )
        {
            for ( auto i = begin( adj[ u ] ); i != end( adj[ u ] ); ++i )
            {
                in_degree[ *i ]++;
            }
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> q;

        for ( int i = 0; i < vertices; ++i )
        {
            if ( in_degree[ i ] == 0 )
            {
                q.push( i );
            }
        }

        if ( Part == 1 )
        {
            std::string top_order;

            while ( !q.empty() )
            {
                int u = q.top();
                q.pop();

                for ( auto i = std::begin( adj[ u ] ); i != std::end( adj[ u ] ); ++i )
                {
                    if ( --in_degree[ *i ] == 0 )
                    {
                        q.push( *i );
                    }
                }

                top_order += char( u + 'A' );
            }

            return top_order;
        }
        else if ( Part == 2 )
        {
            int seconds = 0;
            constexpr int worker_count = 5;
            std::vector<int> workers( worker_count, -1 );
            std::vector<int> workers_start( worker_count, 0 );

            do
            {
                for ( int w = 0; w < worker_count; ++w ) {
                
                    if ( workers[ w ] != -1 )
                    {
                        if ( seconds - workers_start[ w ] - 1  >= workers[ w ] + 60 )
                        {
                            for ( auto i = begin( adj[ workers[ w ] ] ); i != end( adj[ workers[ w ] ] ); ++i )
                            {
                                if ( --in_degree[ *i ] == 0 )
                                {
                                    q.push( *i );
                                }
                            }

                            workers[ w ] = -1;
                        }
                    }

                    if ( workers[ w ] == -1 )
                    {
                        if ( !q.empty() )
                        {
                            int u = q.top();
                            q.pop();

                            workers[ w ] = u;
                            workers_start[ w ] = seconds;
                        }
                    }
                }

                seconds++;
                
            } while ( ( workers[ 0 ] != -1 ) || ( workers[ 1 ] != -1 ) ||
                      ( workers[ 2 ] != -1 ) || ( workers[ 3 ] != -1 ) || ( workers[ 4 ] != -1 ) );

            return std::to_string( seconds - 1 );
        }

        return "";
    }
};

int main()
{
    std::fstream inputf( "input.txt", std::ios::in );
    std::vector<std::string> in;
    graph g( 26 );

    for ( std::string tmp; getline( inputf, tmp );  )
    {
        in.push_back( tmp );
    }

    for ( unsigned int i = 0; i < in.size(); ++i )
    {
        char who = 0;
        char pre = 0;

        sscanf( in[ i ].c_str(), "Step %s must be finished before step %s can begin.", &pre, &who );

        g.add_edge( pre - 'A', who - 'A' );
    }

    std::cout << g.topo_sort<1>() << std::endl;
    std::cout << g.topo_sort<2>() << std::endl;

    return 0;
}
