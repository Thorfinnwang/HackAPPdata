#pragma once
#ifndef __APP_H__
#define __APP_H__

class APP {
public:
    explicit APP() {}
    virtual ~APP() = default;
    
    virtual void decryptCookie() = 0;
    //virtual void decryptPasswd() = 0;

};

#endif // !__APP_H__
