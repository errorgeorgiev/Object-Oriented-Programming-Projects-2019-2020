#pragma once

#include "Trip.h"
#include <fstream>
class User {
private:
    char* username;
    char* password;
    char* email;
    Trip* trips;
    unsigned numberOfTrips;
    char* fileName;
    std::ofstream output;
    std::ifstream input;
    void copy(Trip*& destination,int size, Trip*& from);
    void copy(User*& destination,int size, User*& from);
    User* friends;
    unsigned numberOfFriends;
public:
    User ();
    User (const char* _username, const char* _password, const char* _email);
    User (const User& user);
    User& operator = (const User& rhs);
    ~User ();
    
    void setUsername (const char* _username); 
    void setPassword (const char* _password); 
    void setEmail (const char* _email); 
    void setTrips (const Trip* _trips, unsigned size);
    void setFriends(const User* _friends , unsigned size);
    void setFileName(const char* fileName);
    void uploadToDatabase();
    char* getUsername () const;
    char* getPassword () const;
    char* getEmail () const;
    const Trip* getTrips () const;
    const User* getFriends() const;
    unsigned getNumberOfTrips() const;
    unsigned getNumberOfFriends() const;
    void getParticularTrip(char* name);

    //methods
    bool addTrip (const Trip& trip);
    bool removeTrip(const char* name);
    void loadDatabase();
    void addFriend(const User& user);
    void checkDestinationAmongFriends(char* _destination);
};