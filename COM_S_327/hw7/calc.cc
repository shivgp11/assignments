
#include <iostream>
#include "string.h"
#include "rational.hh"

// #define DEBUG

using namespace std;

int stack_underflow(int i)
{
  cerr << "Stack underflow at argument " << i << "\n";
  return 1;
}

int main(int argc, char** argv)
{
  rational stack[argc];
  unsigned top = 0;

  int i;
  for (i=1; i<argc; i++) {
#ifdef DEBUG
    cerr << "processing arg: " << argv[i] << endl;
#endif
    char* endptr;
    long val = strtol(argv[i], &endptr, 10);
    if (0==*endptr) {
      /* Argument was an integer */
      stack[top++] = val;
      continue;
    }
    if (0==strcmp("+", argv[i])) {
      if (top<2) return stack_underflow(i);
      rational right = stack[--top];
      rational left = stack[--top];
      stack[top++] = left + right;
      continue;
    }
    if (0==strcmp("-", argv[i])) {
      if (top<2) return stack_underflow(i);
      rational right = stack[--top];
      rational left = stack[--top];
      stack[top++] = left - right;
      continue;
    }
    if (0==strcmp("*", argv[i])) {
      if (top<2) return stack_underflow(i);
      rational right = stack[--top];
      rational left = stack[--top];
      stack[top++] = left * right;
      continue;
    }
    if (0==strcmp("/", argv[i])) {
      if (top<2) return stack_underflow(i);
      rational right = stack[--top];
      rational left = stack[--top];
      stack[top++] = left / right;
      continue;
    }
    cerr << "Unexpected argument: '" << argv[i] << "'\n";
    return 1;
  }
  if (top < 1) {
    /* There must have been no arguments */
    cout << "Usage: postfix expression passed as arguments\n";
    return 0;
  }
  if (top > 1) {
    cerr << "Not enough operators\n";
    return 1;
  }
  cout << stack[0] << "\n";
  return 0;
}
