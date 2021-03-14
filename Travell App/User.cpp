#include "User.h"
#include "Trip.h"
#include <iostream>
#include <cstring>
//default constructor
User::User () : username(nullptr) , password(nullptr) , email(nullptr) , numberOfTrips(0) , numberOfFriends(0) {}
//constructor
User::User(const char* _username, const char* _password, const char* _email):numberOfTrips(0){
    setUsername(_username);
    setPassword(_password);
    setEmail(_email);
    setFileName(username);
    loadDatabase();
}
// copy constructor
User::User (const User& user){
    setUsername(user.username);
    setPassword(user.password);
    setEmail(user.password);
    setTrips(user.trips,user.numberOfTrips);
    setFriends(user.friends,user.numberOfFriends);
}
// operator =
User& User::operator = (const User& rhs){
    if(this != &rhs){
        setUsername(rhs.username);
        setPassword(rhs.password);
        setEmail(rhs.email); 
        setTrips(rhs.trips , rhs.numberOfTrips);
    }
    return *this;
}
//destructor
User::~User () {
    //uploadToDatabase();
    delete[] this->username;
    delete[] this->password;
    delete[] this->email;
    delete[] this->trips;
}
//setters
void User::setUsername (const char* _username) {
    char* newUsername = new char[strlen(_username) + 1];

    username = newUsername;
    strcpy_s(username, strlen(_username) + 1, _username);
}
void User::setPassword (const char* _password) {
    password = new char[strlen(_password) + 1];
    strcpy_s(password, strlen(_password) + 1, _password);
}
void User::setEmail (const char* _email) {
    email = new char[strlen(_email) + 1];
    strcpy_s(email, strlen(_email) + 1, _email);
}
void User::setTrips (const Trip* _trips, unsigned size) {

    trips = new Trip[size];

    for(size_t i = 0; i < size ; ++i) {
        trips[i] = _trips[i];
    }
    numberOfTrips = size;
}
void User::setFriends (const User* _friends , unsigned size) {

    friends = new User[size];

    for(size_t i = 0; i < size ; ++i) {
        friends[i] = _friends[i];
    }
    numberOfFriends = size;
}
//getters
char* User::getUsername () const { return this->username; }
char* User::getPassword () const { return this->password; }
char* User::getEmail () const { return this->email; }
const Trip* User::getTrips () const { return this->trips; }
const User* User::getFriends() const { return this->friends; }
//methods
bool User::addTrip (const Trip& trip) {
    Trip* newTrips = new Trip[numberOfTrips+1];
    copy(newTrips,numberOfTrips,trips);
    newTrips[numberOfTrips] = trip;
    //delete [] this->trips;
    this->trips = newTrips;
    numberOfTrips++;
    return true;
}
bool User::removeTrip(const char* name){
    int index = -1;
    for(size_t i = 0; i < numberOfTrips; ++i){
        if(!strcmp(trips[i].getDestination(), name)) {
            index = i;
        }
    }
    if(index == -1) {
        return false;
    }
    unsigned j = 0;
    Trip* newTrips = new Trip[numberOfTrips-1];
    for (int i = 0; i < numberOfTrips; ++i) {
        if(i!=index){
            newTrips[j] = trips[i];
            j++;
        }
    }
    delete [] this->trips;
    this->trips = newTrips;
    numberOfTrips--;
    return true;
}
void User::addFriend(const User& user) {
    User* newFriends = new User[numberOfFriends+1];
    copy(newFriends,numberOfFriends,friends);
    newFriends[numberOfFriends] = user;
    //delete [] this->trips;
    this->friends = newFriends;
    numberOfFriends++;
}

void User::setFileName(const char *fileName) {
    //!!!!!!!!
    int lenUser = strlen(this->username);
    this->fileName = new char[lenUser + 4];
    //strcpy_s(this->fileName, lenUser + 4, this->username);
    int j = 0;
    for (int i = 0; i < lenUser; ++i) {
            this->fileName[i] = this->username[i];
    }
    this->fileName[lenUser] = '.';
    this->fileName[lenUser+1] = 'd';
    this->fileName[lenUser+2] = 'b';
    this->fileName[lenUser + 3] = '\0';
}

