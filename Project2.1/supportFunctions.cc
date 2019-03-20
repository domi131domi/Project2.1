#include "supportFunctions.h"

bool canBeTransformed( const std::string text ) {
    if( text.length() > LARGE_NUMBER_SIZE )
        return false;
    for( unsigned int i = 0; i < text.size(); i++ ) {
        if( text[i] != '1' && text[i] != '0' )
           return false;
    }
    return true;
}

bool convertSign( std::string text ) { if( text[0] == '-' ) return true; return false; }

bool convertSign( long long number ) { if( number < 0 ) return true; return false; }

bool operator>( const std::bitset<LARGE_NUMBER_SIZE>& bits1, const std::bitset<LARGE_NUMBER_SIZE>& bits2 ) {
    for( int i = LARGE_NUMBER_SIZE - 1; i >= 0; i-- )
        if( bits1[i] != bits2[i] )
            return bits1[i];
    return false;
}

std::ostream &operator<<( std::ostream &os, const LargeNumber &number ) {
    if( number.getSign() )
        os << "-";
    os << number.getBitset();
    return os;
}
