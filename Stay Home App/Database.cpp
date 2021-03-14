//
// Created by nedkoudlg on 21.04.20 г..
//

#include "Database.h"
#include <cstring>
Database::Database():numberOfUsers(0),numberOfChallenges(0) {
    usersDatabase = new User[1];
    challangesDatabase = new Challange[1];
    usersDatabase = nullptr;
    challangesDatabase = nullptr;
}
Database::Database(char *name):numberOfUsers(0),numberOfChallenges(0) {
    int len = strlen(name);
    this->name = new char [len+1];
    strcpy(this->name,name);
    usersDatabase = new User[1];
    challangesDatabase = new Challange[1];
    usersDatabase = nullptr;
    challangesDatabase = nullptr;
}
Database::~Database() {
    delete [] usersDatabase;
    delete [] challangesDatabase;
}

Database::Database(const Database &rhs) {
    if(this->usersDatabase != nullptr){
        delete [] usersDatabase;
    }
    if(this->challangesDatabase != nullptr){
        delete [] challangesDatabase;
    }
    this->usersDatabase = new User[rhs.numberOfUsers];
    this->challangesDatabase = new Challange[rhs.numberOfChallenges];

    for (int i = 0; i < rhs.numberOfUsers; ++i) {
        this->usersDatabase[i] = rhs.usersDatabase[i];
    }
    for (int i = 0; i < rhs.numberOfChallenges; ++i) {
        this->challangesDatabase[i] = rhs.challangesDatabase[i];
    }
    this->numberOfChallenges = rhs.numberOfChallenges;
    this->numberOfUsers = rhs.numberOfUsers;
}

Database &Database::operator=(const Database &rhs) {
    if(this!=&rhs){
        if(this->usersDatabase != nullptr){
            delete [] usersDatabase;
        }
        if(this->challangesDatabase != nullptr){
            delete [] challangesDatabase;
        }
        this->usersDatabase = new User[rhs.numberOfUsers];
        this->challangesDatabase = new Challange[rhs.numberOfChallenges];

        for (int i = 0; i < rhs.numberOfUsers; ++i) {
            this->usersDatabase[i] = rhs.usersDatabase[i];
        }
        for (int i = 0; i < rhs.numberOfChallenges; ++i) {
            this->challangesDatabase[i] = rhs.challangesDatabase[i];
        }
        this->numberOfChallenges = rhs.numberOfChallenges;
        this->numberOfUsers = rhs.numberOfUsers;
    }
    return *this;
}

void Database::addUser(const User &rhs) {
    User* newUsers = new User[this->numberOfUsers+1];
    for (int i = 0; i < numberOfUsers; ++i) {
        newUsers[i]=this->usersDatabase[i];
    }
    newUsers[this->numberOfUsers] = rhs;
    delete [] this->usersDatabase;
    this->usersDatabase = newUsers;
    this->numberOfUsers++;
}

User Database::getUser(const unsigned int id) {
    for (int i = 0; i < this->numberOfUsers; ++i) {
        if(usersDatabase[i].getId()==id){
            return usersDatabase[i];
        }
    }
}



