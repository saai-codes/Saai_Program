#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

/*
OWNER / CEO

Username: admin

Password: admin@123

EMPLOYEE

Username: employee

Password: emp@123
*/


/* ---------- STRUCT ---------- */
struct Employee {
    int id;
    char name[50];
    float salary;
    int exp, perf, att;
    float net;
};

/* ---------- COLOR ---------- */
void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/* ---------- SALARY LOGIC ---------- */
float calculate(struct Employee e) {
    float inc = 0, bonus = 0, tax = 0;

    if (e.salary < 20000) inc = e.salary * 0.20;
    else if (e.salary <= 50000) inc = e.salary * 0.10;

    if (e.exp >= 5) bonus += 3000;
    if (e.perf >= 8) bonus += 5000;
    if (e.att >= 90) bonus += 2000;

    if (e.salary > 50000) tax = e.salary * 0.10;
    else tax = e.salary * 0.05;

    return e.salary + inc + bonus - tax;
}

/* ---------- ADD EMPLOYEE ---------- */
void addEmployee() {
    FILE *fp = fopen("employee.dat", "ab");
    struct Employee e;

    system("cls");
    color(11);
    printf("=====================================\n");
    printf("        ADD EMPLOYEE (OWNER)\n");
    printf("=====================================\n");
    color(15);

    printf("Enter Employee ID      : ");
    scanf("%d", &e.id);
    fflush(stdin);   // clear input buffer (Windows)

    printf("Enter Employee Name    : ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0'; // remove newline

    printf("Enter Base Salary      : ");
    scanf("%f", &e.salary);

    printf("Experience (Years)    : ");
    scanf("%d", &e.exp);

    printf("Performance (1-10)    : ");
    scanf("%d", &e.perf);

    printf("Attendance Percentage : ");
    scanf("%d", &e.att);

    e.net = calculate(e);
    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    color(10);
    printf("\n✔ Employee Added Successfully!");
    Sleep(2000);
}


/* ---------- VIEW ALL ---------- */
void viewAll() {
    FILE *fp = fopen("employee.dat", "rb");
    struct Employee e;

    system("cls");
    color(14);
    printf("=====================================\n");
    printf("        EMPLOYEE RECORDS\n");
    printf("=====================================\n");
    color(15);

    while (fread(&e, sizeof(e), 1, fp)) {
        printf("ID:%d  Name:%s  Base:%.2f  Net:%.2f\n",
               e.id, e.name, e.salary, e.net);
    }

    fclose(fp);
    getch();
}

/* ---------- EMPLOYEE VIEW ---------- */
void employeeView() {
    FILE *fp = fopen("employee.dat", "rb");
    struct Employee e;
    int id, found = 0;

    system("cls");
    color(11);
    printf("Enter Your Employee ID: ");
    color(15);
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id == id) {
            found = 1;
            system("cls");
            color(10);
            printf("=====================================\n");
            printf("        SALARY DETAILS\n");
            printf("=====================================\n");
            color(15);
            printf("Name       : %s\n", e.name);
            printf("Base Salary: %.2f\n", e.salary);
            printf("Net Salary : %.2f\n", e.net);
            break;
        }
    }

    fclose(fp);
    if (!found) {
        color(12);
        printf("\nRecord Not Found!");
    }
    getch();
}

/* ---------- OWNER PANEL ---------- */
void ownerPanel() {
    int ch;
    do {
        system("cls");
        color(9);
        printf("=====================================\n");
        printf("            OWNER PANEL\n");
        printf("=====================================\n");
        color(15);
        printf("1. Add Employee\n");
        printf("2. View All Employees\n");
        printf("3. Logout\n");
        printf("Choice: ");
        scanf("%d", &ch);

        if (ch == 1) addEmployee();
        else if (ch == 2) viewAll();

    } while (ch != 3);
}

/* ---------- LOGIN ---------- */
void login() {
    char u[20], p[20];
    int choice;

    system("cls");
    color(14);
    printf("=====================================\n");
    printf("      EMPLOYEE MANAGEMENT SYSTEM\n");
    printf("=====================================\n");
    color(15);

    printf("1. Owner Login\n");
    printf("2. Employee Login\n");
    printf("Choice: ");
    scanf("%d", &choice);

    printf("Username: ");
    scanf("%s", u);
    printf("Password: ");
    scanf("%s", p);

    if (choice == 1 && strcmp(u,"admin")==0 && strcmp(p,"admin@123")==0) {
        ownerPanel();
    }
    else if (choice == 2 && strcmp(u,"employee")==0 && strcmp(p,"emp@123")==0) {
        employeeView();
    }
    else {
        color(12);
        printf("\nInvalid Login!");
        Sleep(2000);
    }
}

/* ---------- MAIN ---------- */
int main() {
    while (1)
        login();
    return 0;
}
