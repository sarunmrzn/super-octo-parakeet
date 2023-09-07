#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "doctor.h"
#include "patient.h"
#define MAX_USERS 100

struct user
{
    char username[20];
    char password[20];
};

int readUserCredentials(struct user users[], const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening user credentials file.\n");
        return 0;
    }

    int count = 0;

    while (fscanf(file, "%s %s", users[count].username, users[count].password) == 2)
    {
        count++;
    }

    fclose(file);
    return count;
}

int authenticateUser(struct user users[], int numUsers, const char *username, const char *password)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    printHospitalInfo();

    system("clear");
    printf("Kirtipur Hospital Management System\n");

    struct user users[MAX_USERS];
    int numUsers = readUserCredentials(users, "user_credentials.txt");

    if (numUsers == 0)
    {
        return 1;
    }

    char username[20];
    char password[20];
    int authenticated = 0;

    do
    {
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);

        authenticated = authenticateUser(users, numUsers, username, password);

        if (!authenticated)
        {
            printf("Authentication failed. Please try again.\n");
        }
    } while (!authenticated);

    printf("Authentication successful. Access granted.\n");

    int choice;
    do
    {
        system("clear");
        printf("Kirtipur Hospital Management System\n");
        printf("\n1. Add Record\n");
        printf("2. List Records\n");
        printf("3. Modify Record\n");
        printf("4. Delete Record\n");
        printf("5. Search Record\n");
        printf("0. Exit\n");
        printf("Please Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Ask the user whether to add a doctor or patient
            system("clear");
            printf("1. Add Doctor\n");
            printf("2. Add Patient\n");
            printf("Please Enter Your Choice: ");
            fflush(stdin);
            char docOrPatientChoice = getchar();

            if (docOrPatientChoice == '1')
            {
                createDoctorRecord();
            }
            else if (docOrPatientChoice == '2')
            {
                createPatientRecord();
            }
            else
            {
                printf("\nInvalid choice. Please try again.\n");
                waitForUserInput();
            }
            break;
        case 2:
            system("clear");
            printf("1. List Doctors\n");
            printf("2. List Patients\n");
            printf("Please Enter Your Choice: ");
            fflush(stdin);
            char listChoice = getchar();

            if (listChoice == '1')
            {
                readDoctorRecords();
            }
            else if (listChoice == '2')
            {
                readPatientRecords();
            }
            else
            {
                printf("\nInvalid choice. Please try again.\n");
                waitForUserInput();
            }
            break;
        case 3:
            system("clear");
            printf("1. Modify Doctor\n");
            printf("2. Modify Patient\n");
            printf("Please Enter Your Choice: ");
            fflush(stdin);
            char modifyChoice = getchar();

            if (modifyChoice == '1')
            {
                modifyDoctorRecord();
            }
            else if (modifyChoice == '2')
            {
                modifyPatientRecord();
            }
            else
            {
                printf("\nInvalid choice. Please try again.\n");
                waitForUserInput();
            }
            break;
        case 4:
            system("clear");
            printf("1. Delete Doctor\n");
            printf("2. Delete Patient\n");
            printf("Please Enter Your Choice: ");
            fflush(stdin);
            char deleteChoice = getchar();

            if (deleteChoice == '1')
            {
                deleteDoctorRecord();
            }
            else if (deleteChoice == '2')
            {
                deletePatientRecord();
            }
            else
            {
                printf("\nInvalid choice. Please try again.\n");
                waitForUserInput();
            }
            break;
        case 5:
            system("clear");
            printf("1. Search Doctor\n");
            printf("2. Search Patient\n");
            printf("Please Enter Your Choice: ");
            fflush(stdin);
            char searchChoice = getchar();

            if (searchChoice == '1')
            {
                searchDoctorRecord();
            }
            else if (searchChoice == '2')
            {
                searchPatientRecord();
            }
            else
            {
                printf("\nInvalid choice. Please try again.\n");
                waitForUserInput();
            }
            break;
        case 0:
            printf("\nThank you for using the Kirtipur Hospital Management System!\n");
            exit(0);
        default:
            printf("\nInvalid choice. Please try again.\n");
            waitForUserInput();
            break;
        }
    } while (choice != 0);

    return 0;
}