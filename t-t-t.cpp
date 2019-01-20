#include<bits/stdc++.h>
using namespace std;

char kacy[3][3];

struct turn
{
	int r,c;
};

char k='X';
char p='O';

int pendturn(char kacy[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(kacy[i][j]=='_')
				return 1;
		}
	}

	return 0;
}

int eval(char kacy[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		if(kacy[i][0]==kacy[i][1] and kacy[i][1]==kacy[i][2] and kacy[i][1]=='X')
			return 10;
		if(kacy[i][0]==kacy[i][1] and kacy[i][1]==kacy[i][2] and kacy[i][1]=='O')
			return -10;
	}
	for (int i = 0; i < 3; i++)
	{
		if(kacy[0][i]==kacy[1][i] and kacy[1][i]==kacy[2][i] and kacy[2][i]=='X')
			return 10;
		if(kacy[0][i]==kacy[1][i] and kacy[1][i]==kacy[2][i] and kacy[2][i]=='O')
			return -10;
	}
	if(kacy[0][0]==kacy[1][1] and kacy[1][1]==kacy[2][2] and kacy[2][2]=='X')
		return 10;
	if(kacy[0][0]==kacy[1][1] and kacy[1][1]==kacy[2][2] and kacy[2][2]=='O')
		return -10;
	if(kacy[2][0]==kacy[1][1] and kacy[1][1]==kacy[0][2] and kacy[2][0]=='X')
		return 10;
	if(kacy[2][0]==kacy[1][1] and kacy[1][1]==kacy[0][2] and kacy[2][0]=='O')
		return -10;

	return 0;
}

int minmax(char kacy[3][3], bool im)
{
	int score = eval(kacy);
	if(score == 10)
		return 10;
	if(score == -10)
		return -10;

	if(pendturn(kacy)==0)
		return 0;

	if(im)
	{
		int b= -100000000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(kacy[i][j]=='_')
				{
					kacy[i][j]=k;
					b=max(b,minmax(kacy, !im));
					kacy[i][j]='_';
				}				
			}
		}
		return b;
	}
	else
	{
		int b= 100000000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(kacy[i][j]=='_')
				{
					kacy[i][j]=p;
					b=min(b,minmax(kacy, !im));
					kacy[i][j]='_';
				}				
			}
		}
		return b;	
	}
}

turn bestturn(char kacy[3][3])
{
	int bestval= -100000000;
	turn bestturn;
	bestturn.r = -1;
	bestturn.c = -1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(kacy[i][j]=='_')
			{
				kacy[i][j] = k;
				int tmp = minmax(kacy, false);
				kacy[i][j]='_';
				if(tmp>bestval)
				{
					bestturn.r=i;
					bestturn.c=j;
					bestval=tmp;
				}
			}
		}
	}
	return bestturn;
}

int main()
{
	while(true)
	{
		cout << "welcome! , kashish garg , enter a for new game or any other key for exiting."<< endl;
		char t;
		cin >> t;
		if(t == 'A' or t == 'a')
		{
			for(int i=0; i<3; i++)
				for(int j=0; j<3; j++)
					kacy[i][j] = '_';
			cout << "Simple rules,enter row no. and column no. as per your choice ,you are O , i am X ,let start the game ,first you." << endl;
		 	while(pendturn(kacy))
			{
				int row,col,testing;
				cin >> row >> col;
				while(kacy[row-1][col-1]!='_')
				{
					cout << "wrong turn. re-enter your turn." << endl;
					cout << kacy[0][0] << "|" << kacy[0][1] << "|" << kacy[0][2] << endl << kacy[1][0] << "|" << kacy[1][1] << "|" << kacy[1][2] << endl << kacy[2][0] << "|" << kacy[2][1] << "|" << kacy[2][2] << endl;
					cin >> row >> col;				
				}
				kacy[row-1][col-1]=p;
				cout << kacy[0][0] << "|" << kacy[0][1] << "|" << kacy[0][2] << endl << kacy[1][0] << "|" << kacy[1][1] << "|" << kacy[1][2] << endl << kacy[2][0] << "|" << kacy[2][1] << "|" << kacy[2][2] << endl;
				testing = eval(kacy);
				if(testing < 0)
				{
					cout << "winner!" << endl;
					break;
				}
				turn mv = bestturn(kacy);
				kacy[mv.r][mv.c] = k;
				cout << "now your turn." << endl;
				cout << kacy[0][0] << "|" << kacy[0][1] << "|" << kacy[0][2] << endl << kacy[1][0] << "|" << kacy[1][1] << "|" << kacy[1][2] << endl << kacy[2][0] << "|" << kacy[2][1] << "|" << kacy[2][2] << endl;
				testing = eval(kacy);
				if(testing > 0)
				{
					cout << "looser" << endl;
					break;
				}
			}
			if(eval(kacy) == 0)
				cout << "OOPs , draw" << endl;
		}
		else 
			return 0;
	}
}