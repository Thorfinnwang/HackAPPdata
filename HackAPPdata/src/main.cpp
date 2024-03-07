//cpp
#include<iostream>
#include<string>
#include<vector>

#include "src/api/api.h"
using namespace std;

int main() {

    cout << "---------请输入想要获取数据的app，再输入想要进行的操作------------" << endl;
    cout << "---------输入finish结束输入----exit退出程序--------" << endl;

vector<string> ItemList;
string item;
while (true) {

    while (true) {

        cin >> item;
        if (item == "finish") {
            break;
        }
        if (item == "exit") {
            exit(0);
        }
        ItemList.push_back(item);
    }

    excute(ItemList);
    ItemList.clear();
    cout << "完毕" << endl;
}
    return 0;
}