#include "LargeNumber.h"
#include "supportFunctions.h"


LargeNumber::LargeNumber( const std::string text ) {
    bits.reset();
    isNegative = convertSign( text );
    std::string t = text;
    if( isNegative )
        t = text.substr( 1, text.size() - 1 );
    if( !canBeTransformed(t) )
        throw std::invalid_argument("Only binary max N-digital number can be transformed into bitset");
    std::bitset<LARGE_NUMBER_SIZE> temp( t );
    bits = temp;

    #ifdef DEBUG
    std::cout << "ConsStr  Value: ";
    for( unsigned int i = 0; i < bits.size(); i++ )
    std::cout << bits[i];
    std::cout << " Sign: " << isNegative << std::endl;
    #endif
}

LargeNumber::LargeNumber( const long long number ) {
    bits.reset();
    isNegative = convertSign( number );
    std::bitset<LARGE_NUMBER_SIZE> temp( abs(number) );
    bits = temp;

    #ifdef DEBUG
    std::cout << "ConsLong Value: ";
    for( unsigned int i = 0; i < bits.size(); i++ )
    std::cout << bits[i];
    std::cout << " Sign: " << isNegative << std::endl;
    #endif
}

LargeNumber::LargeNumber( const LargeNumber &number ) {
    this->bits = number.getBitset();
    this->isNegative = number.getSign();
}

LargeNumber::LargeNumber() {
    bits.reset();
    isNegative = 0;
}

LargeNumber LargeNumber::operator+( const LargeNumber &number ) const {
    bool carry = false;
    LargeNumber result;
    if( isNegative == number.getSign() ) {
        for( unsigned int i = 0; i < bits.size(); i++ ) {
            result.setBit( i,  (number.getBit(i) ^ bits[i]) ^ carry );
            if( (bits[i] && number.getBit(i)) || (bits[i] && carry) || (carry && number.getBit(i)) )
                carry = true;
            else
                carry = false;
    }
    result.setSign( isNegative );
    if( carry )
        throw std::length_error("Number cant be fit in bitset");

    #ifdef DEBUG
    if( !carry )
        std::cout << "+Result: " << result.getBitset() << std::endl;
    #endif
    return result;
    }
    else if( !isNegative )
        return *this - number.negative();
    else
        return number - this->negative();
}

LargeNumber LargeNumber::operator-( const LargeNumber &number ) const {
    bool carry = false;
    LargeNumber result;
    if( isNegative == number.getSign() && !isNegative ) {
        if( *this >= number ) {
            for( unsigned int i = 0; i < bits.size(); i++ ) {
                result.setBit( i, (number.getBit(i) ^ bits[i]) ^ carry );
                if( ( !bits[i] && !number.getBit(i) && carry ) || ( bits[i] && number.getBit(i) && carry ) || ( !bits[i] && number.getBit(i) ) )
                    carry = true;
                else
                    carry = false;
            }
        result.setSign(0);
        }
        else {
            for( unsigned int i = 0; i < bits.size(); i++ ) {
                result.setBit( i, (number.getBit(i) ^ bits[i]) ^ carry );
                if( ( !bits[i] && !number.getBit(i) && carry ) || ( bits[i] && number.getBit(i) && carry ) || ( bits[i] && !number.getBit(i) ) )
                    carry = true;
                else
                    carry = false;
            }
        result.setSign(1);
        }

        #ifdef DEBUG
            std::cout << "-Result: " << result.getBitset() << std::endl;
        #endif
        return result;
    }
    else if( isNegative == number.getSign() && isNegative )
        return *this + number.negative();
    else if( isNegative != number.getSign() && isNegative )
        return ( this->negative() + number ).negative();
    else
        return *this + number.negative();
}

LargeNumber LargeNumber::operator*( const LargeNumber &number ) const {
    LargeNumber temp;
    LargeNumber result;
    LargeNumber zero(0);
    if( *this == zero || number == zero )
        return zero;
    for( unsigned int i = 0; i < number.getBitset().size(); i++ ) {
        temp = zero;
        for( unsigned int e = 0; e < bits.size(); e++ ) {
            if( e + i < temp.getBitset().size() )
                temp.setBit( e + i , bits[e] && number.getBit(i) );
            else
                if( bits[e] && number.getBit(i) )
                    throw std::length_error("Number cant be fit in");
        }
        result += temp;
    }
    if( isNegative == number.getSign() )
        result.setSign(0);
    else
        result.setSign(1);
    return result;
}

