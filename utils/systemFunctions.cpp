#include "fstream"
#include "iostream"
#include "map"
#include "random"
#include "string"
#include "time.h"
#include "vector"

using namespace std;

const string questionFilePath = "./data/questions.txt";
const string usersFilePath = "./data/users.txt";

struct question {
    string id, fromUserId, toUserId;
    bool parent;
    string val, answer;
    vector<question> threads;
    question() {}
    question(const string& parent, const string& questionId,
             const string& fromUserId, const string& toUserId,
             const string& question, const string& answer) {
        this->parent = (parent == "parent");
        this->id = questionId;
        this->fromUserId = fromUserId;
        this->toUserId = toUserId;
        this->val = question;
        this->answer = answer;
    }

    string generateId() {
        srand(time(0));
        string id = "";
        for (int i = 1; i <= 3; i++) id += (rand() % 10) + '0';
        return id;
    }

    vector<string> getQuestionRecordData(const string& line) {
        int cnt = 0;
        string lineSeg;
        vector<string> questionData;
        for (auto& it : line) {
            if (it == ' ' && cnt < 4)
                cnt++, questionData.push_back(lineSeg), lineSeg = "";
            else
                lineSeg += it;
        }
        questionData.push_back(lineSeg);
        return questionData;
    }

    vector<question> getQuestions() {
        ifstream input(questionFilePath);
        vector<question> questions;
        string line, lastParentQuestionId;
        bool isQuestion = true;
        vector<string> questionData;
        string answer;
        while (getline(input, line)) {
            if (isQuestion) {
                questionData = question().getQuestionRecordData(line);
            } else {
                answer = line;
                question question(questionData[0], questionData[1],
                                  questionData[2], questionData[3],
                                  questionData[4], answer);
                if (question.parent) lastParentQuestionId = question.id;
                if (lastParentQuestionId == question.id)
                    questions.push_back(question);
                else
                    questions.back().threads.push_back(question);
            }
            isQuestion = !isQuestion;
        }
        input.close();
        return questions;
    }
    void printQuestion() {
        cout << "Question Id (" << id << ") from user id (" << fromUserId
             << ") \t Question: " << val << "\n";
        cout << "\tAnswer: " << answer << '\n';
        if (!threads.empty()) cout << "threads: \n";
        for (auto& thread : threads) {
            cout << "\tThread: Question Id (" << thread.id << ") from user id ("
                 << thread.fromUserId << ") \t Question: " << thread.val
                 << "\n";
            cout << "\tThread: Answer: " << thread.answer << '\n';
        }
        cout << '\n';
    }

    void printLine(ofstream& outputLine, const question& question) {
        outputLine << (question.parent ? "parent" : "thread") << " "
                   << question.id << " " << question.fromUserId << " "
                   << question.toUserId << " " << question.val << '\n';
        outputLine << question.answer << '\n';
    };

    void updateQuestionsFile(const vector<question>& questions) {
        ofstream output(questionFilePath);
        for (auto& question : questions) {
            printLine(output, question);
            for (auto& thread : question.threads) {
                printLine(output, thread);
            }
        }
        output.close();
    }

    void deleteQuestion(const vector<question>& questions, const string& userId,
                        const string& questionId) {
        ofstream output(questionFilePath);
        for (auto& question : questions) {
            if (question.id == questionId && userId == question.toUserId)
                continue;
            printLine(output, question);
            for (auto& thread : question.threads) {
                if (thread.id == questionId && userId == thread.toUserId)
                    continue;
                printLine(output, thread);
            }
        }
        output.close();
    }

    void addNewQuestion(const string& fromUserId, const string& toUserId,
                        const string& questionId, const string& questionValue) {
        vector<question> questions = getQuestions();
        if (questionId == "-1") {
            questions.push_back(question("parent", generateId(), fromUserId,
                                         toUserId, questionValue, "no answer"));
        } else {
            for (auto& Question : questions) {
                if (Question.id == questionId) {
                    Question.threads.push_back(
                        question("thread", generateId(), fromUserId, toUserId,
                                 questionValue, "no answer"));
                }
            }
        }
        updateQuestionsFile(questions);
    }
};

struct user {
    string userName, password, id, anonymous;
    user() { this->id = generateId(); }
    user(string userName, string password, string id, string anonymous) {
        this->userName = userName;
        this->password = password;
        this->id = id;
        this->anonymous = anonymous;
    }

    string generateId() {
        srand(time(0));
        string id = "";
        for (int i = 1; i <= 4; i++) id += (rand() % 10) + '0';
        return id;
    }

