#include "item.h"

class Item
{
	private:

		int itemNo;
		char name[25];
		int qty;
		float rate;

	public:

		void getRecord();
		void getNewRecord();
		void getModifiedRecord();
		void showRecord();
		void createFile();
		void Search(int);
		void addItem(int);
		void Modify(int);
		void removeItem(int);
		void report();
		void Billing();
};

Item a;

void Item :: getRecord()
{
		 gotoxy(38,13);
		 cprintf("Item Number  : ");
		 cin>>itemNo;
		 gotoxy(38,15);
		 cprintf("Item Name    : ");
		 gets(name);
		 gotoxy(38,17);
		 cprintf("Qty          : ");
		 cin>>qty;
		 gotoxy(38,19);
		 cprintf("Rate         : ");
		 cin>>rate;
}

void Item :: getNewRecord()
{
		 gotoxy(41,15);
		 cprintf("Item Name      : ");
		 gets(name);
		 gotoxy(41,17);
		 cprintf("Qty            : ");
		 cin>>qty;
		 gotoxy(41,19);
		 cprintf("Rate           : ");
		 cin>>rate;
}

void Item :: getModifiedRecord()
{
		 gotoxy(41,15);
		 cprintf("Item Name        : %s",name);
		 gotoxy(41,17);
		 cprintf("Qty (%d)         : ",qty);
		 cin>>qty;
		 gotoxy(41,19);
		 cprintf("Rate (%.2f)      : ",rate);
		 cin>>rate;
}

void Item::showRecord()
{
	cout<<setw(7)<<setiosflags(ios::left)
		 <<setiosflags(ios::fixed)<<itemNo;
	 cout<<setw(25)<<setiosflags(ios::left)
		 <<setiosflags(ios::fixed)<<name;
	 cout<<setw(10)<<setiosflags(ios::right)
		 <<setiosflags(ios::fixed)<<qty;
	 cout<<setw(10)<<setprecision(2)<<rate;
	 cout<<setw(10)<<setprecision(2)<<qty*rate;
}

void Item :: createFile()
{
	ofstream outFile;
	char ch;
	outFile.open("ITEM.DAT",ios::binary);
	do
	{
	  clrBox(34,8,70,23);
	  whiteColor();
	  drawBoxTwo(34,11,70,23);
	  gotoxy(46,9);
	  headingColor();
	  cprintf("STOCK CREATION");
	  lightcyanColor();
	  a.getRecord();
	  outFile.write( (char*)&a,sizeof(a) );
	  whiteColor();
	  drawBox(35,20,69,22);
	  gotoxy(37,21);
	  textcolor(YELLOW+BLINK);
	  cprintf("Record is successfully inserted");
	  gotoxy(37,24);
	  yellowColor();
	  cprintf("Do you want to continue (Y/N) ? ");
	  cin >>ch;
	  ch=toupper(ch);
	  gotoxy(37,24);
	  clreol();
	} while ( ch=='Y');
	outFile.close();
}

void Item::addItem(int iNo)
{
	fstream inFile;
	inFile.open("ITEM.DAT",ios::in | ios::binary);
	if(!inFile)
	{
		gotoxy(44,16);
		warningColor();
		cprintf("File does not exist!!");
		cout<<'\a';
		return;
	}
	inFile.read( (char*)&a,sizeof(a) );
	fstream outFile;
	outFile.open("TEMP.DAT",ios::out | ios::binary);
	boolean found = FALSE;
	while( (!inFile.eof()) && (!found) )
	{
		if(iNo == a.itemNo)
		{
			gotoxy(40,18);
			warningColor();
			cprintf("Duplicate Item No.Rejected..!\n");
			cout<<'\a';
			return;
		}
		else
		if(iNo > a.itemNo)
		{
			outFile.write( (char*)&a, sizeof(a) );
			inFile.read( (char*)&a,sizeof(a) );
		}
		else
			found = TRUE;
	}
	Item newRec;
	newRec.itemNo = iNo;
	lightcyanColor();
	newRec.getNewRecord();
	outFile.write( (char*)&newRec, sizeof(newRec) );
	while(inFile)
	{
		outFile.write( (char*)&a, sizeof(a) );
		inFile.read( (char*)&a,sizeof(a) );
	}
	whiteColor();
	drawBox(37,20,73,22);
	gotoxy(39,21);
	textcolor(YELLOW+BLINK);
	cprintf("Item #. %d is successfully added",iNo);
	inFile.close();
	outFile.close();
	remove("ITEM.DAT");
	rename("TEMP.DAT","ITEM.DAT");
}

