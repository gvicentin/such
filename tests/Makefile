TESTSRCS := test_allocators.c test_collections.c test_string.c
TESTSBIN := $(patsubst %.c, $(BUILDDIR)/%.test, $(TESTSRCS))

$(BUILDDIR)/%.test: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $< -o $(basename $@) -I $(SRCDIR)

compile-tests: $(BUILDDIR) $(TESTSBIN)

.PHONY: compile-tests
