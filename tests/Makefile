TESTSRCS := allocators_test.c collections_test.c string_test.c
TESTSBIN := $(patsubst %.c, $(BUILDDIR)/%.test, $(TESTSRCS))

$(BUILDDIR)/%.test: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $< -o $(basename $@) -I $(SRCDIR)

compile-tests: $(BUILDDIR) $(TESTSBIN)

.PHONY: compile-tests
