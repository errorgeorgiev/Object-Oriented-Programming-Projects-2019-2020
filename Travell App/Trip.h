#pragma once
#include <iostream> 

class Trip {
private:
    char* destination;
    char* beginTimePeriod;
    char* endTimePeriod;
    unsigned grade;
    char* comment;
    char* photos;
public:
    Trip ();
    Trip (const char* _destination , const char* _beginTimePeriod, const char* _endTimePeriod, unsigned _grade , const char* _comment , const char* _photos);
    Trip (const Trip& other);
    Trip& operator = (const Trip& other);
    ~Trip ();

    void setDestination(const char* _destination);
    void setBeginTimePeriod(const char* _timePeriod);
    void setEndTimePeriod(const char* _timePeriod);
    void setGrade(unsigned _grade);
    void setComment(const char* _comment);
    void setPhotos(const char* _photos);

    char* getDestination() const;
    char* getBeginTimePeriod() const;
    char* getEndTimePeriod() const;
    unsigned getGrade() const;
    char* getComment() const;
    char* getPhotos() const;
};

void operator << (std::ostream& out , const Trip& trip);
