#include<iostream>
#include<sstream>
#include<fstream>
#include"stack.h"
#define SIZE 100
using namespace std;


// 0:沒走過
// 1:牆壁
// 2:走過
// 3:死路 (pop)

int out=0;

stack<int> xStack;
stack<int> yStack;

int popcounter=0; //算步數
int gocounter=0; 

//架作標
typedef struct {
    int x; 
    int y;
} Point;
//宣告點
Point pt(int, int);

// maze / 起點 / 終點 / row / col
void go(int[][SIZE], Point, Point, int, int);



int main(void) { 

	int row=0;
	int col=0;
	int start_x,start_y; //起點  
	int end_x,end_y;   //終點

	
	char buffer[100];
	stringstream ss (stringstream::in | stringstream::out);


	char ptr2[100][100];

	int maze[100][100]={0};
	 
//讀檔
	 ifstream file;
	file.open("p3.in");
	if(!file)
	{
		cout<<"開檔失敗!\n";
		system("pause");
		return 0;
	}
	else
	{

		do{

		

		if(file.getline(buffer,sizeof(buffer))==NULL)
			break;
		
	
		ss << buffer;

		int k=0;//暫時的col
		while (1)
        {
			
			ss >> ptr2[row][k];
			k++;
			

			if(row==0)
				col++;

			if(ss.fail())  //如果全部丟完，就跳出while
				break;
        } 

		row++;
		
		ss.clear();
	
		}while(!file.eof());
		file.close();
//讀檔結束
		col=col-1;

//char轉int
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				if(ptr2[i][j]=='0') //沒走過的路
				{
					maze[i+1][j+1]=0;
				}
				else if(ptr2[i][j]=='1') //牆壁
				{
					maze[i+1][j+1]=1;
				}
				else if(ptr2[i][j]=='s' || ptr2[i][j]=='S') //起點
				{
					maze[i+1][j+1]=0; 
				    start_x=i+1;      
					start_y=j+1;
				}
				else if(ptr2[i][j]=='d' || ptr2[i][j]=='D') //終點
				{
					maze[i+1][j+1]=0; 
					end_x=i+1;
					end_y=j+1;
					out=1; // 代表此迷宮有出口，在此做標記
				}
			}
	
		}


		if(out==0){ //代表此迷宮根本沒出口
			cout<<"此迷宮根本沒有出口! stack中無元素"<<endl;
			system("pause");
			exit(1);
		}



//包圍牆
		for(int i=0;i<=row+1;i++)
		{
			for(int j=0;j<=col+1;j++)
			{
				if(i==0 || i==row+1)
					maze[i][j]=1;
				if(j==0 || j==col+1)
					maze[i][j]=1;
			}
			
		}

	}
	row=row+2;
	col=col+2;
//檢查迷宮
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			cout<<maze[i][j];
	cout<<"\n";
	}



    go(maze, pt(start_x, start_y), pt(end_x, end_y),row,col);
	cout<<"此迷宮無路到達出口! stack中無元素"<<endl;

    return 0; 
}

Point pt(int x, int y) {
    Point p = {x, y};
    return p;
}

void go(int maze[][SIZE], Point start, 
           Point end,int ROW,int COL) {


       
    if(maze[start.x][start.y]==0) { //如果沒走過就進來走
         maze[start.x][start.y] = 2;//走過標記為2
		 xStack.push(start.x);
		 yStack.push(start.y);


		 if(gocounter==0) //若該點為起點
		 {
			 maze[start.x][start.y]='s'; 
		     gocounter++;
         }
		 
		 
//寫檔
       if(maze[end.x][end.y]) 
	   {
		   maze[end.x][end.y]='d';


			 char filename[]="p3.out";
	         fstream file;

        file.open((char*) filename, ios::out);      //開啟檔案

        if(!file)     //檢查檔案是否成功開啟

        {

                cerr << "Can't open file!\n";

                exit(1);     //在不正常情形下，中斷程式的執行

        }

		else
		{


	for(int i = 0; i < ROW; i++) 
    { 
        for(int j = 0; j < COL; j++)
		{
			switch(maze[i][j]) 
			{
			case 's':file<<"Ｓ"; break;//起點
			case 'd':file<<"Ｄ"; break;//終點
            case 0 : file<<"０"; break;//沒走過
            case 1 : file<<"１"; break;//牆壁
			case 2 : file<<"＊"; break;//路徑
			case 3 : file<<"３";       //死路
            }
		}
        file<<"\n"; 
    }

	      file<<"\n\n";

	      while(!xStack.isEmpty()){
				 file<<xStack.top()<<" "<<yStack.top()<<"\n";
				 xStack.pop();
				 yStack.pop();
				 popcounter++;
			 }
		  file<<"共走了"<<popcounter-1<<"步"<<"\n"; //扣掉起點的一步

        
			

		}

		file.close();
//寫檔結束
			
	
			 


			 exit(1);  //跑出一條路徑即結束
		 }
         else {

			
		     go(maze, pt(start.x + 1, start.y), end, ROW, COL); //右
			 go(maze, pt(start.x + 1, start.y+1), end, ROW, COL); //右下
             go(maze, pt(start.x, start.y + 1), end, ROW, COL); //下
             go(maze, pt(start.x - 1, start.y + 1), end, ROW, COL); //左下
             go(maze, pt(start.x, start.y - 1), end, ROW, COL); //上
			 go(maze, pt(start.x + 1, start.y - 1), end, ROW, COL); //右上
             go(maze, pt(start.x - 1, start.y), end, ROW, COL); //左
			 go(maze, pt(start.x - 1, start.y-1), end, ROW, COL); //左上		 
											  
		 }
		  maze[start.x][start.y] = 3; //若是死路則標記3
		  xStack.pop();
		  yStack.pop();
		
	}
}


