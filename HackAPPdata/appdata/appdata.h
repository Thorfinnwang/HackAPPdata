#pragma once

#ifndef __APPDATA__
#define __APPDATA__
//cpp
#include <vector>

using namespace std;
//cookie
bool decryptCipher(vector<unsigned char>& key);

//
namespace ChromeWin {
    constexpr int KeyLength = 256 / 8;
    constexpr int VersionLength = 3;
    constexpr int NonceLength = 96 / 8;
}

#endif // !__APPDATA__