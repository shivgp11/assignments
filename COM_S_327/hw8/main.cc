
#include <iostream>
#include <fstream>
#include "list.hh"

// #define DEBUG

using namespace std;

void skip_to_eol(istream &in)
{
  for (;;) {
    int c = in.get();
    if ('\n' == c) return;
    if (EOF == c) return;
  }
}

int main(int argc, char** argv)
{
  ifstream file;
  if (argc>2) {
    cerr << "Usage: " << argv[0] << " (input file)\n";
    cerr << "  If the input file is missing, we read from standard input\n";
    return 1;
  }
  if (argc==2) {
    file.open(argv[1], ifstream::in);
    if (!file) {
      cerr << "Couldn't open file: " << argv[1] << "\n";
      return 1;
    }
  }
  istream &input = (2==argc) ? file : cin;
  try {
    list_builder LB;
    for (;;) {
      char c;
      int value;

      input >> c;
      if (!input) return 0;

      switch (c) {
        case 'F':   input >> value;
                    LB.add_to_front(value);
                    continue;

        case 'B':   input >> value;
                    LB.add_to_back(value);
                    continue;

        case 'L':   {
                      fixed_list L(LB);
                      cout << "List is now: " << L << "\n";
                      continue;
                    }

        case 'R':   LB.reset();
                    continue;

        case '#':   skip_to_eol(input);
                    continue;

        default:    throw c;
      }
    }
  }
  catch (char e) {
    cerr << "Unexpected character: " << e << "\n";
  }
  catch (char* e) {
    cerr << "Caught error: " << e << "\n";
  }
  return 1;
}

