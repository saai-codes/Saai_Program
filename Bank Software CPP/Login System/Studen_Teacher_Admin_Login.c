#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX 50

/* ---------- STRUCT ---------- */
struct Student {
    int id;
    char name[50];
    char username[30];
    char password[30];
};

struct Student students[MAX];
int studentCount = 0;

/* ---------- DESIGN FUNCTIONS ---------- */
void clearScreen() {
    system("cls");
}

void setColor(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void header(char title[]) {
    setColor(11);
    printf("\n============================================\n");
    printf("   %s\n", title);
    printf("============================================\n\n");
    setColor(7);
}

void pause() {
    printf("\nPress any key to continue...");
    getch();
}

/* ---------- ADMIN / TEACHER FUNCTIONS ---------- */
void enrollStudent() {
    clearScreen();
    header("ENROLL STUDENT");

    printf("Student ID        : ");
    scanf("%d", &students[studentCount].id);
    getchar();

    printf("Student Full Name : ");
    gets(students[studentCount].name);

    printf("Create Username   : ");
    gets(students[studentCount].username);

    printf("Create Password   : ");
    gets(students[studentCount].password);

    studentCount++;

    setColor(10);
    printf("\nStudent enrolled successfully!");
    setColor(7);
    pause();
}

void viewStudents() {
    clearScreen();
    header("ENROLLED STUDENTS");

    if (studentCount == 0) {
        printf("No students enrolled yet.\n");
    } else {
        for (int i = 0; i < studentCount; i++) {
            printf("%d) ID: %d | Name: %s | Username: %s\n",
                   i + 1,
                   students[i].id,
                   students[i].name,
                   students[i].username);
        }
    }
    pause();
}

void removeStudent() {
    int id, found = -1;
    clearScreen();
    header("REMOVE STUDENT");

    printf("Enter Student ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nStudent not found!");
    } else {
        for (int i = found; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        setColor(10);
        printf("\nStudent removed successfully!");
        setColor(7);
    }
    pause();
}

/* ---------- STUDENT ---------- */
void studentSubjects() {
    int ch;
    do {
        clearScreen();
        header("STUDENT DASHBOARD");

        printf("1. PIC (Programming in C)\n");
        printf("2. Mathematics\n");
        printf("3. Web Page Designing\n");
        printf("4. Basic Linux\n");
        printf("5. Logout\n\n");

        printf("Choose subject: ");
        scanf("%d", &ch);
        getchar();

        clearScreen();
        switch (ch) {
        case 1:
            header("PIC - Programming in C");
            printf("Topics:\n");
            printf("- Data Types\n- Loops\n- Functions\n- Structures\n");
            break;

        case 2:
            header("Mathematics");
            printf("Topics:\n");
            printf("- Differential Equations\n- Integration\n- Matrices\n");
            break;

        case 3:
            header("Web Page Designing");
            printf("Topics:\n");
            printf("- HTML\n- CSS\n- Basics of JavaScript\n");
            break;

        case 4:
            header("Basic Linux");
            printf("Topics:\n");
            printf("- ls, cd, mkdir\n- File permissions\n");
            break;
        }
        if (ch != 5)
            pause();

    } while (ch != 5);
}


void studentLogin() {
    char u[30], p[30];
    int success = 0;

    clearScreen();
    header("STUDENT LOGIN");

    printf("Username : ");
    gets(u);
    printf("Password : ");
    gets(p);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(u, students[i].username) == 0 &&
            strcmp(p, students[i].password) == 0) {
            success = 1;
            break;
        }
    }

    if (success) {
        setColor(10);
        printf("\nLogin successful!");
        setColor(7);
        pause();
        studentSubjects();
    } else {
        setColor(12);
        printf("\nInvalid login!");
        setColor(7);
        pause();
    }
}

/* ---------- ADMIN / TEACHER MENU ---------- */
void adminTeacherMenu(char role[]) {
    int ch;
    do {
        clearScreen();
        header(role);

        printf("1. Enroll Student\n");
        printf("2. Remove Student\n");
        printf("3. View Enrolled Students\n");
        printf("4. Logout\n\n");
        printf("Choose option: ");
        scanf("%d", &ch);
        getchar();

        switch (ch) {
        case 1: enrollStudent(); break;
        case 2: removeStudent(); break;
        case 3: viewStudents(); break;
        }
    } while (ch != 4);
}

/* ---------- LOGIN ---------- */
int login(char correctUser[], char correctPass[]) {
    char u[30], p[30];

    printf("Username : ");
    gets(u);
    printf("Password : ");
    gets(p);

    if (strcmp(u, correctUser) == 0 && strcmp(p, correctPass) == 0)
        return 1;
    else
        return 0;
}

/* ---------- MAIN ---------- */
int main() {
    int choice;

    do {
        clearScreen();
        header("COLLEGE LEARNING MANAGEMENT SYSTEM");

        printf("1. Student Login\n");
        printf("2. Teacher Login\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n\n");
        printf("Choose your option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            studentLogin();
            break;

        case 2:
            clearScreen();
            header("TEACHER LOGIN");
            if (login("teacher", "teach123"))
                adminTeacherMenu("TEACHER PANEL");
            else {
                printf("\nInvalid login!");
                pause();
            }
            break;

        case 3:
            clearScreen();
            header("ADMIN LOGIN");
            if (login("admin", "admin123"))
                adminTeacherMenu("ADMIN PANEL");
            else {
                printf("\nInvalid login!");
                pause();
            }
            break;
        }
    } while (choice != 4);

    return 0;
}
