CC     := clang
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic

SRCDIR   := src
TESTDIR  := tests
BUILDDIR := build

# 'dev' or 'release'
BUILDENV ?= dev

compile: compile-tests

include $(SRCDIR)/Makefile
include $(TESTDIR)/Makefile

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)

.PHONY: compile clean
