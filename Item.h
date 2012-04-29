#include<fstream.h>
#include<time.h>
#include<iomanip.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<process.h>
#include<string.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<dir.h>

enum boolean{FALSE,TRUE};

void normalColor()
{
	  textbackground(0);
	  textcolor(LIGHTGRAY);
}

void lightcyanColor()
{
	  textbackground(0);
	  textcolor(LIGHTCYAN);
}

void lightredColor()
{
	  textbackground(0);
	  textcolor(LIGHTRED);
}

void warningColor()
{
	  textbackground(7);
	  textcolor(RED+BLINK);
}

void greenColor()
{
	textbackground(0);
	textcolor(GREEN);
}

void lightgreenColor()
{
	textbackground(0);
	textcolor(LIGHTGREEN);
}

void whiteColor()
{
	textbackground(0);
	textcolor(WHITE);
}

void redColor()
{

	textbackground(0);
	textcolor(RED);
}

void lightgrayColor()
{
	textbackground(0);
	textcolor(LIGHTGRAY);
}

void yellowColor()
{
	textbackground(0);
	textcolor(YELLOW);
}

void headingColor()
{
	textbackground(0);
	textcolor(LIGHTMAGENTA);
}

void clrBox(int left, int top, int right, int bottom)
{
	window(left,top,right,bottom);
	clrscr();
	window(1,1,80,25);
}

int nextBillNo()
{
	int nextNo;
	ofstream outFile;
	ifstream inFile;
	inFile.open("BILL_NO.TXT");
	if(!inFile)
	{
		outFile.open("BILL_NO.TXT");
		nextNo=1;
		outFile<<nextNo+1;
		outFile.close();
	}
	else
	{
		inFile>>nextNo;
		inFile.close();
		outFile.open("BILL_NO.TXT");
		outFile<<nextNo+1;
	}
	return nextNo;
}

void drawMainBox(int left,int top, int right, int bottom)
{
	for(int i=left;i<=right+1;i++)
	{
		gotoxy(i,top-1);
		putch(char(220));
		gotoxy(i,top-4);
		putch(char(220));
		gotoxy(i,bottom+1);
		putch(char(223));
	}
	for(i=top-3;i<=bottom;i++)
	{
		gotoxy(left,i);
		putch(char(221));
		putch(char(222));
		gotoxy(right,i);
		putch(char(221));
		putch(char(222));
	}
}

void drawBox(int left, int top, int right, int bottom )
{
	int i,j;
	gotoxy(left,top);    	putch( char(201) );
	gotoxy(right,top);      putch( char(187) );
	gotoxy(left,bottom);    putch( char(200) );
	gotoxy(right,bottom);   putch( char(188) );

	for(i=left+1; i<right; i++)
	{
		gotoxy(i,top);    	putch( char(205) );
		gotoxy(i,bottom);       putch( char(205) );
	}

	for(i=top+1; i<bottom; i++)
	{
		gotoxy(left,i);    	putch( char(186) );
		gotoxy(right,i);   	putch( char(186) );
	}
}

void drawBoxTwo(int left, int top, int right, int bottom )
{

	int i,j;

	for(i=left+1; i<right; i++)
	{
		gotoxy(i,top);    	putch( char(205) );
		gotoxy(i,top-4);    	putch( char(205) );
		gotoxy(i,bottom);       putch( char(205) );
	}

	for(i=top-3; i<bottom; i++)
	{
		gotoxy(left,i);    	putch( char(186) );
		gotoxy(right,i);   	putch( char(186) );
	}

	gotoxy(left,top-4);    	putch( char(201) );
	gotoxy(left,top);    	putch( char(204) );
	gotoxy(right,top-4);    putch( char(187) );
	gotoxy(right,top);      putch( char(185) );
	gotoxy(left,bottom);    putch( char(200) );
	gotoxy(right,bottom);   putch( char(188) );

}

void horLine(int left,int right)
{
	for(int i=left; i<=right; i++)
		putch(char(205));
}

char* getTime()
{
	time_t t;
	time(&t);
	return ctime(&t);
}

