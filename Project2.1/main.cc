/*
Title:      LargeNumber Program
Purpose:    Showing LargeNumber class capabilities
Author:     Dominik Szaciłowski
Version:    0.0.7 09/03/2019
*/
#include <iostream>
#include <string>
#include <bitset>
#include <stdexcept>
#include <cstdlib>
#include "LargeNumber.h"
#include "supportFunctions.h"

using namespace std;

int main() {

    LargeNumber example("101111101011110000011111111");
    LargeNumber example2(99999999);
    cout << example << endl << example2 << endl;
    cout << example.smallToLL(30) << example2.smallToLL(30) << endl << endl;

    LargeNumber a;
    LargeNumber b;
    long long c;
    long long d;

    while( cin >> c ) {
        cin >> d;
        a.fromLL(c);
        b.fromLL(d);
        cout << endl << c << "+" << d << " = " << (a+b).smallToLL(30) << "  " << a+b << endl;
        cout << endl << c << "-" << d << " = " << (a-b).smallToLL(30) << "  " << a-b << endl;
        cout << endl << c << "*" << d << " = " << (a*b).smallToLL(30) << "  " << a*b <<endl << endl;
    }

    a.fromLL(10);
    b.fromLL(17);
    cout << a << " " << b << " " << bool(a==b) << " " << bool(a>b) << endl;
    a = b;
    cout << a << " " << b << " " << bool(a==b) << " " << bool(a<=b) << endl;

    return 0;
}
