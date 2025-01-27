CC = gcc
CFLAGS = -I/usr/include/lua5.1

libnativefunc.so: nativefunc.o# 공유 라이브러리 만들기
	$(CC) $< -shared -o $@

nativefunc.o: nativefunc.c# 컴파일
	$(CC) $< $(CFLAGS) -c

clean:
	rm libnativefunc.so nativefunc.o
