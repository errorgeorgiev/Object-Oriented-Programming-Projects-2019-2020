
#include "UsersDatabase.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstring>


class UI {
private:
    User user;
    UsersDatabase usersDatabase;
    std::vector<Trip> allTrips;


public:
    UI();
    UI(const UI& rhs);
    UI& operator = (const UI& rhs);
    ~UI();

    void updateTrips();
    bool loginIntoAccount();
    void createNewAccount();
    void addFriends();
    void addTripToCurrentUser();
    void seeMyDatabase();
    void checkDestinationAmongFriends();
    void listFriends();
    void checkDestination();
    void listAllDestinations();
    void showOptions();
    void menu();

    
};