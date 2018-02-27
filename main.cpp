#include<iostream>
#include<sstream>
#include<fstream>
#include"stack.h"
#define SIZE 100
using namespace std;


// 0:�S���L
// 1:���
// 2:���L
// 3:���� (pop)

int out=0;

stack<int> xStack;
stack<int> yStack;

int popcounter=0; //��B��
int gocounter=0; 

//�[�@��
typedef struct {
    int x; 
    int y;
} Point;
//�ŧi�I
Point pt(int, int);

// maze / �_�I / ���I / row / col
void go(int[][SIZE], Point, Point, int, int);



int main(void) { 

	int row=0;
	int col=0;
	int start_x,start_y; //�_�I  
	int end_x,end_y;   //���I

	
	char buffer[100];
	stringstream ss (stringstream::in | stringstream::out);


	char ptr2[100][100];

	int maze[100][100]={0};
	 
//Ū��
	 ifstream file;
	file.open("p3.in");
	if(!file)
	{
		cout<<"�}�ɥ���!\n";
		system("pause");
		return 0;
	}
	else
	{

		do{

		

		if(file.getline(buffer,sizeof(buffer))==NULL)
			break;
		
	
		ss << buffer;

		int k=0;//�Ȯɪ�col
		while (1)
        {
			
			ss >> ptr2[row][k];
			k++;
			

			if(row==0)
				col++;

			if(ss.fail())  //�p�G�����᧹�A�N���Xwhile
				break;
        } 

		row++;
		
		ss.clear();
	
		}while(!file.eof());
		file.close();
//Ū�ɵ���
		col=col-1;

//char��int
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				if(ptr2[i][j]=='0') //�S���L����
				{
					maze[i+1][j+1]=0;
				}
				else if(ptr2[i][j]=='1') //���
				{
					maze[i+1][j+1]=1;
				}
				else if(ptr2[i][j]=='s' || ptr2[i][j]=='S') //�_�I
				{
					maze[i+1][j+1]=0; 
				    start_x=i+1;      
					start_y=j+1;
				}
				else if(ptr2[i][j]=='d' || ptr2[i][j]=='D') //���I
				{
					maze[i+1][j+1]=0; 
					end_x=i+1;
					end_y=j+1;
					out=1; // �N���g�c���X�f�A�b�����аO
				}
			}
	
		}


		if(out==0){ //�N���g�c�ڥ��S�X�f
			cout<<"���g�c�ڥ��S���X�f! stack���L����"<<endl;
			system("pause");
			exit(1);
		}



//�]����
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
//�ˬd�g�c
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			cout<<maze[i][j];
	cout<<"\n";
	}



    go(maze, pt(start_x, start_y), pt(end_x, end_y),row,col);
	cout<<"���g�c�L����F�X�f! stack���L����"<<endl;

    return 0; 
}

Point pt(int x, int y) {
    Point p = {x, y};
    return p;
}

void go(int maze[][SIZE], Point start, 
           Point end,int ROW,int COL) {


       
    if(maze[start.x][start.y]==0) { //�p�G�S���L�N�i�Ө�
         maze[start.x][start.y] = 2;//���L�аO��2
		 xStack.push(start.x);
		 yStack.push(start.y);


		 if(gocounter==0) //�Y���I���_�I
		 {
			 maze[start.x][start.y]='s'; 
		     gocounter++;
         }
		 
		 
//�g��
       if(maze[end.x][end.y]) 
	   {
		   maze[end.x][end.y]='d';


			 char filename[]="p3.out";
	         fstream file;

        file.open((char*) filename, ios::out);      //�}���ɮ�

        if(!file)     //�ˬd�ɮ׬O�_���\�}��

        {

                cerr << "Can't open file!\n";

                exit(1);     //�b�����`���ΤU�A���_�{��������

        }

		else
		{


	for(int i = 0; i < ROW; i++) 
    { 
        for(int j = 0; j < COL; j++)
		{
			switch(maze[i][j]) 
			{
			case 's':file<<"��"; break;//�_�I
			case 'd':file<<"��"; break;//���I
            case 0 : file<<"��"; break;//�S���L
            case 1 : file<<"��"; break;//���
			case 2 : file<<"��"; break;//���|
			case 3 : file<<"��";       //����
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
		  file<<"�@���F"<<popcounter-1<<"�B"<<"\n"; //�����_�I���@�B

        
			

		}

		file.close();
//�g�ɵ���
			
	
			 


			 exit(1);  //�]�X�@�����|�Y����
		 }
         else {

			
		     go(maze, pt(start.x + 1, start.y), end, ROW, COL); //�k
			 go(maze, pt(start.x + 1, start.y+1), end, ROW, COL); //�k�U
             go(maze, pt(start.x, start.y + 1), end, ROW, COL); //�U
             go(maze, pt(start.x - 1, start.y + 1), end, ROW, COL); //���U
             go(maze, pt(start.x, start.y - 1), end, ROW, COL); //�W
			 go(maze, pt(start.x + 1, start.y - 1), end, ROW, COL); //�k�W
             go(maze, pt(start.x - 1, start.y), end, ROW, COL); //��
			 go(maze, pt(start.x - 1, start.y-1), end, ROW, COL); //���W		 
											  
		 }
		  maze[start.x][start.y] = 3; //�Y�O�����h�аO3
		  xStack.pop();
		  yStack.pop();
		
	}
}


