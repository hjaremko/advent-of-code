#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct cpu
{
    enum opcode
    {
        addr  = 0,
        addi  = 1,
        multr = 2,
        multi = 3,
        banr  = 4,
        bani  = 5,
        borr  = 6,
        bori  = 7,
        setr  = 8,
        seti  = 9,
        gtir  = 10,
        gtri  = 11,
        gtrr  = 12,
        eqir  = 13,
        eqri  = 14,
        eqrr  = 15
    };

    auto exec( cpu::opcode opcode, int a, int b, int c )
    {
        switch ( opcode )
        {
        case addr:
            regs.at( c ) = regs.at( a ) + regs.at( b );
            break;
        case addi:
            regs.at( c ) = regs.at( a ) + b;
            break;
        case multr:
            regs.at( c ) = regs.at( a ) * regs.at( b );
            break;
        case multi:
            regs.at( c ) = regs.at( a ) * b;
            break;
        case banr:
            regs.at( c ) = regs.at( a ) & regs.at( b );
            break;
        case bani:
            regs.at( c ) = regs.at( a ) & b;
            break;
        case borr:
            regs.at( c ) = regs.at( a ) | regs.at( b );
            break;
        case bori:
            regs.at( c ) = regs.at( a ) | b;
            break;
        case setr:
            regs.at( c ) = regs.at( a) ;
            break;
        case seti:
            regs.at( c ) = a;
            break;
        case gtir:
            if ( a > regs.at( b ) )
                regs.at( c ) = 1;
            else
                regs.at( c ) = 0;

            break;
        case gtri:
            if ( regs.at( a ) > b )
                regs.at( c ) = 1;
            else
                regs.at( c ) = 0;

            break;
        case gtrr:
            if ( regs.at( a ) > regs.at( b ) )
                regs.at( c ) = 1;
            else
                regs.at( c ) = 0;

            break;
        case eqir:
            if ( a == regs.at( b ) )
                regs.at( c ) = 1;
            else
                regs.at( c ) = 0;

            break;
        case eqri:
            if ( regs.at( a ) == b )
                regs.at( c ) = 1;
            else
                regs.at( c ) = 0;

            break;
        case eqrr:
            if ( regs.at( a ) == regs.at( b ) )
                regs.at( c ) = 1;
            else
                regs.at( c ) = 0;

            break;

        }
    }

    void print_regs() const
    {
        for ( auto& r : regs )
            cout << r << ' ';

        cout << endl;
    }

    vector<int> regs{ vector<int>( 4, 0 ) };
};

int main()
{
    std::fstream inputf( "input2.txt", std::ios::in );
    std::fstream inputp( "program.txt", std::ios::in );

    int matching = 0;

    string tmpb;
    string tmpin;
    string tmpa;
    string tmp;
    map<int, int> matched;
    map<int, int> rmatched;

    while ( !inputf.eof() )
    {
        getline( inputf, tmpb );
        getline( inputf, tmpin );
        getline( inputf, tmpa );
        getline( inputf, tmp );

        cpu cpu;
        vector<int> before( 4, 0 );
        vector<int> after ( 4, 0 );

        sscanf( tmpb.c_str(), "Before: [%d, %d, %d, %d]", &before[ 0 ],
                                &before[ 1 ], &before[ 2 ], &before[ 3 ] );
        sscanf( tmpa.c_str(), "After: [%d, %d, %d, %d]", &after[0],
                                &after[ 1 ], &after[ 2 ], &after[ 3 ] );

        int o = 0;
        int a = 0;
        int b = 0;
        int c = 0;
        int mop = 0;
        int tmp_matching = 0;
        
        sscanf( tmpin.c_str(), "%d %d %d %d", &o, &a, &b, &c );

        for ( int op = 0; op < 16; ++op )
        {
            if ( matched.find( op ) == matched.end() )
            {
                cpu.regs = before;
                cpu.exec( cpu::opcode( op ), a, b, c );

                if ( cpu.regs == after )
                {
                    mop = op;
                    tmp_matching++;
                }
            }
        }

        // if ( tmp_matching >= 3 ) //for part one
        if ( tmp_matching == 1 )
        {
            matched.insert( {mop, o} );
            rmatched.insert( {o, mop} );
            matching++;
        }
    }

    // cout << matching << endl; //part one

    int op = 0;
    int a  = 0;
    int b  = 0;
    int c  = 0;

    cpu cpu;

    while ( inputp >> op >> a >> b >> c )
    {
        cpu.exec( cpu::opcode( rmatched[ op ] ), a, b, c );
    }

    cout << cpu.regs.at( 0 ) << endl;

    return 0;
}
