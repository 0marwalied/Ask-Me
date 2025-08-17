#include "iostream"
#include "vector"
#include "fstream"
#include "random"
#include "time.h"

using namespace std;

struct question {
	string id, fromUserId, toUserId;
	bool parent;
	string val, answer;
	vector<question>threads;
	question() {}
	question(const string& parent, const string& questionId, const string& fromUserId, const string& toUserId, const string& question, const string& answer) {
		this->parent = (parent == "parent");
		this->id = questionId;
		this->fromUserId = fromUserId;
		this->toUserId = toUserId;
		this->val = question;
		this->answer = answer;
	}

	vector<string> getQuestionRecordData(const string& line) {
		int cnt = 0;
		string lineSeg;
		vector<string>questionData;
		for (auto &it : line) {
			if (it == ' ' && cnt < 4)
				cnt++, questionData.push_back(lineSeg), lineSeg = "";
			else
				lineSeg += it;
		}
		questionData.push_back(lineSeg);
		return questionData;
	}

	vector<question> getQuestions() {
		ifstream input("questions.txt");
		vector<question>questions;
		string line, lastParentQuestionId;
		bool isQuestion = true;
		vector<string>questionData;
		string answer;
		while (getline(input, line)) {
			if (isQuestion) {
				questionData = question().getQuestionRecordData(line);
			} else {
				answer = line;
				question question(questionData[0], questionData[1], questionData[2], questionData[3], questionData[4], answer);
				if (question.parent) lastParentQuestionId = question.id;
				if (lastParentQuestionId == question.id)questions.push_back(question);
				else questions.back().threads.push_back(question);
			}
			isQuestion = !isQuestion;
		}
		input.close();
		return questions;
	}
	void printQuestion() {
		cout << "Question Id (" << id << ") from user id (" << fromUserId << ") \t Question: " << val << "\n";
		cout << "\tAnswer:" << answer << '\n';
		cout << "threads: \n";
		for (auto &thread : threads) {
			cout << "\tThread: Question Id (" << thread.id << ") from user id (" << thread.fromUserId << ") \t Question: " << thread.val << "\n";
			cout << "\tThread: Answer:" << thread.answer << '\n';
		}
		cout << '\n';
	}
};

struct user {
	string userName, password, id, anonymous;
	user() {}
	user(string userName, string password, string id, string anonymous) {
		this->userName = userName;
		this->password = password;
		this->id = id;
		this->anonymous = anonymous;
	}

	string generateId() {
		srand(time(0));
		string id = "";
		for (int i = 1; i <= 4; i++)
			id += (rand() % 10) + '0';
		return id;
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

	vector<user> getUsers() {
		vector<user>users;
		ifstream input("users.txt");
		string line;
		while (getline(input, line))
			users.push_back(user().getUserInfo(line));
		input.close();
		return users;
	}

};

struct system {
	system() {}

	void addNewUser(const string& userName, const string& paaword, const string& anonymous) {
		vector<user>users = user().getUsers();
		ofstream output("users.txt");
		string newUser = userName + " " + paaword + " " + user().generateId() + " " + (anonymous == "1" ? "anonymous" : "notAnonymous") + '\n';
		for (auto &user : users)
			output << user.userName + " " + user.password + " " + user.id + " " + user.anonymous << '\n';
		output << newUser;
		output.close();
	}

	user checkThisUser(const string& userName, const string& password) {
		ifstream input("users.txt");
		{
			string line;
			while (getline(input, line)) {
				user user = user.getUserInfo(line);
				if (user.userName == userName && user.password == password) {
					return user;
				}
			}
		}
		input.close();
		return user();
	}
	void printQuestionsToMe(const string& userId) {
		vector<question>questions = question().getQuestions();
		for (auto &question : questions) {
			if (question.toUserId == userId) {
				question.printQuestion();
			}
		}
	}

	void listSystemUsers(const string& userId) {
		vector<user>users = user().getUsers();
		for (auto &user : users) {
			if (user.id != userId)cout << "ID: " << user.id << "\t" << "Name: " << user.userName << '\n';
		}
		cout << '\n';
	}
} systemFunctions;

// int main() {
// 	question().getQuestions();
// }