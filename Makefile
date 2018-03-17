SRC= aes.cpp connect.cpp

all:
	g++  -L./cryptopp610 -lcryptopp -o crypt aes.cpp 
	g++ -L./cppconn/lib -lmysqlcppconn-static -o connect connect.cpp

	

run:
	./crypt

clean:
	rm crypt connect

