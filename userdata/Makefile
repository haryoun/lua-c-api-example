CC = gcc
CFLAGS = -I/usr/include/lua5.1

libmatrix.so: matrix.o# 공유 라이브러리 만들기
	$(CC) $< -shared -o $@

matrix.o: matrix.c# 컴파일
	$(CC) $< $(CFLAGS) -c

clean:
	rm libmatrix.so matrix.o
