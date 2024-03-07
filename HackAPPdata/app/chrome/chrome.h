#ifndef __CHROME_H__
#define __CHROME_H__
//cpp
#include <vector>


#include "app/app.h"
using namespace std;

//windows
vector<unsigned char> getMasterkey();

class Chrome : public APP {
    
public:
    
    Chrome(vector<unsigned char> k) : MasterKey(k) {}

    virtual ~Chrome() = default;

    virtual void decryptCookie() override;
 
private:
    vector<unsigned char> MasterKey;

};



#endif