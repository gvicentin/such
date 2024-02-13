#include "minunit.h"
#include "collections.c"

#include <stdio.h>

char mu_assert_msg[MU_MSGBUF_LEN];
int mu_tests_run;

static char *test_array(void);
static char *all_tests(void);

int main(void) {
    // run tests and exit
    char *tests_result = all_tests();
    if (tests_result != 0) {
        printf("%s\n", tests_result);
        return 1;
    }

    printf("%d\n", mu_tests_run);
    return 0;
}

static char *test_array(void) {
    MU_ASSERT(1 == 1, "One should be equal to one");
    MU_PASS;
}

static char *all_tests(void) {
    MU_TEST(test_array);
    MU_PASS;
}
