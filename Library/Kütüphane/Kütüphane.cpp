// Kütüphane.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;


class student
{
private :
	string name;
	string department;
	string id;
	int year;

public:
	student(){}
	student(string n,string ID,string dep,int y)
	{
		name=n;
		department=dep;
		id=ID;
		year=y;
	}
void setAll(string n,string ID,string dep,int y)
{
		name=n;
		department=dep;
		id=ID;
		year=y;
}
void print()
{
	cout<<"Name        : "<<name<<endl;
	cout<<"Department  : "<<department<<endl;
	cout<<"ID          : "<<id<<endl;
	cout<<"Birth Year  : "<<year<<endl;
}
string getId( )
{
	return id;
}
};


class book
{
private :
	string name;
	string id;
	string author;
	string available;
public:
	book(){}
	book(string n,string ID,string a,string av)
	{
		name=n;
		id=ID;
		author=a;
		available=av;
	}
void setAll(string n,string ID,string a,string av)
{
		name=n;
		id=ID;
		author=a;
		available=av;
}
void print()
{
	cout<<"Name        : "<<name<<endl;
	cout<<"Author      : "<<author<<endl;
	cout<<"ID          : "<<id<<endl;
	cout<<"Available   : "<<available<<endl;
}
string getId( )
{
	return id;
}
string getAva( )
{
	return available;
}
void setAv(string avai)
{
	available=avai;
}
};


class borrow
{
private :
	string id;
	string bookID;
public:
	borrow(){}
	borrow(string ID,string bid)
	{
		id=ID;
		bookID=bid;
	}
void setAll(string ID,string bid)
{
		id=ID;
		bookID=bid;
}
void print()
{
	cout<<"id        : "<<id<<endl;
	cout<<"book id   : "<<bookID<<endl;
}
string getId( )
{
	return id;
}
string getsId( )
{
	return bookID;
}
};


void loadBook(vector<book> &b)
{
	ifstream myFile;
	string temp,name,id,aut,av;
	int pos,pos2,pos3;
	int x=0;
	myFile.open("book.txt");
	while(!myFile.eof())
	{
		getline(myFile,temp);
		pos=temp.find(':');
		name=temp.substr(0,pos);
		pos2=temp.find(':',pos+1);
		id=temp.substr(pos+1,pos2-pos-1);
		pos3=temp.find(':',pos2+1);
		aut=temp.substr(pos2+1,pos3-pos2-1);
		av=temp.substr(pos3+1,temp.size()-pos3);
		b[x].setAll(name,id,aut,av);
		x++;
	}
}


void loadBorrow(vector<borrow>&bor)
{
	ifstream myFile;
	string temp,id,bid;
	int pos,pos2;
	int x=0;
	myFile.open("borrow.txt");
	while(!myFile.eof())
	{
		getline(myFile,temp);
		pos=temp.find(':');
		id=temp.substr(0,pos);
		pos2=temp.find(':',pos+1);
		bid=temp.substr(pos+1,temp.size()-pos);
		bor[x].setAll(id,bid);
		x++;
	}

}


void loadStu(vector<student>&stu)
{
	ifstream myFile;
	string temp,name,id,dep,y;
	int year,pos,pos2,pos3;
	int x=0;
	myFile.open("student.txt");
	while(!myFile.eof())
	{
		getline(myFile,temp);
		pos=temp.find(':');
		name=temp.substr(0,pos);
		pos2=temp.find(':',pos+1);
		id=temp.substr(pos+1,pos2-pos-1);
		pos3=temp.find(':',pos2+1);
		dep=temp.substr(pos2+1,pos3-pos2-1);
		y=temp.substr(pos3+1,temp.size()-pos3);
		year=atoi(y.c_str());
		stu[x].setAll(name,id,dep,year);
		x++;
	}
	//for(int i=0;i<x;i++)
		//stu[i].print();
}


int isExist(string id, vector<student> & stu)
{
	int x;
	x=stu.size();
	for(int i=0;i<x;i++)
		if(id==stu[i].getId())
			return 1;
	return 0;
}


int isAvaiable(string id, vector<book> & b)
{
	int x;
	x=b.size();
	for(int i=0;i<x;i++)
		if(id==b[i].getId())
			return 1;
	return 0;
}


int printAv(string id, vector<book> & b,int ava)
{
	int x;
	x=b.size();
	for(int i=0;i<x;i++)
	{
		if(id==b[i].getId())
		{
			if(ava>0)
			b[i].print();
			return 1;
		}
	}
	cout<<"There is no this book.\n";
	return 0;
}


