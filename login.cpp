#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ExistLoginException : public exception {
public:
	ExistLoginException(const string& massage = "Invalid login") :
		exception(massage.data()) {}
};

class FormatPasswordException : public exception {
public:
	FormatPasswordException(const string& massage = "Invalid password format") :
		exception(massage.data()) {}
};

class InvalidLoginException : public exception {
public:
	InvalidLoginException(const string& massage = "Such login does not exist") :
		exception(massage.data()) {}
};

class InvalidPasswordException : public exception {
public:
	InvalidPasswordException(const string& massage = "Wrong password") :
		exception(massage.data()) {}
};





class User {
	string login, password;
public:
	User(const string& login, const string& password) : login{ login }, password{password}{}
	const string& getLogin() const{
		return login;
	}
	const string& getPassword() const {
		return password;
	}
};

class SocialNetwork {
	vector<User> accounts;
	bool checkPassword(const string& password) const {
		if (findDigit(password) && findLowAlpha(password) && findUpAlpha(password) && findPunct(password) && password.size() > 7)
		{
			return true;
		}
		return false;
	}
	bool checkLogin(const string& login) const {
		return findLogin(login) == -1;
	}
	int findLogin(const string& login) const {
		for (size_t i = 0; i < accounts.size(); i++)
		{
			if (accounts[i].getLogin() == login)
			{
				return i;
			}
		}
		return -1;
	}
	bool findDigit(const string& password) const {
		for (size_t i = 0; i < password.size(); i++)
		{
			if (isdigit(password[i])) {
				return true;
			}
		}
		return false;
	}
	bool findLowAlpha(const string& password) const {
		for (size_t i = 0; i < password.size(); i++)
		{
			if (islower(password[i])) {
				return true;
			}
		}
		return false;
	}
	bool findUpAlpha(const string& password) const {
		for (size_t i = 0; i < password.size(); i++)
		{
			if (isupper(password[i])) {
				return true;
			}
		}
		return false;
	}
	bool findPunct(const string& password) const {
		string symbols = "_&$#!?|@*^[]{}+-.";
		for (size_t i = 0; i < password.size(); i++)
		{
			for (size_t j = 0; j < symbols.size(); j++)
			{
				if (password[i] == symbols[j]) {
					return true;
				}
			}
		}
		return false;
	}
public:
	void register_(const string& login, const string& password) {
		if (!checkLogin(login)) {
			throw ExistLoginException();
		}
		if (!checkPassword(password)) {
			throw FormatPasswordException();
		}
		User new_one(login, password);
		accounts.push_back(new_one);
		cout << "Registered" << endl;
	}
	void sign_in(const string& login, const string& password) {
		if (findLogin(login) == -1) {
			throw InvalidLoginException();
		}
		if (accounts[findLogin(login)].getPassword() != password) {
			throw InvalidPasswordException();
		}

		cout << "Welcome" << endl;
	}
};


int main()
{
	SocialNetwork insta;
	while (true)
	{
		int choice;
		cout << "1 - Regicter;\n2 - Sign in;\n0 - exit;\nEnter: ";
		cin >> choice;
		if (choice == 0) break;

		switch (choice)
		{
		case 1:
		{
			try
			{
				string login, password;
				cin.ignore();
				cout << "Enter login :: ";
				getline(cin, login);
				cout << "Enter password :: ";
				getline(cin, password);
				insta.register_(login, password);
				
			}
			catch (const std::exception& ex)
			{
				cout << typeid(ex).name() << " \t " << ex.what() << endl;
			}
			break;
		}
		case 2:
		{
			try
			{
				string login, password;
				cin.ignore();
				cout << "Enter login :: ";
				getline(cin, login);
				cout << "Enter password :: ";
				getline(cin, password);
				insta.sign_in(login, password);
			}
			catch (const std::exception& ex)
			{
				cout << typeid(ex).name() << " \t " << ex.what() << endl;
			}
			break;
		}

		}
	}

}

