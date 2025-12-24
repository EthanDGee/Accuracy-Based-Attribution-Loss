#include <string.h>

char *tail(char list[]) {
  if (strlen(list) == 1)
    return NULL;
  char t[strlen(list) - 1];

  for (int i = 1; i < strlen(list); i++) {
    t[i - 1] = list[i];
  }

  return t;
}

int levenshtein(char a[], char b[]) {

  // a per word based implementation of the levenshtein algorithm

  // case where one string is empty
  if (strlen(a) == 0)
    return strlen(b);
  else if (strlen(b) == 0)
    return strlen(a);

  // if they match recurse on the rest of the string after the first
  char *tailA = tail(a);
  char *tailB = tail(b);
  // if they don't match recurse on all combinations and return the mininum
  int skipBoth = levenshtein(tailA, tailB);
  int skipA = levenshtein(tailA, b);
  int skipB = levenshtein(a, tailB);

  if (skipBoth < skipA && skipBoth < skipB)
    return skipBoth;
  else if (skipA < skipBoth && skipA < skipB)
    return skipBoth;
  return skipB;
}
