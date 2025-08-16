#include "iostream"
#include "vector"
#include "fstream"
#include "random"
#include "time.h"

using namespace std;

string generateId() {
	srand(time(0));
	string id = "";
	for (int i = 1; i <= 4; i++)
		id += (rand() % 10) + '0';
	return id;
}

void addNewUser(const string userName, const string paaword) {
	ifstream input("users.txt");
	vector<string>users;
	string line;
	while (getline(input, line))
		users.push_back(line);
	input.close();

	ofstream output("users.txt");
	string newUser = userName + " " + paaword + " " + generateId() + '\n';
	for (auto &it : users)
		output << it << '\n';
	output << newUser;
	output.close();
}