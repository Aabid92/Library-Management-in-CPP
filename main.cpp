#include <iostream>
#include<stdio.h>
#define clrscr() system("cls");
#include<conio.h>
#include <windows.h>
#include <mysql.h>
#include<string>
#include <iomanip>
#include <locale>
#include <sstream>

using namespace std;

class member
{
public:
    string m_code;
    string m_phone;
	string m_name;
	string m_address;
	string m_course;
    void add_member();
    void update_member();
};

void member::add_member()
{
	cout<<"\n\tMember Code: " ;
    cin>>m_code;
    cout<<"\n\tMember Name: ";
    cin>>m_name;
    cout<<"\n\tCourse Name : " ;
    cin>>m_course;
    cout<<"\n\tAddress: " ;
    cin>>m_address;
    cout<<"\n\tMobile No: " ;
    cin>>m_phone;
}
void member::update_member()
{
	cout<<"\n\nEnter The Name of The Member : ";
	cin>>m_name;
	cout<<"\nEnter Course Name: ";
	cin>>m_course;
    cout<<"\nEnter Mobile Number: ";
	cin>>m_phone;
}

class book
{
public:
    string b_code;
    string b_name;
    string b_author;
    string b_price;
    string b_copies;
    void add_book();
};

void book::add_book()
{
	cout<<"\n\tEnter Book Code: " ;
    cin>>b_code;
    cout<<"\n\tEnter Book Name: ";
    cin>>b_name;
    cout<<"\n\tEnter Author Name : " ;
    cin>>b_author;
    cout<<"\n\tBook Price: Rs- " ;
    cin>>b_price;
    cout<<"\n\tNo OF Copies: " ;
    cin>>b_copies;
}



//Function Declaration
void intro();
void write_member();
void connectdb();
void modify_member(string num);
void delete_member(string num);
void detail_member(string num);
void write_book();
void detail_book(string num);
void issue_book(string num);
void return_book(string num);



// MAIN FUNCTION
int main()
{

	char ch;
    string num;
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\t\t\t\tMAIN MENU";
		cout<<"\n\n\t01. ADD NEW MEMBER";
		cout<<"\n\n\t02. UPDATE MEMMBER DETAIL";
		cout<<"\n\n\t03. DELETE MEMBER INFORMATION";
		cout<<"\n\n\t04. DETAILS OF MEMBER";
		cout<<"\n\n\t05. ADD NEW BOOK";
		cout<<"\n\n\t06. DETAILS OF BOOKS";
		cout<<"\n\n\t07. ISSUE BOOK";
		cout<<"\n\n\t08. RETURN BOOK";
		cout<<"\n\n\t09. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
		case '1':
		    write_member();
			break;
		case '2':
			cout<<"\n\n\tEnter The Member code : "; cin>>num;
			modify_member(num);
			break;
		case '3':
			cout<<"\n\n\tEnter The Member code : "; cin>>num;
			delete_member(num);
			break;
		case '4':
			cout<<"\n\n\tEnter The Member code : "; cin>>num;
			detail_member(num);
			break;
		case '5':
			write_book();
			break;
		 case '6':
			cout<<"\n\n\tEnter The Book Code : "; cin>>num;
            detail_book(num);
			break;
        case '7':
			cout<<"\n\n\tEnter The Book Code : "; cin>>num;
			issue_book(num);
			break;
        case '8':
			cout<<"\n\n\tEnter The Book Code : "; cin>>num;
			return_book(num);
			break;
		 case '9':
			cout<<"\n\n\tThanks for using Library management system";
			break;
		 default :cout<<"\a";
		}
		getch();
    }while(ch!='9');
	return 0;
}


// BOOK ISSUE
void issue_book(string b_code)
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    string bn;
    int qstate, a;
    conn = mysql_init(0);
    if(conn)
        cout<<"connection object ok, conn="<<conn<<endl;
    else
        cout<<"conn object problem: "<<mysql_error(conn);

    conn = mysql_real_connect(conn,"localhost","root","","lms",0,NULL,0);
    string query="select * from book where code='"+b_code+"'";
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
                a=atoi(row[4]);
                cout<<a;
            }
        }
        if(a>0)
        {
        cout<<"Enter the No of Copies Required : ";
        int dep;
        cin>>dep;
        a-=dep;
        ostringstream convert;
        convert << a;
        bn = convert.str();
         if(conn)
        {
        string query="UPDATE book SET copies='"+bn+"' WHERE code='"+b_code+"'";
        const char* q = query.c_str();
        int qstate = mysql_query(conn,q);
          if(!qstate)
            cout<<"Book Issued successfully..."<<endl;
        else
            cout<<"query problem: "<<mysql_error(conn)<<endl;

        }
        }
        else{
            cout<<"Out of Stock";

        }


    mysql_close(conn);
}


// RETURN BOOK
void return_book(string b_code)
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    int qstate, a;
    conn = mysql_init(0);
    if(conn)
        cout<<"connection object ok, conn="<<conn<<endl;
    else
        cout<<"conn object problem: "<<mysql_error(conn);

    conn = mysql_real_connect(conn,"localhost","root","","lms",0,NULL,0);
    string query="select * from book where code='"+b_code+"'";
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
                a=atoi(row[4]);
            }
        }
        cout<<"\n\nEnter The No of Book To Return";
        int dep;
        cin>>dep;
        a+=dep;
        string bn;
        ostringstream convert;
        convert << a;
        bn = convert.str();
        if(conn)
        {
        string query="UPDATE book SET copies='"+bn+"' WHERE code='"+b_code+"'";
        const char* q = query.c_str();
        int qstate = mysql_query(conn,q);
          if(!qstate)
            cout<<"Book Return successfully..."<<endl;
        else
            cout<<"query problem: "<<mysql_error(conn)<<endl;

    }
    mysql_close(conn);
}


