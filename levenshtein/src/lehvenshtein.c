#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 256
#define MAX_WORDS 2048

void tailString(const char list[], char t[]) {
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

void extractSubstring(const char string[], const int start, const int end,
                      char result[]) {
    // returns a substring of `string` based on the indexes (inclusive)
    int len = strlen(string);

    if (start < 0 || end > len || start >= end) {
        result[0] = '\0';
        return;
    }

    for (int i = start; i <= end; i++) {
        result[i] = string[i];
    }

    result[end - start] = '\0';
}

int splitString(const char string[], char results[][MAX_WORD_LENGTH]) {

    // takes a string and splits it by white space characters
    // returns the words found in the form of a list in results
    // and the number of words in the return call

    int len = strlen(string);

    char whitespace[] = " \t\n";
    int bufferStart = 0;
    int wordNumber = 0;

    // loop through the string and add each new word to results
    for (int i = 0; i < len; i++) {
        if (strchr(whitespace, string[i]) != NULL) {
            if (bufferStart < i && wordNumber < MAX_WORDS) {
                extractSubstring(string, bufferStart, i - 1,
                                 results[wordNumber]);
                wordNumber++;
            }
            bufferStart = i + 1;
        }
    }

    // also extract last word after the loop
    if (bufferStart < len && wordNumber < MAX_WORDS) {
        extractSubstring(string, bufferStart, len - 1, results[wordNumber]);
        wordNumber++;
    }

    return wordNumber;
}

int min(int a, int b) {
    // returns the lowest nonnegative number
    if (a < b && a >= 0)
        return a;
    if (b < 0)
        return a;
    return b;
}

void print_2d_array(const int rows, const int cols,
                    const int array[rows][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

int levenshtein(char *a, char *b) {
    int a_length = strlen(a);
    int b_length = strlen(b);

    int results[a_length + 1][b_length + 1];

    // Initialize base cases
    for (int i = 0; i <= a_length; i++)
        results[i][0] = i;
    for (int j = 0; j <= b_length; j++)
        results[0][j] = j;

    // Fill the matrix
    for (int i = 1; i <= a_length; i++) {
        for (int j = 1; j <= b_length; j++) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            int deletion = results[i - 1][j] + 1;
            int insertion = results[i][j - 1] + 1;
            int substitution = results[i - 1][j - 1] + cost;
            results[i][j] = min(deletion, min(insertion, substitution));
        }
    }

    return results[a_length][b_length];
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
    testLehvenshtein("kitten", "sitting", 3);
    testLehvenshtein("flaw", "lawn", 2);
    testLehvenshtein("gumbo", "gambol", 2);
    testLehvenshtein("book", "back", 2);

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
