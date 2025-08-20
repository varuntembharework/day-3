#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define FILE_NAME "records.txt"

// Function to calculate grade
char calculateGrade(float avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 75) return 'B';
    else if (avg >= 50) return 'C';
    else return 'F';
}

// Function to add a student record
void addRecord() {
    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    char name[MAX_NAME];
    int subjects;
    printf("Enter student name: ");
    scanf(" %[^\n]", name);

    printf("Enter number of subjects: ");
    scanf("%d", &subjects);

    if (subjects <= 0) {
        printf("Invalid number of subjects!\n");
        fclose(fp);
        return;
    }

    int marks[subjects];
    int sum = 0;
    for (int i = 0; i < subjects; i++) {
        do {
            printf("Enter marks for subject %d (0-100): ", i + 1);
            scanf("%d", &marks[i]);
        } while (marks[i] < 0 || marks[i] > 100);
        sum += marks[i];
    }

    float avg = (float) sum / subjects;
    char grade = calculateGrade(avg);

    // Write to file
    fprintf(fp, "Name: %s\n", name);
    fprintf(fp, "Subjects: %d\n", subjects);
    fprintf(fp, "Marks: ");
    for (int i = 0; i < subjects; i++) {
        fprintf(fp, "%d", marks[i]);
        if (i != subjects - 1) fprintf(fp, ", ");
    }
    fprintf(fp, "\nAverage: %.2f\n", avg);
    fprintf(fp, "Grade: %c\n", grade);
    fprintf(fp, "------------------------\n");

    fclose(fp);

    printf("\n✅ Record Added:\n");
    printf("Name: %s\nAverage: %.2f\nGrade: %c\n", name, avg, grade);
}

// Function to view all records
void viewRecords() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}

// Function to search for a student
void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    char searchName[MAX_NAME];
    char line[200];
    int found = 0;

    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Name:", 5) == 0) {
            char nameInFile[MAX_NAME];
            sscanf(line, "Name: %[^\n]", nameInFile);

            if (strcmp(nameInFile, searchName) == 0) {
                found = 1;
                printf("\nRecord Found:\n");
                printf("%s", line); // print name line
                // print next few lines until separator
                while (fgets(line, sizeof(line), fp) && strncmp(line, "----------------", 16) != 0) {
                    printf("%s", line);
                }
                break;
            }
        }
    }

    if (!found) {
        printf("\n❌ No record found for '%s'\n", searchName);
    }

    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Student Grade Manager ---\n");
        printf("1. Add new student record\n");
        printf("2. View all records\n");
        printf("3. Search for a student\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: searchStudent(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}