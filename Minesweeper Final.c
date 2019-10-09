#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define tab "\t\t\t\t"
int flags_left;
placebombs(int board[50][50], int size, int diff)
{
	int i, r, c, nbombs=0;
	srand(time(0));
	diff=diff*size;
	for(i=0;i<diff;i++)
	{
		r=1+rand()%size;
		c=1+rand()%size;
		if(board[r][c]!=-1)
		{
			board[r][c]=-1;
			nbombs++;
			calctile(board, size, r, c);
		}
		else
		{
			adjtile(board, size, r, c);
		}
	}
}
adjtile(int board[50][50], int size, int r, int c)
{
	int i,j;
	for(i=r-1;i<=r+1;i++)
	{
		for(j=c-1;j<=c+1;j++)
		{
			if(i>=1&&i<=size&&j>=1&&j<=size)
			{
				if(board[i][j]!=-1)
				{
					board[i][j]=-1;
					calctile(board, size, i, j);
					return ;
				}
			}
			
		}
	}
}
calctile(int board[50][50], int size, int r, int c)
{
	int i, j;
	for(i=r-1;i<=r+1;i++)
	{
		for(j=c-1;j<=c+1;j++)
		{
			if(board[i][j]!=-1)
			{
				board[i][j]++;
			}			
		}
	}
}
void display_board(int x, int y, int size, int board[50][50], int ref_matrix[size][size])
{
    int i,j;
	printf("\n\n%s%c",tab,218);
	for(i=1;i<(size-2)*3;i++)
	{
		printf("%c",196);
		if(i%3==0)
		{
			printf("%c",194);
		}
	}
	printf("%c%c\n",196,191);
    for(i=1;i<size-1;i++)
    {
        printf("%s%c",tab,179);
        for(j=1;j<size-1;j++)
        {
        	if(i == x && j == y)
        	{
        		printf(" + ");
			}
			else if(ref_matrix[i][j]==-1)
       	    {
       	    	printf(" F ");
			}
			else if(ref_matrix[i][j]==0)
       	    {
				if(board[i][j]==0)
				{
       	 	printf("   ");
				}
				else
				{
       	    		printf(" %d ", board[i][j]);
				}
			}
			else
			{
				printf(" %c ", 254);
			}
			printf("%c",179);	    
        }
        if(i<size-2)
        {
        	int mb;
			printf("\n%s%c",tab,195);
			for(mb=1;mb<(size-2)*3;mb++)
			{
				printf("%c",196);
				if(mb%3==0)
				{
					printf("%c",197);
				}
			}
			printf("%c%c",196,180);
        }
        printf("\n");
    }

	printf("%s%c",tab,192);
	for(i=1;i<(size-2)*3;i++)
	{
		printf("%c",196);
		if(i%3==0){
			printf("%c",193);
		}
	}
	printf("%c%c",196,217);
}
void get_input(int size, int* x,int* y,char* choice, int board[50][50], int ref_matrix[size][size])
{
	int key,key1;
	char cell_status[][20] = {"FLAGGED", "OPEN", "CLOSED"};
	while(1)
	{
		z1:
		system("cls");
		display_board(*x, *y, size, board , ref_matrix);
		printf("\n\n%sCell status : %s", tab,cell_status[ref_matrix[*x][*y]+1]);
		printf("\n\n%sFlags remaining : %d",tab, flags_left);
	//	printf("\n\n\t\t\t\t\t    Use arrow keys to move\n\n\t\t\t\tUse 'f' to flag or unflag cells and 'o' to open cells");
		key=getch();
		if(key == 111 || key == 102)
		{
			*choice = (char)key;
			break;
		}
		else if(key != 224)
		{
			printf("\a");
			goto z1;
		}
		key1=0;
		key1=getch();
		switch(key1)
		{
			case 72:
			{
				if(*x>1)
				{
					*x-=1;
				}
				else
				{
            	    goto z;
				}
				break;
			}
			case 80:
			{
				if(*x<size-2)
				{
					*x+=1;
				}
				else
				{
            	    goto z;
				}
				break;
			}
			case 75:
			{
				if(*y>1)
				{
					*y-=1;
				}
				else
				{
                	goto z;
				}
				break;
			}
			case 77:
			{
				if(*y<size-2)
				{
					*y+=1;
				}
				else
				{
        	        goto z;
				}
				break;
			}
			default :
			{
				z:
					printf("\a\n");
				break;
			}
		}
	}
}
void game_over(int size, int board[50][50], int ref_matrix[size][size])
{
	int i,j;
	printf("\n\n%s%c",tab,218);
	for(i=1;i<(size-2)*3;i++)
	{
		printf("%c",196);
		if(i%3==0){
			printf("%c",194);
		}
	}
	printf("%c%c\n",196,191);
	for(i=1;i<size-1;i++)
	{
		printf("%s%c",tab,179);
		for(j=1;j<size-1;j++)
		{
			if(ref_matrix[i][j] == 0)
			{
				if(board[i][j]==0)
				{
					printf("   ");
				}
				else
				{
					printf(" %d ",board[i][j]);
				}
			}
			else if(board[i][j] == -1)
			{
				printf(" %c ",'B');
			}
			else if(ref_matrix[i][j] == -1 && board[i][j] != -1)
			{
				printf(" %c ",'X');
			}
			else
			{
				printf(" %c ",254);
			}
			printf("%c", 179);
		}
		if(i<size-2)
		{
       		int mb;
			printf("\n%s%c",tab,195);
			for(mb=1;mb<(size-2)*3;mb++)
			{
				printf("%c",196);
				if(mb%3==0)
				{
					printf("%c",197);
				}
			}
			printf("%c%c",196,180);
		}
		printf("\n");
	}
	printf("%s%c",tab,192);
	for(i=1;i<(size-2)*3;i++)
	{
		printf("%c",196);
		if(i%3==0){
			printf("%c",193);
		}
	}
	printf("%c%c",196,217);
	printf("\n\n\%s\tGAME OVER\n\n",tab);
}
void open(int x,int y, int size, int board[50][50], int ref_matrix[size][size])
{
    if(ref_matrix[x][y]!=0 && ref_matrix[x][y] != -2 && board[x][y] != -1)
    {
    	if(ref_matrix[x][y] == -1)
    	{
    		flags_left++;
		}
        if(board[x][y] != 0)
        {
        	ref_matrix[x][y]=0;
		}
		else
		{
			ref_matrix[x][y]=0;
			int x1=x-1,x2=x+2,y1=y-1,y2=y+2,i,j;
	        for(i=x1;i<x2;i++)
    	    {
        	    for(j=y1;j<y2;j++)
            	{
                    open(i,j,size,board,ref_matrix);
            	}
        	}
    	}
	}
}
int check_mines(int size, int ref_matrix[size][size],int mines)
{
	int count=0,i,j;
	for(i=1;i<size-1;i++)
	{
		for(j=1;j<size-1;j++)
		{
			if(ref_matrix[i][j] == 1 || ref_matrix[i][j] == -1)
			{
				count++;
			}
		}
	}
	if(count == mines)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int main()
{
	int size, level, i, j, mines, x, y;
	char choice;
	printf("\n\nGRID Sizes\n\n1 - 8 x 8 \n2 - 12 x 12 \n3 - 16 x 16 \n\n\nEnter Grid Size : ");
	scanf("%d",&size);
	system("cls");
	printf("\n\nDIFFICULTY\n\n1 - Beginner \n2 - Intermediate \n3 - Expert\n\n\nEnter Difficulty : ");
	scanf("%d",&level);
	system("cls");
	size = ((size+1)*4)+2, mines = (size-2)*level, x = size-2, y = size-2, flags_left = mines ;
	int board[50][50];
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			board[i][j]=0;
		}
	}
	placebombs(board,size-2,level);
	int ref_matrix[size][size];
	for(i=0;i<size;i++)
    {
		for(j=0;j<size;j++)
		{
			if(i == 0 || j == 0 || i == size-1 || j == size-1)
			{
				ref_matrix[i][j] = -2;
			}
			else
			{
            	ref_matrix[i][j] = 1;
			}
		}
		printf("\n");
	}
	system("cls");
	while(1)
    {
        get_input(size, &x, &y, &choice, board, ref_matrix);
        if(choice == 'f')
        {
        	if(ref_matrix[x][y] == 1)
        	{
        		if(flags_left == 0)
        		{
        			printf("\a");
        			continue;
				}
        		ref_matrix[x][y] =  -1;
        		flags_left--;
			}
			else if(ref_matrix[x][y] == -1)
			{
				ref_matrix[x][y] =  1;
				flags_left++;
			}
			else
			{
				goto z;
			}
        }
        else if(choice == 'o')
        {
			if(ref_matrix[x][y] == 0 || ref_matrix[x][y] == -1)
        	{
            	goto z;
        	}
        	else if(board[x][y] == -1)
        	{
        		system("cls");
        		game_over(size, board, ref_matrix);
        		break;
			}
			else 
        	{
        		open(x, y, size, board, ref_matrix);
        		if(check_mines(size, ref_matrix, mines))
        		{
        			system("cls");
        			x = 0, y = 0;
        			display_board(x, y, size, board , ref_matrix);
        			printf("\n\n\t%sYOU WON\n\n",tab);
        			getch();
        			break;
				}
			}
        }
        else
        {
        	z:
        		printf("\a");
		}  
	}
	return 0;
}