void Item :: Modify(int iNo)
{
	ifstream inFile("ITEM.DAT",ios::binary);

	if(!inFile)
	{
	  gotoxy(44,16);
	  warningColor();
	  cprintf("File does not exist!!");
	  cout<<'\a';
	  return;
	}

	inFile.close();
	fstream modifyFile;
	modifyFile.open("ITEM.DAT",ios::in | ios::out | ios::binary);

	modifyFile.read( (char*)&a,sizeof(a) );
	boolean found = FALSE;
	int rec = 0;
	while( (!modifyFile.eof()) && (!found) )
	{
		rec++;
		if(iNo == a.itemNo)
		{
			lightcyanColor();
			a.getModifiedRecord();
			modifyFile.seekg( (rec-1)*sizeof(a),ios::beg);
			modifyFile.write( (char*)&a, sizeof(a) );
			found = TRUE;
		}
		else
			modifyFile.read( (char*)&a, sizeof(a) );
	}
	if(found)
	{
		whiteColor();
		drawBox(42,20,69,22);
		gotoxy(44,21);
		textcolor(YELLOW+BLINK);
		cprintf("Item #. %d is modified",iNo);
	}
	else
	{
		 gotoxy(43,16);
		 warningColor();
		 cprintf("Item #. %d Not Found!",iNo);
		 cout<<'\a';
		 remove("TEMP.DAT");
		 return;
	}
	modifyFile.close();
}

void Item :: removeItem(int iNo)
{
   fstream inFile;
   inFile.open("ITEM.DAT",ios::in | ios::binary);
   if(!inFile)
   {
	  gotoxy(43,16);
	  warningColor();
	  cprintf("File does not exists");
	  cout<<'\a';
	  return;
   }
   inFile.read((char*)&a,sizeof(a));
   fstream outFile;
   outFile.open("TEMP.DAT",ios::out | ios::binary);
   boolean found = FALSE;
   while((!inFile.eof()))
   {
	  if(iNo != a.itemNo)
		 outFile.write((char*)&a, sizeof(a));
	  else
	  {
		 found=TRUE;
		 gotoxy(38,15);
		 lightcyanColor();
		 cprintf("Item Name        : %s",a.name);
		 gotoxy(38,17);
		 cprintf("Quantity         : %d",a.qty);
		 gotoxy(38,19);
		 cprintf("Rate             : %.2f",a.rate);
		 char confirm;
		 whiteColor();
		 drawBox(38,20,72,22);
		 gotoxy(40,21);
		 textcolor(YELLOW);
		 cprintf("Are you sure to delete(Y/N) ?\a ");
		 cin>>confirm;
		 whiteColor();
		 drawBoxTwo(36,11,74,23);
		 if(confirm != 'Y' && confirm != 'y')
		 {
			outFile.write( (char*)&a, sizeof(a) );
		 }
		 else
		 {
			whiteColor();
			drawBoxTwo(36,11,74,23);
			gotoxy(40,21);
			clreol();
			whiteColor();
			drawBoxTwo(36,11,74,23);
			drawBox(38,20,72,22);
			gotoxy(45,21);
			textcolor(YELLOW+BLINK);
			cprintf("Item #. %d is deleted",iNo);
		 }
	  }
	  inFile.read( (char*)&a,sizeof(a) );
   }
   if(!found)
   {
	  gotoxy(44,16);
	  warningColor();
	  cprintf("Item #. %d Not Found!",iNo);
	  cout<<'\a';
	  remove("TEMP.DAT");
	  return;
   }
   inFile.close();
   outFile.close();
   remove("ITEM.DAT");
   rename("TEMP.DAT","ITEM.DAT");
}

