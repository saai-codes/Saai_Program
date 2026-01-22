#include <stdio.h>
#include <string.h>

int login() {
    char user[20], pass[20];

    printf("===== LOGIN SYSTEM =====\n");
    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(user, "saai") == 0 && strcmp(pass, "1234") == 0) {
        printf("\nLogin Successful!\n\n");
        return 1;
    } else {
        printf("\nAccess Denied!\n");
        return 0;
    }
}


// Function declarations
void checkBalance(float balance);
float deposit(float balance);
float withdraw(float balance);
void atmMenu(float balance);

int main() {
    int pin, enteredPin;
    int attempts = 3;
    float balance = 5000;
    
      if (!login()) {
        return 0;   // stop program if wrong login
    }
  

    pin = 1212;   // Default ATM PIN

    printf("===== WELCOME TO ATM =====\n");

    while (attempts > 0) {
        printf("Enter your PIN: ");
        scanf("%d", &enteredPin);

        if (enteredPin == pin) {
            printf("PIN Verified Successfully!\n");
            atmMenu(balance);
            return 0;
        } else {
            attempts--;
            printf("Wrong PIN! Attempts left: %d\n", attempts);
        }
    }

    printf("ATM Blocked! Too many wrong attempts.\n");
    return 0;
}

// ATM Menu Function
void atmMenu(float balance) {
    int choice;

    do {
        printf("\n--- ATM MENU ---\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                checkBalance(balance);
                break;

            case 2:
                balance = deposit(balance);
                break;

            case 3:
                balance = withdraw(balance);
                break;

            case 4:
                printf("Thank you for using ATM.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 4);
}

// Check Balance
void checkBalance(float balance) {
    printf("Current Balance: %.2f\n", balance);
}

// Deposit Money
float deposit(float balance) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {
        balance += amount;
        printf("Deposit Successful.\n");
    } else {
        printf("Invalid Amount.\n");
    }
    return balance;
}

// Withdraw Money
float withdraw(float balance) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= balance) {
        balance -= amount;
        printf("Please collect your cash.\n");
    } else {
        printf("Insufficient Balance or Invalid Amount.\n");
    }
    return balance;
}
