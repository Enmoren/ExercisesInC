/*
 * Author: Enmo Ren
 * Copyright (c) Enmo Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software.
 *
 * This program creates minunit test on function char *icmpcode_v4(int code)
 * in util.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "util.h"
#include "minunit.h"

int tests_run = 0;

int test1 = 1;
int test2 = 20;

/*
  test_test1: run minunit test to check icmpcode function in util.c
  1 is used for input,"host unreachable" should be returned
  returns: 0 if test pass, msg if test failed
*/

static char * test_test1() {
    char *res = icmpcode_v4(test1);
    char *msg = "Test 1 failed: code 1 should return \"host unreachable\"";
    mu_assert(msg, strcmp("host unreachable", res) == 0);
    return 0;
}

/*
  test_test2: run minunit test to check icmpcode function in util.c
  20 is used for input, "[unknown code]" should be returned
  returns: 0 if test pass, msg if test failed
*/
static char * test_test2() {
    char *res = icmpcode_v4(test2);
    char *msg = "Test 2 failed: code 20 should return \"[unknown code]\"";
    mu_assert("Test 2 failed: code 20 should return \"[unknown code]\"", strcmp("[unknown code]", res) == 0);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_test1);
    mu_run_test(test_test2);
    return 0;
}

/*
  Run all tests and print error messages or "ALL TESTS PASSED"
*/
int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
