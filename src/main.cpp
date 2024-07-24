#include "main.hpp"

#define BITS_TO_READ 6

const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string base64_encode(const vector<char>& data) {
    string encoded;
    int i = 0;
    int j = 0;
    unsigned char ca3[3];
    unsigned char ca4[4];

    for (auto c : data) {
        ca3[i++] = c;
        if (i == 3) {
            ca4[0] = (ca3[0] & 0xfc) >> 2;
            ca4[1] = ((ca3[0] & 0x03) << 4) + ((ca3[1] & 0xf0) >> 4);
            ca4[2] = ((ca3[1] & 0x0f) << 2) + ((ca3[2] & 0xc0) >> 6);
            ca4[3] = ca3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                encoded += base64_chars[ca4[i]];
            i = 0;
        }
    }

    if (i) {
        for(j = i; j < 3; j++)
            ca3[j] = '\0';

        ca4[0] = (ca3[0] & 0xfc) >> 2;
        ca4[1] = ((ca3[0] & 0x03) << 4) + ((ca3[1] & 0xf0) >> 4);
        ca4[2] = ((ca3[1] & 0x0f) << 2) + ((ca3[2] & 0xc0) >> 6);
        ca4[3] = ca3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            encoded += base64_chars[ca4[j]];

        while((i++ < 3))
            encoded += '=';
    }

    return encoded;
}

string base64_decode(const vector<char>& encoded_string) {
    string decoded;
    int i = 0;
    int in_len = encoded_string.size();
    int j = 0;
    int index = 0;

    unsigned char ca4[4], ca3[3];

    while (in_len-- && (encoded_string[index] != '=') && (isalnum(encoded_string[index]) || (encoded_string[index] == '+') || (encoded_string[index] == '/'))) {
        ca4[i++] = encoded_string[index]; index++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                ca4[i] = base64_chars.find(ca4[i]);

            ca3[0] = (ca4[0] << 2) + ((ca4[1] & 0x30) >> 4);
            ca3[1] = ((ca4[1] & 0xf) << 4) + ((ca4[2] & 0x3c) >> 2);
            ca3[2] = ((ca4[2] & 0x3) << 6) + ca4[3];

            for (i = 0; (i < 3); i++)
                decoded += ca3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            ca4[j] = 0;

        for (j = 0; j < 4; j++)
            ca4[j] = base64_chars.find(ca4[j]);

        ca3[0] = (ca4[0] << 2) + ((ca4[1] & 0x30) >> 4);
        ca3[1] = ((ca4[1] & 0xf) << 4) + ((ca4[2] & 0x3c) >> 2);
        ca3[2] = ((ca4[2] & 0x3) << 6) + ca4[3];

        for (j = 0; (j < i - 1); j++) decoded += ca3[j];
    }

    return decoded;
}

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
