// BANKING SYSTEM 
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

class Customers
{
    string name;
    long accountNumber;
    long balance;

public:
    void setname(string name) { this->name = name; }
    void setaccNum(long accountNumber) { this->accountNumber = accountNumber; }
    void setbalance(long balance) { this->balance = balance; }
    string getname() { return name; }
    long getaccNum() { return accountNumber; }
    long getbalance() { return balance; }
};

class Accounts
{
    Customers customer;
    int accounttype; // 1 for savings, 2 for current
public:
    void setCustomer(Customers c) { customer = c; }
    void setaccType(int accounttype) { this->accounttype = accounttype; }
    Customers &getcustomer() { return customer; }
    int getaccType() { return accounttype; }
    string getAccountTypeName()
    {
        return accounttype == 1 ? "Savings" : "Current";
    }
};

class Transactions
{
    Accounts account;
    double amount;

public:
    void setAccount(Accounts acc) { account = acc; }
    void setamount(double amount) { this->amount = amount; }
    double getamount() { return amount; }
    void deposit(double amount)
    {
        account.getcustomer().setbalance(account.getcustomer().getbalance() + amount);
        cout << "Deposit Successful! Current Balance is: " << account.getcustomer().getbalance() << endl;
    }
    void withdrawal(double amount)
    {
        if (account.getcustomer().getbalance() >= amount)
        {
            account.getcustomer().setbalance(account.getcustomer().getbalance() - amount);
            cout << "Withdrawal Successful! Current Balance is: " << account.getcustomer().getbalance() << endl;
        }
        else
        {
            cout << "Withdrawal unsuccessful! Not enough balance in account." << endl;
        }
    }
};

class BankingServices
{
    vector<Accounts> accounts;

public:
    void CreateAccount(Customers c, int accounttype)
    {
        Accounts account;
        account.setCustomer(c);
        account.setaccType(accounttype);
        accounts.push_back(account);
        cout << "Account Created Successfully!" << endl;
    }
    Accounts *getAccountByNumber(long accountNumber)
    {
        for (auto &account : accounts)
        {
            if (account.getcustomer().getaccNum() == accountNumber)
            {
                return &account;
            }
        }
        return nullptr;
    }
    void deposit(long accountNumber, double amount)
    {
        Accounts *account = getAccountByNumber(accountNumber);
        if (account)
        {
            Transactions transaction;
            transaction.setAccount(*account);
            transaction.deposit(amount);
            writeTransactionToFile("Deposit", account->getcustomer(), amount, account->getAccountTypeName());
        }
        else
        {
            cout << "Account not found!" << endl;
        }
    }
    void withdraw(long accountNumber, double amount)
    {
        Accounts *account = getAccountByNumber(accountNumber);
        if (account)
        {
            Transactions transaction;
            transaction.setAccount(*account);
            transaction.withdrawal(amount);
            writeTransactionToFile("Withdrawal", account->getcustomer(), amount, account->getAccountTypeName());
        }
        else
        {
            cout << "Account not found!" << endl;
        }
    }
    void writeTransactionToFile(string type, Customers customer, double amount, string accountType)
    {
        ofstream file("transactions.txt", ios::app);
        if (file.is_open())
        {
            time_t now = time(0);
            tm *ltm = localtime(&now);

            file << "Date: " << 1900 + ltm->tm_year << "-"
                 << 1 + ltm->tm_mon << "-"
                 << ltm->tm_mday << " "
                 << 1 + ltm->tm_hour << ":"
                 << 1 + ltm->tm_min << ":"
                 << 1 + ltm->tm_sec << endl;
            file << "Account Number: " << customer.getaccNum() << endl;
            file << "Account Holder: " << customer.getname() << endl;
            file << "Account Type: " << accountType << endl;
            file << "Transaction Type: " << type << endl;
            file << "Amount: " << amount << endl;
            file << "Balance: " << customer.getbalance() << endl;
            file << "------------------------" << endl;
            file.close();
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }
    void readTransactionsFromFile()
    {
        ifstream file("transactions.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }
};

void displayMenu()
{
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. View Transactions" << endl;
    cout << "5. Exit" << endl;
}

int main()
{
    BankingServices bankService;
    int choice;
    double amount;
    string name;
    long accountNumber;
    int accountType;

    while (true)
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter initial balance: ";
            cin >> amount;
            cout << "Enter account type (1 for Savings, 2 for Current): ";
            cin >> accountType;

            {
                Customers customer;
                customer.setname(name);
                customer.setaccNum(accountNumber);
                customer.setbalance(amount);
                bankService.CreateAccount(customer, accountType);
            }
            break;
        case 2:
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            bankService.deposit(accountNumber, amount);
            break;
        case 3:
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            bankService.withdraw(accountNumber, amount);
            break;
        case 4:
            bankService.readTransactionsFromFile();
            break;
        case 5:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}
