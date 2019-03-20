/*
Title:      LargeNumber Class
Purpose:    Saving numbers larger than supported in C++
Author:     Dominik Szaciłowski
Version:    0.0.7 09/03/2019
*/
#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include<stdexcept>

const unsigned int LARGE_NUMBER_SIZE = 30;  //Size of bitset that LargeNumber is based on

class LargeNumber {
    std::bitset<LARGE_NUMBER_SIZE> bits;
    bool isNegative;
public:
    LargeNumber( const std::string text );
    LargeNumber( const long long number );
    LargeNumber( const LargeNumber &number );
    LargeNumber ();

    LargeNumber operator+( const LargeNumber &number ) const;
    LargeNumber operator-( const LargeNumber &number ) const;
    LargeNumber operator*( const LargeNumber &number ) const;
    LargeNumber negative() const;
    void operator+=( const LargeNumber &number );
    void operator-=( const LargeNumber &number );
    void operator*=( const LargeNumber &number );
    void operator=( const LargeNumber &number );
    bool operator==( const LargeNumber &number ) const;
    bool operator>( const LargeNumber &number ) const;
    bool operator<( const LargeNumber &number ) const;
    bool operator>=( const LargeNumber &number ) const;
    bool operator<=( const LargeNumber &number ) const;
    bool operator!=( const LargeNumber &number ) const;
    bool getBit( const unsigned int index ) const;
    std::bitset<LARGE_NUMBER_SIZE> getBitset() const;
    void setBit( const unsigned int index, const bool value );
    void setBitset( const std::bitset<LARGE_NUMBER_SIZE> &value );
    void setSign( const bool value );
    bool getSign() const;
    std::string toString() const;
    long long smallToLL( const unsigned int range ) const;  //Convetrs 'range' first digits into decimal number. Function does not support bin numbers bigger than long long int size in dec.
    void fromLL( const long long number );
    void fromStr( const std::string text );

};
