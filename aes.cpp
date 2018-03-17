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

void makeAESKeys() {
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
/*	cout << "RSA Parameters:" << endl;
	cout << " n: " << n << endl;
	cout << " p: " << p << endl;
	cout << " q: " << q << endl;
	cout << " d: " << d << endl;
	cout << " e: " << e << endl;
	cout << endl;
*/
	///////////////////////////////////////
	// Create Keys
	cout << "Creating keys...\n";
	CryptoPP::RSA::PrivateKey privateKey(params);
	CryptoPP::RSA::PublicKey publicKey(params);
    
    // Here is where you would add a user to the database, with pub and priv keys

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
		// Message
		string message = "RSA Signature", signature;
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

/*				// Sign and Encode
				CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);
				CryptoPP::StringSource sig(message, true, 
				    new CryptoPP::SignerFilter(rng, signer,
				        new CryptoPP::StringSink(signature)
				   ) // SignerFilter
				); // StringSource*/

				while(getline(file,line)) {
					encLine += line;
				}
                // Here we would get the public key from the database
				CryptoPP::RSAES_OAEP_SHA_Encryptor e(publicKey);
				CryptoPP::StringSource ss1(encLine, true,
					new CryptoPP::PK_EncryptorFilter(rng, e, new CryptoPP::StringSink(cipher))
				);
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

/*				CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
				CryptoPP::StringSource sig(message+signature, true,
				    new CryptoPP::SignatureVerificationFilter(
				        verifier, NULL,
				        CryptoPP::SignatureVerificationFilter::THROW_EXCEPTION
				   ) // SignatureVerificationFilter
				); // StringSource*/

				while(getline(file,line)) {
					decLine += line;
				}
                // Here we would get the user's pviate key from the database
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
		if((doMore == "yes") || (doMore == "y")){
			cout << "Please enter a file name:\n";
			cin >> path;
			cout << "Path: " << path << endl;
			file.open(path);	
		}

	} while ((doMore == "yes") || (doMore == "y"));
	

	file.close();

	return 0;
}
