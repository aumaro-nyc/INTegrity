# INTegrity
Data encryption and integrity application for CIS 433

Set up environment:
    If you do not already have have the crypto++ library on your computer
	1. Download the cryptopp610 file 
	2. In cryptopp610 file, run the Makefile using make (this should produce libcryptopp.a)

Running program:
    make
    make run
    You will be prompted to give the path of the file you would like to have encrypted, please enter a valid file path.
    The encrypted file will be written into the folder encrypted.

Encyrpted files will all end up in the folder called encrypted under the same name the original file was called.

