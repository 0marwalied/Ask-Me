#include "iostream"
#include "menu.cpp"

using namespace std;

int main() {
	user user = loginOrSignupMenu();
	showMenu(user);
}