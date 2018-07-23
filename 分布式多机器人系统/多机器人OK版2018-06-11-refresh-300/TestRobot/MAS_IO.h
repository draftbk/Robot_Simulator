
/******************************************************************************
This program is developed for solving the GMSTP
Version: 1.0
Author: Zhang-Hua Fu
Email: fu@info.univ-angers.fr
All rights reserved @September 2017
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <ctime>
#include <vector>
#include <string.h>
#include <math.h>
#include <string.h>
#include <queue> 
using namespace std;

typedef double Cost_Type;


//#define Max_Inst_Num     2000

#define Time_Div           CLOCKS_PER_SEC
#define Null               -1
#define Inf_Cost           1000000000
#define Max_Goal_To_Visit  10000

//#define Default_Random_Seed  (unsigned)time(NULL);
#define Default_Random_Seed  1416150433;                            
unsigned Random_Seed=Default_Random_Seed;

char *Map_File_Name="InitMap.txt";
char *Robot_InitPos_File="Robot_Init_Position.txt";
char *Robot_CurrentPos_File="Robot_Current_Position.txt";
char *Task_File_Name="Task.txt";
char *Message_To_Show_File="MessageToShow.txt";         

int Row_Num;
int Column_Num;
int Robot_Num;
int Task_Num;
int Task_Order = 0;
int Max_Path_Number;
int **Map;
bool **If_Posisiton_Occupied;


int **Position_Status;

int **Robot_Position;
int **Robot_Goal_To_Visit;
int *Robot_Goal_To_Visit_Num;
int **Task;
int *Robot_Status;
int *Task_Status;
int **Robot_Init_Position;
int **Robot_ShortestPath; 
int *Robot_Wait_Time;

bool *Robot_Flag;

int turn = 3;





//��ȡ��ͼ�ļ��е���Ϣ�����ҽ�����ͼ���Ƿ���õ���Ϣ 
bool Read_Map_Info(char *Map_File_Name)
{
  ifstream FIC;   
  FIC.open(Map_File_Name);   
   
  if (FIC.fail())
  {     
    cout<<"Read_Map_Info() fail! Fail to open the map file "<<Map_File_Name<<endl; 
    return false;     
  }  

  char Temp_Char;
  //Row_Num �� ��ͼ������   Column_Num �ǵ�ͼ������ 
  FIC >> Row_Num;
  FIC >> Temp_Char;
  FIC >> Column_Num;  
  Max_Path_Number = Row_Num * Column_Num;
  
  //���Լ���ӵĲ��Դ���
  //cout<<"Row_Num = "<<Row_Num<<endl;
  //cout<<"Temp_Char = "<< Temp_Char<<endl;
  //cout<<"Column_Num = "<<Column_Num<<endl;
  //���Դ������ 
  

  //New
  Map = new int *[Row_Num];
  Position_Status = new int *[Row_Num];  
  for(int i=0;i<Row_Num;i++){
  	Map[i]=new int [Column_Num];
  	Position_Status[i] = new int [Column_Num];
  }
      
  
  
  //If_Posistion_Occupied ��һ���͵�ͼһ����С�Ķ�άbool�����飬�����жϵ�ǰ��ͼ��ĳ��λ���Ƿ���� 
  If_Posisiton_Occupied = new bool *[Row_Num];  
  for(int i=0;i<Row_Num;i++)
    If_Posisiton_Occupied[i]=new bool [Column_Num];     
  
  int Temp_Data;  
  for(int i=0;i<Row_Num;i++)
    for(int j=0;j<Column_Num;j++)
    {
       FIC >> Temp_Data;     
       Map[i][j]=Temp_Data;
	   Position_Status[i][j] = Temp_Data;   
       
       if(j<Column_Num-1)
         FIC >> Temp_Char;
       
       //cout<<Map[i][j]<<"  ";
       if(j==Column_Num-1)
         //cout<<"\n";
         ;
    }
   
  FIC.close();      
  return true;  
}//End

//Read_Robot_Init_Position ��ȡ���ļ����ǻ����˵ĳ�ʼλ�� 
bool Read_Robot_Init_Position(char *Robot_File_Name)
{
  ifstream FIC;   
  FIC.open(Robot_File_Name);   
   
  if (FIC.fail())
  {     
    cout<<"Read_Robot_Init_Position() fail! Fail to open the robot file "<<Robot_File_Name<<endl;
    return false;     
  }  

  FIC >> Robot_Num;   
  Robot_Position = new int *[Robot_Num];
  
  for(int i=0;i<Robot_Num;i++)
    Robot_Position[i]=new int [4];   
  
  Robot_Flag = new bool[Robot_Num];  
  for( int i = 0 ; i < Robot_Num; ++ i )
  	Robot_Flag[i] = false;
  
  
  Robot_Init_Position = new int *[Robot_Num];  
  for(int i=0;i<Robot_Num;i++)
    Robot_Init_Position[i]=new int [2];
    
    
    
  int Temp_Data;
  char Temp_Char;
  for(int i=0;i<Robot_Num;i++)   
  {
    FIC >> Temp_Data;       
    FIC >> Temp_Char;
        
    FIC >> Temp_Data;   
    Robot_Position[i][0]=Temp_Data-1;
	Robot_Init_Position[i][0] = Temp_Data-1;
    //cout<<Robot_Position[i][0]+1<<"  ";
        
    FIC >> Temp_Char;
       
    FIC >> Temp_Data;   
    Robot_Position[i][1]=Temp_Data-1; 
	Robot_Init_Position[i][1]=Temp_Data-1; 
    //cout<<Robot_Position[i][1]+1<<"\n";

	Position_Status[Robot_Init_Position[i][0]][Robot_Init_Position[i][1]] = 1;

	//����ʼĿ��λ����Ϊ��ֵ
	Robot_Position[i][2] = Null;
	Robot_Position[i][3] = Null;
  }
   
  FIC.close();      
  return true;  
}//End

void Init_Robot_Goal_To_Visit()
{
  Robot_Goal_To_Visit = new int *[Robot_Num];  
  Robot_ShortestPath = new int *[Robot_Num];
  //����ÿ����������Max_Goal_To_Visit������Ҫִ�� 
  for(int i=0;i<Robot_Num;i++){
    Robot_Goal_To_Visit[i]=new int [Max_Goal_To_Visit];   
    Robot_ShortestPath[i] = new int [Max_Path_Number];
  }
  
  
  //��ʼ����������Ϊ�� 
  for(int i=0;i<Robot_Num;i++)
    for(int j=0;j<Max_Goal_To_Visit;j++)
      Robot_Goal_To_Visit[i][j]=Null;
 
 
  //��ʼ·���б�	
  for(int i=0;i<Robot_Num;i++)
    for(int j=0;j<Max_Path_Number;j++)
      Robot_ShortestPath[i][j]=Null;
      
      
  //Robot_Goal_To_Visit_Num ����ÿ�������˽��м�������Ҫִ��  
  Robot_Goal_To_Visit_Num = new int [Robot_Num];  
  Robot_Status = new int [Robot_Num]; 
  Robot_Wait_Time = new int[Robot_Num];
  for(int i=0;i<Robot_Num;i++){
  	Robot_Goal_To_Visit_Num[i]=0;
  	Robot_Status[i]=0;
  	Robot_Wait_Time[i]=-1;
  }
    
}


//�������л����˵ĵ�ǰλ�� 
bool Save_Robot_Current_Position(char *Robot_CurrentPos_File)
{
  FILE *fp; 
  fp=fopen(Robot_CurrentPos_File, "w+"); 
  
  fprintf(fp,"%d\n", Robot_Num);
  
  printf("\n\n");
  for(int i=0;i<Robot_Num;i++)
  {
    fprintf(fp,"%d,%d,%d,%d,%d\n", i+1, Robot_Position[i][0]+1, Robot_Position[i][1]+1,Robot_Position[i][2]+1, Robot_Position[i][3]+1);
//    printf("�����ˣ�%d,λ����Ϣ��%d,%d\n", i+1, Robot_Position[i][0]+1, Robot_Position[i][1]+1);
//    printf("�����ˣ�%d,Ŀ��λ�ã�%d,%d\n", i+1, Robot_Position[i][2]+1, Robot_Position[i][3]+1);
  }
    
  fclose(fp);      
  return true;  
}//End

/*
bool Save_Message_To_Show(char Message[])
{
  FILE *fp; 
  fp=fopen(Message_To_Show_File, "w+"); 
  
  fprintf(fp,"%s\n", Message);    
  fclose(fp);      
  return true;  
}//End
*/

