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

int levenshtein(char *a, char *b) {
    printf("A:%s\n", a);
    printf("B:%s\n", b);

    // a per word based implementation of the levenshtein algorithm
    // case where one string is empty

    if (strlen(a) == 0) {
        printf("A is Empty\n");
        return strlen(b);
    } else if (strlen(b) == 0) {
        printf("B is Empty\n");
        return strlen(a);
    }

    // get tails of both strings
    char tailA[strlen(a) - 1];
    tailString(tailA, a);
    char tailB[strlen(b) - 1];
    tailString(tailB, b);

    // if they match recurse on the rest of the string after the first
    if (a[0] == b[0])
        return levenshtein(tailA, tailB);

    // if they don't match recurse on all combinations and return the mininum
    int skipBoth = 1 + levenshtein(tailA, tailB);
    int skipA = 1 + levenshtein(tailA, b);
    int skipB = 1 + levenshtein(a, tailB);
    printf("Distance:%d,%d,%d\n", skipBoth, skipA, skipB);

    if (skipBoth <= skipA && skipBoth <= skipB)
        return skipBoth;
    else if (skipA <= skipBoth && skipA <= skipB)
        return skipBoth;
    return skipB;
}

int main() {
    char a[] = "Health";
    char b[] = "Health";
    printf("Running\n");
    printf("levenshtein distance:%d\n", levenshtein(a, b));
}
