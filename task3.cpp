#include <fstream>        
#include <iostream>
#include <string>

using namespace std;

void compressFile(const string &inputFile, const string &outputFile) {
	
  ifstream in(inputFile);        
  ofstream out(outputFile);      

  if (!in.is_open() || !out.is_open()) {
    cerr << "Error opening file(s)!" << endl;      
    return;
  }

  char present_char, old_char;
  int count = 1;

  in.get(old_char);           
  while (in.get(present_char)) {             
    if (present_char == old_char) {
      ++count;
    } else {
      out.put(old_char);
      out << count;
      old_char = present_char;
      count = 1;
    }
  }

  out.put(old_char);               
  out << count;

  in.close();
  out.close();
}

void decompressFile(const string &inputFile, const string &outputFile) {
  ifstream in(inputFile);
  ofstream out(outputFile);

  if (!in.is_open() || !out.is_open()) {
    cerr << "Error opening file(s)!" << endl;
    return;
  }

  char present_char;
  int count;

  while (in.get(present_char) && in >> count) {
    for (int i = 0; i < count; ++i) {
      out.put(present_char);
    }
  }

  in.close();
  out.close();
}

int main() {
  string inputFile = "input.txt";
  string compressedFile = "compressed.txt";
  string decompressedFile = "decompressed.txt";

  compressFile(inputFile, compressedFile);
  cout << "File compressed successfully." << endl;

  decompressFile(compressedFile, decompressedFile);
  cout << "File decompressed successfully." << endl;

  return 0;
}
