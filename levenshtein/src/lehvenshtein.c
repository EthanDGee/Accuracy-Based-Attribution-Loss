#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void tailString(char t[], char list[]) {
    // if 't' is empty exit early
    if (strlen(list) == 0) {
        t[0] = '\0';
        return;
    };

    int lengthList = strlen(list);
    for (int i = 1; i < lengthList; i++)
        t[i - 1] = list[i];

    // add the null character at the end
    t[strlen(list) - 1] = '\0';
}

int min(int a, int b) {
    // returns the lowest nonnegative number
    if (a < b && a >= 0)
        return a;
    if (b < 0)
        return a;
    return b;
}

void print_2d_array(int rows, int cols, int array[rows][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}
int levenshtein(char *a, char *b) {
    // a per word based implementation of the levenshtein algorithm
    // case where one string is empty

    int a_length = strlen(a);
    int b_length = strlen(b);

    if (a_length == 0)
        return b_length;
    else if (b_length == 0)
        return a_length;

    // create the memoization array
    int results[a_length][b_length];

    // set base cases
    if (a[0] == b[0])
        results[0][0] = 0;
    else
        // requires deletion and insertion
        results[0][0] = 2;

    for (int a_i = 0; a_i < a_length; a_i++) {
        for (int b_i = a_i; b_i < b_length; b_i++) {
            // skip base
            if (a_i == 0 && b_i == 0)
                continue;

            // match case
            if (a_i == b_i) { // same length
                if (a[a_i] == b[b_i])
                    results[a_i][b_i] = results[a_i - 1][b_i - 1];
                else
                    results[a_i][b_i] = results[a_i - 1][b_i - 1] + 2;
            } else {
                if (a[a_i] == b[b_i]) {

                    int use = results[a_i - 1][b_i - 1];
                    int dont = results[a_i][b_i - 1] + 2;
                    results[a_i][b_i] = min(use, dont);
                } else
                    // add letter to previous
                    results[a_i][b_i] = results[a_i][b_i - 1] + 1;
            }
        }
    }
    // print_2d_array(a_length, b_length, results);
    return results[a_length - 1][b_length - 1];
}

bool testLehvenshtein(char *a, char *b, int expectedResult) {
    int result = levenshtein(a, b);
    if (result == expectedResult)
        printf("%s-%s: Passed\n", a, b);
    else
        printf("%s-%s: Failed Expected %d Got %d\n", a, b, expectedResult,
               result);

    return result == expectedResult;
}

int main() {
    printf("\nSingle Character\n");
    testLehvenshtein("a", "a", 0);
    testLehvenshtein("b", "a", 2);
    testLehvenshtein("a", "b", 2);
    testLehvenshtein("a", "", 1);
    testLehvenshtein("", "b", 1);

    printf("\nIdentical Strings\n");
    testLehvenshtein("", "", 0);
    testLehvenshtein("Hello", "Hello", 0);

    printf("\nEmpty Strings\n");
    testLehvenshtein("", "abc", 3);
    testLehvenshtein("abc", "", 3);

    printf("\nGeneral Cases\n");
    testLehvenshtein("kitten", "sitting", 5);
    testLehvenshtein("flaw", "lawn", 2);
    testLehvenshtein("gumbo", "gambol", 3);
    testLehvenshtein("book", "back", 4);

    printf("\nCase Sensitivity\n");
    testLehvenshtein("abc", "ABC", 3);
    testLehvenshtein("Test", "test", 1);

    printf("\nPrefix/Suffix\n");
    testLehvenshtein("testing", "test", 3);
    testLehvenshtein("test", "testing", 3);

    printf("\nTranspositions\n");
    testLehvenshtein("abcdef", "abcedf", 2);

    printf("\nLong Strings\n");
    testLehvenshtein("abcdefghij", "abcdefghij", 0);
    testLehvenshtein("abcdefghij", "jihgfedcba", 10);

    return 0;
}