bool Read_Task_Info(char *Task_File_Name)
{
  ifstream FIC;   
  FIC.open(Task_File_Name);   
   
  if (FIC.fail())
  {     
    cout<<"Read_Task_Info() fail! Fail to open the task file "<<Task_File_Name<<endl;
    return false;     
  }  
  //�����4�зֱ��������������յ������ 
  FIC >> Task_Num;   
  Task = new int *[Task_Num];  
  Task_Status = new int [Task_Num];
  for(int i=0;i<Task_Num;i++)
    Task[i]=new int [4];   
  
  int Temp_Data;  
  for(int i=0;i<Task_Num;i++)   
  {
    FIC >> Temp_Data;       
           
    FIC >> Temp_Data;   
    Task[i][0]=Temp_Data-1;
    //cout<<Task[i][0]+1<<"  ";
    
    FIC >> Temp_Data;   
    Task[i][1]=Temp_Data-1;
    //cout<<Task[i][1]+1<<"  ";
    
    FIC >> Temp_Data;   
    Task[i][2]=Temp_Data-1;
    //cout<<Task[i][2]+1<<"  ";
    
    FIC >> Temp_Data;   
    Task[i][3]=Temp_Data-1;
    //cout<<Task[i][3]+1<<"\n"; 
  }
   
  FIC.close();      
  return true;  
}//End

//Release the occupied memeory 
void Release_Memory()
{
  cout<<"Begin to release memory"<<endl;
  for(int i=0;i<Row_Num;i++)
    delete []Map[i];
  delete []Map;   
  
  for(int i=0;i<Robot_Num;i++)
    delete []Robot_Position[i];
  delete []Robot_Position;  
  
  for(int i=0;i<Robot_Num;i++)
    delete []Robot_Goal_To_Visit[i];
  delete []Robot_Goal_To_Visit;  
  
  delete []Robot_Goal_To_Visit_Num;
  
  for(int i=0;i<Task_Num;i++)
    delete []Task[i];
  delete []Task;  
  
  cout<<"Release memory finished"<<endl; 
}//End Release_Memory()
