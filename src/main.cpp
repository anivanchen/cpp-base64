/*
  implementation of base64 encoding and decoding in cpp.
  Copyright (C) 2024  Ivan Chen

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
