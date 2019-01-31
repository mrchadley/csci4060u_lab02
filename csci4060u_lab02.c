#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main()
{
    FILE *file = fopen("./CSCI4060U_Lab02_data/1.csv", "r");
    char line[256];

    float highestGPA = 0.0f;
    char highestName[128];

    while (fgets(line, sizeof(line), file))
    {

        char *first = strtok(line, ",");
        char *second = strtok(NULL, ",");
        float gpa = atof(strtok(NULL, ","));
        
        if(gpa > highestGPA)
        {
            highestGPA = gpa;
            sprintf(highestName, "%s %s", first, second);
        }
    }

    fclose(file);

    printf("Best Student: %s (GPA: %f)\n", highestName, highestGPA);

    return 0;
}