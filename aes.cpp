/*
 * Author: Anisha Aggarwal
 * File: aes.cpp
 */
/*
 * Generating a random key for each user will occur here
 * AES encryption and decryption will occur here
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "cryptopp610/osrng.h"
#include "cryptopp610/dh.h"
#include "cryptopp610/nbtheory.h"
using namespace std;

void makeKeys() {



}

/*void Encrypt(SecByteBlock key, ) {
	CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
	cfbEncryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);
}

void Decrypt() {
	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(), iv);
	cfbDecryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);
}*/


int main() {

	// initailize variables
	int aesKeyLength = CryptoPP::SHA256::DIGESTSIZE; // 32 bytes = 256 bit key
	int defBlockSize = CryptoPP::AES::BLOCKSIZE;

	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::PrimeAndGenerator *prime = new CryptoPP::PrimeAndGenerator(1, prng, 512, 511);

	const CryptoPP::Integer p = prime->Prime();
	const CryptoPP::Integer q = prime->SubPrime();
	const CryptoPP::Integer g = prime->Generator();

	CryptoPP::DH *dh = new CryptoPP::DH();//(p, q, g);
	dh->AccessGroupParameters().Initialize(p, q, g);
	CryptoPP::SecByteBlock t1(dh->PrivateKeyLength()), t2(dh->PublicKeyLength());
	dh->GenerateKeyPair(prng, t1, t2);
	const CryptoPP::Integer pubKey(t1, t1.size()), privKey(t2, t2.size());

	cout << "Private key:\n";
	cout << hex << pubKey << endl;
	cout << "Public key:\n";
	cout << hex << privKey << endl;

	//get file user wants to encrypt
	cout << "Please enter a file name:\n";
	string path;
	ifstream file;
	cin >> path;
	cout << "Path: " << path << endl;
	file.open(path);

	//write encrypted file
	ofstream encryp_file;
	int index = path.find_last_of("/");
	string outFile = "encrypted/" + path.substr(index+1);
	cout << "Outfile path: " << outFile << endl;
	encryp_file.open(outFile);


	

/*	// Calculate a SHA-256 hash over the Diffie-Hellman session key
	CryptoPP::SecByteBlock key(CryptoPP::SHA256::DIGESTSIZE);
	CryptoPP::SHA256().CalculateDigest(key, privKey, CryptoPP::SHA256::DIGESTSIZE); 

	cout << "SHA256 Hash: ";
	cout << CryptoPP::SecByteBlock << key << endl;*/


	return 0;
}