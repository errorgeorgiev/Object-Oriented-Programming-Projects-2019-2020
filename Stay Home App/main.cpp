#include <iostream>


#include "Database.h"
using namespace std;
unsigned User::idCount;
unsigned Challange::timesUsedCount;
unsigned User::stataicNumberOfUncompletedChallenges;
int main(){
    /*User first("Teodor",20,"teodor@yahoo.com");
    User second("Tedo", 21);
    cout<<first.getUsername()<<" "<<first.getAge()<<" "<<first.getEmail()<<" "<<first.getId()<<endl;
    cout<<second.getUsername()<<" "<<second.getAge()<<" "<<second.getEmail()<<" "<<second.getId()<<endl;

    Challange challange("#prudni");
    challange.setRate(3);
    challange.addCount();
    challange.setRate(7);
    cout<<challange.getTag()<<" "<<challange.getRate()<<" "<<challange.getStatus()<<" "<<challange.getCount()<<endl;

    if(!first.isInNonCompletedChallenges(challange)){
        first.addToNonCompletedChallenges(challange);
    }
    cout<<first.getNonCompletedChallenges()<<endl;*/
    User first("Nedyalko",20,"nedyalkoboydev@yahoo.com");
    User second("Tedo", 21);
    Database database("database");
    database.addUser(first);
    cout<<database.getUser(1).getUsername()<<endl;
    Challange challange("#goOut");
    Challange challange1("#stayHome");
    second.addUncompletedChallenge(challange1);
    first.addUncompletedChallenge(challange);
    first.addUncompletedChallenge(challange1);
    first.finish("#goOut",first.getId(),3);
    for (int i = 0; i < first.getUncompletedChallangesSize(); ++i) {
        cout<<first.getUncompletedChallanges()[i];
    }
    return 0;
}
