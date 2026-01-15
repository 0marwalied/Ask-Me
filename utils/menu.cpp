#include "cstdlib"
#include "iostream"
#include "string"
#include "systemFunctions.cpp"

using namespace std;

void showMenu(user user);

void signUp();

user login();

user loginOrSignupMenu();

void showMenu(user user) {
showMenu:
    system("cls");
    cout << "Menu:\n";
    cout << "\t1: Print Questions To Me\n";
    cout << "\t2: Print Questions From Me\n";
    cout << "\t3: Answer Question\n";
    cout << "\t4: Delete Question\n";
    cout << "\t5: Ask Question\n";
    cout << "\t6: List System Users\n";
    cout << "\t7: Feed\n";
    cout << "\t8: Logout\n";
    cout << "Enter number in range (1 - 8): ";
    string choice;
    cin >> choice;
    cout << '\n';
    if ("1" <= choice && choice <= "8" && (int)choice.size() == 1) {
        switch (stoi(choice)) {
            case 1: {
                systemFunctions.printQuestionsToMe(user.id);
                break;
            }
            case 2: {
                systemFunctions.printQuestionsFromMe(user.id);
                break;
            }
            case 3: {
                systemFunctions.answerQuestion();
                break;
            }
            case 4: {
                systemFunctions.deleteQuestion(user.id);
                break;
            }
            case 5: {
                systemFunctions.askQuestion(user.id);
                break;
            }
            case 6: {
                systemFunctions.listSystemUsers(user.id);
                break;
            }
            case 7: {
                systemFunctions.feed();
                break;
            }
            default: {
                cout << "Loggedout :)\n";
                exit(0);
            }
        }
        system("pause");
        goto showMenu;
    } else {
        cout << "ERROR: Invalid number....Try again\n";
        system("pause");
        goto showMenu;
    }
}

user loginOrSignupMenu() {
loginOrSignupMenu:
    system("cls");
    cout << "Menu:\n";
    cout << "\t1: Login\n";
    cout << "\t2: Sign Up\n";
    cout << "\t3: Exit\n";
    cout << "\nEnter number in range 1 - 3: ";
    string choice;
    cin >> choice;
    if (choice == "1") {
        return login();
    } else if (choice == "2") {
        signUp();
        goto loginOrSignupMenu;
    } else if (choice == "3") {
        exit(0);
    } else {
        cout << "Invalid number....try again :(\n";
        system("pause");
        goto loginOrSignupMenu;
    }
}

void signUp() {
    system("cls");
    cout << "\nEnter user name. (No Spaces): ";
    string userName;
    cin >> userName;
    cout << "\nEnter Password: ";
    string password;
    cin >> password;
    cout << "\nEnter name: ";
    string name;
    cin >> name;
    cout << "\nEnter email: ";
    string email;
    cin >> email;
    cout << "\nAllow anonymous questions? (0 or 1): ";
    string anonymous;
    cin >> anonymous;
    systemFunctions.addNewUser(userName, password, anonymous);
    cout << "\nYour email created successfully :)\n";
    system("pause");
}

user login() {
login:
    system("cls");
    cout << "\nEnter user name: ";
    string userName;
    cin >> userName;
    cout << "\nEnter Password: ";
    string password;
    cin >> password;
    user user = systemFunctions.checkThisUser(userName, password);
    if (user.id != "") {
        cout << "\nWelcome :)\n";
        system("pause");
        return user;
    } else {
        cout << "\nThe User Name or Password is incorrect :(\n";
        system("pause");
        goto login;
    }
    system("pause");
}