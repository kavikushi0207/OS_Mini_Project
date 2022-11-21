
// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Structure to store
// student details

struct Student {

    char index[30];
    float as1;
    float as2;
    float prj;
    float fin;
};
  float sum = 0;
  float avgSum = 0;
  int count = 0;

int main()
{
    printf("index: ");
    scanf("%s",index);
    printf("marks of assignment 1: ");
    scanf("%d",&as1);
    printf("marks of assignment 2: ");
    scanf("%d",&as2);
    printf("marks of project: ");
    scanf("%d",&prj);
    printf("marks of final exam: ");
    scanf("%d",&fin);
    
    FILE* of;

    of = fopen("test.txt", "w");

    if (of == NULL) {

        fprintf(stderr,"\nError to open the file\n");
        exit(1);
    }
 

    struct Student stud1 = { "3376",14.5,11.2,16.4,32.4 };
    struct Student stud2 = { "3377",1.5,1.2,15.4,33.4 };
    struct Student stud3 = { "3378",2.5,10.2,12.4,35.4 };
    struct Student stud4 = { "3378",1,12.2,10.4,37.4 };
    struct Student stud5 = { "3370",13.5,4.2,18.4,45.4 }; 

    fwrite(&stud1, sizeof(struct Student),1, of);
    fwrite(&stud2, sizeof(struct Student),1, of);
    fwrite(&stud3, sizeof(struct Student),1, of);
    fwrite(&stud4, sizeof(struct Student),1, of);
    fwrite(&stud5, sizeof(struct Student),1, of);



    if (fwrite != 0)

        printf("Contents to file written successfully !\n");

    else

        printf("Error writing file !\n");

    fclose(of);
 

    // File pointer to read from file

    FILE* inf;

    struct Student stud;

    inf = fopen("test.txt", "r");
 

    if (inf == NULL) {

        fprintf(stderr,"\nError to open the file\n");
        exit(1);

    }
 

    while (fread(&stud, sizeof(struct Student),1, inf)){
        sum = stud.as1 + stud.as2 + stud.prj;
        printf("index= %s \tAS1: %f\tAS2:%f \tPRJ: %f \tCAsum: %.2f\tfinal:%f  \n ",stud.index, stud.as1,stud.as2,stud.prj,sum,stud.fin);
         
        avgSum+= sum;
        if(sum < 25.00){
            count++;
        }
        
    }
   
    printf("Average of CA MARKS: %2f \n",avgSum/5);
    printf("Number of Students below than 25 percent CA marks: %d\n",count);

    fclose(inf);
}
	
