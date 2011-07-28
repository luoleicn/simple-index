FLAGS = -g -Wall
all:
	make vbyte gvi simple9
vbyte:
	g++ -o vbyteTest.o vbyte.h vbyte.cpp vbyteTest.cpp ${FLAGS}
gvi:
	g++ -o gviTest.o gvi.h gvi.cpp gviTest.cpp exception.h exception.cpp ${FLAGS}
simple9:
	g++ -o simple9.o s9Test.cpp simple9.h simple9.cpp exception.h exception.cpp ${FLAGS}
clean:
	rm *.o
