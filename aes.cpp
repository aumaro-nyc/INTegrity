/*
 * Author: Anisha Aggarwal
 * File: aes.cpp
 */
/*
 * Generating a random key for each user will occur here
 * AES encryption and decryption will occur here
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "cryptopp610/osrng.h"
#include "cryptopp610/dh.h"
#include "cryptopp610/nbtheory.h"
using namespace std;

void makeKeys() {



}

void Encrypt() {
	CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
	cfbEncryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);
}


int main() {

	// initailize variables
	//int aesKeyLength = SHA256::DIGESTSIZE; // 32 bytes = 256 bit key
	//int defBlockSize = AES::BLOCKSIZE;

	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::PrimeAndGenerator *prime = new CryptoPP::PrimeAndGenerator(1, prng, 512, 511);

	//prime.Generate(1, prng, 512, 511);
	const CryptoPP::Integer p = prime->Prime();
	const CryptoPP::Integer q = prime->SubPrime();
	const CryptoPP::Integer g = prime->Generator();

	CryptoPP::DH *dh = new CryptoPP::DH();//(p, q, g);
	dh->AccessGroupParameters().Initialize(p, q, g);
	CryptoPP::SecByteBlock t1(dh->PrivateKeyLength()), t2(dh->PublicKeyLength());
	//dh->GenerateStaticKeyPair(prng, t1, t2);
	dh->GenerateKeyPair(prng, t1, t2);
	const CryptoPP::Integer pubKey(t1, t1.size()), privKey(t2, t2.size());

	cout << "Private key:\n";
	cout << hex << pubKey << endl;
	cout << "Public key:\n";
	cout << hex << privKey << endl;
	

	// Calculate a SHA-256 hash over the Diffie-Hellman session key
	SecByteBlock key(SHA256::DIGESTSIZE);
	SHA256().CalculateDigest(key, privKey, privKey.size()); 

	// Generate a random IV
	byte iv[AES::BLOCKSIZE];
	arngA.GenerateBlock(iv, AES::BLOCKSIZE);


	// Encrypt
	CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
	cfbEncryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);


	// Decrypt
	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(), iv);
	cfbDecryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);

	return 0;
}
