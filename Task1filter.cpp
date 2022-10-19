//#include <ios>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <set>

#include <algorithm>
#include <random>
#include <vector>
#include <chrono>


void Taskfilter( int argc, char *argv[ ] ){
    std::string line = "";
    std::fstream file;
    std::set<std::string> strSet;
    file.open( argv[ 1 ] );
    if( !file ){
        std::cerr << "Error: file could not be opened" << std::endl;
        exit( 1 );
    }
    while( getline( file, line ) ){
        if( line.size( ) >= 3 &&  line.size( ) <= 15 ){
            strSet.insert( line );}
    }
    file.close( );

    std::vector<std::string> vstr( strSet.begin( ), strSet.end( ) );
    unsigned seed = std::chrono::system_clock::now( ).time_since_epoch( ).count( );
    shuffle( vstr.begin( ), vstr.end( ), std::default_random_engine( seed ) );

    std::ofstream outdata;
    outdata.open( argv[ 2 ],  std::ios_base::out );
    if( !outdata ){
        std::cerr << "Error: file could not be opened" << std::endl;
        exit( 1 );
    }
    for( auto i : vstr ){
        outdata << i << std::endl;
    }
    outdata.close( );
}

int main( int argc, char *argv[ ] ){

    if( argc == 3 )
        Taskfilter( argc, argv );
    else{
        std::cout << "failed to provide proper arguments\n";
        exit( 1 );
    }

	return 0;
}
