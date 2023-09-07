#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "utilities.h"

struct doc
{
    char dname[10];
    char dgender[10];
    int dage;
    char dspecial[10];
};

void createDoctorRecord()
{
    FILE *file;
    file = fopen("doctor_records.dat", "ab+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct doc newDoctor;

    printf("Enter doctor's name: ");
    scanf("%s", newDoctor.dname);
    printf("Enter doctor's gender: ");
    scanf("%s", newDoctor.dgender);
    printf("Enter doctor's age: ");
    scanf("%d", &newDoctor.dage);
    printf("Enter doctor's specialization: ");
    scanf("%s", newDoctor.dspecial);

    fwrite(&newDoctor, sizeof(struct doc), 1, file);
    fclose(file);

    printf("Doctor record added successfully!\n");
    waitForUserInput();
}

void doctorTableHeader()
{
    printf("| %-25s | %-12s | %-4s | %-25s |\n", "Doctor's Name", "Gender", "Age", "Specialization");
    printf("|---------------------------|--------------|------|---------------------------|\n");
}

void doctorTableContent(struct doc currentDoctor)
{
    printf("| %-25s | %-12s | %-4d | %-25s |\n", currentDoctor.dname, currentDoctor.dgender, currentDoctor.dage, currentDoctor.dspecial);
}

void readDoctorRecords()
{
    FILE *file;
    file = fopen("doctor_records.dat", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct doc currentDoctor;

    doctorTableHeader();

    while (fread(&currentDoctor, sizeof(struct doc), 1, file) == 1)
    {
        doctorTableContent(currentDoctor);
    }
    fclose(file);
    waitForUserInput();
}

void modifyDoctorRecord()
{
    FILE *file;
    file = fopen("doctor_records.dat", "ab+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char searchName[10];
    printf("Enter the name of the doctor to modify: ");
    scanf("%s", searchName);

    struct doc currentDoctor;
    FILE *tempFile = fopen("temp.dat", "wb+");

    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    int found = 0;

    while (fread(&currentDoctor, sizeof(struct doc), 1, file) == 1)
    {

        if (strcmp(currentDoctor.dname, searchName) == 0)
        {
            found = 1;

            printf("Current Doctor Record:\n");
            doctorTableHeader();
            doctorTableContent(currentDoctor);

            // Prompt for modifications
            printf("Enter new values for the doctor:\n");
            printf("Enter name:");
            scanf("%s", currentDoctor.dname);
            printf("Enter gender: ");
            scanf("%s", currentDoctor.dgender);
            printf("Enter age: ");
            scanf("%d", &currentDoctor.dage);
            printf("Enter specialization: ");
            scanf("%s", currentDoctor.dspecial);
        }
        fwrite(&currentDoctor, sizeof(struct doc), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("doctor_records.dat");
    rename("temp.dat", "doctor_records.dat");

    if (!found)
    {
        printf("Doctor with name '%s' not found.\n", searchName);
        waitForUserInput();
        return;
    }

    printf("Doctor record updated successfully!\n");
    waitForUserInput();
}

void deleteDoctorRecord()
{

    FILE *file;
    file = fopen("doctor_records.dat", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char searchName[10];
    printf("Enter the name of the doctor to delete: ");
    scanf("%s", searchName);

    struct doc currentDoctor;
    FILE *tempFile = fopen("temp.dat", "wb+");

    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    int found = 0;

    while (fread(&currentDoctor, sizeof(struct doc), 1, file) == 1)
    {
        if (strcmp(currentDoctor.dname, searchName) == 0)
        {
            found = 1;
            printf("Doctor record with name '%s' has been deleted.\n", searchName);
        }
        else
        {
            fwrite(&currentDoctor, sizeof(struct doc), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("doctor_records.dat");
    rename("temp.dat", "doctor_records.dat");

    if (!found)
    {
        printf("Doctor with name '%s' not found.\n", searchName);
    }

    printf("Doctor record deleted successfully!\n");
    waitForUserInput();
}

void searchDoctorRecord()
{

    FILE *file;
    file = fopen("doctor_records.dat", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char searchName[10];
    printf("Enter the name of the doctor to search for: ");
    scanf("%s", searchName);

    struct doc currentDoctor;
    int found = 0;

    while (fread(&currentDoctor, sizeof(struct doc), 1, file) == 1)
    {
        if (strcmp(currentDoctor.dname, searchName) == 0)
        {
            found = 1;

            doctorTableHeader();
            doctorTableContent(currentDoctor);
        }
    }

    if (!found)
    {
        printf("Doctor with name '%s' not found.\n", searchName);
    }

    fclose(file);
    waitForUserInput();
}