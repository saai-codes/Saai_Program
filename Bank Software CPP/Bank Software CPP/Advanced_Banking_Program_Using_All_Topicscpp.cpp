#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

/* ================= CLASS DEFINITION ================= */
/* This class represents a Bank Account */ 
class BankAccount {
private:
    int accountNumber;     // Stores account number
    char name[50];         // Stores account holder name
    char accountType;      // S = Saving, C = Current
    float balance;         // Stores balance amount

public:
    /* Function to create a new account */
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cout << "Enter Account Holder Name: ";
        cin.ignore();                 // Clears buffer
        cin.getline(name, 50);        // Takes full name with space     

        cout << "Enter Account Type (S for Saving / C for Current): ";
        cin >> accountType;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        cout << "\nAccount Created Successfully!\n";
    }

    /* Function to display account details */
    void showAccount() const {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder Name: " << name;
        cout << "\nAccount Type: " << accountType;
        cout << "\nBalance: " << balance << endl;
    }

    /* Function to deposit money */
    void deposit(float amt) {
        balance += amt;
    }

    /* Function to withdraw money */
    void withdraw(float amt) {
        // IF-ELSE CONDITION USED HERE
        if (balance >= amt)
            balance -= amt;
        else
            cout << "\nInsufficient Balance!";
    }

    /* Getter for account number */
    int getAccountNumber() const {
        return accountNumber;
    }

    /* Getter for balance */
    float getBalance() const {
        return balance;
    }
};

/* ================= FILE HANDLING FUNCTIONS ================= */

/* Function to write account data into file */
void writeAccount() {
    BankAccount acc;   // Object of class

    ofstream outFile("bank.dat", ios::binary | ios::app);
    acc.createAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
    outFile.close();
}

/* Function to display account details using account number */
void displayAccount(int n) {
    BankAccount acc;
    ifstream inFile("bank.dat", ios::binary);
    bool found = false;

    // Loop to read file
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        // IF CONDITION USED HERE
        if (acc.getAccountNumber() == n) {
            acc.showAccount();
            found = true;
        }
    }
    inFile.close();

    // IF CONDITION USED HERE
    if (!found)
        cout << "\nAccount Not Found!";
}

/* Function to deposit or withdraw money */
void depositWithdraw(int n, int option) {
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    float amt;
    bool found = false;

    while (!file.eof() && !found) {
        file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount));

        // IF CONDITION USED HERE
        if (acc.getAccountNumber() == n) {
            acc.showAccount();

            // IF-ELSE USED TO CHOOSE DEPOSIT OR WITHDRAW
            if (option == 1) {
                cout << "\nEnter Amount to Deposit: ";
                cin >> amt;
                acc.deposit(amt);
            } else {
                cout << "\nEnter Amount to Withdraw: ";
                cin >> amt;
                acc.withdraw(amt);
            }

            // Move file pointer back
            int pos = (-1) * static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);

            // Write updated record
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            cout << "\nTransaction Successful!";
            found = true;
        }
    }
    file.close();

    // IF CONDITION USED HERE
    if (!found)
        cout << "\nAccount Not Found!";
}

/* ================= MAIN FUNCTION ================= */
int main() {
    int choice, num;


    cout <<"\n\n--------Welcome To Saai National Bank--------";

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create New Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Balance Enquiry";
        cout << "\n5. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        // SWITCH-CASE USED FOR MENU
        switch (choice) {
        case 1:
            writeAccount();
            break;

        case 2:
            cout << "\nEnter Account Number: ";
            cin >> num;
            depositWithdraw(num, 1);
            break;

        case 3:
            cout << "\nEnter Account Number: ";
            cin >> num;
            depositWithdraw(num, 2);
            break;

        case 4:
            cout << "\nEnter Account Number: ";
            cin >> num;
            displayAccount(num);
            break;

        case 5:
            cout << "\n\nThank You for Using Saai's Bank System!\n\n";
            break;

        default:
            cout << "\nInvalid Choice!";
        }

    } while (choice != 5);

    return 0;
}
