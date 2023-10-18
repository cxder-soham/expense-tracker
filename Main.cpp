#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <vector>
using namespace std;

class Authenticate
{
    string name;
    string username;
    string pin;

public:
    Authenticate() {}

    bool log_in(string id, string pass)
    {
        // Write Log in code
        cout << "Logged in" << endl;
        return true;
    }
    void sign_up(string name, string id, string pass)
    {
        // Write Sign up code
        cout << "Account created successfully" << endl;
    }
};

class Wallet
{
    double balance;
    map<string, float> pending_expenses; // format -> pending expense desc , amount
    map<string, float>::iterator it = pending_expenses.begin();

public:
    Wallet() {}
    Wallet(string id, double bal)
    {
        username = id;
        balance = bal;
        if (authenticate(username, bal))
            cout << "Account created successfully" << endl;
        else
            cout << "Username already exists"
    }
    Wallet(float b)
    {
        balance = b;
    }
    void operator<<(Wallet &w) // displaying object
    {
        cout << w.balance << endl;
        while (it != pending_expenses.end())
        {
            cout << "Key: " << it->first << ", Value: " << it->second << endl;
            ++it;
        }
    }
    void newAccount()
    {
        while (b)
        {   
            char ch1;
            cout << "Enter username" << endl;
            cin >> username;
            b = authenticate(username); // if b is true means username already exists
            if (b)
            {
                cout << "Already exists, do you want to login? y or n " << endl;
                cin >> ch1;
                if (ch1 == 'y')
                {   
                    Login();
                    break;
                }
            }
        }
    }
    void Login()
    {

    }
    bool authenticate(string id, double bal)
    {
        bool found_record = false;
        ifstream file("userdatabase.csv");
        string line;

        while (getline(file, line) && !found_record)
        {
            size_t pos = line.find(id + ',');
            if (pos != string::npos)
            {
                found_record = true;
            }
        }
        return found_record;
    }
    void depositMoney(int amt)
    {
    }
    void withdrawMoney(int amt)
    {
    }
    void test()
    {
        ofstream file;
        file.open("userdatabase.csv");
        string line;
        while (file)
        {
            getline(cin, line);
            cout << line;
        }
    }
};

class Expense_tracker
{
    float dailyLimit;
    float weeklyLimit;
    float monthlyLimit;
    map<string, float> expenses;

public:
    Expense_tracker() {}

    void setLimit(int type, float limit)
    {
        if (type == 1)
        {
            dailyLimit = limit;
        }
        else if (type == 2)
        {
            weeklyLimit = limit;
        }
        else if (type == 3)
        {
            monthlyLimit = limit;
        }
    }

    // this function would call the limit functions inside its body to check if expense can be added
    void AddExpense(string description, float amount, int type)
    {
        expenses[description] = amount;
        // Check if adding the expense exceeds the daily, weekly, or monthly limit
        if ((type == 1 && amount <= dailyLimit) || (type == 2 && amount <= dailyLimit) || (type == 3 && amount <= monthlyLimit))
        {
            cout << "Expense added Successfully!" << endl;
        }
        else
        {
            cout << "Expense exceeded the limit..\n";
        }
    } // this function would call the limit functions inside its body to check if expense can be added
      // Also it would add to pending expenses in wallet
};

class Savings
{
    float savingGoal;
};

int main()
{
    Wallet w;
    double bal;
    int n;
    int choice;
    char ch, ch1;
    string s;
    float amt;
    bool bb;
    int type;
    float limit;
    bool b = true;
    vector<string, float> exp; // for expenses with description and amount
    while (true)
    {
        cout << "*****************Login*****************" << endl;
        cout << "Are you a new user? y or n" << endl;
        cin >> ch;
        if (ch == 'y')
        {
            w.newAccount();
        }
        else
        {
            w.Login();
        }
    }

    return 0;
}
