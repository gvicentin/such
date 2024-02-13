#ifndef MINUNIT_H
#define MINUNIT_H

#define MU_MSGBUF_LEN 1024
#define MU_PASS       return NULL
#define MU_MSG_FMT    "%s | %s::%d -> "
#define MU_MSG_ARGS   __FILE__, __FUNCTION__, __LINE__

#define MU_ASSERT(test, message)                                               \
    do {                                                                       \
        if (!(test)) {                                                         \
            sprintf(mu_assert_msg, MU_MSG_FMT message, MU_MSG_ARGS);           \
            return mu_assert_msg;                                              \
        }                                                                      \
    } while (0)

#define MU_ASSERT_FMT(test, msg_format, ...)                                   \
    do {                                                                       \
        if (!(test)) {                                                         \
            sprintf(mu_assert_msg, MU_MSG_FMT msg_format, MU_MSG_ARGS,         \
                    ##__VA_ARGS__);                                            \
            return mu_assert_msg;                                              \
        }                                                                      \
    } while (0)

#define MU_TEST(test)                                                          \
    do {                                                                       \
        char *message = test();                                                \
        mu_tests_run++;                                                        \
        if (message)                                                           \
            return message;                                                    \
    } while (0)

extern char mu_assert_msg[MU_MSGBUF_LEN];
extern int mu_tests_run;

#endif // MINUNIT_H
