#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class User {
private:
	string password;
public:
	string username;
	bool check(string name, string pass) {
		if (name == username && pass == password)
			return 1;
		return 0;
	}
	bool isPassValid(string pass) {
		bool digits = 0;
		bool alphas = 0;
		if (pass.length() < 7)
			return 0;
		if (pass == "")
			return 0;
		for (auto symbol : pass) {
			if (isdigit(symbol)) {
				digits = 1;
			}
			else if (isalpha(symbol)) {
				alphas = 1;
			}
		}
		if (!alphas || !digits)
			return 0;
		return 1;

	}
	User(string name, string pass) {
		username = name;
		password = pass;
	}
};

vector<User> getUsers() {
	vector<User>users;
	ifstream usersList("usersList.txt");
	if (!usersList.is_open()) {
		cout << "< The file wasn't found! >" << endl;
		ofstream newuserlist;
		newuserlist.open("usersList.txt");
		cout << "The file has recently been created!" << endl;
		newuserlist << "ADMIN ADMIN" << endl;
		cout << "Admin profile is created!";
		users = getUsers();
		newuserlist.close();
		return users;
	}
	while(usersList.good()){
		string name;
		getline(usersList, name, ' ');
		string pass;
		getline(usersList, pass, '\n');
		if (name != "" && pass != "") {
			//cout << "< Log: " << name << endl;
			//cout << "< Pass: " << pass << endl;
			users.push_back(User(name, pass));
		}
	}
	return users;
}

void enter(vector<User>users) {
	string username, password;
	bool userExists = false;
	cout << "< Please enter your information >" << endl;
	cout << "> Login: "; cin >> username;
	cout << "> Password: "; cin >> password;
	for (auto user : users) {
		if (user.check(username, password)) {
			cout << "< You are successfully logged in >" << endl;
			return;
		}
	}
	cout << "<! The information is not valid !>" << endl;
	return;
}
void userRegistration(vector<User>&users) {
	ofstream newUser;
	newUser.open("usersList.txt", std::ios::app);

	string username, password;

	cout << "> Enter your username: "; cin >> username;
	while (1) {
		cout << "> Enter you password: ";  cin >> password;
		if (users[0].isPassValid(password)) {
			break;
		}
		cout << "< Your password is not valid, try again >" << endl;
	}
	
	newUser << username << " " << password << endl;
	users.push_back(User(username, password));
	return;
}

int main() {
	vector<User>users = getUsers();;
	cout << "Users' accounts: " << size(users) << endl;
	int choice;
	cout << "< Choose your option:" << endl;
	while (true) {
		cout << "> 1 - Login" << endl;
		cout << "> 2 - Register" << endl;
		cout << "> 3 - Exit" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			enter(users);
			break;
		case 2:
			userRegistration(users);
			cout << size(users) << endl;
			break;
		case 3:
			return 0;
		default:
			cout << "< Please, try again... (1/2/3) >" << endl;
			break;
		}
	}
}
