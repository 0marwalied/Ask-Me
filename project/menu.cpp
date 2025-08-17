#include "iostream"
#include "cstdlib"
#include "systemFunctions.cpp"

using namespace std;

void showMenu(user user);

void signUp();

void login();

void loginOrSignupMenu();

void showMenu(user user) {
showMenu:
	system("cls");
	cout << "Menu:\n";
	// cout << user.userName << " " << user.password << " " << user.id << " " << user.anonymous << '\n';
	cout << "\t1: Print Questions To Me\n";
	cout << "\t1: Print Questions From Me\n";
	cout << "\t3: Answer Question\n";
	cout << "\t4: Delete Question\n";
	cout << "\t5: Ask Question\n";
	cout << "\t6: List System Users\n";
	cout << "\t7: Feed\n";
	cout << "\t8: Logout\n";
	cout << "Enter number in range (1 - 8): ";
	string choice; cin >> choice;
	cout << '\n';
	if ("1" <= choice && choice <= "8" && (int)choice.size() == 1) {
		switch (stoi(choice)) {
		case 1: {break;}
		case 2: {break;}
		case 3: {break;}
		case 4: {break;}
		case 5: {break;}
		case 6: {systemFunctions.listSystemUsers(user.id); break;}
		case 7: {break;}
		default: {cout << "Loggedout :)\n"; exit(0);}
		}
		system("pause");
		goto showMenu;
	} else {
		cout << "ERROR: Invalid number....Try again\n";
		system("pause");
		goto showMenu;
	}
}

void loginOrSignupMenu() {
loginOrSignupMenu:
	system("cls");
	cout << "Menu:\n";
	cout << "\t1: Login\n";
	cout << "\t2: Sign Up\n";
	cout << "\nEnter number in range 1 - 2: ";
	string choice; cin >> choice;
	if (choice == "1") {
		login();
	} else if (choice == "2") {
		signUp();
		goto loginOrSignupMenu;
	} else {
		cout << "Invalid number....try again :(\n";
		system("pause");
		goto loginOrSignupMenu;
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
	systemFunctions.addNewUser(userName, password, anonymous);
	cout << "\nYour email created successfully :)\n";
	system("pause");
}

void login() {
login:
	system("cls");
	cout << "\nEnter user name: ";
	string userName; cin >> userName;
	cout << "\nEnter Password: ";
	string password; cin >> password;
	user user = systemFunctions.checkThisUser(userName, password);
	if (user.id != "") {
		cout << "\nWelcome :)\n";
		system("pause");
		showMenu(user);
	}
	else {
		cout << "\nThe User Name or Password is incorrect :(\n";
		system("pause");
		goto login;
	}
	system("pause");
}