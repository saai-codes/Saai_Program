#include <stdio.h>

// Function declarations
void checkBalance(float balance);
float deposit(float balance);
float withdraw(float balance);

int main() {
    int choice;
    float balance = 5000;   // Initial balance

    do {
        printf("\n--- BANK MENU ---\n");
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
                printf("Thank you for using our bank.\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 4);

    return 0;
}

// This function is used to check balance
void checkBalance(float balance) {
    printf("Current Balance: %.2f\n", balance);
}

// This Function is used to deposit money
float deposit(float balance) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {
        balance += amount;
        printf("Amount deposited successfully.\n");
    } else {
        printf("Invalid amount.\n");
    }
    return balance;
}

// This Function is used to withdraw money
float withdraw(float balance) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= balance) {
        balance -= amount;
        printf("Please collect your cash.\n");
    } else {
        printf("Insufficient balance or invalid amount.\n");
    }
    return balance;
}
