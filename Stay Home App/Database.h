//
// Created by nedkoudlg on 21.04.20 г..
//

#ifndef TEDOC__2_DATABASE_H
#define TEDOC__2_DATABASE_H

#include "User.h"
#include "Challange.h"
class Database {
private:
    unsigned numberOfUsers;
    unsigned numberOfChallenges;
    User* usersDatabase;
    Challange* challangesDatabase;
    char* name;
public:
    Database();
    Database(char* name);
    ~Database();
    Database(const Database& rhs);
    Database& operator = (const Database& rhs);
    void addUser(const User& rhs);
    void addChallenge(const Challange& rhs);

    User getUser(const unsigned id);
    User* getUsersByName(const char* name);
    Challange getChallenge(const char* tag);
};


#endif //TEDOC__2_DATABASE_H
