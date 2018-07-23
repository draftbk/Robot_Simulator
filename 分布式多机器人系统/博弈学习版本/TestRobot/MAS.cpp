#include "MAS_IO.h"




//返回最短路径上的所有点集，即从起点到目标点的最短路径 
vector<int> ShortestPath( int Robot_ID , int x , int y , int x1 , int y1 ){
	
	
	
	vector<vector<int> > temp_map(Row_Num,vector<int>( Column_Num , 0 ) );
	vector<vector<int> > visited( Row_Num , vector<int>( Column_Num,0));
	
	
	
	
//	cout<<"Robot_ID="<<Robot_ID<<endl;
	
	for( int i = 0 ; i < Row_Num ; ++ i ){
		for( int j = 0 ; j < Column_Num ; ++ j ){
			temp_map[i][j] = Robot_Map[Robot_ID][i][j];
//			cout<<temp_map[i][j]<<"  "; 
		}	
	}
//	getchar();
	
	int tmp_x , tmp_y;
	tmp_x = x;
	tmp_y = y;
	
	
	
	
	queue<vector<int> > path;
	queue<int> wait_time;
	vector<int> tmp_path;
	
		
	
	
	
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

	int wait_num = temp_map[x][y];
	wait_time.push( wait_num );

	

	//从起点开始，将经过的每一个点加入path数组
	while( true  && !path.empty() ){
		tmp_path = path.front();
		wait_num = wait_time.front();
		int p_x,p_y;
		tmp_x = tmp_path[ tmp_path.size() - 2 ];
		tmp_y = tmp_path[ tmp_path.size() - 1 ];
		if( wait_num < 0 ){
			path.pop();
			path.push( tmp_path );
			wait_num ++;
			wait_time.pop();
			wait_time.push( wait_num );
			continue;
		}
		vector<int> mid_path;
		if( ( tmp_x - 1 ) >= 0 && ( tmp_x - 1 ) < Row_Num ){
			mid_path = tmp_path;
			if( visited[ tmp_x-1][tmp_y] == 0 && temp_map[ tmp_x-1][tmp_y] <= 0 ){
				p_x = tmp_x - 1;
				p_y = tmp_y;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				wait_num = temp_map[tmp_x-1][tmp_y];
				wait_time.push( wait_num );
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
			if( visited[ tmp_x+1][tmp_y] == 0 && temp_map[ tmp_x+1][tmp_y] <= 0 ){
				p_x = tmp_x + 1;
				p_y = tmp_y;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				wait_num = temp_map[tmp_x+1][tmp_y];
				wait_time.push( wait_num );
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
			if( visited[ tmp_x][tmp_y - 1] == 0 && temp_map[ tmp_x][tmp_y-1] <= 0 ){
				p_x = tmp_x ;
				p_y = tmp_y - 1;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				wait_num = temp_map[ tmp_x][tmp_y-1];
				wait_time.push( wait_num );
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
			if( visited[ tmp_x][tmp_y + 1] == 0 && temp_map[ tmp_x][tmp_y+1] <= 0){
				p_x = tmp_x ;
				p_y = tmp_y + 1;
				mid_path.push_back( p_x );
				mid_path.push_back( p_y );
				path.push ( mid_path ); 
				visiting.push_back( p_x );
				visiting.push_back( p_y );
				wait_num = temp_map[ tmp_x][tmp_y+1];
				wait_time.push( wait_num );
				if( p_x == x1 && p_y == y1 ){
					return mid_path;
					path.pop();
					break;
				}
			}
			mid_path.clear();
		}
		path.pop();
		wait_time.pop();
		
		for( int i = 0 ; i < visiting.size() ; i = i + 2 ){
			visited[ visiting[i] ][ visiting[i+1] ] = 1;
		}
		
		visiting.clear() ;
	} 
	
	
	while( path.size() != 0 ){
		tmp_path = path.front();
		if( tmp_path[tmp_path.size()-2] == x1 && tmp_path[tmp_path.size()-1] == y1)
			break;
		path.pop();
	}
	int result = tmp_path.size() / 2;
	return tmp_path;
}



//每个机器人单独的马尔科夫决策移动 
bool Robot_Markov_Move(int Robot_ID)
{
  
	int Visit_Num = Robot_Goal_To_Visit_Num[Robot_ID];
	
	int Cur_Goal_Row = Robot_Goal_To_Visit[Robot_ID][Visit_Num * 2];
	int Cur_Goal_Column = Robot_Goal_To_Visit[Robot_ID][Visit_Num * 2 + 1 ] ;
	Robot_Position[Robot_ID][2] = Cur_Goal_Row;
	Robot_Position[Robot_ID][3] = Cur_Goal_Column;
	
	if( Robot_ShortestPath[Robot_ID][0] == Null ){
		vector<int> tmp_path = ShortestPath( Robot_ID , Robot_Position[Robot_ID][0] , Robot_Position[Robot_ID][1] , Cur_Goal_Row , Cur_Goal_Column );
		for( int p = 0 ; p < tmp_path.size() ; ++ p ){
	    	Robot_ShortestPath[Robot_ID][p] = tmp_path[p];
		}
	}
	
	
	if( turn == 1 )
		turn = 5;
   	if( Robot_Wait_Time[Robot_ID] == -1 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] != 0 ){
   		int Robot_Another = Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] - 10 ;
   		if( Robot_Another >= 0 ){
				
	   			Robot_Map[Robot_ID][Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] --;
	   			if( Robot_Map[Robot_ID][Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] == ( -1 ) * ( Robot_ID + 1 ) * 20 )
	   				Robot_Map[Robot_ID][Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] = 0;
	   			Robot_Map[Robot_Another][Robot_Position[Robot_ID][0]][Robot_Position[Robot_ID][1]] --;
	   			if( Robot_Map[Robot_Another][Robot_Position[Robot_ID][0]][Robot_Position[Robot_ID][1]] == ( -1 ) * ( Robot_Another + 1 ) * 20 )
	   				Robot_Map[Robot_Another][Robot_Position[Robot_ID][0]][Robot_Position[Robot_ID][1]] = 0;
	   	}
		Robot_Wait_Time[Robot_ID] = 3;
		-- turn;
	}
	if( Robot_Wait_Time[Robot_ID] > 0 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] != 0 ){
		-- Robot_Wait_Time[Robot_ID];	
	}
	if( Robot_Wait_Time[Robot_ID] > 0 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] == 0 ){
			-- Robot_Wait_Time[Robot_ID];
	}
	   	
	if( Robot_Wait_Time[Robot_ID] == 0 && Position_Status[Robot_ShortestPath[Robot_ID][0]][Robot_ShortestPath[Robot_ID][1]] != 0 ){
		Robot_Flag[Robot_ID] = true;
		vector<int> tmp_path = ShortestPath( Robot_ID , Robot_Position[Robot_ID][0] , Robot_Position[Robot_ID][1] , Cur_Goal_Row , Cur_Goal_Column );
		if( tmp_path.size() == 2 ){
			Robot_Wait_Time[Robot_ID] = turn;
			-- turn;
		}
			
		else{
			int p = 0;
		    for( int p = 0 ; p < tmp_path.size() ; ++ p ){
		    	Robot_ShortestPath[Robot_ID][p] = tmp_path[p];
		    }
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
  
	  
	  if(Robot_Position[Robot_ID][0]==Cur_Goal_Row && Robot_Position[Robot_ID][1]==Cur_Goal_Column)
	  {
	  	 
	    Robot_Goal_To_Visit_Num[Robot_ID] = ( Robot_Goal_To_Visit_Num[Robot_ID] + 1 ) % 3 ;
		
		Visit_Num = Robot_Goal_To_Visit_Num[Robot_ID];
		
		
		Cur_Goal_Row = Robot_Goal_To_Visit[Robot_ID][Visit_Num * 2 ];
	    Cur_Goal_Column = Robot_Goal_To_Visit[Robot_ID][Visit_Num * 2 + 1];
    	vector<int> tmp_path = ShortestPath( Robot_ID , Robot_Position[Robot_ID][0] , Robot_Position[Robot_ID][1] , Cur_Goal_Row , Cur_Goal_Column );
	    for( int p = 0 ; p < tmp_path.size() ; ++ p ){
	    	Robot_ShortestPath[Robot_ID][p] = tmp_path[p];
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
			Position_Status[Robot_Position[i][0]][Robot_Position[i][1]] = i + 10;
		}
		
	}      
}



int main(int argc, char ** argv)
{  
  
  Read_Map_Info(Map_File_Name);   //读入地图信息 
  Read_Robot_Init_Position(Robot_InitPos_File); //读入机器人初始位置 
  Save_Robot_Current_Position(Robot_CurrentPos_File);  //保存机器人当前位置 
  Init_Robot_Goal_To_Visit();      //初始化机器人任务列表 

  
  cout<<"Press any key to begin"<<endl;
  getchar();
     
  double Overall_Begin_Time=(double)clock();     
  int i=0;
  //while(Check_All_Robot_Finish_Task()==false)
  while( true )
  {
    if((double)clock()-Overall_Begin_Time > 500)  
    {     
      All_Robot_Markov_Move();
      Save_Robot_Current_Position(Robot_CurrentPos_File);
      Overall_Begin_Time = (double)clock();      
      cout << i++ << endl;
      if( i % 100 == 0 ){
      	for( int i= 0 ; i < Robot_Num ; ++ i ){
      		for( int j = 0 ; j < Row_Num ; ++ j ){
      			for( int k = 0 ; k < Column_Num ; ++ k ){
      				if( Robot_Map[i][j][k] < 0 ){
      					Robot_Map[i][j][k] = Robot_Map[i][j][k] / 2 - 1 ;
					  }
				  }
			  }
		  }
	  }
    }
  }
  Release_Memory(); 
  
  cout<<"\nAll Task Finished! Press any key to quit.\n"<<endl;
  getchar();
  
  return 0;    
}
