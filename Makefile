CXXFLAGS := -std=c++11

all : crc7

crc7 : crc7.cc

clean :
	rm -rf crc7

.PHONY : all clean
