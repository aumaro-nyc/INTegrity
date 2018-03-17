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
#include "cryptopp610/modes.h"
#include "cryptopp610/rsa.h"
#include "cryptopp610/nbtheory.h"
using namespace std;

void makeKeys() {
	// initailize varibles
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


	/*
		cout << "Private key:\n";
		cout << hex << pubKey << endl;
		cout << "Public key:\n";
		cout << hex << privKey << endl;
	*/

}
/*
void Encrypt(SecByteBlock key, ) {
	CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
	cfbEncryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);
}

void Decrypt() {
	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(), iv);
	cfbDecryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);
}

*/
int main() {

	string user;
	string password;

	//get user information
	cout << "Please enter a valid email: ";
	cin >> user;
	cout << "Please enter a password: ";
	cin >> password;

	cout << "user: " << user << endl;
	cout << "password: " << password << endl;
	cout << "Creating keys...\n";
	//makeKeys();
	int aesKeyLength = CryptoPP::SHA256::DIGESTSIZE; // 32 bytes = 256 bit key
	int defBlockSize = CryptoPP::AES::BLOCKSIZE;
	// Generate a random IV
	//CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
	//CryptoPP::AutoSeededRandomPool rnd;
	//rnd.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);
/*
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
*/

	// Pseudo Random Number Generator
	CryptoPP::AutoSeededRandomPool rng;

	///////////////////////////////////////
	// Generate Parameters
	CryptoPP::InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rng, 3072);

	///////////////////////////////////////
	// Generated Parameters
	const CryptoPP::Integer& n = params.GetModulus();
	const CryptoPP::Integer& p = params.GetPrime1();
	const CryptoPP::Integer& q = params.GetPrime2();
	const CryptoPP::Integer& d = params.GetPrivateExponent();
	const CryptoPP::Integer& e = params.GetPublicExponent();

	///////////////////////////////////////
	// Dump
	cout << "RSA Parameters:" << endl;
	cout << " n: " << n << endl;
	cout << " p: " << p << endl;
	cout << " q: " << q << endl;
	cout << " d: " << d << endl;
	cout << " e: " << e << endl;
	cout << endl;

	///////////////////////////////////////
	// Create Keys
	CryptoPP::RSA::PrivateKey privateKey(params);
	CryptoPP::RSA::PublicKey publicKey(params);




	//get file user wants to encrypt
	cout << "Please enter a file name:\n";
	string path;
	ifstream file;
	cin >> path;
	cout << "Path: " << path << endl;
	file.open(path);

	string doMore;
	do {

		string whatDo;
		string line, encLine, cipher, decLine, decipher;
		do {
			cout << "Would you like to encrypt or decrypt this file?\n";
			cin >> whatDo;
			if (whatDo == "encrypt") {
				//write encrypted file
				ofstream encryp_file;
				int index = path.find_last_of("/");
				string outFile = "encrypted/" + path.substr(index+1);
				cout << "Encrypted file path: " << outFile << endl;
				encryp_file.open(outFile);
				while(getline(file,line)) {
					encLine += line;
				}
				CryptoPP::RSAES_OAEP_SHA_Encryptor e(publicKey);
				CryptoPP::StringSource ss1(encLine, true,
					new CryptoPP::PK_EncryptorFilter(rng, e, new CryptoPP::StringSink(cipher))
				);
/*					CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(pubKey, dh->PublicKeyLength(), iv);
				cfbEncryption.ProcessData((unsigned char *)line, (unsigned char *)line, line.length());*/
				encryp_file << cipher << endl;
				encryp_file.close();
				file.close();
				break;
			}
			else if (whatDo == "decrypt") {
				//write decrypted file
				ofstream decryp_file;
				int index = path.find_last_of("/");
				string outFile = "decrypted/" + path.substr(index+1);
				cout << "Decrypted file path: " << outFile << endl;
				decryp_file.open(outFile);
				while(getline(file,line)) {
					decLine += line;
				}
				CryptoPP::RSAES_OAEP_SHA_Decryptor d(privateKey);
				CryptoPP::StringSource ss2(decLine, true,
				    new CryptoPP::PK_DecryptorFilter(rng, d,
				        new CryptoPP::StringSink(decipher)
				   ) // PK_DecryptorFilter
				);
				decryp_file << decipher << endl;
				decryp_file.close();
				file.close();
				break;
			}
			cout << "\nI'm sorry, it is unclear what you would like to do with the file\n";

		} while ( (whatDo != "encrypt") && (whatDo != "decrypt"));

		
		cout << "Would you like to do more? yes(y) or no(n)\n";
		cin >> doMore;
		cout << "Please enter a file name:\n";
/*		string path;
		ifstream file;*/
		cin >> path;
		cout << "Path: " << path << endl;
		file.open(path);

	} while ((doMore == "yes") || (doMore == "y"));
	

/*	// Calculate a SHA-256 hash over the Diffie-Hellman session key
	CryptoPP::SecByteBlock key(CryptoPP::SHA256::DIGESTSIZE);
	CryptoPP::SHA256().CalculateDigest(key, privKey, CryptoPP::SHA256::DIGESTSIZE); 

	cout << "SHA256 Hash: ";
	cout << CryptoPP::SecByteBlock << key << endl;*/

	file.close();

	return 0;
}
