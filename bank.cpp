#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

class Bank
{
private:
	string name;
	string card;
	string balance;
	string national_id;
	string password;
public:
	void return_accounts(string set_name, string set_national_id, string set_balance, string set_card, string set_pass)
	{
		name = set_name;
		national_id = set_national_id;
		balance = set_balance;
		card = set_card;
		password = set_pass;
	}
	void create_account(string set_name, string set_national_id, string set_balance)
	{
		name = set_name;
		national_id = set_national_id;
		balance = set_balance;
		//create card
		card.clear();
		srand(static_cast<unsigned short>(time(nullptr)));
		card.append(to_string(rand() % 1000 + 4000));
		for (unsigned short i = 0; i < 3; i++)
		{
			card.push_back('-');
			const unsigned short seed = rand() % 10000;
			seed < 1000 ? card.append(to_string(seed + 4000)) : card.append(to_string(seed));
		}
		//create password
		password.clear();
		while (password.size() < 8)
		{
			const unsigned short asci = rand() % 123;
			if (asci > 64 && (asci > 96 || asci < 91)) password.push_back(static_cast<char>(asci));
			else if (asci > 47 && asci < 58 || (asci == 33 || asci == 42 || (asci > 34 && asci < 39))) password.push_back(static_cast<char>(asci));
		}
		cout << "Signup successful\n";
	}

	void deposit(string get_balance)
	{
		float float_balance = stof(balance), float_get_balance = stof(get_balance);
		float_balance += float_get_balance;
		balance = to_string(float_balance);
		cout << "Done, Deposit successful.\n\n";
	}

	void withdraw(string get_balance)
	{
		float float_balance = stof(balance), float_get_balance = stof(get_balance);
		if (float_balance >= float_get_balance)
		{
			float_balance -= float_get_balance;
			balance = to_string(float_balance);
			cout << "Done, Deposit successful.\n\n";
		}
		else
		{
			cout << "Balance is low\nError, Deposit unsuccessful.\n\n";
			return;
		}
	}

	void show_my_account() const
	{
		cout << "Name: " << name << '\n';
		cout << "National ID: " << national_id << '\n';
		cout << "Card Number: " << card << '\n';
		cout << "Balance: " << balance << '\n';
		cout << "Password: " << password << "\n\n";
	}

	bool login(string get_password, string get_card) const
	{
		get_card.insert(4, "-");
		get_card.insert(9, "-");
		get_card.insert(14, "-");
		if (get_password == password && get_card == card) return true;
		return false;
	}

	string get_card() const
	{
		return card;
	}

	string get_password() const
	{
		return password;
	}

	string get_name() const
	{
		return name;
	}

	string get_national_id() const
	{
		return national_id;
	}

	string get_balance() const
	{
		return balance;
	}
};

void logo()
{
	cout << "[1] Login\n";
	cout << "[2] Signup\n";
	cout << "[3] Exit\n";
}

void login_logo()
{
	cout << "[1] Show My Account\n";
	cout << "[2] Deposit\n";
	cout << "[3] Withdraw\n";
	cout << "[4] Logout\n";
}

bool get_name(string& name)
{
	bool space = false;
	for (const char& ch : name) 
  {
    if (ch == ' ')
    {
      space = true;
      break;
    }
  }
	if (space)
	{
		for (int i = 0; i < name.size(); i++)
		{
			if (!i) name.at(i) = toupper(name.at(i));
			else if (name.at(i) == ' ') name.at(i + 1) = toupper(name.at(i + 1));
		}
		return false;
	}
	cout << "Error, Name contain your name & father name.\n";
	return true;
}

bool get_national_id(string national_id)
{
	if (national_id.size() != 14)
	{
		cout << "Error, National ID contain 14 digit.\n";
		return true;
	}
	return false;
}

bool get_balance(string balance)
{
	if (balance == ".") return true;
	for (const char& ch : balance)
	{
		if (!isdigit(ch) && ch != '.')
		{
			cout << "Error, Amount contain digit.\n";
			return true;
		}
	}
	return false;
}

bool get_card(string card)
{
	if (card.size() != 16)
	{
		cout << "Error, Card Number contain 16 digit.\n";
		return true;
	}
	return false;
}

bool get_password(string pass)
{
	if (pass.size() < 8)
	{
		cout << "Error, Password contain 8 digit or more.\n";
		return true;
	}
	return false;
}

