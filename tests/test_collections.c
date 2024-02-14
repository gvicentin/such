#include "collections.c"
#include "minunit.h"

#include <stdio.h>

char mu_assert_msg[MU_MSGBUF_LEN];
int mu_tests_run;

static char *test_array_init(void);
static char *test_array_expand(void);
static char *test_array_append(void);
static char *test_array_remove(void);
static char *test_array_fast_remove(void);

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

static char *test_array_init(void) {
    int *nums = array(int);

    MU_ASSERT_FMT(sizeof(int) == array_header(nums)->size,
                  "Expect (%lu), but got (%lu)", sizeof(int),
                  array_header(nums)->size);
    MU_ASSERT_FMT(ARRAY_DEFAULT_CAPACITY == array_cap(nums),
                  "Expect (%d), but got (%lu)", ARRAY_DEFAULT_CAPACITY,
                  array_cap(nums));
    MU_ASSERT_FMT(0 == array_len(nums), "Expect (%d), but got (%lu)", 0,
                  array_len(nums));

    MU_PASS;
}

static char *test_array_expand(void) {
    int *nums = array(float);
    array_expand(nums, 64);

    MU_ASSERT_FMT(64 == array_cap(nums), "Expect (%d), but got (%lu)", 64,
                  array_cap(nums));

    MU_PASS;
}

static char *test_array_append(void) {
    int *nums = array(int);

    for (int i = 0; i < 100; ++i) {
        array_append(nums, i * 5);
    }

    MU_ASSERT_FMT(100 < array_cap(nums),
                  "Expect greater than (%d), but got (%lu)", 100,
                  array_cap(nums));
    MU_ASSERT_FMT(100 == array_len(nums), "Expect (%d), but got (%lu)", 100,
                  array_len(nums));
    MU_ASSERT_FMT(250 == nums[50], "Expect (%d), but got (%d)", 250, nums[50]);

    MU_PASS;
}

static char *test_array_remove(void) {
    int *nums = array(int);
    int expected[] = {10, 15};

    for (int i = 0; i < 5; ++i) {
        array_append(nums, i * 5);
    }

    array_remove(nums, 1);
    array_remove(nums, 3);
    array_remove(nums, 0);

    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
        MU_ASSERT_FMT(expected[i] == nums[i], "Expect (%d), but got (%d)",
                      expected[i], nums[i]);
    }

    MU_ASSERT_FMT(2 == array_len(nums), "Expect (%d), but got (%lu)", 2,
                  array_len(nums));

    MU_PASS;
}

static char *test_array_fast_remove(void) {
    int *nums = array(int);
    int expected[] = {30, 50};

    for (int i = 1; i <= 5; ++i) {
        array_append(nums, i * 10);
    }

    array_fast_remove(nums, 1);
    array_fast_remove(nums, 3);
    array_fast_remove(nums, 0);

    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
        MU_ASSERT_FMT(expected[i] == nums[i], "Expect (%d), but got (%d)",
                      expected[i], nums[i]);
    }

    MU_ASSERT_FMT(2 == array_len(nums), "Expect (%d), but got (%lu)", 2,
                  array_len(nums));

    MU_PASS;
}

static char *all_tests(void) {
    MU_TEST(test_array_init);
    MU_TEST(test_array_expand);
    MU_TEST(test_array_append);
    MU_TEST(test_array_remove);
    MU_TEST(test_array_fast_remove);
    MU_PASS;
}
