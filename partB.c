// #include <fcntl.h>
// #include <errno.h>
// #include <sys/wait.h>
// #include <sys/msg.h>
// #include <sys/stat.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// struct student{
//     char student_index[20]; //EG/XXXX/XXXX
//     float assgnmt01_marks; //15%
//     float assgnmt02_marks; //15%
//     float project_marks; //20%
//     float finalExam_marks; //50%
//     //float all_marks;
// };
// //this is ipc inter process communication
// void main(){
//     key_t fileTok = ftok("studData", 56); //later need this value to access messege ques

//     //create ou messege que - this is in kernel spacee,
//     int msgQID = msgget(fileTok,IPC_CREAT | 0666); //WRIT PERMISSIONS
//     if(msgQID == -1){
//         perror ("msgget error");
//         printf("Error No: %d\n",errno);
//         exit(0);
//     }
//     pid_t PID = fork();

//     if(PID == -1){
//         perror ("fork error");
//         printf("Error No: %d\n",errno);
//         exit(0);
//     }else if(PID == 0){//child process
//         struct student rcvStud1;
//         int retMsgRcv = msgrcv(msgQID,&rcvStud1,sizeof(rcvStud1.student_index),200,IPC_NOWAIT);
//         struct student rcvStud2;
//         int retMsgRcv2 = msgrcv(msgQID,&rcvStud2,sizeof(rcvStud2.student_index),0,IPC_NOWAIT);
//          //try to handle errors
//         if(retMsgRcv == -1){
//             perror ("msgrcv error");
//             printf("Error No: %d\n",errno);
//             exit(0);
//         }
//         printf("CHILD RECIVED %s %sn",rcvStud1.student_index,rcvStud2.student_index);

//     }else{//parent process
//         struct student stud1 = {"EG/2018/3375",11.2,13,16.7,34.6};
//         struct student stud2 = {"EG/2018/3376",13.5,10,11.4,23.8};
//         struct student stud3 = {"EG/2018/3377",10,12,17.3,43.5};
//         struct student stud4 = {"EG/2018/3378",10,12,7.3,46.5};

//         msgsnd(msgQID,&stud1,sizeof(stud1.student_index),IPC_NOWAIT);
//         msgsnd(msgQID,&stud2,sizeof(stud2.student_index),IPC_NOWAIT);
//         msgsnd(msgQID,&stud3,sizeof(stud3.student_index),IPC_NOWAIT);
//         msgsnd(msgQID,&stud4,sizeof(stud4.student_index),IPC_NOWAIT);

//         printf("Parent sent mesgs\n");
//         waitpid(PID,NULL,0);

//         msgctl(msgQID,IPC_RMID,0);///IPC_RMID - FLAG FOR DELETE MSG
//     }
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>

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


struct msg{
    long type;
    char text[100];

};
struct msg create_msg(long msgType, char* msgBody); //create a formatted msg

float sum1 = 90.0;
float average1 = 30.0;
float count1 =  1;
//this is ipc inter process communication
void main(){
    //partA
    FILE* of;

    of = fopen("newStudentData.txt", "w");

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
 
//partB

    key_t fileTok = ftok("myFIle", 56); //later need this value to access messege ques

    //create ou messege que - this is in kernel spacee,
    int msgQID = msgget(fileTok,IPC_CREAT | 0666); //WRIT PERMISSIONS
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
    }else if(PID == 0){//child process
        usleep(5);

        // struct msg rcvMsg1;
        // int retMsgRcv = msgrcv(msgQID,&rcvMsg1,sizeof(rcvMsg1.text),0,IPC_NOWAIT);
        // struct msg rcvMsg2;
        // int retMsgRcv2 = msgrcv(msgQID,&rcvMsg2,sizeof(rcvMsg2.text),100,IPC_NOWAIT);
        //  //try to handle errors
        // if(retMsgRcv == -1 || retMsgRcv2 == -1){
        //     perror ("fmsgrcv error");
        //     printf("Error No: %d\n",errno);
        //     exit(0);
        // }

        struct msg rcvMsg[3];

        for(int i = 0;i<3;i++){
            int rcvmsgRet = msgrcv(msgQID,&rcvMsg[i],sizeof(rcvMsg[i].text),-400,IPC_NOWAIT);
            if(rcvmsgRet == -1){
                perror ("msgrcverror");
                printf("Error No: %d\n",errno);
                exit(0);
            }
        }
        
         printf("sum of CA:  %s\n",rcvMsg[0].text);
         printf("Average of CA:  %s\n",rcvMsg[1].text);
        printf("No of students below 25 percent:  %s\n",rcvMsg[2].text);

    }else{//parent process
        // struct msg msg1 = {100,"MY FIRST MSG!"};
        // struct msg msg2 = {200,"MY SECOND MSG!"};
        // struct msg msg3 = {300,"MY THIRD MSG!"};
        // struct msg msg4 = {400,"MY FOURTH MSG!"};

        // msgsnd(msgQID,&msg1,sizeof(msg1.text),IPC_NOWAIT);
        // msgsnd(msgQID,&msg2,sizeof(msg2.text),IPC_NOWAIT);
        // msgsnd(msgQID,&msg3,sizeof(msg3.text),IPC_NOWAIT);
        // msgsnd(msgQID,&msg4,sizeof(msg4.text),IPC_NOWAIT);
        //struct msg buffer[100];
        struct msg sndMsg[3];

        sndMsg[0]=create_msg(100,gcvt(sum1,6,sndMsg[0].text));
        sndMsg[1]=create_msg(200,gcvt(average1,6,sndMsg[1].text));
        sndMsg[2]=create_msg(300,gcvt(count1,6,sndMsg[2].text));
        //sndMsg[3]=create_msg(400,"My frth msg!");

        for(int i = 0; i<3;i++){
            int sentRet = msgsnd(msgQID,&sndMsg[i],sizeof(sndMsg[i].text),IPC_NOWAIT);
            if(sentRet == -1){
                perror ("msgsnd error");
                printf("Error No: %d\n",errno);
                exit(0);
            }
        }
        printf("Parent sent mesgs\n");
        pid_t wpidRet = waitpid(PID,NULL,0);
        if(wpidRet == -1){
           perror ("msgsnd error");
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