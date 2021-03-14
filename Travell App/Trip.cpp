#include "Trip.h"
#include <cstring> 

//default constructor
Trip::Trip () : destination(nullptr) , beginTimePeriod(nullptr), endTimePeriod(nullptr) , grade(0) , comment(nullptr) , photos(nullptr) {}
//constructor
Trip::Trip (const char* _destination , const char* _beginTimePeriod ,const char* _endTimePeriod, unsigned _grade , const char* _comment , const char* _photos) {
    setDestination(_destination);
    setBeginTimePeriod(_beginTimePeriod);
    setEndTimePeriod(_endTimePeriod);
    setGrade(_grade);
    setComment(_comment);
    setPhotos(_photos);
}
//copy constructor 
Trip::Trip (const Trip& other) {
    setDestination(other.destination);
    setBeginTimePeriod(other.beginTimePeriod);
    setEndTimePeriod(other.endTimePeriod);
    setGrade(other.grade);
    setComment(other.comment);
    setPhotos(other.photos);
}
//operator = 
Trip& Trip::operator = (const Trip& other) {
    if(this != &other) {
        setDestination(other.destination);
        setBeginTimePeriod(other.beginTimePeriod);
        setEndTimePeriod(other.endTimePeriod);
        setGrade(other.grade);
        setComment(other.comment);
        setPhotos(other.photos);
    }
    return *this;
}
    //destructor
Trip::~Trip () {
    delete[] destination;
    delete[] beginTimePeriod;
    delete[] endTimePeriod;
    delete[] comment;
    delete[] photos;
}
//getters
char* Trip::getDestination()const { return this->destination; }
char* Trip::getBeginTimePeriod()const { return this->beginTimePeriod; }
unsigned Trip::getGrade() const { return this->grade; }
char* Trip::getComment() const { return this->comment; }
char* Trip::getPhotos() const { return this->photos; }
//setters
void Trip::setDestination(const char* _destination) {
    char* newDestination = new char[strlen(_destination) + 1];
    destination = newDestination;
    strcpy_s(destination, strlen(_destination) + 1, _destination);
}
void Trip::setBeginTimePeriod(const char* _timePeriod) {
    this->beginTimePeriod = new char[strlen(_timePeriod) + 1];
    strcpy_s(beginTimePeriod, strlen(_timePeriod) + 1, _timePeriod);
}
void Trip::setGrade(unsigned _grade) {
    this->grade = _grade;
}
void Trip::setComment(const char* _comment) {
    char* newComment = new char[strlen(_comment) + 1];

    comment = newComment;
    strcpy_s(comment, strlen(_comment) + 1, _comment);
}
void Trip::setPhotos(const char* _photos) {
    char* newPhotos = new char[strlen(_photos) + 1];
    photos = newPhotos;
    strcpy_s(photos, strlen(_photos) + 1, _photos);
}

void Trip::setEndTimePeriod(const char *_timePeriod) {
    this->endTimePeriod = new char[strlen(_timePeriod) + 1];;
    strcpy_s(endTimePeriod, strlen(_timePeriod) + 1, _timePeriod);
}

char *Trip::getEndTimePeriod() const {
    return this->endTimePeriod;
}


void operator << (std::ostream& out , const Trip& trip) {
    std::cout << "Destination:" << trip.getDestination() << std::endl;
    std::cout << "Time period:" << trip.getBeginTimePeriod() <<" - " << trip.getEndTimePeriod() << std::endl;
    std::cout << "Grade: " << trip.getGrade() << std::endl;
    std::cout << "Comment:" << trip.getComment() << std::endl;
    std::cout << "Photos:" << trip.getPhotos() << std::endl;
}
