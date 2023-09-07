#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "utilities.h"

struct patient
{
    char name[10];
    char gender[10];
    int age;
    int ward;
    char doc[10];
};

void createPatientRecord()
{
    FILE *file;
    file = fopen("patient_records.dat", "ab+"); // Open the file in append and binary mode
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct patient newPatient;

    printf("Enter patient name: ");
    scanf("%s", newPatient.name);
    printf("Enter gender: ");
    scanf("%s", newPatient.gender);
    printf("Enter age: ");
    scanf("%d", &newPatient.age);
    printf("Enter ward: ");
    scanf("%d", &newPatient.ward);
    printf("Enter doctor's name: ");
    scanf("%s", newPatient.doc);

    fwrite(&newPatient, sizeof(struct patient), 1, file);
    fclose(file);

    printf("Patient record added successfully!\n");
    waitForUserInput();
}

void patientTableHeader()
{

    printf("| %-20s | %-10s | %-4s | %-8s | %-20s |\n", "Name", "Gender", "Age", "Ward No.", "Doctor's Name");
    printf("|----------------------|------------|------|----------|----------------------|\n");
}

void patientTableContent(struct patient currentPatient)
{

    printf("| %-20s | %-10s | %-4d | %-8d | %-20s |\n", currentPatient.name, currentPatient.gender, currentPatient.age, currentPatient.ward, currentPatient.doc);
}

void readPatientRecords()
{
    FILE *file;
    file = fopen("patient_records.dat", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct patient currentPatient;

    patientTableHeader();

    // Read and display all patient records in the file
    while (fread(&currentPatient, sizeof(struct patient), 1, file) == 1)
    {
        patientTableContent(currentPatient);
    }

    fclose(file);
    waitForUserInput();
}

void modifyPatientRecord()
{

    FILE *file;
    file = fopen("patient_records.dat", "ab+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char searchName[10];
    printf("Enter the name of the patient to modify: ");
    scanf("%s", searchName);

    struct patient currentPatient;
    FILE *tempFile = fopen("temp.dat", "wb+"); // Temporary file for updates

    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    // Search for the patient record by name
    int found = 0;

    while (fread(&currentPatient, sizeof(struct patient), 1, file) == 1)
    {

        if (strcmp(currentPatient.name, searchName) == 0)
        {
            found = 1;

            // Display the current patient record
            printf("Current Patient Record:\n");
            patientTableHeader();
            patientTableContent(currentPatient);

            // Prompt for modifications
            printf("Enter new values for the patient:\n");
            printf("Enter name:");
            scanf("%s", currentPatient.name);
            printf("Enter gender: ");
            scanf("%s", currentPatient.gender);
            printf("Enter age: ");
            scanf("%d", &currentPatient.age);
            printf("Enter Ward No.: ");
            scanf("%d", &currentPatient.ward);
            printf("Enter doctor's name: ");
            scanf("%s", currentPatient.doc);
        }
        fwrite(&currentPatient, sizeof(struct patient), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("patient_records.dat");
    rename("temp.dat", "patient_records.dat");

    if (!found)
    {
        printf("Patient with name '%s' not found.\n", searchName);
        waitForUserInput();
        return;
    }

    printf("Patient record updated successfully!\n");
    waitForUserInput();
}

// Function to delete a patient record by name
void deletePatientRecord()
{

    FILE *file;
    file = fopen("patient_records.dat", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char searchName[10];
    printf("Enter the name of the patient to delete: ");
    scanf("%s", searchName);

    struct patient currentPatient;
    FILE *tempFile = fopen("temp.dat", "wb+");

    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    int found = 0;

    while (fread(&currentPatient, sizeof(struct patient), 1, file) == 1)
    {
        if (strcmp(currentPatient.name, searchName) == 0)
        {
            found = 1;
            printf("Patient record with name '%s' has been deleted.\n", searchName);
        }
        else
        {
            // Write all other patient records to the temporary file
            fwrite(&currentPatient, sizeof(struct patient), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file
    remove("patient_records.dat");
    rename("temp.dat", "patient_records.dat");

    if (!found)
    {
        printf("Patient with name '%s' not found.\n", searchName);
    }

    printf("Patient record deleted successfully!\n");
    waitForUserInput();
}

void searchPatientRecord()
{

    FILE *file;
    file = fopen("patient_records.dat", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char searchName[10];
    printf("Enter the name of the patient to search for: ");
    scanf("%s", searchName);

    struct patient currentPatient;
    int found = 0;

    while (fread(&currentPatient, sizeof(struct patient), 1, file) == 1)
    {
        if (strcmp(currentPatient.name, searchName) == 0)
        {
            found = 1;

            patientTableHeader();
            patientTableContent(currentPatient);
        }
    }

    if (!found)
    {
        printf("Patient with name '%s' not found.\n", searchName);
    }

    fclose(file);
    waitForUserInput();
}
