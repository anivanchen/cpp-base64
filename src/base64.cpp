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

#include "base64.hpp"

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

string base64_decode(const vector<char>& data) {
    string decoded;
    int i = 0;
    int in_len = data.size();
    int j = 0;
    int index = 0;

    unsigned char ca4[4], ca3[3];

    while (in_len-- && (data[index] != '=') && (isalnum(data[index]) || (data[index] == '+') || (data[index] == '/'))) {
        ca4[i++] = data[index]; index++;
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
