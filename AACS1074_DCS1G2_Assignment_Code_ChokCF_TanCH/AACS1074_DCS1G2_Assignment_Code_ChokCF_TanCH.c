#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

//Define Constant
#define SEM_PER_YEAR 3                       // Constant for Semester in a year
#define COURSE_PER_SEM 2                     // Assuming Course per Semester is 2
#define MAX_COURSE_CODE_LENGTH 9             // Maximum CourseCode Length 8 for example : AAA1003  , +1 to terminating null character
#define MAX_STUDENT_ID_LENGTH 10             // Maximum Student ID Length 9 for example : KPKL12345 , +1 to terminating null character
#define MAX_STUDENT_NAME_LENGTH 51           // Constant for Student Name storing 50char,+1 to terminating null character
#define MAX_STUDENTS 5000                    // Maximumm Students loop per data entry 
#define MAX_GRADE_LENGTH 3                   // Constant for Maximum Grade Length for example : A-,+1 for terminating null character 

//Global Variables 

typedef struct {                             // A structure name Student to increase code redability for each Variables
    char studentID[MAX_STUDENT_ID_LENGTH];
    char studentName[MAX_STUDENT_NAME_LENGTH];
    char courseCode[SEM_PER_YEAR][COURSE_PER_SEM][MAX_COURSE_CODE_LENGTH + 1];  //  3D arrays to store Courecode according SEMESTER in year,number of Course per SEMSTER,MAXIMUM CODE LENGTH
    char grade[SEM_PER_YEAR][COURSE_PER_SEM][MAX_GRADE_LENGTH];                 //  3D arrays to store Grade according SEMESTER in year,number of Course per SEMSTER, grade length
    int creditHours[SEM_PER_YEAR][COURSE_PER_SEM];                              //  2D arrays to store CreditHours according SEMESTER in year,number of Course per SEMSTER, 
    float qualityPoints[SEM_PER_YEAR][COURSE_PER_SEM];                          //  2D arrays to store QualityPoints according SEMESTER in year,number of Course per SEMSTER
    float gpa[SEM_PER_YEAR];                                                    //  An Arrays to store GPA accoring SEMESTER
    float cgpa;
} Student;

Student students[MAX_STUDENTS];                                                 // An Arrays to store mutiple Students
int studentCount = 0;                                                           // Student Count from 0 everytime runs program for Array used

//Functions declarations 
int mainMenu();
void gradeMenu();
float gradeValue(const char* grade);
void addStudentDetails();
void courseDetails();
void calculateGPA();
void calculateCGPA();
void displayGrades();
void saveStudentDataToFile();
int backMenu();

void studentMode();
void displayStudentData(const char* studentID);

