//
//  main.cpp
//  Project One
//
//  Created by ritu mathews on 5/28/23.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <random>
#include <cstring>

using namespace std;

class time12 {
private:
    int userNumber, min, sec, AMorPM;
    string amorpm;
public:
    void twelvehourformat() {
        random_device rd;
        mt19937 rand(rd());
        uniform_int_distribution<int> num(0, 59); // rand() wasn't working, so switched to this
        //uniform_int_distribution<int> apm(0, 1);
        
        do {
            cout << "Enter the Hour, between 1 and 12: ";
            cin >> userNumber;
            cin.ignore(); // Ignore the newline character in the input
            min = num(rand);
            sec = num(rand);
  
            if (userNumber >= 1 && userNumber <= 12) {
                cout << "Is it AM or PM: ";
                getline(cin, amorpm);
                
                if (strcasecmp(amorpm.c_str(), "AM") == 0) { // ignores case
                    AMorPM = 0;
                }
                else if (strcasecmp(amorpm.c_str(), "PM") == 0) { // ignores case
                    AMorPM = 1;
                }
                else {
                    cout << "Invalid input" << endl;
                }
            }
            else {
                cout << "Invalid, Enter a number between 1 and 12." << endl;
            }
        }
        while ((userNumber < 1 || userNumber > 12) || (strcasecmp(amorpm.c_str(), "AM") != 0 && strcasecmp(amorpm.c_str(), "PM") != 0));
    }
    
    void display() const { //the actual clock

        cout << "**********************\n";
        cout << "*    12-Hour Clock   *\n";
        cout << "*     ";
        cout << setw(2) << setfill('0') << userNumber;
        cout << ":" << setw(2) << setfill('0') << min;
        cout << ":" << setw(2) << setfill('0') << sec;
        cout << " " << (AMorPM == 0 ? "AM" : "PM");
        cout << "    *" << endl;
        cout << "**********************\n";
        cout << endl;
    }

    // Function to add one hour to the time
    void addOneHour() {
        userNumber = (userNumber % 12) + 1;
    }

    // Function to add one minute to the time
    void addOneMinute() {
        min = (min + 1) % 60;
        if (min == 0) {
            addOneHour(); // Increment hour if minute wraps around to 0
        }
    }

    // Function to add one second to the time
    void addOneSecond() {
        sec = (sec + 1) % 60;
        if (sec == 0) {
            addOneMinute(); // Increment minute if second wraps around to 0
        }
    }
    
    int getUserNumber() const { // setter and getter but for c++
        return userNumber;
    }

    int getMin() const {
        return min;
    }

    int getSec() const {
        return sec;
    }

    int getAMorPM() const {
        return AMorPM;
    }
};

class time24 {
private:
    int hours, min, sec;
public:
    void twenty4hourformat(const time12& time) {
        time.display();
        int userNumber = time.getUserNumber();
        int min = time.getMin();
        int sec = time.getSec();
        int AMorPM = time.getAMorPM();

        // Perform conversion to 24-hour format
        if (AMorPM == 1 && userNumber < 12) {
            userNumber += 12;
        }
        // 12 AM is 24
        if (AMorPM == 0 && userNumber == 12) {
            userNumber += 12;
        }

        cout << "**********************\n";
        cout << "*    24-Hour Clock   *\n";
        cout << "*     ";
        cout << setw(2) << setfill('0') << userNumber;
        cout << ":" << setw(2) << setfill('0') << min;
        cout << ":" << setw(2) << setfill('0') << sec;
        cout << " " << (AMorPM == 0 ? "AM" : "PM");
        cout << "    *" << endl;
        cout << "**********************\n";
        cout << endl;
        
    }
};



void displayMenu() { // da menu
    cout << "**********************\n";
    cout << "* 1 - Add One Hour   *\n";
    cout << "* 2 - Add One Minute *\n";
    cout << "* 3 - Add One Second *\n";
    cout << "* 4 - Exit Program   *\n";
    cout << "**********************";
    cout << endl;
}



void loopMenu(time12& time, time24& time24) {
    bool t = true;
    while (t) {
        displayMenu();
        int menuInput;
        cin >> menuInput;
        switch (menuInput) {
            case 1:
                time.addOneHour();
                time24.twenty4hourformat(time);
                break;
            case 2:
                time.addOneMinute();
                time24.twenty4hourformat(time);
                break;
            case 3:
                time.addOneSecond();
                time24.twenty4hourformat(time);
                break;
            case 4:
                t = false;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 to 4 quit\n";
        }
    }
}

int main() { // with as little code in main 
    class time12 time;
    class time24 time24;
    
    time.twelvehourformat();
    time24.twenty4hourformat(time);
    
    loopMenu(time, time24);
    return 0;
}
