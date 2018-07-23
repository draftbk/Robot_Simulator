#include "MAS_IO.h"





int Get_Random_Int(int Divide_Num)
{ 
  return rand()%Divide_Num;
}//End Get_Random_Int()


//生成任务 
bool Generate_Task(char *Task_File_Name,int Task_Num)
{
  FILE *fp; 
  fp=fopen(Task_File_Name, "w+");     
  
  fprintf(fp,"%d \n",Task_Num);  
  for(int i=0;i<Task_Num;i++)
  {
    int Begin_Row;
    int Begin_Column;
    int End_Row;
    int End_Column;
    do        
    {
      Begin_Row = Get_Random_Int(Row_Num);
      Begin_Column = Get_Random_Int(Column_Num);    
      End_Row = Get_Random_Int(Row_Num);  
      End_Column = Get_Random_Int(Column_Num); 
    }while(Map[Begin_Row][Begin_Column] == 1 || Map[End_Row][End_Column] == 1 || (Begin_Row==End_Row && Begin_Column==End_Column));
    
    fprintf(fp,"%d %d %d %d %d\n",i+1,Begin_Row+1,Begin_Column+1,End_Row+1,End_Column+1);     
  }     
  fclose(fp);
}

//返回最短路径上的所有点集，即从起点到目标点的最短路径 
int ShortestDistance(int x , int y , int x1 , int y1 ){
	vector<vector<int> > temp_map(Row_Num,vector<int>( Column_Num , 0 ) );
	vector<vector<int> > visited( Row_Num , vector<int>( Column_Num,0));
	
	for( int i = 0 ; i < Row_Num ; ++ i ){
		for( int j = 0 ; j < Column_Num ; ++ j ){
			temp_map[i][j] = Position_Status[i][j];
		}	
	}
	//int distance = 0;
	int tmp_x , tmp_y;
	tmp_x = x;
	tmp_y = y;
	
	int goal_x , goal_y;
	goal_x = x1;
	goal_y = y1;
	
	
	queue<vector<int> > path;
	vector<int> tmp_path;
	if( x == x1 && y == y1 ){
//		tmp_path.push_back( x );
//		tmp_path.push_back( y );
//		return tmp_path.size() / 2;
		return Inf_Cost;
	}
	tmp_path.push_back( tmp_x );
	tmp_path.push_back( tmp_y );
	path.push( tmp_path );
	vector<int> visiting;
	visited[x][y] = 1;
	
	//从起点开始，将经过的每一个点加入path数组
	while( true  && !path.empty() ){
		tmp_path = path.front();
		int p_x,p_y;
		tmp_x = tmp_path[ tmp_path.size() - 2 ];
		tmp_y = tmp_path[ tmp_path.size() - 1 ];
		vector<int> mid_path;
		if( ( tmp_x - 1 ) >= 0 && ( tmp_x - 1 ) < Row_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x-1][tmp_y] == 0 && temp_map[ tmp_x-1][tmp_y] == 0 ){
				p_x = tmp_x - 1;
				p_y = tmp_y;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				if( p_x == x1 && p_y == y1 ){
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		if( ( tmp_x + 1 ) >= 0 && ( tmp_x + 1 ) < Row_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x+1][tmp_y] == 0 && temp_map[ tmp_x+1][tmp_y] == 0 ){
				p_x = tmp_x + 1;
				p_y = tmp_y;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				if( p_x == x1 && p_y == y1 ){
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		
		if( ( tmp_y - 1 ) >= 0 && ( tmp_y - 1 ) < Column_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x][tmp_y - 1] == 0 && temp_map[ tmp_x][tmp_y-1] == 0 ){
				p_x = tmp_x ;
				p_y = tmp_y - 1;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				if( p_x == x1 && p_y == y1 ){
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		if( ( tmp_y + 1 ) >= 0 && ( tmp_y + 1 ) < Column_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x][tmp_y + 1] == 0 && temp_map[ tmp_x][tmp_y+1] == 0){
				p_x = tmp_x ;
				p_y = tmp_y + 1;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				if( p_x == x1 && p_y == y1 ){
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		path.pop();
		
		for( int i = 0 ; i < visiting.size() ; i = i + 2 ){
			visited[ visiting[i] ][ visiting[i+1] ] = 1;
		}
		
		visiting.clear() ;
	} 
	
	if( path.empty() ){
//		tmp_path.push_back(x);
//		tmp_path.push_back(y);
//		return tmp_path.size() / 2;
		return Inf_Cost;
	}
	
	vector<int> goal_path;
	
	while( path.size() != 0 ){
		tmp_path = path.front();
		path.pop();
	}
	int result = tmp_path.size() / 2;
	return result;
}


//返回最短路径上的所有点集，即从起点到目标点的最短路径 
vector<int> ShortestPath(int x , int y , int x1 , int y1 ){
	
	
	
	vector<vector<int> > temp_map(Row_Num,vector<int>( Column_Num , 0 ) );
	vector<vector<int> > visited( Row_Num , vector<int>( Column_Num,0));
	
	for( int i = 0 ; i < Row_Num ; ++ i ){
		for( int j = 0 ; j < Column_Num ; ++ j ){
			temp_map[i][j] = Position_Status[i][j];
			//cout<<temp_map[i][j]<<"  ";
		}	
		//cout<<endl;
	}
	
	
	
	
	//cout<<"起点："<<x<<"   "<<y<<"   终点："<<x1<<"    "<<y1<<endl;
	
	
	//int distance = 0;
	int tmp_x , tmp_y;
	tmp_x = x;
	tmp_y = y;
	
	int goal_x , goal_y;
	goal_x = x1;
	goal_y = y1;
	
	
	queue<vector<int> > path;
	vector<int> tmp_path;
	
	if( temp_map[x1][y1] == 1 ){
		tmp_path.push_back(x);
		tmp_path.push_back(y);
		return tmp_path;
	}
		
	
	
	
	if( x == x1 && y == y1 ){
		tmp_path.push_back( x );
		tmp_path.push_back( y );
		return tmp_path;
	}
	tmp_path.push_back( tmp_x );
	tmp_path.push_back( tmp_y );
	path.push( tmp_path );
	vector<int> visiting;
	visited[x][y] = 1;
	
	//从起点开始，将经过的每一个点加入path数组
	while( true  && !path.empty() ){
		tmp_path = path.front();
		int p_x,p_y;
		tmp_x = tmp_path[ tmp_path.size() - 2 ];
		tmp_y = tmp_path[ tmp_path.size() - 1 ];
		vector<int> mid_path;
		if( ( tmp_x - 1 ) >= 0 && ( tmp_x - 1 ) < Row_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x-1][tmp_y] == 0 && temp_map[ tmp_x-1][tmp_y] == 0 ){
				p_x = tmp_x - 1;
				p_y = tmp_y;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				if( p_x == x1 && p_y == y1 ){
					return mid_path;
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		if( ( tmp_x + 1 ) >= 0 && ( tmp_x + 1 ) < Row_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x+1][tmp_y] == 0 && temp_map[ tmp_x+1][tmp_y] == 0 ){
				p_x = tmp_x + 1;
				p_y = tmp_y;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				if( p_x == x1 && p_y == y1 ){
					return mid_path;
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		
		if( ( tmp_y - 1 ) >= 0 && ( tmp_y - 1 ) < Column_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x][tmp_y - 1] == 0 && temp_map[ tmp_x][tmp_y-1] == 0 ){
				p_x = tmp_x ;
				p_y = tmp_y - 1;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				if( p_x == x1 && p_y == y1 ){
					return mid_path;
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		if( ( tmp_y + 1 ) >= 0 && ( tmp_y + 1 ) < Column_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x][tmp_y + 1] == 0 && temp_map[ tmp_x][tmp_y+1] == 0){
				p_x = tmp_x ;
				p_y = tmp_y + 1;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				if( p_x == x1 && p_y == y1 ){
					return mid_path;
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		path.pop();
		
		for( int i = 0 ; i < visiting.size() ; i = i + 2 ){
			visited[ visiting[i] ][ visiting[i+1] ] = 1;
		}
		
		visiting.clear() ;
	} 
	
	if( path.empty() ){
		tmp_path.push_back(x);
		tmp_path.push_back(y);
		return tmp_path;
	}
	
	vector<int> goal_path;
	
	while( path.size() != 0 ){
		tmp_path = path.front();
		if( tmp_path[tmp_path.size()-2] == x1 && tmp_path[tmp_path.size()-1] == y1)
			break;
		path.pop();
	}
	int result = tmp_path.size() / 2;
//	for( int i = 0 ; i < tmp_path.size() ; ++ i ){
//		cout<<tmp_path[i]<<"   ";
//	}
//	cout<<endl;
	return tmp_path;
}





//分配任务，当前代码分配任务的方式属于随机分配 
void Allocate_Task()
{
	 for(  ; Task_Order < Task_Num ; ++ Task_Order ){
	 	int x = Task[Task_Order][0] , y = Task[Task_Order][1];
	 	int To_Robot = 0;
	 	int distance = Inf_Cost; 
	 	int Robot_Status_Sum = 0;
	 	for( int j = 0 ; j < Robot_Num ; ++ j ){
	 		if( Robot_Status[j] == 1  )
	 			continue;
	 		int tmp = 0; 
	 		
	 		tmp =  ShortestDistance(Robot_Position[j][0] , Robot_Position[j][1] , x , y );
	 		
	 		if( tmp < distance ){
	 			distance = tmp;
	 			To_Robot = j;
			 }
		 }
		 
		int Cur_Index=Robot_Goal_To_Visit_Num[To_Robot];
		
	    Robot_Goal_To_Visit[To_Robot][Cur_Index]=Task[Task_Order][0]*Column_Num+Task[Task_Order][1];
	    
	    Robot_Goal_To_Visit[To_Robot][Cur_Index]=Task[Task_Order][0]*Column_Num+Task[Task_Order][1];
	    
	    Robot_Goal_To_Visit_Num[To_Robot]++;
	    
	    
	    vector<int> tmp_path = ShortestPath( Robot_Position[To_Robot][0], Robot_Position[To_Robot][1], Task[Task_Order][0]  , Task[Task_Order][1] );
	    
	    
	    
	    //把计算出来的最短路径加入到Robot_ShortestPath数组中 
	    for( int p = 0 ; p < tmp_path.size() ; ++ p ){
	    	//cout<<tmp_path[p]<< "   ";
	    	Robot_ShortestPath[To_Robot][p] = tmp_path[p];
		}
	    //cout<<endl;
	    
	    
	    Cur_Index=Robot_Goal_To_Visit_Num[To_Robot];
	    
	    Robot_Goal_To_Visit[To_Robot][Cur_Index]=Task[Task_Order][2]*Column_Num+Task[Task_Order][3];
	    
	    Robot_Goal_To_Visit_Num[To_Robot]++;
	    
	    //cout<<To_Robot<<endl;
	    Robot_Status[To_Robot] = 1;
	    for( int k = 0 ; k < Robot_Num ; ++ k ){
	 		if( Robot_Status[k] == 1 )
	 			Robot_Status_Sum ++ ;
		}
		if( Robot_Status_Sum == Robot_Num )	break;
	 }
	 
	 
	 
	 
	 
   //以上代码为按照距离远近来分配任务 
	
	
	
	
   //以下是随机分配方法 
//  for(int i=0;i<Task_Num;i++)
//  {
//    int Robot_Id=Get_Random_Int(Robot_Num);
//    
//    int Cur_Index=Robot_Goal_To_Visit_Num[Robot_Id];
//    Robot_Goal_To_Visit[Robot_Id][Cur_Index]=Task[i][0]*Row_Num+Task[i][1];
//    Robot_Goal_To_Visit_Num[Robot_Id]++;
//    
//    Cur_Index=Robot_Goal_To_Visit_Num[Robot_Id];
//    Robot_Goal_To_Visit[Robot_Id][Cur_Index]=Task[i][2]*Row_Num+Task[i][3];
//    Robot_Goal_To_Visit_Num[Robot_Id]++;         
//  }
  
  for(int i=0;i<Robot_Num;i++)  
     Robot_Goal_To_Visit[i][Robot_Goal_To_Visit_Num[i]++]=Robot_Position[i][0]*Column_Num+Robot_Position[i][1];
}


//检查所有机器人是否都已经执行完任务 
bool Check_All_Robot_Finish_Task()
{
  for(int i=0;i<Robot_Num;i++)
  {
    if(Robot_Goal_To_Visit_Num[i]>0)     
      return false;        
  }
  
  return true;
}

//每个机器人单独的马尔科夫决策移动 
bool Robot_Markov_Move(int Robot_ID)
{
  if(Robot_Goal_To_Visit_Num[Robot_ID] <=0)
    return false;
  
  int Cur_Goal_Row = Robot_Goal_To_Visit[Robot_ID][0]/Column_Num;
  int Cur_Goal_Column = Robot_Goal_To_Visit[Robot_ID][0]%Column_Num;
  Robot_Position[Robot_ID][2] = Cur_Goal_Row;
  Robot_Position[Robot_ID][3] = Cur_Goal_Column;
  
  
   
//  if( flag ){
//  
//	  int Direction_Score[4];
//	  
//	  // 向下 
//	 
//	  if(Robot_Position[Robot_ID][0] < Row_Num-1 && If_Posisiton_Occupied[Robot_Position[Robot_ID][0]+1][Robot_Position[Robot_ID][1]] == false)
//	  {
//	     if(Robot_Position[Robot_ID][0] < Cur_Goal_Row)   
//	       Direction_Score[0]=1;   
//	     else
//	       Direction_Score[0]=-1;                         
//	  }
//	  else
//	    Direction_Score[0]=-Inf_Cost;
//	   
//	  // 向上 
//	  if(Robot_Position[Robot_ID][0] >0 && If_Posisiton_Occupied[Robot_Position[Robot_ID][0]-1][Robot_Position[Robot_ID][1]] == false)
//	  {
//	     if(Robot_Position[Robot_ID][0] > Cur_Goal_Row)   
//	       Direction_Score[1]=1;   
//	     else
//	       Direction_Score[1]=-1;                         
//	  }
//	  else
//	    Direction_Score[1]=-Inf_Cost;
//	    
//	   // 向右 
//	  if(Robot_Position[Robot_ID][1] < Column_Num-1 && If_Posisiton_Occupied[Robot_Position[Robot_ID][0]][Robot_Position[Robot_ID][1]+1] == false)
//	  {
//	     if(Robot_Position[Robot_ID][1] < Cur_Goal_Column)   
//	       Direction_Score[2]=1;   
//	     else
//	       Direction_Score[2]=-1;                         
//	  }
//	  else
//	    Direction_Score[2]=-Inf_Cost;
//	    
//	  // 向左 
//	  if(Robot_Position[Robot_ID][1] > 0 && If_Posisiton_Occupied[Robot_Position[Robot_ID][0]][Robot_Position[Robot_ID][1]-1] == false)
//	  {
//	     if(Robot_Position[Robot_ID][1] > Cur_Goal_Column)   
//	       Direction_Score[3]=1;   
//	     else
//	       Direction_Score[3]=-1;                         
//	  }
//	  else
//	    Direction_Score[3]=-Inf_Cost;
//	    
//	  int Best_Sore_Direction=Null;
//	  
//	  //选择最好的移动方向 
//	  for(int i=0;i<4;i++)
//	  {
//	    if(Direction_Score[i] == -Inf_Cost)
//	      continue;
//	    
//	    if(Best_Sore_Direction==Null)
//	    {
//	      Best_Sore_Direction=i;
//	      continue;
//	    }
//	    
//	    if((Direction_Score[i] > Direction_Score[Best_Sore_Direction] && Get_Random_Int(100) < 80) || (Direction_Score[i] == Direction_Score[Best_Sore_Direction] && Get_Random_Int(100) < 50))
//	    {
//	      Best_Sore_Direction=i;
//	      continue;
//	    }    
//	  }
//	      
//	  if(Best_Sore_Direction == Null)
//	    return false;
//	  
//	  if(Best_Sore_Direction==0)
//	    Robot_Position[Robot_ID][0]++;
//	  else if(Best_Sore_Direction==1)
//	    Robot_Position[Robot_ID][0]--;
//	  else if(Best_Sore_Direction==2)
//	    Robot_Position[Robot_ID][1]++;
//	  else if(Best_Sore_Direction==3)
//	    Robot_Position[Robot_ID][1]--;
//	    
//	  If_Posisiton_Occupied[Robot_Position[Robot_ID][0]][Robot_Position[Robot_ID][1]]=true;
//	  
//	}
  
  
//   else{
   		if( turn == 1 )
   			turn = 5;
	   	if( Robot_Wait_Time[Robot_ID] == -1 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] == 1 ){
    		Robot_Wait_Time[Robot_ID] = turn;
    		-- turn;
		}
   		if( Robot_Wait_Time[Robot_ID] > 0 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] == 1 ){
   			-- Robot_Wait_Time[Robot_ID];	
		}
		if( Robot_Wait_Time[Robot_ID] > 0 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] == 0 ){
			if( !Robot_Flag )
   				Robot_Wait_Time[Robot_ID] = -1;
			else{
				-- Robot_Wait_Time[Robot_ID];
				if( Robot_Wait_Time[Robot_ID] == 1  )
					Robot_Flag[Robot_ID] = false;
			}
					
		}
	   	
		if( Robot_Wait_Time[Robot_ID] == 0 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] == 1 ){
			Robot_Flag[Robot_ID] = true;
			vector<int> tmp_path = ShortestPath( Robot_Position[Robot_ID][0] , Robot_Position[Robot_ID][1] , Cur_Goal_Row , Cur_Goal_Column );
			if( tmp_path.size() == 2 ){
				Robot_Wait_Time[Robot_ID] = turn;
				-- turn;
			}
				
			else{
				int p = 0;
				//cout<<"Robot is "<<Robot_ID<<endl;
			    for( int p = 0 ; p < tmp_path.size() ; ++ p ){
			    	Robot_ShortestPath[Robot_ID][p] = tmp_path[p];
			    	
			    	//cout<<tmp_path[p]<<"   ";
			    }
			    //getchar();
			    Robot_Wait_Time[Robot_ID] = -1;
			}
			
		}
		if( Robot_Wait_Time[Robot_ID] == 0 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] == 0 ){
		    Robot_Wait_Time[Robot_ID] = -1;
		}
   		if( Robot_Wait_Time[Robot_ID] == -1 ){
   			//根据最短路径进行移动
			   Robot_Position[Robot_ID][0] = Robot_ShortestPath[Robot_ID][0];
			   Robot_Position[Robot_ID][1] = Robot_ShortestPath[Robot_ID][1];
			   
			   int p = 0 ;
			   while( p < Max_Path_Number && Robot_ShortestPath[Robot_ID][p] != Null ){
			   	Robot_ShortestPath[Robot_ID][p] = Robot_ShortestPath[Robot_ID][p+2];
			   	++ p;
			   	Robot_ShortestPath[Robot_ID][p] = Robot_ShortestPath[Robot_ID][p+2];
			   	++ p;
		   }
	  		
	   }   
  
//	}
  
	  
	  if(Robot_Position[Robot_ID][0]==Cur_Goal_Row && Robot_Position[Robot_ID][1]==Cur_Goal_Column)
	  {
	  	//依次将后续任务往前移动 
	    for(int i=0;i<Robot_Goal_To_Visit_Num[Robot_ID];i++)  
	      Robot_Goal_To_Visit[Robot_ID][i] =  Robot_Goal_To_Visit[Robot_ID][i+1];  
	     
	    Robot_Goal_To_Visit_Num[Robot_ID]--;
	    
	    
	    
	    //Allocate_Task();
		//给当前机器人重新分配任务，如果任务池还有未执行的任务
		 
		int sum = 0;
		for( int i = 0 ; i < Task_Num ; ++ i ){
			if( Task_Status[i] == 1 )
				sum ++ ;
		}
		
		
		if( sum < Task_Num && Robot_Goal_To_Visit_Num[Robot_ID] == 0 ){
			
			Robot_Status[Robot_ID] = 0 ;
			int To_Task = 0;
			int distance = Inf_Cost;
			for( int j = 0 ;  j < Task_Num ; ++ j ){
				if( Task_Status[j] == 1 )
					continue;
				int tmp = 0 ;
				tmp =  ShortestDistance(Robot_Position[Robot_ID][0] , Robot_Position[Robot_ID][1] , Task[j][0] , Task[j][1] );
				if( tmp < distance ){
					distance = tmp;
					To_Task = j;
				}
			}
			
			int Cur_Index=Robot_Goal_To_Visit_Num[Robot_ID];
			
		    Robot_Goal_To_Visit[Robot_ID][Cur_Index]=Task[To_Task][0]*Column_Num+Task[To_Task][1];
		    
		    Robot_Goal_To_Visit_Num[Robot_ID]++;
		    
		    Cur_Index=Robot_Goal_To_Visit_Num[Robot_ID];
		    
		    Robot_Goal_To_Visit[Robot_ID][Cur_Index]=Task[To_Task][2]*Column_Num+Task[To_Task][3];
		    
		    Robot_Goal_To_Visit_Num[Robot_ID]++;
		    
		    //cout<<To_Robot<<endl;
		    Task_Status[To_Task] = 1;
		} 
		
		if( sum == Task_Num && Robot_Goal_To_Visit_Num[Robot_ID] == 0 )
		{
			Robot_Status[Robot_ID] = 0 ;
			//让机器人回到最初的位置
			 if( Robot_Init_Position[Robot_ID][0]==Cur_Goal_Row && Robot_Init_Position[Robot_ID][1]==Cur_Goal_Column ){
			 	Robot_Goal_To_Visit_Num[Robot_ID] = -1;
			 }else{
			 	int To_Robot = Robot_ID;
	
				int Cur_Index=Robot_Goal_To_Visit_Num[To_Robot];
				
			    Robot_Goal_To_Visit[To_Robot][Cur_Index]=Robot_Init_Position[Robot_ID][0]*Column_Num+Robot_Init_Position[Robot_ID][1];
			    
			    Robot_Goal_To_Visit_Num[To_Robot]++;
			    
			 }
		}
		
		Cur_Goal_Row = Robot_Goal_To_Visit[Robot_ID][0]/Column_Num;
	    Cur_Goal_Column = Robot_Goal_To_Visit[Robot_ID][0]%Column_Num;
	    if( Robot_Goal_To_Visit_Num[Robot_ID] != -1 ){
	    	vector<int> tmp_path = ShortestPath( Robot_Position[Robot_ID][0] , Robot_Position[Robot_ID][1] , Cur_Goal_Row , Cur_Goal_Column );
		    for( int p = 0 ; p < tmp_path.size() ; ++ p ){
		    	Robot_ShortestPath[Robot_ID][p] = tmp_path[p];
			}
		}
	    
	} 
  
  return true;
}

//所有机器人移动 
bool All_Robot_Markov_Move()
{
  
	for(int i=0;i<Row_Num;i++)
		for(int j=0;j<Column_Num;j++)
		{
			Position_Status[i][j] = Map[i][j];
			if(Map[i][j]==0)
		    	If_Posisiton_Occupied[i][j]=false;
			else
		    	If_Posisiton_Occupied[i][j]=true;
		}
	
	for(int i=0;i<Robot_Num;i++){
		If_Posisiton_Occupied[Robot_Position[i][0]][Robot_Position[i][1]]=true;  
		Position_Status[Robot_Position[i][0]][Robot_Position[i][1]] = 1;
	}
    
    
	FILE *fp; 
	fp=fopen(Message_To_Show_File, "w+");    
	fprintf(fp,"\n");
	for(int i=0;i<Robot_Num;i++)  
	{ 
		Robot_Markov_Move(i);
		
		for(int i=0;i<Row_Num;i++)
			for(int j=0;j<Column_Num;j++)
			{
				Position_Status[i][j] = Map[i][j];
				if(Map[i][j]==0)
			    	If_Posisiton_Occupied[i][j]=false;
				else
			    	If_Posisiton_Occupied[i][j]=true;
			}
	
		for(int i=0;i<Robot_Num;i++){
			If_Posisiton_Occupied[Robot_Position[i][0]][Robot_Position[i][1]]=true;  
			Position_Status[Robot_Position[i][0]][Robot_Position[i][1]] = 1;
		}
		
		
		 
//		if(Robot_Goal_To_Visit_Num[i] > 0)
//	      fprintf(fp,"G%d: %d %d     ",i+1,Robot_Goal_To_Visit[i][0]/Column_Num+1,Robot_Goal_To_Visit[i][0]%Column_Num+1); 
//	    else
//	      fprintf(fp,"G%d: Null    ",i+1); 
//	    if( (i+1)%2 == 0 )
//		  fprintf(fp,"\n");	 
		}    
			fclose(fp);  
	}



int main(int argc, char ** argv)
{  
  srand(Random_Seed);
  
  Read_Map_Info(Map_File_Name);   //读入地图信息 
  Read_Robot_Init_Position(Robot_InitPos_File); //读入机器人初始位置 
  Save_Robot_Current_Position(Robot_CurrentPos_File);  //保存机器人当前位置 
  Init_Robot_Goal_To_Visit();      //初始化机器人任务列表 
  
  //Generate_Task(Task_File_Name,50);   
//  return 0;
  Read_Task_Info(Task_File_Name);    //初始任务池 
  
  Allocate_Task();   //分配任务 
  
  
  
  
  
//  FILE *fp; 
//  fp=fopen(Message_To_Show_File, "w+");    
//  
//  for(int i=0;i<Robot_Num;i++)  
//  { 
//    if(Robot_Goal_To_Visit_Num[i] > 0)
//      fprintf(fp,"G%d: %d %d     ",i+1,Robot_Goal_To_Visit[i][0]/Column_Num+1,Robot_Goal_To_Visit[i][0]%Column_Num+1); 
//    else
//      fprintf(fp,"G%d: Null    ",i+1); 
//    if( (i+1)%2 == 0 )
//	  fprintf(fp,"\n");	 
//  }
//    
//  fclose(fp);
  
  cout<<"Press any key to begin"<<endl;
  getchar();
     
  double Overall_Begin_Time=(double)clock();     
  int i=0;
  while(Check_All_Robot_Finish_Task()==false)
  {
    if((double)clock()-Overall_Begin_Time > 300)  
    {     
      All_Robot_Markov_Move();
      Save_Robot_Current_Position(Robot_CurrentPos_File);
      //Allocate_Task(); 
      Overall_Begin_Time = (double)clock();      
      cout << i++ << endl;
    }
  }
  Release_Memory(); 
  
  cout<<"\nAll Task Finished! Press any key to quit.\n"<<endl;
  getchar();
  
  return 0;    
}
