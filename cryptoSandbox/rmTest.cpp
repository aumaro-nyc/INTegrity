/*
 * File: rmTest.cpp
 * Author: Austin Snyder
 * Date: Winter 2018
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <random>
#include <climits>
#include <string>

#define ll long long
using namespace std;


/*

 * Function to calculate (a * b) % c

 */
ll multmod(ll a, ll b, ll modulo)
{

    ll x = 0;
    ll y = a % modulo;

    while (b > 0)
    {

        if (b % 2 == 1)
	{
	    x = (x + y) % modulo;
	}
	y = (y * 2) % modulo;
	b /= 2;

    }
    return x % modulo;
}


/*

 * Function to perform modular exponentiation

 */
ll mod(ll base, ll exp, ll modulo)
{

    ll x = 1;
    ll y = base;
    while (exp > 0)
    {
	if (exp % 2 == 1)
	    x = (x * y) % modulo;
	y = (y * y) % modulo;
	exp = exp / 2;
    }
    return x % modulo;
}


/*

 * Miller-Rabin Primality Test

 */
bool millerRab(ll p, int iterations)
{
    if (p < 2)
    {
	return false;
    }
    
    if (p != 2 && p % 2 == 0)
    {
	return false;
    }

    ll s = p - 1;
    while (s % 2 == 0)
    {
	s /= 2;
    }

    for(int i = 0; i < iterations; i++)
    {
	ll a = rand() % (p - 1) + 1;
	ll temp = s;
	ll modulo = mod(a, temp, p);

	while (temp != p - 1 && modulo != 1 && modulo != p - 1)
	{
	    modulo = multmod(modulo, modulo, p);
	    temp *= 2;
	}
	
	if (modulo != p - 1 && temp % 2 == 0)
	{
	    return false;
	}
    }

    return true;
}

/*

 * Greatest Common Denominator Function for testing relative primality

 */
ll gcd(ll a, ll b)
{
    ll temp;
    while (b != 0)
    {
	temp = a;
	a = b;
	b = temp % b;
    }
    return a;
}

/*

 * Random Number Generation Function

 */
ll genRand(ll max)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::uniform_int_distribution<ll> dist(10, max);

    return dist(generator);
}

/*
 * Function to generate random prime numbers
 */
ll genPrime()
{
    ll num;
    int iteration = 5;

    do
    {
    num = genRand((ll)INT_MAX);

    } while(!millerRab(num, iteration));
    
    return num;
}

/*

 * Public Key Generation function

 */
ll generateEKey(ll p, ll q)
{
    ll sentinel = (p - 1) * (q - 1);
    cout << "(genEKey): sentinel value: " << sentinel << endl;
    ll eKey;
    
    do
    {
	eKey = genRand(100000);
    }while(gcd(sentinel, eKey) != 1);

   // cout << "GCD between key and sentinel: " << gcd(eKey, sentinel) << endl;

    return eKey;
}

/*

 * Private Key Generation Function
 
 */
ll generateDKey(ll eKey, ll p, ll q)
{
    ll mod = (p - 1) * (q - 1);
    ll dKey;
    ll sentinel;

    cout << "Mod Value: " << mod << endl;

    do
    {
	dKey = genRand(LLONG_MAX);
	sentinel = eKey * dKey;
	cout << "Remainder:   " << (sentinel - 1) % mod << endl;
    } while ((sentinel - 1) % mod != 0);

    return dKey;
}


/* D Key attempt #2 */
ll generateDecKey(ll eKey, ll p, ll q)
{
    ll mod = (p - 1) * (q - 1);
    ll dKey;

    ll magicNum = genRand(13);
    
    dKey = (mod * magicNum + 1) / eKey;

    return dKey;
}


/*

 * RSA Encryption Function

 */


int main()
{

/*
    int iteration = 5;
    ll num;
    cout << "Enter integer to test: ";
    cin >> num;

    if (millerRab(num, iteration))
	cout << num << " is prime." << endl;
    else
	cout << num << " is not prime." << endl;

    cout << "GCD: " << gcd((ll)10, num) << endl;

    cout << genRand((ll)100) << endl;
*/

    ll p = genPrime();
    ll q = genPrime();

    cout << "Value of p: " << p << endl;
    cout << "Value of q: " << q << endl;

    ll encKey = generateEKey(p, q);
    cout << "Encryption key: " << encKey << endl;

    ll decKey = generateDecKey(encKey, p, q);
    string decStr = to_string(decKey);
    cout << "Decryption key (int): " << decKey << endl;
    cout << "Decryption key (hex): " << hex << decKey << endl;
    cout << "Decryption key (oct): " << oct << decKey << endl;

    return 0;
}
