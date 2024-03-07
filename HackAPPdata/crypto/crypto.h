#pragma once
#ifndef __CRYPTO__
#define __CRYPTO__
//cpp
#include <string>
#include <vector>

using namespace std;

void AES_Decrypt(string& iv, string& cipher, vector<unsigned char> key, string& DecryptedValue);

bool DecryptStringWithDPAPI(string& Encryptedkey, vector<unsigned char>& Decryptedkey);

#endif // !__CRYPTO__