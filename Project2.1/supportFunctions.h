/*
Title:      Support functions for LargeNumber.h
Purpose:    Additional functions used in LargeNumber.h
Author:     Dominik Szaciłowski
Version:    0.0.7 09/03/2019
*/
#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include "LargeNumber.h"

bool canBeTransformed( const std::string text );    //Function checks if string can be transformed into binary number.
bool convertSign( std::string text );
bool convertSign( long long number );
bool operator>( const std::bitset<LARGE_NUMBER_SIZE>& bits1, const std::bitset<LARGE_NUMBER_SIZE>& bits2 );
std::ostream &operator<<( std::ostream &os, const LargeNumber &number );
