//
// Created by nedkoudlg on 19.04.20 г..
//

#include "Challange.h"
#include <cstring>
Challange::Challange():br(0){

}

Challange::Challange(char *nameTag):rate(0.0),br(0) {
    this->nameTag = new char[strlen(nameTag)+1];
    strcpy(this->nameTag, nameTag);
    timesUsed = ++timesUsedCount;
}

void Challange::addCount() {
    timesUsed = ++timesUsedCount;
    br++;
}

char *Challange::getStatus() const {
    if(this->br == 1){
        return "New";
    }else if(this->br>1 && this->br<11)
        return "Quite recently";
    else return "Old";
}

Challange::Challange(const Challange &rhs) {

    this->nameTag = new char[strlen(rhs.nameTag)+1];
    strcpy(this->nameTag,rhs.nameTag);
    this->timesUsed = rhs.timesUsed;
    this->timesUsedCount = rhs.timesUsedCount;
    this->rate = rhs.rate;
    this->br = rhs.br;
}

Challange& Challange::operator=(const Challange &rhs) {
    if(this != &rhs){
        this->nameTag = new char[strlen(rhs.nameTag)+1];
        strcpy(this->nameTag,rhs.nameTag);
        this->timesUsed = rhs.timesUsed;
        this->timesUsedCount = rhs.timesUsedCount;
        this->rate = rhs.rate;
        this->br=rhs.br;
    }
    return *this;
}

void Challange::setRate(float rate) {
    this->rate = (this->rate + rate)/timesUsed;
}

float Challange::getRate() const{
    return this->rate;
}

char *Challange::getTag() const {
    return this->nameTag;
}

unsigned Challange::getCount() const {
    return this->br;
}

Challange::~Challange() {
    if(nameTag!= nullptr)
        delete[] nameTag;
}

bool Challange::operator==(const Challange &rhs) {
    unsigned lenLhs = strlen(this->getTag());
    unsigned lenRhs = strlen(rhs.getTag());
    if(lenLhs == lenRhs){
        for (int i = 0; i < lenLhs; ++i) {
            if(this->getTag()[i]!=rhs.getTag()[i]) return false;
        }
        return true;
    } else return false;
}

std::ostream &operator<<(std::ostream &out, const Challange &rhs) {
    out<<rhs.getTag()<<" "<<rhs.getRate()<<" "<<rhs.getStatus()<<" "<<rhs.getCount()<<std::endl;
    return out;
}
