CC = clang

LDFLAGS = -framework Foundation
IFLAGS = -I../helpers/ -I../helpers/

OBJS = $(wildcard *.o)

.PHONY: objc
objc :
	$(CC) -o objc gcd.m $(LDFLAGS) $(IFLAGS)

.PHONY: swift
swift:
	swiftc -o swift gcd.swift

clean: 
	rm -rf objc swift