#include <stdio.h>
#include <string.h>

void tail(char t[], char list[]) {
    for (int i = 1; i < strlen(list); i++)
        t[i - 1] = list[i];

    // add the null character at the end
    t[strlen(list) - 1] = '\0';
}

int levenshtein(char a[], char b[]) {
    printf("A:%s\n", a);
    printf("B:%s\n", b);

    // a per word based implementation of the levenshtein algorithm
    // case where one string is empty
    if (strlen(a) == 0 && strlen(b) == 0) {
        printf("Both Empty\n");
        return 0;
    }

    if (strlen(a) == 0) {
        printf("A is Empty\n");
        return strlen(b);
    } else if (strlen(b) == 0) {
        printf("B is Empty\n");
        return strlen(a);
    }
    // if they match recurse on the rest of the string after the first

    char tailA[strlen(a) - 1];
    tail(tailA, a);
    char tailB[strlen(b) - 1];
    tail(tailB, b);
    // if they don't match recurse on all combinations and return the mininum
    int skipBoth = 1 + levenshtein(tailA, tailB);
    int skipA = 1 + levenshtein(tailA, b);
    int skipB = 1 + levenshtein(a, tailB);
    printf("Distance:%d,%d,%d", skipBoth, skipA, skipB);

    if (skipBoth < skipA && skipBoth < skipB)
        return skipBoth;
    else if (skipA < skipBoth && skipA < skipB)

        return skipBoth;
    return skipB;
}

int main() {
    char a[] = "Hello";
    char b[] = "Hallo";
    printf("Running");
    printf("levenshtein distance: %d", levenshtein(a, b));
}
