#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Authenticate
{
public:
    string name;
    string username;
    string pin;
    string balance;
    // vector<string> userdata;

public:
    Authenticate() {}
    bool log_in()
    {
        bool x = true;
        bool found_record = false;
        ifstream file("userdatabase.csv");
        string field_one;
        string field_two;
        string field_three;

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter 4 digit PIN: ";
        cin >> pin;

        while (getline(file, field_one, ',') && getline(file, field_two, ','))
        {
            if (field_one == username)
            {
                if (field_two == pin)
                {
                    found_record = true;
                    getline(file, field_three, ',');

                    balance = field_three;
                    cout << balance;
                    break; // Stop searching once found
                }
                else
                {
                    cout << "Re-enter 4 digit PIN: ";
                    cin >> pin;
                    file.seekg(0, ios::beg); // Move the pointer to the beginning of the file
                    continue;
                }
            }
            getline(file, field_three, '\n');
        }

        if (found_record)
        {
            cout << "Logged in" << endl;
            return true;
        }
        else
        {
            cout << "Account does not exist" << endl;
            exit(0);
        }
    }

    bool sign_up()
    {
        bool b = true;

        double bal;
        // Write Sign up code
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
                    return (log_in());
                }
                else
                    cout << "Enter a different username" << endl;
            }
            else
                break;
        }
        cout << "Enter Password" << endl;
        cin >> pin;
        cout << "Enter Balance" << endl;
        cin >> bal;
        createAccount(username, pin, bal);
        ofstream file;
        file.open("expense_data.csv", ios::out | ios_base::app);
        file << "\n"
             << username << ",";
        cout << "Account created successfully" << endl;
        return true;
    }
    bool authenticate(string id)
    {
        bool found_record = false;
        ifstream file("userdatabase.csv");
        string field_one;
        string field_two;
        string field_three;
        while (getline(file, field_one, ',') && !file.eof())
        {
            if (field_one == id)
            {
                found_record = true;
                break; // Stop searching once found
            }

            getline(file, field_three, '\n');
        }
        return found_record;
    }
    void createAccount(string field_one, string field_two, double field_three)
    {
        ofstream file;
        file.open("userdatabase.csv", ios_base::app);
        file << field_one << ',' << field_two << ',' << field_three << endl;
    }
};
class Expense_tracker
{
protected:
    float dailyLimit;
    float weeklyLimit;
    float monthlyLimit;
    map<string, float> expenses;
    int expcount = 0;

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
    void displaycount(string b)
    {   
        cout<< b;
        cout << "Number of expenses"<<expcount;
    }
    // this function would call the limit functions inside its body to check if expense can be added
    void AddExpense(string description, float amount, int type, string id)
    {
        ofstream file;
        file.open("expense_data.csv", ios::out | ios_base::app);
        expenses[description] = amount;
        ofstream file1;
        file1.open("userdatabase.csv", ios::out | ios_base::app);

        ifstream file2("userdatabase.csv", ios::in);
        string field_one;
        string field_two;

        string field_three;
        string s = description + ":" + to_string(amount);
        // Check if adding the expense exceeds the daily, weekly, or monthly limit
        if ((type == 1 && amount <= dailyLimit) || (type == 2 && amount <= dailyLimit) || (type == 3 && amount <= monthlyLimit))
        {
            file << s << ",";
            cout << "Expense added Successfully!" << endl;
            expcount++;
            while (getline(file2, field_one, ',') && !file2.eof())
            {
                if (field_one == id)
                {
                    // field_three = stof(field_three) - amount);
                    break; // Stop searching once found
                }

                getline(file2, field_three, '\n');
            }
        }
        else
        {
            cout << "Expense exceeded the limit..\n";
        }
    } // this function would call the limit functions inside its body to check if expense can be added
      // Also it would add to pending expenses in wallet
};
class Wallet : public Authenticate, public Expense_tracker // class Wallet inherits class Authenticate
{
    string bal = balance;
    // inherited username
    map<string, float> pending_expenses; // format -> pending expense desc , amount
    map<string, float>::iterator it = pending_expenses.begin();

public:
    string id = username;
    int exp_cnt = expcount;
    Wallet() {}
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
    friend void viewWallet(Wallet &s);
    void chkwallet()
    {
        ifstream file("expense_data.csv", ios::in);
        string temp, line, word, user, field_one;

        while (getline(file, field_one, ',') && !file.eof())
        {
            if (field_one == id)
            {
                getline(file, line, '\n');
                cout << line;
                break; // Stop searching once found
            }

            getline(file, line, '\n');
        }
    }

    void depositMoney(int amt)
    {
    }
    void withdrawMoney(int amt)
    {
    }
    /*void test()
    {
        ofstream file;
        file.open("userdatabase.csv");
        string line;
        while (file)
        {
            getline(cin, line);
            cout << line;
        }
    }*/
};
void viewWallet(Wallet &w)
{
    cout << "Wallet Balance: " << w.bal;
}
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
    char ch;
    string s;
    float amt;
    bool user_exists;
    int type;
    float limit;

    bool is_logged_in;
    string name, username, pin;
    Authenticate auth;
    Expense_tracker e;
    while (1)
    {
        cout << "*****************Welcome*****************" << endl;
        if (!is_logged_in)
        {
            cout << "1. Create New Account\n2. Login to you Account\n3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {

                is_logged_in = auth.sign_up();
            }
            else if (choice == 2)
            {

                is_logged_in = auth.log_in();
            }
            else if (choice == 3)
            {
                return 0;
            }
            else
            {
                cout << "Invalid Input" << endl;
            }
        }
        else
        {
            cout << "1. Wallet\n2. Expense Tracker\n3. Savings\n4. Log out" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == 1)
            {
                cout << "Wallet" << endl; // balance, view wallet -> expense list - name, amt

            e.displaycount(auth.balance);
            }
            else if (choice == 2)
            {
                cout << "Expense Tracker" << endl;
                cout << "1. Set Limit\n2. Add Expense\n3. Track" << endl;

                cin >> choice;

                Expense_tracker et;
                if (choice == 1)
                {
                    cout << "Choose a type of limit:\n1. Daily\n2. Weekly\n3. Monthly\n";
                    cin >> type;
                    cout << "Enter your limit: ";
                    cin >> limit;

                    et.setLimit(type, limit);
                }
                else if (choice == 2)
                {
                    string description;
                    float expense;

                    cout << "Add Expense" << endl;
                    cout << "Description: ";
                    cin >> description;
                    cout << "Expense: ";
                    cin >> expense;

                    et.AddExpense(description, expense, type, w.id);
                }
            }
            else if (choice == 3)
            {
            }
            else if (choice == 4)
            {
                is_logged_in = false;
            }
            else
                cout << "Invalid Input" << endl;
        }
    }

    return 0;
}
