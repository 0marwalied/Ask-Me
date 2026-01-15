#include "./utils/menu.cpp"
#include "iostream"

using namespace std;

int main() {
    user user = loginOrSignupMenu();
    showMenu(user);
}