void Item::Search(int iNo)
{
	ifstream inFile;
	inFile.open("ITEM.DAT",ios::binary);
	if(!inFile)
	{
		gotoxy(44,16);
		warningColor();
		cprintf("File does not exist!!");
		cout<<'\a';
		normalColor();
		return;
	}
	lightgreenColor();
	inFile.read((char*)&a,sizeof(a));
	boolean found=FALSE;
	while(!inFile.eof() && (!found))
	{
		if(iNo==a.itemNo)
			found=TRUE;
		else
			inFile.read((char*)&a, sizeof(a));
	}
	if(found)
	{
		gotoxy(38,15);
		lightcyanColor();
		cprintf("Item Name        : %s",a.name);
		gotoxy(38,17);
		lightcyanColor();
		cprintf("Quantity         : %d",a.qty);
		gotoxy(38,19);
		lightcyanColor();
		cprintf("Rate             : %.2f",a.rate);
		gotoxy(38,21);
		lightcyanColor();
		cprintf("Price            : %.2f",a.qty*a.rate);

	}
	else
	{
		gotoxy(43,16);
		warningColor();
		cprintf("Item #. %d Not Found!",iNo);
		cout<<'\a';
	}
	inFile.close();
}


void Item::Billing()
{
	normalColor();
	clrscr();
	ifstream inFile;
	inFile.open("ITEM.DAT",ios::in | ios::binary);
	if(!inFile)
	{
		gotoxy(30,12);
		warningColor();
		cprintf("File does not exist!!");
		cout<<'\a';
		delay(500);
		normalColor();
		return;
	}
	fstream recordBill("BILLS.TXT",ios::app);
	inFile.close();
	char* time;
	int billNo;
	int sNo=0;
	int sQty;
	int iNo;
	int itemK=0;
	int lcount;
	float price;
	float amount=0;
	billNo=nextBillNo();
	time=getTime();
	clrscr();
	gotoxy(30,1);
	headingColor();
	cprintf("ABC STORES MANAGEMENT");
	gotoxy(30,2);
	cprintf("---------------------");
	gotoxy(37,3);
	cprintf("BILLING");
	gotoxy(37,4);
	cprintf("-------");
	gotoxy(4,4);
	yellowColor();
	time=getTime();
	cprintf("%s",time);
	lcount=8;
	do
	{
		sNo++;
		whiteColor();
		drawBox(3,5,55,23);
		gotoxy(3,25);
		yellowColor();
		cprintf("Type '0' to item# to end input");
		gotoxy(4,7);
		whiteColor();
		horLine(4,54);
		lightgreenColor();
		gotoxy(5,6);
		cprintf("Item#  Name           Qty       Rate   Price");
		clrBox(57,5,80,23);
		whiteColor();
		drawBox(57,5,80,23);
		gotoxy(58,7);
		whiteColor();
		horLine(58,79);
		lightgreenColor();
		gotoxy(59,6);
		cprintf("Item#  Name");
		normalColor();
		inFile.open("ITEM.DAT",ios::binary);
		int line=8;
		inFile.read((char*)&a,sizeof(a));
		while(inFile)
		{
			gotoxy(59,line); cprintf("%d",itemNo);
			gotoxy(66,line); cprintf("%s",name);
			line++;
			inFile.read((char*)&a,sizeof(a));
		}
		inFile.close();
		gotoxy(5,lcount);
		cin>>iNo;
		if(iNo==0)
		{
			gotoxy(3,25);
			clreol();
			gotoxy(5,lcount);
			clrBox(5,lcount,10,lcount);
			clrBox(57,5,80,23);
			gotoxy(39,lcount+1);
			cprintf("------------");
			gotoxy(30,lcount+2);
			cprintf("Amount = Rs. ");
			gotoxy(43,lcount+2);
			cout<<setw(6)<<amount;
			gotoxy(39,lcount+3);
			cprintf("------------");
			gotoxy(4,lcount+4);
			whiteColor();
			drawBox(4,lcount+4,54,lcount+6);
			gotoxy(20,lcount+5);
			normalColor();
			cprintf("PLEASE PAY Rs. %.2f",amount);
			getch();
			if(itemK)
			{
				recordBill<<"Bill No. "<<billNo<<'\t'<<time;
				recordBill<<"Amount = Rs. "<<amount<<'\n'<<'\n'<<'\n'<<'\n';
			}
			 else
			 {
				ofstream outFile;
				outFile.open("BILL_NO.TXT");
				outFile<<billNo;
			 }
			return;
		}
		inFile.open("ITEM.DAT",ios::binary);
		inFile.read((char*)&a,sizeof(a));
		boolean found=FALSE;
		while(!inFile.eof() && (!found))
		{
			if(iNo==a.itemNo)
				found=TRUE;
			else
				inFile.read((char*)&a, sizeof(a));
		}
		if(found)
		{
			itemK++;
			gotoxy(12,lcount);
			cprintf("%s",a.name);
			clrBox(57,5,80,23);
			whiteColor();
			drawBox(57,5,80,23);
			gotoxy(58,7);
			whiteColor();
			horLine(58,79);
			gotoxy(59,6);
			line=8;
			yellowColor();
			cprintf("Item#    Qty");
			normalColor();
			gotoxy(60,line); cprintf("%d",itemNo);
			gotoxy(68,line); cprintf("%d",qty);
			do
			{
				gotoxy(27,lcount);
				cin>>sQty;
				if(sQty>qty)
				{
					clrBox(27,lcount,35,lcount);
					cout<<'\a';
				}
			}while(sQty>qty);
			fstream modifyFile;
			modifyFile.open("ITEM.DAT",ios::in | ios::out | ios::binary);
			modifyFile.read( (char*)&a,sizeof(a) );
			found = FALSE;
			int rec = 0;
			while( (!modifyFile.eof()) && (!found) )
			{
				rec++;
				if(iNo == a.itemNo)
				{
					a.qty-=sQty;
					modifyFile.seekg( (rec-1)*sizeof(a),ios::beg);
					modifyFile.write( (char*)&a, sizeof(a) );
					found = TRUE;
				}
				else
					modifyFile.read( (char*)&a, sizeof(a) );
			}
			modifyFile.close();
			gotoxy(35,lcount);
			cout<<setw(6)<<rate;
			price=sQty*rate;
			gotoxy(43,lcount);
			cout<<setw(6)<<price;
			amount+=price;
			recordBill<<setw(7)<<setiosflags(ios::left)
				 <<setiosflags(ios::fixed)<<sNo;
			recordBill<<setw(18)<<setiosflags(ios::left)
				 <<setiosflags(ios::fixed)<<a.name;
			recordBill<<setw(10)<<setiosflags(ios::left)
				 <<setiosflags(ios::fixed)<<sQty;
			recordBill<<setw(10)<<setiosflags(ios::left)
				 <<setiosflags(ios::fixed)<<a.rate;
			recordBill<<setw(10)<<setiosflags(ios::left)
				 <<setiosflags(ios::fixed)<<price;
			recordBill.put('\n');
			lcount++;
		}
		else
		{
			gotoxy(5,lcount);
			clrBox(5,lcount,10,lcount);
			cout<<'\a';
		}
		inFile.close();
		if(lcount+5==22)
		{
			clrBox(3,5,55,23);
			lcount=8;
		}
	}while(iNo!=0);
}

