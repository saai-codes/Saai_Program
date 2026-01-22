#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

/* ---------- STRUCTURE ---------- */
struct Student {
    int roll;
    char name[50];
    int age;
    char className[10];
    char address[100];
    char parentMobile[15];
    char email[50];
    float marks;
};

/* ---------- FUNCTION DECLARATIONS ---------- */
void login();
void loading();
void mainMenu();
void studentMenu();

void addStudent();
void displayStudents();
void updateStudent();
void deleteStudent();

/* ---------- MAIN ---------- */
int main() {
    login();
    mainMenu();
    return 0;
}

/* ---------- LOGIN ---------- */

/*is used to clear the console screen.
It executes a Windows command using the system function.
It improves program readability but is OS dependent."
*/

void login() {
    char username[20], password[20];

    system("cls");
    system("color 0A");

    printf("=========== ADMIN LOGIN ===========\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "1234") == 0) {
        printf("\nLogin Successful!\n");
        loading();
    } else {
        printf("\nInvalid Login!\n");
        Sleep(1500);
        login();
    }
}

/* ---------- LOADING ---------- */
void loading() {
    printf("\nLoading");
    for (int i = 0; i < 5; i++) {
        Sleep(400);
        printf(".");
    }
}

/* ---------- MAIN MENU ---------- */
void mainMenu() {
    int choice;

    do {
        system("cls");
        system("color 0B");

        printf("======= STUDENT MANAGEMENT =======\n");
        printf("1. Student Menu\n");
        printf("2. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: studentMenu(); break;
            case 2: exit(0);
            default: printf("Invalid Choice!\n"); Sleep(1000);
        }
    } while (choice != 2);
}

/* ---------- STUDENT MENU ---------- */
void studentMenu() {
    int choice;

    do {
        system("cls");
        system("color 0E");

        printf("=========== STUDENT MENU ===========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Back\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: return;
            default: printf("Invalid Choice!\n"); Sleep(1000);
        }
    } while (choice != 5);
}

/* ---------- ADD STUDENT ---------- */
void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");

    printf("\nRoll Number     : ");
    scanf("%d", &s.roll);

    printf("Name            : ");
    scanf(" %[^\n]", s.name);

    printf("Age             : ");
    scanf("%d", &s.age);

    printf("Class           : ");
    scanf("%s", s.className);

    printf("Address         : ");
    scanf(" %[^\n]", s.address);

    printf("Parent Mobile   : ");
    scanf("%s", s.parentMobile);

    printf("Email ID        : ");
    scanf("%s", s.email);

    printf("Marks           : ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\n✔ Student Added Successfully!\n");
    Sleep(1500);
}

/* ---------- DISPLAY STUDENTS ---------- */
void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No Records Found!\n");
        Sleep(1500);
        return;
    }

    system("cls");
    printf("========= STUDENT RECORDS =========\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll    : %d", s.roll);
        printf("\nName    : %s", s.name);
        printf("\nAge     : %d", s.age);
        printf("\nClass   : %s", s.className);
        printf("\nAddress : %s", s.address);
        printf("\nParent Mobile : %s", s.parentMobile);
        printf("\nEmail   : %s", s.email);
        printf("\nMarks   : %.2f", s.marks);
        printf("\n----------------------------------");
    }

    fclose(fp);
    printf("\nPress any key...");
    getch();
}

/* ---------- UPDATE STUDENT ---------- */
void updateStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb+");
    int roll, found = 0;

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;

            printf("\n1.Name  2.Age  3.Class  4.Address  5.Parent Mobile  6.Email  7.Marks\n");
            printf("Enter Choice: ");

            int ch;
            scanf("%d", &ch);

            switch (ch) {
                case 1: scanf(" %[^\n]", s.name); break;
                case 2: scanf("%d", &s.age); break;
                case 3: scanf("%s", s.className); break;
                case 4: scanf(" %[^\n]", s.address); break;
                case 5: scanf("%s", s.parentMobile); break;
                case 6: scanf("%s", s.email); break;
                case 7: scanf("%f", &s.marks); break;
                default: printf("Invalid!\n");
            }

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("✔ Record Updated!\n");
            break;
        }
    }

    fclose(fp);
    if (!found) printf("Student Not Found!\n");
    Sleep(1500);
}

/* ---------- DELETE STUDENT ---------- */
void deleteStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    int roll, found = 0;
    printf("\nEnter Roll to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll != roll)
            fwrite(&s, sizeof(s), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("✔ Student Deleted!\n");
    else
        printf("Student Not Found!\n");

    Sleep(1500);
}