//Main function 
int main() {

    //Variables declaration

    int choice;

    //Welcome Screen 
    puts("\t\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts("\t\t+                                   Welcome                                   +");
    puts("\t\t+                                     to                                      +");
    puts("\t\t+                                Kolej Pasar                                  +");
    puts("\t\t+-----------------------------------------------------------------------------+");
    puts("\t\t+                                    RULES                                    +");
    puts("\t\t+                         Follow the on screen prompts.                       +");
    puts("\t\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts("\n");

    while (1) {  //Looping Main Function until User enter [3] to exit  
        choice = mainMenu();
        if (choice == 1) {  // Enter to admin mode
            system("cls");  // Screen Clearing 
            puts("\n\t\t+---------------------------------------------+");
            puts("\t\t+          [1] Adminstration Mode!            +");
            puts("\t\t+---------------------------------------------+");
            addStudentDetails(students);
            courseDetails(students);
            calculateGPA(students);
            calculateCGPA(students);
            displayGrades(students);
        }
        else if (choice == 2) { //Enter to student mode 
            system("cls");
            puts("\t\t+---------------------------------------------+");
            puts("\t\t+             [2] Student Mode!               +");
            puts("\t\t+---------------------------------------------+");
            studentMode();
        }
        else if (choice == 3) { //Exit Program
            system("cls");
            puts("\n\n\t\t+---------------------------------------------+");
            puts("\t\t+        [3] Exit Successfully!               +");
            puts("\t\t+---------------------------------------------+\n\n");
            exit(0);
        }
        else {
            printf("\n");
            printf("Invalid,please enter only(1-3)\n");
        }
    }
}

// Menu function to let user choose Mode or exit  
int mainMenu() {
    int choice;
    printf("[1] Administration mode\n");
    printf("[2] Student mode\n");
    printf("[3] Exit : ");
    scanf("%d", &choice);
    rewind(stdin);
    return choice;
}
//Function to prompt user back to Menu Loop or Exit
int backMenu() {
    int choice2;
    do {
        puts("+\t[D] Do you want to continue?\t\t\t+");
        printf("\n[1] Back to Menu\n");
        printf("[2] Exit : ");
        scanf("%d", &choice2);
        rewind(stdin);
        if (choice2 == 1) { // Back to menu 
            system("cls");  // Screen clearing 
            puts("\t\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            puts("\t\t+                                   Welcome                                   +");
            puts("\t\t+                                     to                                      +");
            puts("\t\t+                                Kolej Pasar                                  +");
            puts("\t\t+-----------------------------------------------------------------------------+");
            puts("\t\t+                                    RULES                                    +");
            puts("\t\t+                         Follow the on screen prompts.                       +");
            puts("\t\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            puts("\n");
        }
        else if (choice2 == 2) { // Choice to Exit Program 
            system("cls");
            puts("\n\n\t\t+---------------------------------------------+");
            puts("\t\t+        [3] Exit Successfully!               +");
            puts("\t\t+---------------------------------------------+\n\n");
            exit(0);
        }
        else {
            printf("\n");
            printf("Invalid,please enter only(1-2)\n\n");
        }
    } while (choice2 != 1 && choice2 != 2);  //Loop while user input error 
}

//Function for Adminstration enter student details 
void addStudentDetails() {

    puts("\n");
    printf("+\t[A] Enter Student Details\t+\n");
    printf("\nEnter Student ID (e.g., KPKL12345): ");
    scanf("%9[^\n]", students[studentCount].studentID);
    rewind(stdin);     // Clear input buffer

    printf("Enter Student Name: ");
    scanf("%50[^\n]", students[studentCount].studentName);
    rewind(stdin);     // Clear input buffer
    studentCount++;    // Student Data +1 for each Adminstration Mode runs once 
}
//Function to show Grade Menu 
void gradeMenu() {
    puts("\n");
    puts("+\t[C] Grade (Gradepoints)\t\t\t+");
    puts("+-----------------------------------------------+");
    printf("+\tA\t(4.00)\t\tA-\t(3.75)  +\n");
    printf("+\tB+\t(3.50)\t\tB\t(3.00)  +\n");
    printf("+\tB-\t(2.75)\t\tC+\t(2.50)  +\n");
    printf("+\tC\t(2.00)\t\tF\t(0.00)  +\n");
    puts("+-----------------------------------------------+");
}
// Function to store Course Details
void courseDetails() {
    puts("\n");
    // Loop through semesters and courses to enter course details
    for (int j = 0; j < SEM_PER_YEAR; j++) {
        printf("+\t[B] Entering Course Details(Semester %d)\t+\n", j + 1);
        for (int i = 0; i < COURSE_PER_SEM; i++) {
            printf("\nCourse %d:\n", i + 1);
            printf("Enter Course Code:");
            scanf("%s", students[studentCount - 1].courseCode[j][i]);

            int creditHours;  // A temporary variables to check whether input is correct 
            do {
                printf("Enter Credit Hours (1-4): ");
                if (scanf("%d", &creditHours) != 1 || creditHours < 1 || creditHours > 4) {
                    printf("\nInvalid input. Please enter a number between 1 and 4.\n\n");
                    rewind(stdin); // Clear the input buffer
                }
                else {
                    students[studentCount - 1].creditHours[j][i] = creditHours;
                    break; // Exit the loop if input is valid
                }
            } while (1); // Repeat until valid input is received

            gradeMenu();

            char grade[3];    // A temporary variables to check whether input is correct 
            do {
                printf("Enter Grade (A, A-, B+, B, B-, C+, C, F): ");
                scanf("%2s", grade);
                // Remove any newline characters from previous input
                scanf("%*[^\n]");
                scanf("%*c"); // Consume the newline
                if (gradeValue(grade) == -1) {
                    printf("\nInvalid grade. Please enter a valid grade.\n\n");
                }
                else {
                    strcpy(students[studentCount - 1].grade[j][i], grade); //String copy (strcpy) to Grade in Structure Student
                    break; // Exit the loop if input is valid
                }
            } while (1); // Repeat until valid input is received
        }
        system("cls");
    }
}
//Function to convert Grade entered into gradepoints
//String Comparing (strcmp) to check whether enter a valid Grade then convert to gradepoints 
float gradeValue(const char* grade) {
    if (strcmp(grade, "A") == 0) {
        return 4.00;
    }
    else if (strcmp(grade, "A-") == 0) {
        return 3.75;
    }
    else if (strcmp(grade, "B+") == 0) {
        return 3.50;
    }
    else if (strcmp(grade, "B") == 0) {
        return 3.00;
    }
    else if (strcmp(grade, "B-") == 0) {
        return 2.75;
    }
    else if (strcmp(grade, "C+") == 0) {
        return 2.50;
    }
    else if (strcmp(grade, "C") == 0) {
        return 2.00;
    }
    else if (strcmp(grade, "F") == 0) {
        return 0.00;
    }
    else {
        return -1;
    }
}
// Function to Calculate GPA per SEMESTER
void calculateGPA() {

    //Temporaly Variables to calculate GPA 
    float qualityPoints[SEM_PER_YEAR];
    int creditHours[SEM_PER_YEAR];

    // Loop through semesters and courses to calculate GPA
    for (int j = 0; j < SEM_PER_YEAR; j++) {
        qualityPoints[j] = 0.0;
        creditHours[j] = 0;
    }
    for (int j = 0; j < SEM_PER_YEAR; j++) {
        for (int i = 0; i < COURSE_PER_SEM; i++) {
            qualityPoints[j] += gradeValue(students[studentCount - 1].grade[j][i]) * students[studentCount - 1].creditHours[j][i];
            creditHours[j] += students[studentCount - 1].creditHours[j][i];
        }
        students[studentCount - 1].gpa[j] = qualityPoints[j] / creditHours[j];
    }
}
//Function to Calculate CGPA 
void calculateCGPA() {
    //Temporaly Variables to calculate CGPA 
    float totalQualityPoints = 0;
    int totalCreditHours = 0;

    // Loop through semesters and courses to calculate CGPA
    for (int j = 0; j < SEM_PER_YEAR; j++) {
        for (int i = 0; i < COURSE_PER_SEM; i++) {
            float gradePoints = gradeValue(students[studentCount - 1].grade[j][i]);
            if (gradePoints >= 0) {
                totalQualityPoints += gradeValue(students[studentCount - 1].grade[j][i]) * students[studentCount - 1].creditHours[j][i];
                totalCreditHours += students[studentCount - 1].creditHours[j][i];
            }
        }
    }
    students[studentCount - 1].cgpa = totalQualityPoints / totalCreditHours;
}
//Function to display Student's Grade in Adminstration Mode after entered all the Student Data 
void displayGrades() {
    printf("\nStudent ID: %-10s\n", students[studentCount - 1].studentID);
    printf("Student Name: %-50s\n\n", students[studentCount - 1].studentName);
    for (int j = 0; j < SEM_PER_YEAR; j++) {
        printf("<Semester %d>\t<GPA : %.2f>\nCoursecode\tCredit Hours\tGrade\n", j + 1, students[studentCount - 1].gpa[j]);
        puts("------------------------------------------------");
        for (int i = 0; i < COURSE_PER_SEM; i++) {
            printf("%s\t\t%d\t\t%s\t\t\n", students[studentCount - 1].courseCode[j][i], students[studentCount - 1].creditHours[j][i], students[studentCount - 1].grade[j][i]);
        }
        puts("------------------------------------------------");
    }
    printf("CGPA: %.2f\n\n", students[studentCount - 1].cgpa);
    saveStudentDataToFile(students);   //Function to Save Student Data into txt.file 
    backMenu();                        //Function to ask user back to Menu or exit
}
//Extra Feature
// Function to add Student Data into a txt.file
void saveStudentDataToFile() {

    //Variable for file storing according Student ID   
    char filename[MAX_STUDENT_ID_LENGTH + 5]; // +5 for ".txt"

    sprintf(filename, "%s.txt", students[studentCount - 1].studentID);  //Create txt.file according to Student ID
    FILE* file = fopen(filename, "w");  // 'W' write date into file 
    if (file == NULL) {     //Fail to create if Student Data is empty 
        printf("Failed to create file for student %s.\n", students[studentCount - 1].studentID);
        return;
    }

    fprintf(file, "Student ID: %-10s\n", students[studentCount - 1].studentID);
    fprintf(file, "Student Name: %-50s\n\n", students[studentCount - 1].studentName);

    // Loop through semesters and courses to save the data
    for (int j = 0; j < SEM_PER_YEAR; j++) {
        fprintf(file, "<Semester %d>\t<GPA : %.2f>\nCoursecode\tCredit Hours\tGrade\n", j + 1, students[studentCount - 1].gpa[j]);
        fprintf(file, "------------------------------------------------\n");
        for (int i = 0; i < COURSE_PER_SEM; i++) {
            fprintf(file, "%s\t\t%d\t\t%s\n", students[studentCount - 1].courseCode[j][i], students[studentCount - 1].creditHours[j][i], students[studentCount - 1].grade[j][i]);
        }
        fprintf(file, "------------------------------------------------\n");
    }

    fprintf(file, "CGPA: %.2f\n\n", students[studentCount - 1].cgpa);

    fclose(file);
}
//Function for Student Mode
void studentMode() {
    // Temporary Variable to check Student ID input 
    char studentIDInput[MAX_STUDENT_ID_LENGTH];
    printf("Enter Student ID: ");
    scanf("%s", studentIDInput);

    printf("\n");

    displayStudentData(studentIDInput);  // Function to display Student Data if Student ID exist procced to display Student Data
    backMenu();                          // Function to ask use go back to menu or quit 

}

//Extra feature 
// Function to display student data from a file
void displayStudentData(const char* studentID) {

    //Variable for opening file according to studentID input 
    char filename[MAX_STUDENT_ID_LENGTH + 5]; // +5 for ".txt"
    sprintf(filename, "%s.txt", studentID);
    FILE* file = fopen(filename, "r");  // Read data from File

    system("cls");  // Screen Clearing to show Student Data 
    printf("+\tLogin Successfully !!\t+\n\n");

    if (file != NULL) {     // If file exist show student data line by line 
        char studentData[100];
        while (fgets(studentData, sizeof(studentData), file)) {
            printf("%s", studentData);
        }

        fclose(file);
    }
    else {                      // Student ID doesnt exist 
        system("cls");
        printf("Student data not found. Please check the Student ID.\n");
        printf("\n");
    }
}



