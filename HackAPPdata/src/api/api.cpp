#pragma once
//cpp
#include <vector>
#include <string>
#include <memory>
#include<utility>
#include<iostream>

#include "src/api/api.h"
#include "app/app.h"
#include "app/chrome/chrome.h"
//#include "app/edge/edge.h"

#define WIN

using namespace std; 

#ifdef WIN
void excute(const vector<string>& ItemList) {

    if (ItemList[0] == "chrome") {
        vector<unsigned char> masterkey = getMasterkey();
        unique_ptr<APP> ch = make_unique<Chrome>(masterkey);

        for (int i = 1; i < ItemList.size(); i++) {

            if (ItemList[i] == "cookie") {
                ch->decryptCookie();
            }
            //if (ItemList[i] == "passwd") {} 
            else {
                std::cout << "暂不提供该数据解析服务" << std::endl;
            }
        }
    }
    /*
    else if (ItemList[0] == "edge") {
        unique_ptr<APP> ed = make_unique<Edge>();
        for (int i = 1; i < ItemList.size(); i++) {
            if (ItemList[i] == "cookie") {
            }
            //if (ItemList[i] == "passwd") {}
        }
    }
    else if (ItemList[0] == "firefox") {
        unique_ptr<APP> ff = make_unique<Firefox>();
        for (int i = 1; i < ItemList.size(); i++) {
            if (ItemList[i] == "cookie") {
            }
            //if (ItemList[i] == "passwd") {}
        }
    }
    else if (ItemList[0] == "ie") {
        unique_ptr<APP> ie = make_unique<IE>();
        for (int i = 1; i < ItemList.size(); i++) {
            if (ItemList[i] == "cookie") {
            }
            //if (ItemList[i] == "passwd") {}
        }
    }
    else if (ItemList[0] == "opera") {
        unique_ptr<APP> op = make_unique<Opera>();
        for (int i = 1; i < ItemList.size(); i++) {
            if (ItemList[i] == "cookie") {
            }
            //if (ItemList[i] == "passwd") {}
        }
    }
    else if (ItemList[0] == "safari") {
        unique_ptr<APP> sf = make_unique<Safari>();
        for (int i = 1; i < ItemList.size(); i++) {
            if (ItemList[i] == "cookie") {
            }
            //if (ItemList[i] == "passwd") {}
        }
    }
    else if (ItemList[0] == "qq") {
        unique_ptr<APP> qq = make_unique<QQ>();
        vector<unsigned char>MasterKey =
    }
    */
    else {
        std::cout << "暂不提供该软件服务" << std::endl;
    }
}

#endif // !WIN