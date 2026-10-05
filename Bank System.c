#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[50];
    float balance;
};

void createAccount() {
    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Account acc;
    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accountNumber);
    printf("Enter Name: ");
    scanf(" %[^\n]s", acc.name);
    printf("Enter Initial Deposit Amount: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(struct Account), 1, file);
    fclose(file);

    printf("Account created successfully.\n");
}

void depositMoney() {
    FILE *file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }

    int accNo;
    float amount;
    int found = 0;
    struct Account acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNo) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Invalid deposit amount.\n");
                fclose(file);
                return;
            }

            acc.balance += amount;
            fseek(file, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, file);

            printf("Deposit successful. Updated Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }

    fclose(file);
}

void withdrawMoney() {
    FILE *file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }

    int accNo;
    float amount;
    int found = 0;
    struct Account acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNo) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Invalid amount.\n");
            } else if (amount > acc.balance) {
                printf("Insufficient balance. Current Balance: %.2f\n", acc.balance);
            } else {
                acc.balance -= amount;
                fseek(file, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, file);
                printf("Withdrawal successful. Remaining Balance: %.2f\n", acc.balance);
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }

    fclose(file);
}

void balanceEnquiry() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }

    int accNo;
    int found = 0;
    struct Account acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNo) {
            printf("\n--- Account Details ---\n");
            printf("Account Number: %d\n", acc.accountNumber);
            printf("Account Holder: %s\n", acc.name);
            printf("Current Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }

    fclose(file);
}

int main() {
    int choice;

    while (1) {
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                balanceEnquiry();
                break;
            case 5:
                printf("Exiting system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}