// DELETE MEMBER
void delete_member(string m_code)
{
    MYSQL* conn;
	   conn = mysql_init(0);
    if(conn)
        cout<<"connection object ok, conn="<<conn<<endl;
    else
        cout<<"conn object problem: "<<mysql_error(conn);

    conn = mysql_real_connect(conn,"localhost","root","","lms",0,NULL,0);

	if(conn)
    {
        string query="DELETE FROM member WHERE code='"+m_code+"'";
        const char* q = query.c_str();
        //cout<<"query is: "<<q<<endl;
        int qstate = mysql_query(conn,q);
          if(!qstate)
            cout<<" Member Information Deleted"<<endl;
        else
            cout<<"query problem: "<<mysql_error(conn)<<endl;

    }
    mysql_close(conn);

}

// DETAILS OF MEMBER
void detail_member(string m_code)
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    int qstate;
    conn = mysql_init(0);
    if(conn)
        cout<<"connection object ok, conn="<<conn<<endl;
    else
        cout<<"conn object problem: "<<mysql_error(conn);

    conn = mysql_real_connect(conn,"localhost","root","","lms",0,NULL,0);
    string query="select * from member where code='"+m_code+"'";
        const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
                cout<<"Member Name: "<<row[1]<<endl<<"Course: "<<row[2]<<endl<<"Address: "<<row[3]<<endl<<"Phone No: "<<row[4]<<endl;
            }
        }
        mysql_close(conn);
}

//WRITE MEMBER
void write_member()
{
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
	member m;
	   conn = mysql_init(0);
    if(conn)
        cout<<"connection object ok, conn="<<conn<<endl;
    else
        cout<<"conn object problem: "<<mysql_error(conn);

    conn = mysql_real_connect(conn,"localhost","root","","lms",0,NULL,0);
	m.add_member();
	if(conn)
    {
        string query="INSERT INTO member(code,name,course,address,phone) VALUES('"+m.m_code+"','"+m.m_name+"','"+m.m_course+"','"+m.m_address+"','"+m.m_phone+"')";

        const char* q = query.c_str();
        int qstate = mysql_query(conn,q);
        if(!qstate)
            cout<<"Record Inserted Successfully..."<<endl;
           else
            cout<<"query problem: "<<mysql_error(conn)<<endl;
    }
        mysql_close(conn);
}

//MODIFY MEMBER DETAIL
void modify_member(string m_code)
{
    MYSQL* conn;
    member m;
    conn = mysql_init(0);
    if(conn)
        cout<<"connection object ok, conn="<<conn<<endl;
    else
        cout<<"conn object problem: "<<mysql_error(conn);

    conn = mysql_real_connect(conn,"localhost","root","","lms",0,NULL,0);
	m.update_member();
	if(conn)
    {
        string query="UPDATE member SET name='"+m.m_name+"',course='"+m.m_course+"',phone='"+m.m_phone+"' WHERE code='"+m_code+"'";
        const char* q = query.c_str();
        int qstate = mysql_query(conn,q);
          if(!qstate)
            cout<<"Record Updated Successfully..."<<endl;
        else
            cout<<"query problem: "<<mysql_error(conn)<<endl;

    }
    mysql_close(conn);
}

//WRITE BOOK
void write_book()
{
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
	book b;
	   conn = mysql_init(0);
    if(conn)
        cout<<"connection object ok, conn="<<conn<<endl;
    else
        cout<<"conn object problem: "<<mysql_error(conn);

    conn = mysql_real_connect(conn,"localhost","root","","lms",0,NULL,0);
	b.add_book();
	if(conn)
    {
        string query="INSERT INTO book(code,name,author,price,copies) VALUES('"+b.b_code+"','"+b.b_name+"','"+b.b_author+"','"+b.b_price+"','"+b.b_copies+"')";
        const char* q = query.c_str();
        int qstate = mysql_query(conn,q);
        if(!qstate)
            cout<<"Record Inserted Successfully..."<<endl;
           else
            cout<<"query problem: "<<mysql_error(conn)<<endl;
    }
        mysql_close(conn);
}

// DETAILS OF BOOK
void detail_book(string b_code)
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    int qstate;
    conn = mysql_init(0);
    if(conn)
        cout<<"connection object ok, conn="<<conn<<endl;
    else
        cout<<"conn object problem: "<<mysql_error(conn);

    conn = mysql_real_connect(conn,"localhost","root","","lms",0,NULL,0);
    string query="select * from book where code='"+b_code+"'";
        const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
                cout<<"Book Name: "<<row[1]<<endl<<"Author Name: "<<row[2]<<endl<<"Price : "<<row[3]<<endl<<"No of Copies: "<<row[4]<<endl;
            }
        }
        mysql_close(conn);
}

//    	INTRODUCTION FUNCTION
void intro()
{
    cout<<"\t\t______________________________________________________";
	cout<<"\n\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
	cout<<"\n\t\t______________________________________________________";
	cout<<"\n\n\t\t\t\t\t--BY--";
	cout<<"\n\n\t\t\tROLL NO\t\t\tNAME";
	cout<<"\n\t\t-------------------------------------------------------";
	cout<<"\n\t\t\t77\t\t-->\t AABID SHAIKH";


	getch();
}


