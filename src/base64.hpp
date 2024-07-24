/*
  implementation of base64 encoding and decoding in cpp.
  Copyright (C) 2024  Ivan Chen
*/

#ifndef BASE64_H
#define BASE64_H

#include <vector>
#include <string>
#include <cstring>

using namespace std;

string base64_encode(const vector<char>& data);
string base64_decode(const vector<char>& data);

#endif
