//
// Created by nedkoudlg on 19.04.20 г..
//

#ifndef TEDOC__2_CHALLANGE_H
#define TEDOC__2_CHALLANGE_H

//tag#
//timesUsed
//rate
//status-new, recent, old
#include <iostream>
class Challange {
friend std::ostream& operator<<(std::ostream& out, const Challange& rhs);
private:
    char* nameTag;
    float rate;
    unsigned br;
public:
    unsigned timesUsed;
    unsigned static timesUsedCount;
    Challange();
    Challange(char *nameTag);
    Challange(const Challange& rhs);
    Challange& operator=(const Challange& rhs);
    ~Challange();

    bool operator == (const Challange& rhs);

    void addCount();
    void setRate(float rate);

    char* getStatus() const;
    float getRate() const;
    char* getTag() const;
    unsigned getCount() const;
};
std::ostream& operator<<(std::ostream& out, const Challange& rhs);

#endif //TEDOC__2_CHALLANGE_H
