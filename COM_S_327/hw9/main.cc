
#include <iostream>
#include <fstream>
#include "intbox.hh"

using namespace std;

class expected {
    const char* choices;
    char received;
  public:
    expected(const char* ch, char got) {
      choices = ch;
      received = got;
    }
    friend ostream& operator<< (ostream& os, expected e);
};

ostream& operator<< (ostream &os, expected e)
{
  os << "Invalid character: '" << e.received << "'; expected ";
  for (unsigned i=0; e.choices[i]; i++) {
    if (i) os << " or ";
    os << "'" << e.choices[i] << "'"; 
  }
  return os;
}


void skip_to_eol(istream &in)
{
  for (;;) {
    int c = in.get();
    if ('\n' == c) return;
    if (EOF == c) return;
  }
}

void pull_char(istream &in, const char* sugar)
{
  char c;
  in >> c;
  if (!in) throw "Unexpected EOF";
  if (c != sugar[0]) throw expected(sugar, c);
}

intbox* parse_intbox(istream &in);

intbox* parse_singleton(istream &in)
{
  int value;
  in >> value;
  return new singleton(value);
}

intbox* parse_interval(istream &in)
{
  int low, high;
  pull_char(in, "[");
  in >> low;
  pull_char(in, ",");
  in >> high;
  pull_char(in, "]");
  return new interval(low, high);
}

intbox* parse_collection(istream &in)
{
  unsigned size;
  in >> size;
  collection* C = new collection(size);
  pull_char(in, "{");
  for (unsigned i=0; i<size; i++) {
    if (i) pull_char(in, ",");
    C->set_item(i, parse_intbox(in));
  }
  pull_char(in, "}");
  return C;
}

intbox* parse_intbox(istream &in)
{
  for (;;) {
    char c;
    in >> c;
    switch (c) {
      case '#':   skip_to_eol(in);
                  continue;

      case 's':   return parse_singleton(in);

      case 'i':   return parse_interval(in);

      case 'c':   return parse_collection(in);

      default:    throw expected("sic", c);
    }
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
    intbox* I = parse_intbox(input);

    if (0==I) {
      cout << "Null intbox\n";
      return 0;
    }

    cout << "Querying intbox: ";
    I->show(cout);
    cout << "\n";

    for (;;) {
      char c;
      input >> c;
      if (!input) break;
      if ('#' == c) {
        skip_to_eol(input);
        continue;
      }
      if (c != '?') throw expected("?", c);
      int value;
      input >> value;
      cout << value << ": ";
      if (I->contains(value)) cout << "YES\n";
      else                    cout << "NO\n";
    }
    delete I;
    return 0;
  }
  catch (expected e) {
    cerr << "Parse error: " << e << "\n";
  }
  catch (const char* e) {
    cerr << e << "\n";
  }
  return 1;
}

