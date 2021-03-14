//
// Created by nedkoudlg on 19.04.20 г..
//

#ifndef TEDOC__2_USER_H
#define TEDOC__2_USER_H
#include <iostream>
#include "Challange.h"

class User {
private:
    char* username;
    unsigned short age;
    char* email;
    Challange* uncompletedChallanges;
    unsigned uncompletedBr;
    //unsigned numberOfUncompleteChallanges;
protected:
    unsigned id;
    static unsigned idCount;
    unsigned numberOfUncompleteChallanges;
    static unsigned stataicNumberOfUncompletedChallenges;

public:
    //constructors
    User ();
    User (const char* _username , const unsigned short _age , const char* _email);
    User (const char* _username , const unsigned short _age);
    User (const char* _username , const char* _email);
    User (const User& user);
    User& operator = (const User& other);
    ~User ();
    //getters
    char* getUsername () const;
    unsigned short getAge () const;
    char* getEmail () const;
    unsigned getId () const;
    Challange* getUncompletedChallanges() const;
    unsigned getUncompletedChallangesSize() const;
    //setters
    bool setUsername (const char* _username);
    bool setAge (const unsigned short _age);
    bool setEmail (const char* _email);
    void setUncompletedChallanges(const Challange* _uncompletedChallanges , unsigned size);
    bool addUncompletedChallenge(Challange& uncompletedChallange);
    bool removeUncompletedChallenge(const char* name);
    void finish(const char* tagOfUncompletedChallange, unsigned userId , float rate);
    void showInfo();
};




#endif //TEDOC__2_USER_H
