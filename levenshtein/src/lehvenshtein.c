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
    // returns the lowest nonnecative number
    if (a < b && a >= 0)
        return a;
    if (b < 0)
        return a;
    return b;
}

int levenshtein(char *a, char *b) {
    // printf("A:%s\n", a);
    // printf("B:%s\n", b);

    // a per word based implementation of the levenshtein algorithm
    // case where one string is empty

    int a_length = strlen(a);
    int b_length = strlen(b);

    if (a_length == 0) {
        printf("A is Empty\n");
        return b_length;
    } else if (b_length == 0) {
        printf("B is Empty\n");
        return a_length;
    }

    // create the memoization array
    int results[a_length][b_length];

    // set base cases
    if (a[0] == b[0])
        results[0][0] = 0;
    else
        // requires deletion and insertion
        results[0][0] = 2;

    for (int a_i = 0; a_i < a_length; a_i++) {
        for (int b_i = 0; b_i < b_length; b_i++) {
            // match case

            int scoreChange;
            if (a[a_i] == b[b_i])
                scoreChange = 0;
            else
                scoreChange = 1;

            // skip a case
            int skipA;
            int skipB;
            int skipBoth;

            if (a_i != 0)
                skipA = results[a_i - 1][b_i];
            else
                skipA = INT_MIN; // this is done to prevent integer overflow

            // skip b case
            if (b_i != 0)
                skipB = results[a_i][b_i - 1];
            else
                skipB = INT_MIN;

            // skip both case
            if (a_i != 0 && b_i != 0)
                skipBoth = results[a_i - 1][b_i - 1];
            else
                skipBoth = INT_MIN;

            // set best to min + scoreChange
            results[a_i][b_i] = min(skipA, min(skipB, skipBoth)) + scoreChange;
        }
    }

    return results[a_length - 1][b_length - 1];
}

bool testLehvenshtein(char *a, char *b, int expectedResult) {
    printf("Testing %s-%s\n", a, b);
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

    return 0;
}
