#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


class Dat{
        std::vector<std::string> st;
        std::string name;
        std::vector<unsigned> k;
    public:
        Dat(  std::vector<std::string> &vs, const std::string &s ) : st( std::move( vs ) ), name( s ) {
            k.resize( st.size( ) );
            for( size_t i = 0; i < st.size( ); i++ ){
                k[ i ] = i;
            }
        }

        void partition( std::vector<unsigned> &m, int start, int high ){
            int i = start, j = high;
            std::string mid = st[ m[ ( i + j ) / 2 ] ].substr( 2 );
            while( i <= j ){
                while( st[ m[ i ] ].substr( 2 ) < mid ) i++;
                while( st[ m[ j ] ].substr( 2 ) > mid ) j--;
                if( i <= j ){
                    std::swap( m[ i ], m[ j ] );
                    i++; j--;
                }
            }
            if( start <  j ) partition( m, start, j );
            if( i < high ) partition( m, i, high );
        }

        void sort(  ){
            partition( k, 0, k.size( ) - 1 );
        }

        void save( ){
            std::ofstream ofile;
            ofile.open( name );
            for( size_t i = 0; i < st.size( ); i++ ){
                ofile << st[ k[ i ] ] << std::endl;
            }
            ofile.close( );
        }
};


void  task(  std::vector<std::string> &d, const std::string &s ){
    Dat k( d, s );
    k.sort( );
    k.save( );
}


int main( int argc, char *argv[ ] ){

    std::vector<std::vector<std::string>> s1( 13 );

    for( int i = 1; i < argc; i++){
        std::ifstream ifile;
        std::string line;
        std::string fname = argv[ i ];
        ifile.open( fname );
        while( getline( ifile, line ) ){
            int l = line.size( );
            switch( l ){
                case 3:
                    s1[ 0 ].push_back( line );
                    break;
                case 4:
                    s1[ 1 ].push_back( line );
                    break;
                case 5:
                    s1[ 2 ].push_back( line );
                    break;
                case 6:
                    s1[ 3 ].push_back( line );
                    break;
                case 7:
                    s1[ 4 ].push_back( line );
                    break;
                case 8:
                    s1[ 5].push_back( line );
                    break;
                case 9:
                    s1[ 6 ].push_back( line );
                    break;
                case 10:
                    s1[ 7 ].push_back( line );
                    break;
                case 11:
                    s1[ 8 ].push_back( line );
                    break;
                case 12:
                    s1[ 9 ].push_back( line );
                    break;
                case 13:
                    s1[ 10 ].push_back( line );
                    break;
                case 14:
                    s1[ 11 ].push_back( line );
                    break;
                case 15:
                    s1[ 12 ].push_back( line );
                    break;
            }
        }
        std::cout << argv[ i ] << std::endl;
    }

    std::vector<std::thread> dv;
    int n = 3, bf = 2;
    for( auto &vec : s1){

        std::string st = "text";
        std::string n2 = std::to_string( n );
        int sz = bf - n2.size( );
        std::string fs = st.append( sz, '0' ).append( n2 );

        std::thread th( task, std::ref( vec ), ( fs ) );
        dv.emplace_back( std::move( th ) );
        n++;
    }

    for( auto &t : dv ){
        t.join( );
    }
	return 0;
}

