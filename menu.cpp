#include "iostream"
#include "cstdlib"
#include "systemFunctions.cpp"

using namespace std;

void signUp();

void login();

void loginOrSignup();

void loginOrSignup() {
	cout << "Menu:\n";
	cout << "\t1: Login\n";
	cout << "\t2: Sign Up\n";
	cout << "\nEnter number in range 1 - 2: ";
	string choice; cin >> choice;

	if (choice == "1") {
		login();
	} else if (choice == "2") {
		signUp();
		login();
	} else {
		cout << "Invalied number try again :(\n";
		system("pause");
		system("cls");
		loginOrSignup();
	}
}

void signUp() {
	system("cls");
	cout << "\nEnter user name. (No Spaces): ";
	string userName; cin >> userName;
	cout << "\nEnter Password: ";
	string password; cin >> password;
	cout << "\nEnter name: ";
	string name; cin >> name;
	cout << "\nEnter email: ";
	string email; cin >> email;
	cout << "\nAllow anonymous questions? (0 or 1): ";
	string anonymous; cin >> anonymous;
	addNewUser(userName, password);
	cout << "\nYour email created successfully :)";
}

void login() {
	system("cls");
	cout << "\nEnter user name: ";
	string userName; cin >> userName;
	cout << "\nEnter Password: ";
	string password; cin >> password;
	cout << "\nWelcome :)\n";
	system("pause");
	system("cls");
}