int countBorrow(vector<borrow> &bor,string stuId)
{
	int count=0;
	int x=bor.size();
	for(int i=0;i<x;i++)
	{
		if(bor[i].getId()==stuId)
			count++;
		
	}
	//cout<<"Ögrencideki ödünç alýnan kitap sayýsý : "<<count;
	return count;
}


int controltwobooks(vector<borrow> &bor,string stuId,string bookid)
{
	int x=bor.size();
	for(int i=0;i<x;i++)
	{
		if(bor[i].getId()!=stuId && bor[i].getsId()!=bookid)
			return 1;
		else
			return 0;
	}
}


void borrowBook(string ID,string id,vector<borrow> & bor)
{
	if(controltwobooks(bor,id,ID))
	{
		int x=5;
		ofstream myFile;
		myFile.open("borrow.txt",ios::app);
		bor[x].setAll(ID,id);
		myFile<<ID<<":"<<id<<endl;
		myFile.close();
	}
	else
		cout<<"bu adamda ayný kitap var"<<endl;
}


void menu()
{
	cout<<"\n\nWhat Do You Want ?"
		<<"\n\nAdd Student    --> 1"
		<<"\n\nAdd Book       --> 2"
		<<"\n\nAdd Borrow     --> 3"
		<<"\n\nDelete Student --> 4"
		<<"\n\nDelete Book    --> 5"
		<<"\n\nUpdate Student --> 6"
		<<"\n\nUpdate Book    --> 7"
		<<endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*ofstream myFile;
	myFile.open("student.txt",ios::app);
	ofstream myFileBook;
	myFileBook.open("book.txt",ios::app);
	ofstream myFileBor;
	myFileBor.open("borrow.txt",ios::app);*/
	int x=5;
	int r=0,year;
	string name,id,dep,y,del,sil;
	string Bname,Bid,aut,av;
	string ava;
	int avai;
	vector<student>stu;
	vector<book>b;
	vector<borrow>bor;
	stu.resize(10);
	b.resize(10);
	bor.resize(10);
	loadStu(stu);
	loadBook(b);
	loadBorrow(bor);
	size_t found;
	while(r<8)
	{
		menu();
		cin>>r;
		if(r==1)
		{
			ofstream myFile;
			myFile.open("student.txt",ios::app);
			do
			{
				cout<<"Please insert name"<<endl;
				cin>>name;
				cout<<"Please insert department"<<endl;
				cin>>dep;
				cout<<"Please insert number"<<endl;
				cin>>id;
				cout<<"Please insert year"<<endl;
				cin>>y;
				year=atoi(y.c_str());
				x=x+1;
			}
			while(isExist(id,stu));
		
			stu[x].setAll(name,id,dep,year);
			//stu[x].print();
			myFile<<"\n"<<name<<":"<<dep<<":"<<id<<":"<<year<<endl;
			myFile.close();
		}
		if(r==2)
		{
			ofstream myFileBook;
			myFileBook.open("book.txt",ios::app);
			do
			{
				cout<<"\nPlease insert name"<<endl;
				cin>>Bname;
				cout<<"Please insert number"<<endl;
				cin>>Bid;
				cout<<"Please insert author"<<endl;
				cin>>aut;
				cout<<"avaiable"<<endl;
				cin>>av;
				x=x+1;
				if(isAvaiable(Bid,b))
				cout<<"\n\n!!!There is a book which has this id";
			}
			while(isAvaiable(Bid,b));
		
			b[x].setAll(Bname,Bid,aut,av);
			//b[x].print();
			myFileBook<<"\n"<<Bname<<":"<<Bid<<":"<<aut<<":"<<av<<endl;
			myFileBook.close();
		
		}
		if(r==3)
		{
			cout<<"Please insert book number"<<endl;
			cin>>Bid;
			b[x].setAv(ava);
			avai=atoi(ava.c_str());
			if(printAv(Bid,b,avai))
			{
				cout<<"Enter the student ID\n";
				cin>>id; 
				if(countBorrow(bor,id)<3)
				{
					borrowBook(Bid,id,bor);
					avai--;
				}
				else
				   cout<<"Student can not borrow more than 3 books\n";

			}
			else
				cout<<"Book is not available\n";

		}
		//if(r==4)
		//if(r==5)
		//if(r==6)
		//if(r==7)
	}
	system("PAUSE");
	return 0;
}