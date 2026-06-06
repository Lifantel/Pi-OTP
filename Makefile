# kbhit kütüphanesi + Pi-OTP projesi Makefile

CC      = gcc
CFLAGS  = -Wall -Wextra -O2
LIBS    = -lcurl

pisayisi: pisayisi.c kbhit.o
	$(CC) $(CFLAGS) pisayisi.c kbhit.o -o pisayisi $(LIBS)

# --- Kütüphane nesnesi ---
kbhit.o: kbhit.c kbhit.h
	$(CC) $(CFLAGS) -c kbhit.c -o kbhit.o

libkbhit.a: kbhit.o
	ar rcs libkbhit.a kbhit.o

clean:
	rm -f *.o libkbhit.a pisayisi

.PHONY: clean
