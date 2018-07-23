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

int **Map;
int Row_Num;
int Column_Num;
char *Map_File_Name="InitMap.txt";



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
  //Row_Num 是 地图的行数   Column_Num 是地图的列数 
  FIC >> Row_Num;
  FIC >> Temp_Char;
  FIC >> Column_Num;  
  
  

  //New
  Map = new int *[Row_Num];  
  for(int i=0;i<Row_Num;i++)
    Map[i]=new int [Column_Num];  
  
    
  
  int Temp_Data;  
  for(int i=0;i<Row_Num;i++)
    for(int j=0;j<Column_Num;j++)
    {
       FIC >> Temp_Data;     
       Map[i][j]=Temp_Data;   
       
       if(j<Column_Num-1)
         FIC >> Temp_Char;
       
       cout<<Map[i][j]<<"  ";
       if(j==Column_Num-1)
         cout<<"\n";
    }
   
  FIC.close();      
  return true;  
}//End


int ShortestDistance(int x , int y , int x1 , int y1 ){
	vector<vector<int> > temp_map(Row_Num,vector<int>( Column_Num , 0 ) );
	vector<vector<int> > visited( Row_Num , vector<int>( Column_Num,0));
	
	for( int i = 0 ; i < Row_Num ; ++ i ){
		for( int j = 0 ; j < Column_Num ; ++ j ){
			temp_map[i][j] = Map[i][j];
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
	tmp_path.push_back( tmp_x );
	tmp_path.push_back( tmp_y );
	path.push( tmp_path );
	vector<int> visiting;
	visited[x][y] = 1;
	
	//从起点开始，将经过的每一个点加入path数组
	while( true ){
		tmp_path = path.front();
		for( int i = 0 ; i < tmp_path.size() ; ++ i ){
			cout<< tmp_path[i]<<"   ";
		}
		cout<<endl;
		int p_x,p_y;
		tmp_x = tmp_path[ tmp_path.size() - 2 ];
		tmp_y = tmp_path[ tmp_path.size() - 1 ];
		cout<<"tmp_x = "<<tmp_x<<"   tmp_y = " << tmp_y<<endl;
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
	
	vector<int> goal_path;
	
	cout<<"path.size = " << path.size() << endl;
	
	while( path.size() != 0 ){
		tmp_path = path.front();
		for( int i = 0 ; i < tmp_path.size(); i = i + 2 ){
			cout<< tmp_path[i]<< "   "<< tmp_path[i+1] << "   " ; 
		}
		cout<<endl;
//		if( tmp_path[ tmp_path.size() - 2 ] == x1 && tmp_path[ tmp_path.size() - 1 ] == y1 ){
//			break;
//		}
		path.pop();
	}
	cout<<"tmp_path.size = " << tmp_path.size() << endl;
	int result = tmp_path.size() / 2;
	for( int i = 0 ; i < tmp_path.size() ; ++ i ){
		cout<<tmp_path[i]<<"   ";
	}
	cout<<endl;
	return result;
}



int main(){
	Read_Map_Info( Map_File_Name );
	int result = ShortestDistance( 2 , 1 , 3 ,9 );
	cout<<result<<endl;
} 


