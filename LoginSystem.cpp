#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <windows.h>

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

void gotoxy(short a, short b) //Custom gotoxy() function
{
	COORD coordinates; //Data type of co-ordinates
	coordinates.X = a; //Assign value to X- Co-ordinate
	coordinates.Y = b; //Assign value to Y Co-ordinate

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), coordinates);

}
void square(short a, short b, short x, short y) {
	gotoxy(x, y);
	for (int i = 0; i < a; i++) {
		cout << "=";
	}
	for (int i = 0; i < b - 2; i++) {
		gotoxy(x, y + i + 1);
		cout << "|";
		for (int j = 0; j < a - 2; j++) {
			cout << " ";
		}
		cout << "|";
	}
	cout << endl;
	gotoxy(x, y + b - 1);
	for (int i = 0; i < a; i++) {
		cout << "=";
	}
}

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
	while (usersList.good()) {
		string name;
		getline(usersList, name, ' ');
		string pass;
		getline(usersList, pass, '\n');
		if (name != "" && pass != "") {
			//	cout << "< Log: " << name << endl;
			//	cout << "< Pass: " << pass << endl;
			users.push_back(User(name, pass));
		}
	}
	return users;
}

void enter(vector<User>users) {
	string username, password;
	bool userExists = false;
	square(33, 5, 9, 4);
	gotoxy(10, 5);
	cout << " Please enter your information " << endl;
	gotoxy(10, 7);
	cout << "> Login: "; cin >> username;
	square(33, 7, 9, 4);
	gotoxy(10, 5);
	cout << " Please enter your information " << endl;
	gotoxy(10, 7);
	cout << "> Login: " << username << endl;
	gotoxy(10, 8);
	cout << "> Password: "; cin >> password;
	for (auto user : users) {
		if (user.check(username, password)) {
			system("cls");
			square(35, 3, 9, 4);
			gotoxy(10, 5);
			cout << "< You are successfully logged in >" << endl;
			gotoxy(11, 7);
			system("pause");
			return;
		}
	}
	system("cls");
	square(35, 3, 9, 4);
	gotoxy(10, 5);
	cout << "<! The information is not valid !>" << endl;
	gotoxy(11, 7);
	system("pause");
	return;
}
void userRegistration(vector<User>& users) {
	ofstream newUser;
	newUser.open("usersList.txt", std::ios::app);

	string username, password;
	square(40, 3, 9, 4);
	gotoxy(10, 5);
	cout << " Enter your username: ";
	cin >> username;
	while (1) {
		square(40, 5, 9, 4);
		gotoxy(10, 5);
		cout << " Enter your username: " << username;
		gotoxy(10, 6);
		cout << " Enter you password: ";  cin >> password;
		if (users[0].isPassValid(password)) {
			break;
		}
		gotoxy(10, 7);
		cout << " Your password is not valid, try again ";
	}

	newUser << username << " " << password << endl;
	users.push_back(User(username, password));
	return;
}


int main() {
	vector<User>users = getUsers();;
	int choice;

	while (true) {
		system("cls");
		square(22, 7, 9, 4);
		gotoxy(10, 5);
		cout << " Choose your option " << endl;
		gotoxy(10, 6);
		cout << "> 1 - Login" << endl;
		gotoxy(10, 7);
		cout << "> 2 - Register" << endl;
		gotoxy(10, 8);
		cout << "> 3 - Exit" << endl;
		gotoxy(16, 9);
		cout << "<<   >>";
		gotoxy(19, 9);
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1:
			enter(users);
			break;
		case 2:
			userRegistration(users);
			break;
		case 3:
			return 0;
		default:
			cout << "< Please, try again... (1/2/3) >" << endl;
			break;
		}
	}
}
