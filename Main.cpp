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
    double bal;
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
class Wallet : public Authenticate // class Wallet inherits class Authenticate
{
    float bal;
    // inherited username
    map<string, float> pending_expenses; // format -> pending expense desc , amount
    map<string, float>::iterator it = pending_expenses.begin();

public:
   
   // int exp_cnt = expcount;
    Wallet() {}
    Wallet(float b)
    {
        bal = b;
    }
    void operator<<(Wallet &w) // displaying object
    {
        cout << balance << endl;
        while (it != pending_expenses.end())
        {
            cout << "Key: " << it->first << ", Value: " << it->second << endl;
            ++it;
        }
    }
    
    friend void viewWallet(Wallet &s);
    
    float get_balance()
    {
        ifstream file("balance.csv");
        float balance;
        file >> balance;
        file.close();
        return balance;
    }

    void set_balance(float bal)
    {
        ofstream file;
        file.open("balance.csv", ios::out | ios_base::trunc);
        file << bal;
    }

    void depositMoney(float amt)
    {
        bal = get_balance();
        bal += amt;
        set_balance(bal);
        cout << "Balance updated!\nNew Balance: " << bal << endl;
    }
    void withdrawMoney(int amt)
    {
        bal = get_balance();
        bal -= amt;
        set_balance(bal);
        cout << "Balance updated!\nNew Balance: " << bal << endl;
    }
   
};
void viewWallet(Wallet &w)
{
    w.bal = w.get_balance();
    cout << "Wallet Balance: " << w.bal << endl;
}

class Expense_tracker : public Wallet
{
protected:
    float dailyLimit;
    float weeklyLimit;
    float monthlyLimit;
    float savings = 0.0;
    map<string, float> expenses;
    int expcount = 0;
    
public:
    Wallet w;
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
    void displaycount()
    {
        cout << "Number of expenses " << expcount << endl;
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
            savings = (dailyLimit - amount);
            w.withdrawMoney(amount);
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
            savings -= amount;
        }
    } 
 
    void saving()
    {
        cout << "Your savings today =" << savings << endl;
    }
};


int main()
{
    double bal;
    int n;
    int choice;
    char ch;
    string s;
    float amt;
    bool user_exists;
    int type;
    float limit;
    Wallet v;
    bool is_logged_in;
    string name, username, pin;
    Authenticate auth;
    Expense_tracker e;
    Expense_tracker et;
    while (1)
    {
        cout << "****************Welcome****************" << endl;
        if (!is_logged_in)
        {
            cout << "1. Create New Account\n2. Login to you Account\n3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {

                is_logged_in = auth.sign_up();
                if(is_logged_in)
                {
                    v.depositMoney(auth.bal);
                }

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
                Wallet w;
                float amount;

                cout << "Wallet" << endl; // balance, view wallet -> expense list - name, amt
                cout << "1. View Wallet\n2. Deposit Money\n3. Withdraw Money" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1)
                {
                    // w.chkwallet();
                    viewWallet(w);
                    e.displaycount();
                }
                else if (choice == 2)
                {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    w.depositMoney(amount);
                }
                else if (choice == 3)
                {
                    float amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    w.withdrawMoney(amount);
                }
            }
            else if (choice == 2)
            {
                cout << "Expense Tracker" << endl;
                cout << "1. Set Limit\n2. Add Expense\n3. Track" << endl;

                cin >> choice;

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

                    et.AddExpense(description, expense, type, auth.username);
                }
            }
            else if (choice == 3)
            {
                et.saving();
            }
            else if (choice == 4)
            {
                is_logged_in = false;
            }
            else
                cout << "Invalid Input" << endl;
        }
    }
}