void Item::report()
{
	ifstream inFile;
	inFile.open("ITEM.DAT",ios::binary);
	if(!inFile)
	{
		clrscr();
		gotoxy(30,12);
		warningColor();
		cprintf("File does not exist!!");
		cout<<'\a';
		delay(500);
		normalColor();
		return;
	}
	inFile.read( (char*)&a, sizeof(a) );
	clrscr();
	gotoxy(30,2);
	headingColor();
	cprintf("ABC STORES MANAGEMENT");
	whiteColor();
	drawMainBox(2,7,79,23);
	gotoxy(34,5);
	headingColor();
	cprintf("STOCK LIST");
	gotoxy(5,8);
	lightgrayColor();
	horLine(5,76);
	gotoxy(6,9);
	lightgreenColor();
	cprintf("Item #.");
	gotoxy(15,9);
	cprintf("Name of the Item");
	gotoxy(47,9);
	cprintf("Qty");
	gotoxy(56,9);
	cprintf("Rate");
	gotoxy(65,9);
	cprintf("Price");
	gotoxy(5,10);
	lightgrayColor();
	horLine(5,76);
	int row = 11;
	while(!inFile.eof())
	{
		if(row==21)
		{
			gotoxy(36,row+1);
			redColor();
			cprintf("Press any key to continue...");
			if(getch()==0x1b)
				return;
			lightcyanColor();
			row=11;
			clrBox(5,11,77,22);
		}
		gotoxy(8,row++);
		a.showRecord();
		inFile.read( (char*)&a,sizeof(a) );
	}
	gotoxy(5,row);
	yellowColor();
	cprintf("-----------------------------END OF REPORT------------------------------");
	gotoxy(8,25);
	cprintf("Press any key to continue...");
	inFile.close();
	getche();
}

