#include <iostream>
#include <string>
#include <vector>

using namespace std;

class transaction {
public:
    string type;
    double amount;
    double newbal;

    transaction(string t, double a, double n) : type(t), amount(a), newbal(n) {}
};

class account {
    string accnum;
    double bal;
    vector<transaction> transactions;

public:
    account(string an, double ogbal) : accnum(an), bal(ogbal) {
        transactions.push_back(transaction("Original balance", bal, bal));
    }

    string getaccnum() { return accnum; }
    double getbal() { return bal; }

    void deposit(double amount) {
        bal += amount;
        transactions.push_back(transaction("Deposit", amount, bal));
    }

    bool withdraw(double amount) {
        if (amount > bal) {
            cout << "Insufficient funds for this transaction.\n";
            return false;
        } else {
            bal -= amount;
            transactions.push_back(transaction("Withdrawal", amount, bal));
            return true;
        }
    }

    void transfer(account& recipient, double amount) {
        if (withdraw(amount)) {
            recipient.deposit(amount);
            transactions.push_back(transaction("Transfer to " + recipient.getaccnum(), amount, bal));
        }
    }

    void records() const {
        cout << "Account Number: " << accnum << endl;
        cout << "Balance: PKR " << bal << endl;
        cout << "Transaction History:\n";
        for (const auto& t : transactions) {
            cout << t.type << ": PKR " << t.amount << ", New balance: PKR " << t.newbal << endl;
        }
    }
};

class person {
    string name;
    string id;
    vector<account> accounts;

public:
    person(string n, string i) : name(n), id(i) {}

    string getid() { return id; }

    void addacc(const account& acc) {
        accounts.push_back(acc);
    }

    account* getacc(const string& accnum) {
        for (auto& a : accounts) {
            if (a.getaccnum() == accnum) {
                return &a;
            }
        }
        return nullptr;
    }

    void print() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Accounts:\n";
        for (const auto& a : accounts) {
            a.records();
            cout << endl;
        }
    }
};

class bank {
    vector<person> persons;

public:
    void addperson(const person& newperson) {
        persons.push_back(newperson);
    }

    person* getperson(const string& id) {
        for (auto& p : persons) {
            if (p.getid() == id) {
                return &p;
            }
        }
        return nullptr;
    }

    void printall() const {
        for (const auto& p : persons) {
            p.print();
            cout << "____________________\n";
        }
    }
};

int main() {
    cout << "ONLINE BANKING SYSTEM\n\n";

    bank mybank;

    person p1("Arbaaz", "001");
    p1.addacc(account("A1", 2000.00));
    p1.addacc(account("A2", 10000.00));
    mybank.addperson(p1);

    person p2("Murtaza", "002");
    p2.addacc(account("M1", 45000.00));
    p2.addacc(account("M2", 100.00));
    mybank.addperson(p2);

    mybank.printall();
    cout << endl << endl << "After transferring PKR 300 from Acc.No. A1 to Acc.No. M1:\n\n";

    person* c1 = mybank.getperson("001");
    person* c2 = mybank.getperson("002");

    if (c1 && c2) {
        account* from = c1->getacc("A1");
        account* to = c2->getacc("M1");
        if (from && to) {
            from->transfer(*to, 300.0);
        }
    }

    mybank.printall();
}