LargeNumber LargeNumber::negative() const {
    LargeNumber temp = *this;
    temp.setSign(!isNegative);
    return temp;
}

void LargeNumber::operator+=( const LargeNumber &number ) {
    *this = *this + number;
}

void LargeNumber::operator-=( const LargeNumber &number ) {
    *this = *this - number;
}


void LargeNumber::operator*=( const LargeNumber &number ) {
    *this = *this * number;
}

void LargeNumber::operator=( const LargeNumber &number ) {
    bits = number.bits;
    isNegative = number.isNegative;

    #ifdef DEBUG
    std::cout << "EqualSign" << std::endl;
    #endif
}

bool LargeNumber::operator==( const LargeNumber &number ) const {
    if( bits == number.getBitset() && isNegative == number.getSign() )
        return true;
    if( bits.none() && number.getBitset().none() )
        return true;

    #ifdef DEBUG
    std::cout << "== Not equal" << std::endl;
    #endif
    return false;
}

bool LargeNumber::operator>( const LargeNumber &number ) const {
    if( *this == number ) {

        #ifdef DEBUG
        std::cout << "Not bigger" << std::endl;
        #endif
        return false;
    }
    else if( isNegative > number.getSign() ) {

        #ifdef DEBUG
        std::cout << "Not bigger" << std::endl;
        #endif
        return false;
    }
    else if( isNegative < number.getSign() )
        return true;
    else {
        if( !isNegative )
            if( bits > number.getBitset() )
                return true;
            else {

                #ifdef DEBUG
                std::cout << "Not bigger" << std::endl;
                #endif
                return false;
            }
        else
            if( bits > number.getBitset() ) {

                #ifdef DEBUG
                std::cout << "Not bigger" << std::endl;
                #endif
                return false;
            }
            else
                return true;
    }
}

bool LargeNumber::operator<( const LargeNumber &number ) const {
    return !(*this >= number);
}

bool LargeNumber::operator>=( const LargeNumber &number ) const {
    return (*this > number || *this == number);
}


bool LargeNumber::operator<=( const LargeNumber &number ) const {
    return (*this < number || *this == number);
}

bool LargeNumber::operator!=( const LargeNumber &number ) const {
    if( *this == number )
        return false;

    #ifdef DEBUG
    std::cout << "!= Not equal" << std::endl;
    #endif
    return true;
}

bool LargeNumber::getBit( const unsigned int index ) const {
    if( index >= LARGE_NUMBER_SIZE )
        throw std::invalid_argument("Index too big");
    return bits[index];
}

std::bitset<LARGE_NUMBER_SIZE> LargeNumber::getBitset() const {
    return bits;
}

void LargeNumber::setBit( const unsigned int index, const bool value ) {
    if( index >= LARGE_NUMBER_SIZE )
        throw std::invalid_argument("Index too big");
    bits[index] = value;
}

void LargeNumber::setBitset( const std::bitset<LARGE_NUMBER_SIZE> &value ) {
    bits = value;
}

void LargeNumber::setSign( const bool value ) {
    isNegative = value;
}

bool LargeNumber::getSign() const {
    return isNegative;
}

std::string LargeNumber::toString() const {
    if( isNegative ) {

        #ifdef DEBUG
        std::cout << "-" + bits.to_string() << std::endl;
        #endif
        return "-" + bits.to_string();
    }
    else {

        #ifdef DEBUG
        std::cout << bits.to_string() << std::endl;
        #endif
        return bits.to_string();
    }
}

long long LargeNumber::smallToLL( const unsigned int range ) const {
    if( range > LARGE_NUMBER_SIZE )
        throw std::length_error("Index too big");
    long long result = 0;
    for( unsigned int i = 0; i < range; i++ )
        result += ( pow(2,i) * bits[i] );
    if( isNegative )
        result *= -1;
    return result;
}

void LargeNumber::fromLL( const long long number ) {
    LargeNumber temp(number);
    *this = temp;
}

void LargeNumber::fromStr( const std::string text ) {
    LargeNumber temp(text);
    *this = temp;
}
