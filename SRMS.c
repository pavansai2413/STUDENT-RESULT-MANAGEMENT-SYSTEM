#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STUD_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"
struct Student {
    int roll;
    char name[50];
    float marks;
};
char currentRole[10];
char currentUser[50];
struct Student arr[100];
int count = 0;
char getGrade(float m) {
    if (m >= 90) return 'A';
    if (m >= 80) return 'B';
    if (m >= 70) return 'C';
    if (m >= 60) return 'D';
    if (m >= 50) return 'E';
    return 'FAIL';
}
int loginsystem() {
    char username[50], password[50];
    char fuser[50], fpass[50], frole[10];
    printf("\nLOGIN PORTAL\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);
    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: credentials file missing!\n");
        return 0;
    }
    while (fscanf(fp, "%s %s %s", fuser, fpass, frole) == 3) {
        if (strcmp(username, fuser) == 0 &&
            strcmp(password, fpass) == 0) {

            strcpy(currentUser, fuser);
            strcpy(currentRole, frole);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
void loadStudents() {
    FILE *fp = fopen(STUD_FILE, "r");
    count = 0;
    if (!fp) return;
    while (fscanf(fp, "%d %[^\t] %f", &arr[count].roll, arr[count].name, &arr[count].marks) == 3) {
        count++;
    }
    fclose(fp);
}
void saveStudents() {
    FILE *fp = fopen(STUD_FILE, "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d\t%s\t%.2f\n", arr[i].roll, arr[i].name, arr[i].marks);
    }
    fclose(fp);
}
void add() {
    struct Student s;
    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    FILE *fp = fopen(STUD_FILE, "a");
    fprintf(fp, "%d\t%s\t%.2f\n", s.roll, s.name, s.marks);
    fclose(fp);
    printf("Student Added Successfully!\n");
}
void display() {
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No students found.\n");
        return;
    }
    int roll;
    char name[50];
    float mark;
    printf("\nRoll\tName\tMarks\tGrade\n");
    while (fscanf(fp, "%d %[^\t] %f", &roll, name, &mark) == 3) {
        printf("%d\t%s\t%.2f\t%c\n", roll, name, mark, getGrade(mark));
    }
    fclose(fp);
}
void search() {
    int find;
    printf("Enter Roll to Search: ");
    scanf("%d", &find);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("File missing.\n");
        return;
    }
    int roll;
    char name[50];
    float mark;
    while (fscanf(fp, "%d %[^\t] %f", &roll, name, &mark) == 3) {
        if (roll == find) {
            printf("Found: %d  %s  %.2f  (%c)\n", roll, name, mark, getGrade(mark));
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("Student Not Found!\n");
}
void delete1() {
    int delRoll;
    printf("Enter Roll to Delete: ");
    scanf("%d", &delRoll);
    loadStudents();
    int found = 0;
    FILE *fp = fopen(STUD_FILE, "w");

    for (int i = 0; i < count; i++) {
        if (arr[i].roll != delRoll) {
            fprintf(fp, "%d\t%s\t%.2f\n", arr[i].roll, arr[i].name, arr[i].marks);
        } else {
            found = 1;
        }
    }
    fclose(fp);

    if (found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Roll Not Found!\n");
}
void update() {
    int uRoll;
    printf("Enter Roll to Update: ");
    scanf("%d", &uRoll);
    loadStudents();
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (arr[i].roll == uRoll) {
            found = 1;
            printf("New Name: ");
            scanf(" %[^\n]", arr[i].name);
            printf("New Marks: ");
            scanf("%f", &arr[i].marks);
        }
    }
    saveStudents();
    if (found)
        printf("Student Updated!\n");
    else
        printf("Roll Not Found!\n");
}
void sortByRoll() {
    loadStudents();
    for (int i = 0; i < count; i++)
        for (int j = i + 1; j < count; j++)
            if (arr[i].roll > arr[j].roll) {
                struct Student t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }
    saveStudents();
    display();
}
void sortByName() {
    loadStudents();
    for (int i = 0; i < count; i++)
        for (int j = i + 1; j < count; j++)
            if (strcmp(arr[i].name, arr[j].name) > 0) {
                struct Student t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }

    saveStudents();
    display();
}
void sortByMarks() {
    loadStudents();
    for (int i = 0; i < count; i++)
        for (int j = i + 1; j < count; j++)
            if (arr[i].marks < arr[j].marks) {
                struct Student t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }

    saveStudents();
    display();
}
void sortMenu() {
    int c;
    printf("\n1. Sort by Roll\n2. Sort by Name\n3. Sort by Marks\nChoice: ");
    scanf("%d", &c);
    if (c == 1) sortByRoll();
    else if (c == 2) sortByName();
    else if (c == 3) sortByMarks();
}
void addUser() {
    char u[50], p[50], r[10];
    printf("Username: ");
    scanf("%s", u);
    printf("Password: ");
    scanf("%s", p);
    printf("Role (ADMIN/STAFF/GUEST): ");
    scanf("%s", r);
    FILE *fp = fopen(CREDENTIAL_FILE, "a");
    fprintf(fp, "%s %s %s\n", u, p, r);
    fclose(fp);

    printf("User Added Successfully!\n");
}
void changePassword() {
    char user[50], pass[50], role[10];
    char newPass[50];
    printf("Enter New Password: ");
    scanf("%s", newPass);
    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    while (fscanf(fp, "%s %s %s", user, pass, role) == 3) {
        if (strcmp(user, currentUser) == 0)
            fprintf(temp, "%s %s %s\n", user, newPass, role);
        else
            fprintf(temp, "%s %s %s\n", user, pass, role);
    }
    fclose(fp);
    fclose(temp);
    remove(CREDENTIAL_FILE);
    rename("temp.txt", CREDENTIAL_FILE);
    printf("Password Updated Successfully!\n");
}
void adminmenu() {
    int c;
    while (1) {
        printf("\n--- ADMIN MENU ---\n1.Add\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Sort\n7.Add User\n8.Change Password\n9.Logout\nChoice: ");
        printf("choice:");
        scanf("%d", &c);
        switch (c) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: update(); break;
            case 5: delete1(); break;
            case 6: sortMenu(); break;
            case 7: addUser(); break;
            case 8: changePassword(); break;
            case 9: return;
        }
    }
}
void staff() {
    int c;
    while (1) {
        printf("\n--- STAFF MENU ---\n1.Add\n2.Display\n3.Search\n4.Update\n5.Logout\nChoice: ");
        printf("choice");
        scanf("%d", &c);
        switch (c) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: update(); break;
            case 5: return;
        }
    }
}
void guest() {
    int c;
    while (1) {
        printf("\n--- GUEST MENU ---\n1.Display\n2.Search\n3.Logout\nChoice: ");
        printf("choice:");
		scanf("%d", &c);
        switch (c) {
            case 1: display(); break;
            case 2: search(); break;
            case 3: return;
        }
    }
}
void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0) adminmenu();
    else if (strcmp(currentRole, "STAFF") == 0) staff();
    else guest();
}
int main() {
    if (loginsystem())
        mainMenu();
    else
        printf("\nAccess Denied\n");
    return 0;
}