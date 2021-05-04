# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

.PHONY: clean

IDIR=../include
BDIR=../bin

CC=g++
CFLAGS=-I$(IDIR) -std=c++17
LIBS=-lthrift -lstdc++fs

DEPS=microbench_like.cpp \
	$(IDIR)/buzzblog/gen/buzzblog_types.cpp \
	$(IDIR)/buzzblog/gen/buzzblog_constants.cpp \
	$(IDIR)/buzzblog/gen/TAccountService.cpp \
	$(IDIR)/buzzblog/gen/TPostService.cpp \
	$(IDIR)/buzzblog/gen/TLikeService.cpp

all: clean
	mkdir $(BDIR)
	$(CC) -o $(BDIR)/microbench_like $(DEPS) $(CFLAGS) $(LIBS)

clean:
	rm -rf $(BDIR)
