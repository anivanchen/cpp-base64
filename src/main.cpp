#include "main.hpp"
#include "base64.hpp"

int main(int argc, char* argv[]) {

  ifstream file(argv[2], ios::binary | ios::ate);
  streamsize size = file.tellg();
  file.seekg(0, ios::beg);

  vector<char> buffer(size);

  if (file.read(buffer.data(), size)) {
    cout << "Read " << size << " bytes" << endl;
  } else {
    cerr << "Failed to read " << size << " bytes" << endl; 
    return 1;
  }

  file.close();

  if (strcmp(argv[1], "encode") == 0) {
    cout << base64_encode(buffer);
  }

  else if (strcmp(argv[1], "decode") == 0) {
    cout << base64_decode(buffer);
  }

  return 0;
}
