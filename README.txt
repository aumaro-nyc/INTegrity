# INTegrity
Data encryption and integrity application for CIS 433

Set up environment:
    If you do not already have have the crypto++ library on your computer
	1. Download the cryptopp610 file 
	2. In cryptopp610 file, run the Makefile using make (this should produce libcryptopp.a)
    Make directories:
    	encrypted
	decrypted

Running program:
    make
    make run
    You will be prompted to give the path of the file you would like to have encrypted/decrypted, please enter a valid file path.
    Then you will be prompted on whether you would like the file encrypted or decrypted.
    
    The encrypted file will be written into the folder encrypted and decrypted file will be written into the folder decrypt.

 *Note: Only .txt files can be encrypted and decrypted. Also the decrypted file will no longer contain any newline characters that were in the original file.

Files will all end up in the folder called encrypted/decrypted (based on selected option) under the same name the original file was called.

