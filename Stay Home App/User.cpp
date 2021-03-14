#include <iostream>
#include <cstring>
#include "User.h"
#include "Challange.h"

User::User () : username(nullptr) , age(0) , email(nullptr) , id(0) , uncompletedChallanges(nullptr), uncompletedBr(0) {}
User::User (const char* _username , const unsigned short _age , const char* _email) : uncompletedBr(0) {
    setUsername (_username);
    setAge (_age);
    setEmail (_email);
    id=++idCount;
}
User::User (const char* _username , const unsigned short _age):uncompletedBr(0) {
    setUsername (_username);
    setAge (_age);
    setEmail ("Unknown");
    id=++idCount;
}
User::User (const char* _username , const char* _email):uncompletedBr(0) {
    setUsername (_username);
    setAge (0);
    setEmail (_email);
    id=++idCount;
}
//copy constructor
User::User (const User& user) {
    setUsername(user.username);
    setAge(user.age);
    setEmail(user.email);
    this->id = user.id;
    setUncompletedChallanges(user.uncompletedChallanges , user.numberOfUncompleteChallanges );
    this->numberOfUncompleteChallanges = user.numberOfUncompleteChallanges;
    this->uncompletedBr = user.uncompletedBr;
}
//operator =
User& User::operator = (const User& other) {
    if(this != &other) {
        setUsername(other.username);
        setAge(other.age);
        setEmail(other.email);
        this->id = other.id;
        this->uncompletedChallanges = other.uncompletedChallanges;
        this->uncompletedBr = other.uncompletedBr;
    }
    return *this;
}
//destructor
User::~User () {
    delete[] username;
    delete[] email;
    delete[] uncompletedChallanges;
}
//getters
char* User::getUsername () const {
    return username;
}
unsigned short User::getAge () const { return age; }
char* User::getEmail () const { return email; }
unsigned User::getId() const  { return id; }
Challange* User::getUncompletedChallanges() const { return uncompletedChallanges; }

//setters
bool User::setUsername (const char* _username) {
    username = new char[strlen(_username)+1];
    strcpy(username,_username);
    return true;
}
bool User::setAge (const unsigned short _age) {
    if (_age > 90) {
        std::cout << "Registation Fail.You are too old for this App" << std::endl;
        return false;
    }
    age = _age;
    return true;
}
bool User::setEmail (const char* _email) {
    unsigned emailLenght = strlen(_email);
    if (emailLenght > 100)
        return false;
    email = new char[emailLenght+1];
    strcpy(email, _email);
    return true;
}
void User::setUncompletedChallanges(const Challange* _uncompletedChallanges , unsigned size) {
    delete[] uncompletedChallanges;
    uncompletedChallanges = new Challange[size];
    for(unsigned i = 0; i < size; i++) {
        uncompletedChallanges[i] = _uncompletedChallanges[i];
    }
    numberOfUncompleteChallanges= size;
}
bool User::addUncompletedChallenge(Challange& uncompletedChallange) {
    numberOfUncompleteChallanges = ++stataicNumberOfUncompletedChallenges;
    uncompletedBr++;
    Challange* newUncompletedChallanges = new Challange[uncompletedBr];
    for(int i = 0; i < uncompletedBr-1; i++){
        newUncompletedChallanges[i] = uncompletedChallanges[i];
    }
    uncompletedChallange.addCount();
    newUncompletedChallanges[uncompletedBr-1] = uncompletedChallange;
    this->uncompletedChallanges = newUncompletedChallanges;
    return true;
}
bool User::removeUncompletedChallenge(const char* name) {
    int index = -1;
    for(int i = 0; i < uncompletedBr; ++i){
        if(!strcmp(uncompletedChallanges[i].getTag(), name)) {
            index = i;
            break;
        }
    }
    if(index == -1)
        return false;
    Challange* newUncompletedChallanges = new Challange[uncompletedBr-1];
    unsigned localbr=0;
    for(int i = 0; i < uncompletedBr; i++){
        if(i!=index) {
            newUncompletedChallanges[localbr] = uncompletedChallanges[i];
            localbr++;
        }
    }
    uncompletedBr--;
    this->uncompletedChallanges = newUncompletedChallanges;
//    uncompletedChallanges[index] = uncompletedChallanges[numberOfUncompleteChallanges - 1];
//    --numberOfUncompleteChallanges;
    return true;
}
void User::finish(const char* tagOfUncompletedChallange, unsigned userId , float rate) {
    if(rate > 10.0 || rate < -5.0) {
        std::cout << "Sorry. Invalid rating! The challenge is not completed, yet." << std::endl;
    }
    else {
        if(this->id == userId) {
            for(int i = 0;i < uncompletedBr; ++i) {
                if(!strcmp(uncompletedChallanges[i].getTag() , tagOfUncompletedChallange)){
                    uncompletedChallanges[i].setRate(rate);
                    break;
                }
            }
            removeUncompletedChallenge(tagOfUncompletedChallange);
            std::cout << "Well done! May the challenge be with you!" << std::endl;
        }
    }
}
void User::showInfo() {
    std::cout <<" "<< this->getUsername() <<" "<< this->getAge() <<" "<< this->getEmail() <<" "<< std::endl;
}

unsigned User::getUncompletedChallangesSize() const {
    //return this->numberOfUncompleteChallanges;
    return this->uncompletedBr;
}



