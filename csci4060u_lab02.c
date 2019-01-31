#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_THREADS 3
#define NUM_FILES 8

struct Student
{
    char name[256];
    float gpa;
};

void swap(struct Student *a, struct Student *b) 
{ 
    struct Student temp = *a; 
    *a = *b; 
    *b = temp; 
} 

void bubbleSort(struct Student arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j].gpa < arr[j+1].gpa) 
              swap(&arr[j], &arr[j+1]); 
} 
  
void printArray(struct Student arr[], int size) 
{ 
    printf("Top Students:\n");
    for (int i=0; i < size; i++) 
        printf("%d. Name: %s, GPA: %f\n", i+1, arr[i].name, arr[i].gpa);
}

int main()
{
    struct Student best_students[NUM_FILES];

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int file_num = thread_id + 1;
        
        while(file_num < NUM_FILES + 1)
        {
            char filename[256];
            sprintf(filename, "./CSCI4060U_Lab02_data/%d.csv", file_num);
            FILE *file = fopen(filename, "r");
            char line[256];

            struct Student best = {.name = "", .gpa = 0.0f};
            

            while (fgets(line, sizeof(line), file))
            {

                char *first = strtok(line, ",");
                char *second = strtok(NULL, ",");
                float gpa = atof(strtok(NULL, ","));
            
                if(gpa > best.gpa)
                {
                    best.gpa = gpa;
                    sprintf(best.name, "%s %s", first, second);
                }
            }

            fclose(file);

            best_students[file_num-1] = best;

            //printf("Best Student(thread %d): %s (GPA: %f)\n", thread_id, best.name, best.gpa);
            file_num += num_threads;
        }
        #pragma omp barrier
    }

    //do the sorting thing
    bubbleSort(best_students, NUM_FILES);
    printArray(best_students, NUM_FILES);

    return 0;
}