void User::uploadToDatabase(){
    std::ofstream out(fileName, std::ios::binary);
    out.write((char*)& numberOfTrips, sizeof(numberOfTrips));
    for(int i = 0; i < numberOfTrips; i++){
        unsigned destinationLenght = strlen(trips[i].getDestination());
        out.write((char*)&destinationLenght, sizeof(destinationLenght));
        out.write(trips[i].getDestination(),destinationLenght);

        unsigned beginTimePeriodLenght = strlen(trips[i].getBeginTimePeriod());
        out.write((char*)&beginTimePeriodLenght, sizeof(beginTimePeriodLenght));
        out.write(trips[i].getBeginTimePeriod(),beginTimePeriodLenght);

        unsigned endTimePeriodLenght = strlen(trips[i].getEndTimePeriod());
        out.write((char*)&endTimePeriodLenght, sizeof(endTimePeriodLenght));
        out.write(trips[i].getEndTimePeriod(),endTimePeriodLenght);

        unsigned grade = trips[i].getGrade();
        out.write((char*)&grade, sizeof(grade));

        unsigned commentLenght = strlen(trips[i].getComment());
        out.write((char*)&commentLenght, sizeof(commentLenght));
        out.write(trips[i].getComment(),commentLenght);

        unsigned photosLenght = strlen(trips[i].getPhotos());
        out.write((char*)&photosLenght, sizeof(photosLenght));
        out.write(trips[i].getPhotos(),photosLenght);
    }
    out.close();
}


void User::copy(Trip *&destination, int size, Trip *&from) {
    for (int i = 0; i < size; ++i) {
        destination[i] = from[i];
    }
}

void User::copy(User *&destination, int size, User *&from) {
    for (int i = 0; i < size; ++i) {
        destination[i] = from[i];
    }
}

void User::loadDatabase() {
    std::ifstream in(fileName, std::ios::binary);
    in.read((char*)&numberOfTrips, sizeof(numberOfTrips));
    //std::std::cout<<"NumberRead: "<<numberOfTrips<<std::std::endl;
    trips = new Trip[numberOfTrips];
    //reading every trip
    for(size_t i = 0; i < numberOfTrips; ++i) {
        //reading destinations
        unsigned tripDestinationLenght;
        in.read((char*)&tripDestinationLenght, sizeof(tripDestinationLenght));
        char* tripDestination = new char[tripDestinationLenght + 1];
        in.read(tripDestination, tripDestinationLenght);
        trips[i].setDestination(tripDestination);
        //reading time periods
        unsigned tripBeginTimePeriodLenght;
        in.read((char*)&tripBeginTimePeriodLenght, sizeof(tripBeginTimePeriodLenght));
        char* tripBeginTimePeriod = new char[tripBeginTimePeriodLenght + 1];
        in.read(tripBeginTimePeriod, tripBeginTimePeriodLenght);
        trips[i].setBeginTimePeriod(tripBeginTimePeriod);

        unsigned tripEndTimePeriodLenght;
        in.read((char*)&tripEndTimePeriodLenght, sizeof(tripEndTimePeriodLenght));
        char* tripEndTimePeriod = new char[tripEndTimePeriodLenght + 1];
        in.read(tripEndTimePeriod, tripEndTimePeriodLenght);
        trips[i].setEndTimePeriod(tripEndTimePeriod);
        //reading grades
        unsigned tripGrade;
        in.read((char*)&tripGrade, sizeof(tripGrade));
        trips[i].setGrade(tripGrade);
        //reading comments
        unsigned tripCommentLenght;
        in.read((char*)&tripCommentLenght, sizeof(tripCommentLenght));
        char* tripComment = new char[tripCommentLenght + 1];
        in.read(tripComment, tripCommentLenght);
        trips[i].setComment(tripComment);
        //reading photos
        unsigned tripPhotosLenght;
        in.read((char*)&tripPhotosLenght, sizeof(tripPhotosLenght));
        char *tripPhotos = new char[tripPhotosLenght + 1];
        in.read(tripPhotos, tripPhotosLenght);
        trips[i].setPhotos(tripPhotos);

    }
    in.close();
}

unsigned User::getNumberOfTrips() const {
    return numberOfTrips;
}
unsigned User::getNumberOfFriends() const {
    return numberOfFriends;
}
//should be working
void User::checkDestinationAmongFriends(char* _destination) {
    bool flag = 0;
    for(size_t i = 0; i < numberOfFriends; i++) {
        for(size_t j = 0; j < friends[i].getNumberOfTrips(); j++) {
            if (!strcmp(friends[i].trips[j].getDestination() , _destination)) {
                flag = 1;
                std::cout << friends[i].getUsername() << ":" << std::endl;
                std::cout << "Comment: " << friends[i].trips[j].getComment() << std::endl;
            }
        }
    }
    if (flag == 0) {
        std::cout << "None of your friends have visited this destination." << std::endl;
    }
}
void User::getParticularTrip(char* name) {
    for(int i = 0; i < numberOfTrips; i++) {
        if(!strcmp(trips[i].getDestination(),name)) {
            std::cout << getUsername() << ":" << " " << trips[i].getGrade() << std::endl;
        }
    }
} 