//main------------------------------------------------------------------------
int main()
{
	Bank account;
	vector<Bank> vec;
	ifstream read_accounts("Accounts.txt");
	string word;
	while (getline(read_accounts, word))
	{
		string name;
		string national_id;
		string balance;
		string card;
		string password;
		name = word.substr(0, word.find(','));
		word.erase(0, word.find(',') + 1);
		national_id = word.substr(0, word.find(','));
		word.erase(0, word.find(',') + 1);
		balance = word.substr(0, word.find(','));
		word.erase(0, word.find(',') + 1);
		card = word.substr(0, word.find(','));
		word.erase(0, word.find(',') + 1);
		password = word;
		account.return_accounts(name, national_id, balance, card, password);
		vec.push_back(account);
	}
	while (true)
	{
		//logo---------------------------------------------------------------
		logo();
		string select_option;
		string balance;
	ReEnter_select_option_logo:
		getline(cin, select_option);
		if (select_option.size() != 1)
		{
			cout << "Enter a valid option: ";
			goto ReEnter_select_option_logo;
		}
		else if (select_option.size() == 1 && (select_option.at(0) > '3' || select_option.at(0) < '1'))
		{
			cout << "Enter a valid option: ";
			goto ReEnter_select_option_logo;
		}
		if (select_option.at(0) == '3') break;
		switch (select_option.at(0))
		{
			//login------------------------------------------------------------
		case '1':
		{
			string password;
			string card;
		ReEnter_pass:
			cout << "Enter Password: ";
			getline(cin, password);
			if (get_password(password)) goto ReEnter_pass;
		ReEnter_card:
			cout << "Enter Card Number: ";
			getline(cin, card);
			if (get_card(card)) goto ReEnter_card;
			bool logined = false;
			unsigned short indd = -1;
			for (const Bank& word : vec)
			{
				indd++;
				if (word.login(password, card))
				{
					logined = word.login(password, card);
					break;
				}
			}
			if (logined)
			{
				cout << "Done, Login successful\n\n";
			ReLogin:
				login_logo();
			ReEnter_select_option_login:
				getline(cin, select_option);
				if (select_option.size() != 1)
				{
					cout << "Enter a valid option: ";
					goto ReEnter_select_option_login;
				}
				else if (select_option.size() == 1 && (select_option.at(0) > '4' || select_option.at(0) < '1'))
				{
					cout << "Enter a valid option: ";
					goto ReEnter_select_option_login;
				}
				if (select_option.at(0) == '4') break;
				switch (select_option.at(0))
				{
				case '1':
					vec.at(indd).show_my_account(); goto ReLogin;
				case '2':
				{
				ReEnter_balance_deposit:
					cout << "Enter Amount: ";
					getline(cin, balance);
					if (get_balance(balance)) goto ReEnter_balance_deposit;
					vec.at(indd).deposit(balance);
					for (const Bank& word : vec)
					{
						ofstream edit("Edit.txt", ios::app);
						edit << word.get_name() << ',' << word.get_national_id() << ',' << word.get_balance() << ',' << word.get_card() << ',' << word.get_password() << '\n';
					}
					ofstream ofile_acc("Accounts.txt");
					string str;
					ifstream ifile_acc("Edit.txt");
					vec.clear();
					while (getline(ifile_acc, str))
					{
						ofstream ofile_accounts("Accounts.txt", ios::app);
						string name_edit;
						string national_id_edit;
						string balance_edit;
						string card_edit;
						string password_edit;
						name_edit = str.substr(0, str.find(','));
						str.erase(0, str.find(',') + 1);
						national_id_edit = str.substr(0, str.find(','));
						str.erase(0, str.find(',') + 1);
						balance_edit = str.substr(0, str.find(','));
						str.erase(0, str.find(',') + 1);
						card_edit = str.substr(0, str.find(','));
						str.erase(0, str.find(',') + 1);
						password_edit = str;
						account.return_accounts(name_edit, national_id_edit, balance_edit, card_edit, password_edit);
						vec.push_back(account);
						ofile_accounts << name_edit << ',' << national_id_edit << ',' << balance_edit << ',' << card_edit << ',' << password_edit << '\n';
					}
					ofstream ofile_edit("Edit.txt");
					goto ReLogin;
				}
				case '3':
				{
				ReEnter_balance_withdraw:
					cout << "Enter Amount: ";
					getline(cin, balance);
					if (get_balance(balance)) goto ReEnter_balance_withdraw;
					vec.at(indd).withdraw(balance);
					for (const Bank& word : vec)
					{
						ofstream edit("Edit.txt", ios::app);
						edit << word.get_name() << ',' << word.get_national_id() << ',' << word.get_balance() << ',' << word.get_card() << ',' << word.get_password() << '\n';
					}
					ofstream ofile_acc("Accounts.txt");
					string str;
					ifstream ifile_acc("Edit.txt");
					vec.clear();
					while (getline(ifile_acc, str))
					{
						ofstream ofile_accounts("Accounts.txt", ios::app);
						string name_edit;
						string national_id_edit;
						string balance_edit;
						string card_edit;
						string password_edit;
						name_edit = str.substr(0, str.find(','));
						str.erase(0, str.find(',') + 1);
						national_id_edit = str.substr(0, str.find(','));
						str.erase(0, str.find(',') + 1);
						balance_edit = str.substr(0, str.find(','));
						str.erase(0, str.find(',') + 1);
						card_edit = str.substr(0, str.find(','));
						str.erase(0, str.find(',') + 1);
						password_edit = str;
						account.return_accounts(name_edit, national_id_edit, balance_edit, card_edit, password_edit);
						vec.push_back(account);
						ofile_accounts << name_edit << ',' << national_id_edit << ',' << balance_edit << ',' << card_edit << ',' << password_edit << '\n';
					}
					ofstream ofile_edit("Edit.txt");
					goto ReLogin;
				}
				}
			}
			else cout << "Error, Login unsuccessful.\n\n";
			break;
		}
		//signup----------------------------------------------------------
		case '2':
		{
			string name;
			string national_id;
			//name
		ReEnter_name:
			cout << "Enter Dual Name: ";
			getline(cin, name);
			if (get_name(name)) goto ReEnter_name;
			//national id
		ReEnter_national_id:
			cout << "Enter National ID: ";
			getline(cin, national_id);
			if (get_national_id(national_id)) goto ReEnter_national_id;
			//balance
		ReEnter_balance_signup:
			cout << "Enter Amount: ";
			getline(cin, balance);
			if (get_balance(balance)) goto ReEnter_balance_signup;
			account.create_account(name, national_id, balance);
			cout << "\nCard Number: " << account.get_card();
			cout << "\nPassword: " << account.get_password() << "\n\n";
			vec.push_back(account);
			ofstream add_account("Accounts.txt", ios::app);
			add_account << name << ',' << national_id << ',' << balance << ',' << account.get_card() << ',' << account.get_password() << '\n';
			break;
		}
		//signup--------------------------------------------------------
		}
	}
	return 0;
}