//cpp
#include<iostream>
#include<string>
#include<vector>

#include "src/api/api.h"
using namespace std;

int main() {

    cout << "---------��������Ҫ��ȡ���ݵ�app����������Ҫ���еĲ���------------" << endl;
    cout << "---------����finish��������----exit�˳�����--------" << endl;

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
    cout << "���" << endl;
}
    return 0;
}