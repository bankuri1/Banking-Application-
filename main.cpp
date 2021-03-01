#include<iostream>
#include<map>
#include<fstream>
#include<cstring>

using namespace std;

//bs ek cheej or krne de bss plleahsee abey karlee raaam seee
class account {
private:
	string name;
	float amount;
	int acc_number;
	static int nextno;
public:
	account() {

	}
	account(string name, float balance);
	int getaccountno() {
		return acc_number;
	}
	string getname() {
		return name;
	}
	float getbalance() {
		return amount;
	}
	void deposit(float amm);
	void withdraw(float amm);
	friend ostream& operator<<(ostream &out, account &a);
	friend ifstream& operator >>(ifstream &ifs, account &a);
	friend ofstream& operator <<(ofstream &ofs, account &a);
	static void setaccno(int pre) {
		nextno = pre;
	}
};
int account::nextno = 0;
class bank {
private:
	map<int, account> m1;
public:
	bank();
	account openacc(string name, int amt);
	void closeacc(int acc_no);
	account deposit(int acc_no, int amt);
	account withdraw(int acc_no, int amt);
	void showall();
	account acc_enquiry(int acc_no);
	~bank();
};
account::account(string name, float balance) {
	this->name = name;
	amount = balance;
	nextno++;
	acc_number = nextno;
}
void account::deposit(float amm) {
	amount += amm;
}
void account::withdraw(float amm) {
if((amount-amm)<500){
	cout<<"cannot withdraw min account balance should be 500" ;
 return;
}
	amount -= amm;

}

ostream& operator<<(ostream &out, account &a) {
	out << "account no is: " << a.getaccountno() << endl;
	out << "Name of account holder is: " << a.getname() << endl;

	out << "Balance of account holder is: " << a.getbalance() << endl;
	return out;
}
ifstream& operator >>(ifstream &ifs, account &a) {
	ifs >> a.acc_number;
	ifs >> a.name;
	ifs >> a.amount;
	return ifs;
}
ofstream& operator <<(ofstream &ofs, account &a) {
	ofs << a.acc_number << endl;
	ofs << a.name << endl;
	ofs << a.amount << endl;
	return ofs;
}

/*Bank method definition*/

account bank::openacc(string name, int amt) {
	account a1(name, amt);
	m1.insert(pair<int, account>(a1.getaccountno(), a1));
	return a1;
}
void bank::showall() {
	map<int, account>::iterator i1;
	for (i1 = m1.begin(); i1 != m1.end(); i1++) {
		cout << i1->second << endl;
	}
}
account bank::deposit(int acc_no, int amt) {
	map<int, account>::iterator i1;
	i1 = m1.find(acc_no);
	i1->second.deposit(amt);
	return i1->second;
}
account bank::acc_enquiry(int acc_no) {
	map<int, account>::iterator i1;
	i1 = m1.find(acc_no);
	return i1->second;

}
void bank::closeacc(int acc_no) {
	map<int, account>::iterator i1;
	i1 = m1.find(acc_no);
	cout << "Account deleted successfully: ";
	m1.erase(acc_no);
}
account bank::withdraw(int acc_no, int amt) {
	map<int, account>::iterator i1;
	i1 = m1.find(acc_no);
	i1->second.withdraw(amt);
	return i1->second;
}
bank::bank() {
	ifstream ifline;
	account a1;
	ifline.open("bank.data");
	if (!ifline) {
		
		return;
	}
	while (!ifline.eof()) {
		ifline >> a1;
		m1.insert(pair<int, account>(a1.getaccountno(), a1));

	}

	account::setaccno(a1.getaccountno());
	ifline.close();
}
bank::~bank() {
	ofstream ofline;
	ofline.open("bank.data", ios::trunc);
	map<int, account>::iterator it;
	for (it = m1.begin(); it != m1.end(); it++) {
		ofline << it->second;
	}
	ofline.close();

}

int main() {
	account a;
	bank b;
	float amt;
	string name;
	int choice, acc_no;

	while (1) {
		cout << "\n 1) Create Account :";
		cout << "\n 2) Deposit :";
		cout << "\n 3) Withdraw :";
		cout << "\n 4) Account Inquiry :";
		cout << "\n 5) Close Account :";
		cout << "\n 6) Show all account";
		cout << "\n 7) Exit :";
		cout << "\n choose from the above option : :";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\nEnter name for your account: ";
			cin >> name;
			cout << "Enter the initial account: ";
			cin >> amt;
			a = b.openacc(name, amt);
			cout << "\nCongratulation account created : " << endl;
			cout <<"\n"<< a<<endl;
			break;
		case 2:
			cout << "\nEnter the account no : ";
			cin >> acc_no;
            cout << "Enter the amount: ";
			cin >> amt;
			a = b.deposit(acc_no, amt);
			cout <<"\n"<< a<<endl;
			break;
		case 3:
			cout << "\nEnter the account no : ";
			cin >> acc_no;
			cout << "Enter the amount: ";
			cin >> amt;
			a = b.withdraw(acc_no, amt);
			cout <<"\n"<< a<<endl;

			break;
		case 4:
			cout << "\nEnter the account no : ";
			cin >> acc_no;
			a  = b.acc_enquiry(acc_no);
			cout << "\nAccount found detial  is: \n\n" <<a<<endl;
			break;
		case 5:
			cout << "\nEnter the account no : ";
			cin >> acc_no;
			b.closeacc(acc_no);
			cout<<"\nYour account has been closed: "<<endl;
			break;
		case 6:
			b.showall();
           break;
		case 7:
			goto out;
		} 
	}
	out:
	return 0;
}