void main()
{
	clrscr();
	char option;
	char choice;
	int iNo;
	do{
		clrscr();
		whiteColor();
		drawMainBox(21,5,51,21);
		gotoxy(27,3);
		headingColor();
		cprintf("ABC STORES MANAGEMENT");
		gotoxy(28,6);
		lightgreenColor();
		cprintf("1. Create File");
		gotoxy(28,8);
		cprintf("2. Add Item");
		gotoxy(28,10);
		cprintf("3. Modify Item");
		gotoxy(28,12);
		cprintf("4. Delete Item");
		gotoxy(28,14);
		cprintf("5. Search Item");
		gotoxy(28,16);
		cprintf("6. Billing");
		gotoxy(28,18);
		cprintf("7. Item List");
		gotoxy(28,20);
		cprintf("8. Exit");
		gotoxy(28,23);
		yellowColor();
		cprintf("Enter Option (1-8) : ");
		cin>>option;
		gotoxy(28,23);
		clreol();
		switch(option)
		{
			case '1': a.createFile();
				  break;

			case '2' : do
				  {
					clrBox(36,8,74,23);
					whiteColor();
					drawBoxTwo(36,11,74,23);
					gotoxy(50,9);
					headingColor();
					cprintf("ADD ITEM");
					gotoxy(41,13);
					lightcyanColor();
					cprintf("Item #  To Add : ");
					cin>>iNo;
					a.addItem(iNo);
					gotoxy(39,24);
					yellowColor();
					cprintf("Do You Wish To Add Again (Y/N) ? ");
					cin>>choice;
					gotoxy(37,24);
					clreol();
				 }while(choice=='y'||choice=='Y');
				 break;

			case '3' : do
				   {
					clrBox(36,8,74,23);
					whiteColor();
					drawBoxTwo(36,11,74,23);
					gotoxy(46,9);
					headingColor();
					cprintf("MODIFY ITEM DETAILS");
					gotoxy(41,13);
					lightcyanColor();
					cprintf("Item # To Modify : ");
					cin>>iNo;
					a.Modify(iNo);
					gotoxy(38,24);
					yellowColor();
					cprintf("Do you wish to Modify again (Y/N) ? ");
					cin>>choice;
					gotoxy(38,24);
					clreol();
				  }while(choice=='Y'||choice=='y');
				  break;

			case '4': do
				  {
					clrBox(36,8,74,23);
					whiteColor();
					drawBoxTwo(36,11,74,23);
					gotoxy(50,9);
					headingColor();
					cprintf("REMOVE ITEM");
					gotoxy(38,13);
					lightcyanColor();
					cprintf("Item # To Remove : ");
					cin>>iNo;
					a.removeItem(iNo);
					gotoxy(38,24);
					yellowColor();
					cprintf("Do You Wish To Remove Again (Y/N) ? ");
					cin>>choice;
					gotoxy(38,24);
					clreol();
				 }while(choice=='Y'||choice=='y');
				 break;

			case '5': do
				  {
					clrBox(36,8,72,22);
					whiteColor();
					drawBoxTwo(36,11,72,22);
					gotoxy(48,9);
					headingColor();
					cprintf("SEARCH ITEM");
					gotoxy(38,13);
					lightcyanColor();
					cprintf("Item # To Search : ");
					cin>>iNo;
					a.Search(iNo);
					gotoxy(37,23);
					yellowColor();
					cprintf("Do you wish to search again (Y/N) ? ");
					cin>>choice;
					gotoxy(37,23);
					clreol();
					lightcyanColor();
				 }while(choice=='Y'||choice=='y');
				 break;

			case '6': a.Billing();
				  break;

			case '7': lightcyanColor();
				  a.report();
				  break;

			case '8': clrscr();
				  gotoxy(32,4);
				  cprintf("PROJECT DONE BY :");
				  whiteColor();
				  drawBox(30,6,50,16);
				  lightredColor();
				  gotoxy(35,8);
				  cprintf("T. Aravinth");
				  sound(100);delay(1000);nosound();
				  gotoxy(34,10);
				  cprintf("M. Arul Manoj");
				  sound(200);delay(1000);nosound();
				  gotoxy(35,12);
				  cprintf("N. Dhevakar");
				  sound(300);delay(1000);nosound();
				  gotoxy(37,14);
				  cprintf("S. Vijay");
				  sound(400);delay(1000);nosound();
				  delay(3000);
				  break;

			default:  gotoxy(27,23);
				  cprintf("Enter From 1-8 Please!");
				  sound(500);
				  delay(500);
				  nosound();
				  delay(1000);
				  break;
		}
	}while(option!='8');
}
