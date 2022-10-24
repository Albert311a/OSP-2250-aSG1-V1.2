//#include <ios>
#include <iostream>
#include <fstream>
//#include <iterator>
#include <string>
//#include <set>
//#include <sys/types.h>
//#include <type_traits>
#include <unistd.h> // fork
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>

bool letter3( const std::string &s1, const std::string &s2 ){
    std::string k1 = s1.substr( 2 );
    std::string k2 = s2.substr( 2 );
    if( k1 > k2 )
        return true;
    return false;
}

void map2( std::vector<std::string> &strSet, char *argv[ ] ){
    std::vector<std::string>::iterator it = strSet.begin( );
    std::vector<std::string> sz3;
    std::vector<std::string> sz15;

    while( it != strSet.end( ) ){
        if( it->length( ) >= 4 && it->length( ) <= 15 ){
            sz15.push_back( *it );
        } else if( it->length( ) == 3 ){
            sz3.push_back( *it );
        }
        it++;
    }

    pid_t pid = fork( );
    if( pid == 0 ){
        sort( sz15.begin( ), sz15.end( ), letter3 );
    } else if( pid > 0 ){
        sort( sz3.begin( ), sz3.end( ), letter3 );
    } else {
        std::cerr << "unable to open fork" << std::endl;
        exit( 1 );
    }

    for( auto i : sz3 )
        std::cout << i << std::endl;
    std::ofstream file3;
    file3.open( argv[ 1 ],  std::ios_base::out );
    if( !file3 ){
        std::cerr << "Error: " << argv[ 1 ] << " file could not be opened" << std::endl;
        exit( 1 );
    }

    for( auto i : sz3 ){
        file3 << i << std::endl;
    }
    file3.close( );

    std::ofstream file15;
    file15.open( argv[ 2 ] );
    if( !file15 ){
        std::cerr << "Error: file " << argv[ 2 ] << " could not be opened" << std::endl;
        exit( 1 );
    }
    for( auto i : sz15 ){
        file15 << i << std::endl;
    }
    file15.close( );
}

void Task1filter( std::vector<std::string> &vstr, const int &i, char *argv[ ] ){
    std::fstream file;
    std::string line;
    file.open( argv[ i ] );
    if( !file ){
        std::cerr << "File " << argv[ i ] << " not found" << std::endl;
        exit( 1 );
    }
    while( getline( file, line ) ){
        vstr.push_back( line );
    }
    std::vector<std::string>::iterator it;
    it = unique( vstr.begin( ), vstr.end( ) );
    unsigned seed = std::chrono::system_clock::now( ).time_since_epoch( ).count( );
    shuffle( vstr.begin( ), vstr.end( ), std::default_random_engine( seed ) );

}
void reduce( int argc, char *argv[ ] ){
    int i = 3;
    std::fstream file;
    std::string line = "";
    std::vector<std::string> data;

    while( i < argc ){
        std::vector<std::string> vstr;
        Task1filter( vstr, i , argv );
        data.insert( data.end( ), vstr.begin( ), vstr.end( ) );
        i++;
    }
    std::vector<std::string>::iterator it;
    it = unique( data.begin( ), data.end( ) );
    map2( data, argv );
}

int main( int argc, char *argv[ ] ){

    if( argc > 3  )
        reduce( argc, argv );
    else{
        std::cerr << "failed to provide proper arguments\n";
        exit( 1 );
    }

	return 0;
}

