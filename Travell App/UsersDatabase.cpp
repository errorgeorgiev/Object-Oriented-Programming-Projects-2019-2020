#include "UsersDatabase.h"
#include <iostream>
#include <cstring>
#include <fstream>


//default constructor
UsersDatabase::UsersDatabase () : users(nullptr), numberOfUsers(0){
}
//copy constructor
UsersDatabase::UsersDatabase (const UsersDatabase& other) : users(nullptr), numberOfUsers(0) {
    setUsers (other.users, other.numberOfUsers);
}
//operator = 
UsersDatabase& UsersDatabase::operator = (const UsersDatabase& other) {
    if(this != &other) {
        setUsers(other.users, other.numberOfUsers);
    }
    return *this;
}
//destructor
UsersDatabase::~UsersDatabase () {
    delete[] users;
}
//setters
void UsersDatabase::setUsers(const User* _users , unsigned size) {
    delete[] users;
    users = new User[size];
    for(size_t i = 0; i < size ; ++i){
        users[i] = _users[i];
    }
}
//getters
User* UsersDatabase::getUsers () const { return users; }
unsigned UsersDatabase::getNumberOfUsers () const { return numberOfUsers; }
//other methods
void UsersDatabase::addUser (const User& user) {
    User* newUsers = new User[numberOfUsers + 1];
    for(int i = 0; i < numberOfUsers; i++) {
        newUsers[i] = users[i];
    }
    newUsers[numberOfUsers] = user;
    numberOfUsers++;
    users = newUsers;
    uploadToDatabase();

}

User& UsersDatabase::operator [] (unsigned index) {
    return users[index];
}
User UsersDatabase::operator [] (unsigned index) const {
    return users[index];
}

//creating users.db
void UsersDatabase::uploadToDatabase() {
    std::ofstream out("users.db" ,std::ios::binary);
    out.write((char*)&numberOfUsers, sizeof(numberOfUsers));

    for(size_t i = 0; i < numberOfUsers; ++i){
        unsigned usernameLenght = strlen(users[i].getUsername());
        out.write((const char*)&usernameLenght, sizeof(usernameLenght));
        out.write(users[i].getUsername(),usernameLenght);

        unsigned passwordLenght = strlen(users[i].getPassword());
        out.write((const char*)&passwordLenght, sizeof(passwordLenght));
        out.write(users[i].getPassword(),passwordLenght);

        unsigned emailLenght = strlen(users[i].getEmail());
        out.write((const char*)&emailLenght, sizeof(emailLenght));
        out.write(users[i].getEmail(),emailLenght);
    }
    out.close();
}
//reading from users.db
void UsersDatabase::loadDatabase() {
    std::ifstream in("users.db", std::ios::binary);
    in.read((char*)&numberOfUsers, sizeof(numberOfUsers));
    
    users = new User[numberOfUsers];
    for(size_t i = 0; i < numberOfUsers; i++) {
        unsigned userUsernameLenght = 0;
        in.read((char*)&userUsernameLenght, sizeof(userUsernameLenght));
        char* userUsername = new char[userUsernameLenght + 1];
        in.read(userUsername, userUsernameLenght);
        users[i].setUsername(userUsername);

        unsigned userPasswordLenght = 0;
        in.read((char*)&userPasswordLenght, sizeof(userPasswordLenght));
        char* userPassword = new char[userPasswordLenght + 1];
        in.read(userPassword, userPasswordLenght);
        users[i].setPassword(userPassword);

        unsigned userEmailLenght = 0;
        in.read((char*)&userUsernameLenght, sizeof(userUsernameLenght));
        char* userEmail = new char[userEmailLenght + 1];
        in.read(userEmail, userEmailLenght);
        users[i].setEmail(userEmail);

    }
    in.close();        

}





