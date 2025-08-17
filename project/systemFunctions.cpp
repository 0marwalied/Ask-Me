#include "iostream"
#include "vector"
#include "fstream"
#include "random"
#include "time.h"

using namespace std;

struct user {
	string userName, password, id, anonymous;
	user() {}
	user(string userName, string password, string id, string anonymous) {
		this->userName = userName;
		this->password = password;
		this->id = id;
		this->anonymous = anonymous;
	}
};

struct Systems {
	Systems() {}
	string generateId() {
		srand(time(0));
		string id = "";
		for (int i = 1; i <= 4; i++)
			id += (rand() % 10) + '0';
		return id;
	}
	void addNewUser(const string& userName, const string& paaword, const string& anonymous) {
		ifstream input("users.txt");
		vector<string>users;
		string line;
		while (getline(input, line))
			users.push_back(line);
		input.close();

		ofstream output("users.txt");
		string newUser = userName + " " + paaword + " " + generateId() + " " + (anonymous == "1" ? "anonymous" : "notAnonymous") + '\n';
		for (auto &it : users)
			output << it << '\n';
		output << newUser;
		output.close();
	}
	user getUserInfo(const string& line) {
		vector<string>data;
		string lineSeg;
		for (auto &it : line) {
			if (it == ' ')
				data.push_back(lineSeg), lineSeg = "";
			else
				lineSeg += it;
		}
		data.push_back(lineSeg);
		user user(data[0], data[1], data[2], data[3]);
		return user;
	}
	user checkThisUser(const string& userName, const string& password) {
		ifstream input("users.txt");
		{

			string line;
			while (getline(input, line)) {
				user user = getUserInfo(line);
				if (user.userName == userName && user.password == password) {
					return user;
				}
			}

		}
		input.close();
		return user();
	}
} systemFunctions;