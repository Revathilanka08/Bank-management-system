#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "bankdata.txt"

struct account {
    int acc_no;
    char name[50];
    float balance;
};

void create_account();
void view_accounts();
void deposit_money();
void withdraw_money();
void check_balance();
void delete_account();
void menu();

int main() {
    int choice;

    while (1) {
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_account(); break;
            case 2: view_accounts(); break;
            case 3: deposit_money(); break;
            case 4: withdraw_money(); break;
            case 5: check_balance(); break;
            case 6: delete_account(); break;
            case 7: 
                printf("Exiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void menu() {
    printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
    printf("1. Create New Account\n");
    printf("2. View All Accounts\n");
    printf("3. Deposit Money\n");
    printf("4. Withdraw Money\n");
    printf("5. Check Balance\n");
    printf("6. Delete Account\n");
    printf("7. Exit\n");
}

void create_account() {
    struct account acc;
    FILE *fp = fopen(FILENAME, "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fprintf(fp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    fclose(fp);
    printf("Account created successfully!\n");
}

void view_accounts() {
    struct account acc;
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("No data found!\n");
        return;
    }

    printf("\n%-10s %-20s %-10s\n", "Acc No", "Name", "Balance");
    printf("-------------------------------------------\n");

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        printf("%-10d %-20s %-10.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
}

void deposit_money() {
    int acc_no, found = 0;
    float amount;
    struct account acc;
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            acc.balance += amount;
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Amount deposited successfully!\n");
    else
        printf("Account not found!\n");
}

void withdraw_money() {
    int acc_no, found = 0;
    float amount;
    struct account acc;
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                found = 1;
            } else {
                printf("Insufficient balance!\n");
                fprintf(temp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
                continue;
            }
        }
        fprintf(temp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Amount withdrawn successfully!\n");
    else
        printf("Account not found or insufficient balance!\n");
}

void check_balance() {
    int acc_no, found = 0;
    struct account acc;
    FILE *fp = fopen(FILENAME, "r");

    if (!fp) {
        printf("No data found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc_no);

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            printf("Account Holder: %s\nBalance: %.2f\n", acc.name, acc.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found!\n");

    fclose(fp);
}

void delete_account() {
    int acc_no, found = 0;
    struct account acc;
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number to Delete: ");
    scanf("%d", &acc_no);

    while (fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        if (acc.acc_no != acc_no)
            fprintf(temp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Account deleted successfully!\n");
    else
        printf("Account not found!\n");
}

