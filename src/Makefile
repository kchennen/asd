# Makefile for asd

#G++FLAG = -g

#osx
G++FLAG = -fast
LINK_OPTS2 = -pthread -lz

#linux
#G++FLAG = -O3
#LINK_OPTS2 = -pthread -lz

#for windows, using MinGW build environment
#CC = g++.exe
#G++FLAG = -DPTW32_STATIC_LIB -O3 -static-libgcc -static-libstdc++
#LINK_OPTS2 = ../lib/win32/libpthreadGC2.a ../lib/win32/libz.a 
#I_PATH = -I../include -I../include/win32 
#L_PATH = ../lib/win32

asd : asd.o param_t.o gzstream.o asd-cli.o errlog.o asd-data.o asd-dist.o pbar.o
	g++ -o asd asd.o param_t.o gzstream.o asd-cli.o errlog.o asd-data.o asd-dist.o pbar.o -lm $(LINK_OPTS2) $(I_PATH)

asd.o : asd.cpp
	g++ $(G++FLAG) -c asd.cpp $(I_PATH)

asd-cli.o : asd-cli.cpp
	g++ $(G++FLAG) -c asd-cli.cpp $(I_PATH)

asd-data.o : asd-data.cpp
	g++ $(G++FLAG) -c asd-data.cpp $(I_PATH)

asd-dist.o : asd-dist.cpp
	g++ $(G++FLAG) -c asd-dist.cpp $(I_PATH)

param_t.o : param_t.cpp
	g++ $(G++FLAG) -c param_t.cpp $(I_PATH)

errlog.o : errlog.cpp
	g++ $(G++FLAG) -c errlog.cpp $(I_PATH)

pbar.o : pbar.cpp
	g++ $(G++FLAG) -c pbar.cpp $(I_PATH)

gzstream.o : gzstream.C
	g++ $(G++FLAG) -c gzstream.C $(I_PATH)

clean:
	rm *.o
