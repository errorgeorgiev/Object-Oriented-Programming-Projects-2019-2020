#include "Trip.h"
#include "User.h"

class UsersDatabase {
private:
    User* users;
    unsigned numberOfUsers;

public:
    UsersDatabase (); 
    UsersDatabase (const UsersDatabase& other); 
    UsersDatabase& operator = (const UsersDatabase& other); 
    ~UsersDatabase (); 

    void setUsers(const User* _users , unsigned size); 

    User* getUsers () const; 
    unsigned getNumberOfUsers () const;

    void addUser (const User& user); 

    User& operator [] (unsigned index);
    User operator [] (unsigned index) const;
    void uploadToDatabase();
    void loadDatabase();
};