    user getUserInfo(const string& line) {
        vector<string> data;
        string lineSeg;
        for (auto& it : line) {
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
        vector<user> users;
        ifstream input(usersFilePath);
        string line;
        while (getline(input, line)) users.push_back(user().getUserInfo(line));
        input.close();
        return users;
    }
};

struct system {
    vector<user> users;
    vector<question> questions;
    map<string, bool> isAnonymous;
    system() {
        users = user().getUsers(), questions = question().getQuestions();
        for (auto& user : users)
            if (user.anonymous == "anonymous") isAnonymous[user.id] = true;
    }

    void addNewUser(const string& userName, const string& password,
                    const string& anonymous) {
        ofstream output(usersFilePath);
        string newUser = userName + " " + password + " " + user().id + " " +
                         (anonymous == "1" ? "anonymous" : "notAnonymous") +
                         '\n';
        for (auto& user : users)
            output << user.userName + " " + user.password + " " + user.id +
                          " " + user.anonymous
                   << '\n';
        output << newUser;
        output.close();
    }

    user checkThisUser(const string& userName, const string& password) {
        ifstream input(usersFilePath);
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
        return user("", "", "", "");
    }

    void printQuestionsToMe(const string& userId) {
        for (auto& question : questions) {
            if (question.toUserId == userId) {
                question.printQuestion();
            }
        }
    }

    void listSystemUsers(const string& userId) {
        for (auto& user : users) {
            if (user.id != userId)
                cout << "ID: " << user.id << "\t" << "Name: " << user.userName
                     << '\n';
        }
        cout << '\n';
    }

    void printQuestionsFromMe(const string& userId) {
        for (auto& question : questions) {
            if (question.fromUserId == userId) {
                cout << "Question Id (" << question.id << ") "
                     << (!isAnonymous[question.toUserId] ? "!AQ" : "")
                     << " to user id (" << question.toUserId
                     << ")\t Question: " << question.val
                     << "\t Answer: " << question.answer << '\n';
            }
        }
    }

    void answerQuestion() {
        string questionId;
        cout << "Enter Question id or -1 to cancel: ";
        cin >> questionId;
        if (questionId == "-1") return;
        for (auto& question : questions) {
            if (question.id == questionId) {
                cout << "Question Id (" << question.id << ") "
                     << (!isAnonymous[question.toUserId] ? "!AQ" : "")
                     << " to user id (" << question.toUserId
                     << ")\t Question: " << question.val
                     << "\t Answer: " << question.answer << '\n';
                if (question.answer != "no answer")
                    cout << "\n\nWarning: Already answered. Answer will be "
                            "updated\n";
                cout << "Enter answer: ";
                cin.ignore(), getline(cin, question.answer);
            }
            for (auto& thread : question.threads) {
                if (thread.id == questionId) {
                    cout << "Thread Id (" << thread.id << ") "
                         << (!isAnonymous[thread.toUserId] ? "!AQ" : "")
                         << " to user id (" << thread.toUserId
                         << ")\t Question: " << thread.val
                         << "\t Answer: " << thread.answer << '\n';
                    if (thread.answer != "no answer")
                        cout << "\n\nWarning: Already answered. Answer will be "
                                "updated\n";
                    cout << "Enter answer: ";
                    cin.ignore(), getline(cin, thread.answer);
                }
            }
        }
        question().updateQuestionsFile(questions);
    }

    void deleteQuestion(const string& userId) {
        string questionId;
        cout << "Enter Question Id or -1 to cancel: ";
        cin >> questionId;
        question().deleteQuestion(questions, userId, questionId);
        questions = question().getQuestions();
    }

    void askQuestion(const string& userId) {
        string toUserId, questionId, questionValue;
        cout << "Enter User Id or -1 to cancel: ";
        cin >> toUserId;
        if (toUserId == "-1") return;
        if (!isAnonymous[toUserId])
            cout << "Note: Anonymous questions are not allowed for this user\n";
        cout << "For thread question: Enter Question id or -1 for new "
                "question: ";
        cin >> questionId;
        cout << "Enter question text: ";
        cin.ignore(), getline(cin, questionValue);
        question().addNewQuestion(userId, toUserId, questionId, questionValue);
        questions = question().getQuestions();
    }

    void feed() {
        for (auto& question : questions) {
            cout << "Question Id (" << question.id << ") from user id("
                 << question.fromUserId << ") "
                 << (!isAnonymous[question.toUserId]
                         ? "To user id(" + question.toUserId + ")"
                         : "");
            cout << "\t" << question.val << '\n';
            cout << "\tAnswer: " << question.answer << '\n';
            for (auto& thread : question.threads) {
                cout << "Thread parent Quesion ID (" << question.id
                     << ") from user id(" << thread.fromUserId << ") "
                     << (!isAnonymous[thread.toUserId]
                             ? "To user id(" + thread.toUserId + ")"
                             : "");
                cout << "\t" << thread.val << '\n';
                cout << "\tAnswer: " << thread.answer << '\n';
            }
        }
    }
} systemFunctions;
