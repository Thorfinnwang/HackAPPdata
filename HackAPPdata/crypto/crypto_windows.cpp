//cpp
#include <vector>
#include <string>
#include <iostream>

//win
#include <Windows.h>
#include <Dpapi.h>


//crypto
#include"3rdparts/cryptopp/filters.h"
#include"3rdparts/cryptopp/base64.h"
#include"3rdparts/cryptopp/Hex.h"
#include"3rdparts/cryptopp/gcm.h"
#include"3rdparts/cryptopp/aes.h"


#include "crypto/crypto.h"
using namespace CryptoPP;
using namespace std;

bool DecryptStringWithDPAPI(string& Encryptedkey, vector<unsigned char>& Decryptedkey) {

	string Decoded;
	StringSource((byte*)Encryptedkey.data(), Encryptedkey.length(), true, new Base64Decoder(new StringSink(Decoded)));    //base64½âÂë	
	Encryptedkey = Decoded;
	Encryptedkey = Encryptedkey.substr(5); //É¾³ýÇ°5¸ö×Ö·û

	DATA_BLOB input;
	input.cbData = Encryptedkey.length();
	input.pbData = (BYTE*)Encryptedkey.data();

	DATA_BLOB output;

	if (!CryptUnprotectData(&input, nullptr, nullptr, nullptr, nullptr, 0, &output)) {


			cerr << "Decrypt() fail with number: " << GetLastError() << endl;
			system("pause");
			LocalFree(output.pbData);

			exit(-1);

	}


	Decryptedkey.assign((unsigned char*)output.pbData, (unsigned char*)(output.pbData + output.cbData));

	LocalFree(output.pbData);
	return true;
}

void AES_Decrypt(string& iv, string& cipher, vector<unsigned char> key, string& DecryptedValue)
{
	try
	{
		string Decoded;
		StringSource(iv, true, new HexDecoder(new StringSink(Decoded)));
		iv = Decoded;
		Decoded.clear();
		StringSource(cipher, true, new HexDecoder(new StringSink(Decoded)));
		cipher = Decoded;
		Decoded.clear();

		GCM< AES >::Decryption d;
		d.SetKeyWithIV((byte*)key.data(), key.size(), (byte*)iv.data(), iv.length());

		StringSource s(cipher, true,
			new AuthenticatedDecryptionFilter(
				d,
				new StringSink(DecryptedValue)
			));
	}
	catch (CryptoPP::Exception& e)
	{
		cerr << "Caught Exception..." << endl;
		cerr << e.what() << endl;
	}
}


