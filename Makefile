SRC= aes.cpp

all:
	g++  -L./cryptopp610 -lcryptopp -o crypt aes.cpp 

run:
	./crypt

clean:
	rm crypt

