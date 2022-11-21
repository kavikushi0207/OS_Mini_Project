
#include <stdio.h> //standard i/o
#include <stdlib.h>//highlevel i/o
#include <unistd.h>//low level i/o
#include <fcntl.h>//permissions
#include <errno.h>//store the error num
#include <sys/wait.h>//used for waits
#include <sys/msg.h>//used for msgq
#include <sys/stat.h>
#include <string.h>//to get string library

//student structure
struct Student {

    char index[30]; //EG/2018/XXXX
    float as1; //15% ASSIGNMENT 1
    float as2;//15% ASSIGNMENT 2
    float prj;//20% PROJECT
    float fin;///50% FNAL EXAM
};
  float sum = 0;
  float avgSum = 0;
  int count = 0;
//structure for msg q
struct msg{
    long type;
    char text[100];

};
struct msg create_msg(long msgType, char* msgBody); //create a formatted msg
//this is ipc inter process communication

void main(){
    //partA
    FILE* of;
    //int ret;
     //write create apprend permission in high level
    of = fopen("newStudentData.txt", "a");

//     if (of == NULL) {

//         fprintf(stderr,"\nError to open the file\n");
//         exit(1);
//     }
//     else{
//     struct Student studW;
//     printf("index: ");
//     scanf("%s",studW.index);
//     printf("marks of assignment 1: ");
//     scanf("%f",&studW.as1);
//     printf("marks of assignment 2: ");
//     scanf("%f",&studW.as2);
//     printf("marks of project: ");
//     scanf("%f",&studW.prj);
//     printf("marks of final exam: ");
//     scanf("%f",&studW.fin);
//     ret = fprintf(of, " %s \t%f\t%f \t %f \t%f  \n",studW.index,studW.as1,studW.as2,studW.prj,studW.fin);
//    // fwrite(&studW, sizeof(struct Student),1, of);
//     //printf("index= %s \tAS1: %f\tAS2:%f \tPRJ: %f \tfinal:%f  \n ---------------------\n",studW.index,studW.as1,studW.as2,studW.prj,studW.fin);
//     if(ret<0){
//     perror("fprint doc1.text: " );
//     printf("error no %d\n",errno);
//     exit(1);
//     }
//     else{printf("successfully written into file\n");}

//     }

 
//manual checking structure instances
    struct Student stud1 = { "EG/2018/3375",12.0000,14.5000,16.4000,45.9000 };
    struct Student stud2 = { "EG/2018/3377",1.5000,13.1000,10.3000,25.2000};
    struct Student stud3 = { "EG/2018/3378",12.3000,14.7000,18.2000,47.0000 };
    struct Student stud4 = { "EG/2018/3368",2.6000,4.0000,11.0000,46.7000 };
    struct Student stud5 = { "EG/2018/3370",12.0000,10.5000,16.0000,35.5000}; 
    
    fwrite(&stud1, sizeof(struct Student),1, of);
    fwrite(&stud2, sizeof(struct Student),1, of);
    fwrite(&stud3, sizeof(struct Student),1, of);
    fwrite(&stud4, sizeof(struct Student),1, of);
    fwrite(&stud5, sizeof(struct Student),1, of);



    if (fwrite != 0)

       printf("successfully written into file\n");

    else

        printf("Error writing file !\n");

    fclose(of);

    //--------------------------------------------//

    // File pointer to read from file

    FILE* inf;
   
    struct Student stud;
    //opening file for reading data
    inf = fopen("newStudentData.txt", "r");
 

    if (inf == NULL) {

        fprintf(stderr,"\nError to open the file\n");
        exit(1);

    }
    
     //printf(sizeof(struct Student));
    while (fread(&stud, sizeof(struct Student),1, inf)){
        //printf(sizeof(struct Student));
        sum = stud.as1 + stud.as2 + stud.prj;
        printf("index: %s \tAS1: %f\tAS2:%f \tPRJ: %f \tCAsum: %.2f\tfinal:%f  \n ",stud.index, stud.as1,stud.as2,stud.prj,sum,stud.fin);
         
        avgSum+= sum;
        if(sum < 25.00){
            count++;
        }
        
    }
   
    fclose(inf);
 
//partB

    key_t fileTok = ftok("ProgamFile", 56); //later need this value to access messege ques

    //create ou messege que - this is in kernel spacee,
    int msgQID = msgget(fileTok,IPC_CREAT | 0666); //WRITE PERMISSIONS
    if(msgQID == -1){
        perror ("msgget error");
        printf("Error No: %d\n",errno);
        exit(0);
    }
    pid_t PID = fork();

    if(PID == -1){
        perror ("fork error");
        printf("Error No: %d\n",errno);
        exit(0);
    }else if(PID == 0){//child process c1
        usleep(5);

        struct msg rcvMsg[3];

        for(int i = 0;i<3;i++){
            int rcvmsgRet = msgrcv(msgQID,&rcvMsg[i],sizeof(rcvMsg[i].text),-400,IPC_NOWAIT);
            if(rcvmsgRet == -1){
                perror ("msg rcve error");
                printf("Error No: %d\n",errno);
                exit(0);
            }
        }
        
        printf("child C1 received message\n");
        printf("sum of CA:  %s\n",rcvMsg[0].text);
        
        pid_t PID1 = fork();
        printf("child C1 sent messages as parent\n");
        
        pid_t PID2 = fork();
        if(PID2 == -1){
            perror ("fork error");
            printf("Error No: %d\n",errno);
            exit(0);
        }else if(PID2 == 0){//child process cc2
            printf("child CC2 received message\n");
             printf("Average of CA:  %s\n",rcvMsg[1].text);
        }
        if(PID1 == -1){
            perror ("fork error");
            printf("Error No: %d\n",errno);
            exit(0);
        }else if(PID1 == 0){//child process cc1
            printf("child CC1 received message\n");
            printf("\nNo of students below 25 percent:  %s\n",rcvMsg[2].text);
            
        }
       

    }else{//parent process
        
        struct msg sndMsg[3];

        sndMsg[0]=create_msg(100,gcvt(avgSum,6,sndMsg[0].text));
        sndMsg[1]=create_msg(200,gcvt(avgSum/5,6,sndMsg[1].text));
        sndMsg[2]=create_msg(300,gcvt(count,6,sndMsg[2].text));

        for(int i = 0; i<3;i++){
            int sentRet = msgsnd(msgQID,&sndMsg[i],sizeof(sndMsg[i].text),IPC_NOWAIT);
            if(sentRet == -1){
                perror ("msgsnd error");
                printf("Error No: %d\n",errno);
                exit(0);
            }
        }
        printf("Parent sent messages\n");
        pid_t wpidRet = waitpid(PID,NULL,0);
        if(wpidRet == -1){
           perror ("msgsnd error at parent");
            printf("Error No: %d\n",errno);
           exit(0); 
        }
        

        int ctrlRet =  msgctl(msgQID,IPC_RMID,0);
        if(ctrlRet == -1){
           perror ("msgsnd error");
            printf("Error No: %d\n",errno);
           exit(0); 
        }//IPC_RMID - FLAG FOR DELETE MSG
    }
}
struct msg create_msg(long msgType, char* msgBody){

    struct msg newMsg;
    newMsg.type = msgType;
    strcpy(newMsg.text,msgBody);
    return newMsg;
}