#include "UI.h"

UI::UI() {
    usersDatabase.loadDatabase();
    updateTrips();
}
UI::UI(const UI& rhs) {
    user = rhs.user;
    usersDatabase = rhs.usersDatabase;
    allTrips = rhs.allTrips;
}
UI& UI::operator = (const UI& rhs) {
    if(this != &rhs) {
        user = rhs.user;
        usersDatabase = rhs.usersDatabase;
        allTrips = rhs.allTrips;
    }
    return *this;
}

UI::~UI()
{

}

void UI::updateTrips() {
    if (usersDatabase.getNumberOfUsers() == 0) return;
    for(int i = 0; i < usersDatabase.getNumberOfUsers(); i++) {
        for(int j = 0; j < usersDatabase[i].getNumberOfTrips(); j++) {
            allTrips.push_back(usersDatabase[i].getTrips()[j]);
        }
    }
}
bool UI::loginIntoAccount() {
    char* username = new char[255];
    char* password = new char[255];
    std::cout << "Enter account information: " << std::endl;
    std::cout << "Username: ";
    std::cin.ignore();
    std::cin.getline(username,255);
    std::cout << "Password: ";
    std::cin.ignore();
    std::cout << "1";
    std::cin.getline(password,255);
    for(size_t i = 0; i < usersDatabase.getNumberOfUsers(); i++) {
        if(!strcmp(usersDatabase.getUsers()[i].getUsername() , username) && !strcmp(usersDatabase.getUsers()[i].getPassword(), password)) {
            this->user = usersDatabase.getUsers()[i];
            std::cout << "Login succesfull!";
            return true;
        }
        else {
            std::cout << "Login failed!" << std::endl;
            return false;
        }
    }
    return false;
}
void UI::createNewAccount() {

    char* username = new char[255];
    char* password = new char[255];
    char* email = new char[255];

    std::cout << "Enter account information: " << std::endl;
    std::cout << "Username: ";
    std::cin.ignore();
    std::cin.getline(username,255);
    std::cout << "Password: ";
    std::cin.ignore();
    std::cin.getline(password,255);
    std::cout << "Email: ";
    std::cin.ignore();
    std::cin.getline(email,255);

    User newUser(username,password,email);
    this->user = newUser;
    usersDatabase.addUser(newUser);
    //usersDatabase.uploadToDatabase();
}
void UI::addFriends() {
    char* nameOfFriend = new char[255];
    std::cout << "Name of friend: " << std::endl;
    std::cin.ignore();
    std::cin.getline(nameOfFriend,255);
    for(int i = 0; i < usersDatabase.getNumberOfUsers(); i++) {
        if(!strcmp(usersDatabase.getUsers()[i].getUsername(),nameOfFriend)) {
            user.addFriend(usersDatabase.getUsers()[i]);
        }
    }
}
void UI::addTripToCurrentUser() {
    char* destination = new char[255];
    char* beginTimePeriod = new char[255];
    char* endTimePeriod = new char[255];
    unsigned grade;
    char* comment = new char[255];
    char* photos = new char[255];
    
    std::cout << "Enter trip information:" << std::endl;
    std::cout << "Destination: ";
    std::cin.ignore();
    std::cin.getline(destination,255);
    std::cout << "Begining of trip: ";
    std::cin.ignore();
    std::cin.getline(beginTimePeriod,255);
    std::cout << "End of trip: ";
    std::cin.ignore();
    std::cin.getline(endTimePeriod,255);
    std::cout << "Grade: ";
    std::cin >> grade;
    std::cout << "Comment: ";
    std::cin.ignore();
    std::cin.getline(comment,255);
    std::cout << "Photos: ";
    std::cin.ignore();
    std::cin.getline(photos,255);

    Trip newTrip(destination,beginTimePeriod,endTimePeriod,grade,comment,photos);
    user.addTrip(newTrip);
    allTrips.push_back(newTrip);
    
}
void UI::seeMyDatabase() {
    user.loadDatabase();
    for(int i = 0; i < user.getNumberOfTrips(); i++) {
        std::cout << "Destination:" << user.getTrips()[i].getDestination() << std::endl; 
        std::cout << "Time period:" << user.getTrips()[i].getBeginTimePeriod() <<" - " << user.getTrips()[i].getEndTimePeriod() << std::endl;
        std::cout << "Grade: " << user.getTrips()[i].getGrade() << std::endl;
        std::cout << "Comment:" << user.getTrips()[i].getComment() << std::endl;
        std::cout << "Photos:" << user.getTrips()[i].getPhotos() << std::endl;
        std::cout << std::endl;
    }

}
void UI::checkDestinationAmongFriends() {
    char* destinationName = new char[255];
    std::cin.getline(destinationName,255);
    user.checkDestinationAmongFriends(destinationName);
}
void UI::listFriends() {
    for(int i = 0; i < user.getNumberOfFriends(); i++) {
        std::cout << user.getFriends()[i].getUsername() << " " << user.getFriends()[i].getEmail() << std::endl;
    }
}
void UI::checkDestination() {
    char* destinationName = new char[255];
    std::cin.getline(destinationName,255);
    std::cout << "Destination: " << destinationName << std::endl;
    for(int j = 0; j < usersDatabase.getNumberOfUsers(); j++) {
        usersDatabase[j].getParticularTrip(destinationName);
    }
    int tripCounter = 0;
    int tripSum = 0;
    for(int i = 0; i < allTrips.size(); i++) {
        if(!strcmp(allTrips[i].getDestination(),destinationName)) {
            tripCounter++;
            tripSum += allTrips[i].getGrade();
        }
    }
    double average = tripSum / tripCounter;
    std::cout << "Average grade: " << average << std::endl;
}
void UI::listAllDestinations() {
    std::vector<std::string> allNames;
    bool flag = 0;
    for(int i = 0; i < allTrips.size(); i++) {
        flag = 0;
        for(int j = 0; j < allNames.size(); j++) {
            if(allTrips[i].getDestination() == allNames[j]) {
                flag = 1;
            }
            if(!flag) {
                allNames.push_back(allTrips[i].getDestination());
            }
        }
        
    }
    for(int k = 0; k < allNames.size(); k++) {
        std::cout << allNames[k] << std::endl;
    }
}
void UI::showOptions()
{
    std::cout << "Choose option:" << std::endl;
    std::cout << "1.Add new trip to your profile" << std::endl;
    std::cout << "2.Add new friend to you profile" << std::endl;
    std::cout << "3.Chech destination among friends" << std::endl;
    std::cout << "4.Chech information for destination" << std::endl;
    std::cout << "5.Open my database" << std::endl;
    std::cout << "6.List my friends" << std::endl;
    std::cout << "7.List all destinations" << std::endl;
    std::cout << "8.Log out" << std::endl;
}
void UI::menu()
{
    updateTrips();
    std::cout << "Menu is oppedned.Choose option: " << std::endl;
    std::cout << "1.Register new profile" << std::endl;
    std::cout << "2.Log in profile" << std::endl;
    char command;
    std::cin >> command;
    if(command == '1') {
        createNewAccount();
        showOptions();
        char command;
        std::cin >> command;
        if(command == '1') {
            addTripToCurrentUser();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '2') {
            addFriends();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '3') {
            checkDestinationAmongFriends();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '4') {
            checkDestination();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '5') {
            seeMyDatabase();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '6') {
            listFriends();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '7') {
            listAllDestinations();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '8') {
            menu();
        }
        else {
            std::cout << "Invalid command!" << std::endl;
            showOptions();
        }
    }
    else if (command == '2' && loginIntoAccount()) {
        showOptions();
        char command;
        std::cin >> command;
        if(command == '1') {
            addTripToCurrentUser();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '2') {
            addFriends();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '3') {
            checkDestinationAmongFriends();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '4') {
            checkDestination();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '5') {
            seeMyDatabase();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '6') {
            listFriends();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '7') {
            listAllDestinations();
            std::cout << std::endl;
            std::cout << "1.Go to menu" << std::endl;
            char choose;
            std::cin >> choose;
            if(choose == '1') {
                showOptions();
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        if(command == '8') {
            menu();
        }
        else {
            std::cout << "Invalid command!" << std::endl;
            showOptions();
        }

    }
    else {
        std::cout << "Invalid command or login failure!" << std::endl;
        menu();
    }

}
