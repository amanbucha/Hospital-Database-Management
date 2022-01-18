#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<process.h>

ofstream fout;
ifstream fin,fin1;
fstream fio;

class Admin
{
	public:

	char login_id[10];
	char password[10];

	Admin()
	{
		strcpy(login_id,"admin");
		strcpy(password,"password");
	}
}g_admin;

void initialize()
{
	fout.open("login.dat",ios::noreplace);
	fout.write((char*)&g_admin,sizeof(g_admin));
	fout.close();
}


class Patient
{
	public:

	char name[50];
	char mob_no[11];
	int unique_id;

	void generate_id();

}g_pat;

void Patient::generate_id()
{
	randomize();
	unique_id=random(9000)+1000;
}

class Doctor
{
	public:

	char name[50];
	char mobno[11];
	char specialization;
	int table[2][7];
	Doctor();
	void doc_show_appoint();
	void modify_appoint();
	void day(int);
	void spec();	//Prints specialization

}g_doc;

Doctor::Doctor()
{
	for(int i=0;i<2;i++)
		for(int j=0;j<7;j++)
			table[i][j]=0;
}


void Doctor :: day(int a)
{
	switch(a)
	{
		case 0 : cout<<"Monday"<<endl;
			 break;
		case 1 : cout<<"Tuesday"<<endl;
			 break;
		case 2 : cout<<"Wednesday"<<endl;
			 break;
		case 3 : cout<<"Thursday"<<endl;
			 break;
		case 4 : cout<<"Friday"<<endl;
			 break;
		case 5 : cout<<"Saturday"<<endl;
			 break;
		case 6 : cout<<"Sunday"<<endl;
			 break;
	}
}


void Doctor::doc_show_appoint()
{
	int ctr=0;
	cout<<endl;
	for(int i=0;i<7;i++)
	{
		if(table[0][i]==1)
		{
			Patient pat;
			fin1.open("patient.dat",ios::binary|ios::in);
			while(fin1.read((char*)&pat,sizeof(pat)))
			{
				if(table[1][i]==pat.unique_id)
				{
					cout<<"Name : "<<pat.name<<endl;
					cout<<"Mobile no : "<<pat.mob_no<<endl;
					cout<<"DAY : ";
					day(i);
					cout<<endl;
					ctr++;
					break;
				}
			}
			fin1.close();
		}
	}
	cout<<ctr<<" Appointment found!"<<endl;
}

void Doctor :: spec()
{
	if(specialization=='p'||specialization=='P')
	{
		cout<<"Physician"<<endl;
	}
	else if(specialization=='n'||specialization=='N')
	{
		cout<<"Neurologist"<<endl;
	}
	else if(specialization=='c'||specialization=='C')
	{
		cout<<"Cardiologist"<<endl;
	}
	else if(specialization=='o'||specialization=='O')
	{
		cout<<"Orthopedic"<<endl;
	}

}

void login_page()
{
	char username[50];
	char password[50];
	int flag=0;
	char choice0;
	fin.open("LOGIN.dat",ios::binary|ios::in);
	fin.read((char*)&g_admin,sizeof(g_admin));
	do
	{
		do
		{
			clrscr();
			cout<<"\t\t\t###########################################"<<endl;
			cout<<"\t\t\t#                                         #"<<endl;
			cout<<"\t\t\t#                Welcome!                 #"<<endl;
			cout<<"\t\t\t#    $ This is Health care database $     #"<<endl;
			cout<<"\t\t\t#                                         #"<<endl;
			cout<<"\t\t\t###########################################"<<endl;
			cout<<endl<<endl<<endl<<endl;
			cout<<"Enter 1 to login"<<endl;
			cout<<"Enter 2 to exit"<<endl;
			cin>>choice0;
			if(!(choice0=='1'||choice0=='2'))
			{
				clrscr();
				cout<<"Wrong input"<<endl;
				cout<<"Press any key to try again";
				getch();
			}
		}while(!(choice0=='1'||choice0=='2'));

		if(choice0=='1')
		{
			cout<<"Enter the login Id : "<<endl;
			gets(username);
			cout<<"Enter the password : "<<endl;
			gets(password);
			if(strcmp(username,g_admin.login_id)==0)
			{
				if(strcmp(password,g_admin.password)==0)
					flag=1;
			}
			if(flag==1)
			{
				fin.close();
				return;
			}
			else
			{
				cout<<endl<<"Credentials Mismatch"<<endl<<"Press any key to try again"<<endl;
				getch();
				continue;
			}

		}
		else if(choice0=='2')
		{
			fin.close();
			exit(0);
		}
	}while(1);


}

char admin_menu()
{
	char choice;
	do
	{
		clrscr();
		cout<<"Press 1 to enter in doctor menu"<<endl;
		cout<<"Press 2 to enter in patient menu"<<endl;
		cout<<"Press 3 to logout from Admin"<<endl;
		cin>>choice;
		if(!(choice=='1'||choice=='2'||choice=='3'))
		{
			clrscr();
			cout<<"Invalid choice. Press any key to try again";
			getch();
		}
	}while(!(choice=='1'||choice=='2'||choice=='3'));

	return choice;

}

char doc_menu1()
{
	char choice;
	do
	{
		clrscr();
		cout<<"Press 1 to create a new profile"<<endl;
		cout<<"Press 2 to see an existing profile"<<endl;
		cout<<"Press 3 to move to the previous menu"<<endl;
		cin>>choice;
		if(!(choice=='1'||choice=='2'||choice=='3'))
		{
			clrscr();
			cout<<"Wrong input Press any key to try again"<<endl;
			getch();
		}
	}while(!(choice=='1'||choice=='2'||choice=='3'));


	return choice;
}

void new_doc()
{
	Doctor obj;
	cout<<"Enter name : ";
	gets(obj.name);
	cout<<"Enter mobile no : ";
	gets(obj.mobno);
	do
	{
	cout<<"Enter specializtion as per below table "<<endl<<endl;
	cout<<"Press P for a Physician "<<endl;
	cout<<"Press N for a Neurologist"<<endl;
	cout<<"Press C for a Cardiologist"<<endl;
	cout<<"Press O for an Orthopedic"<<endl;
	cin>>obj.specialization;
	if(!(obj.specialization=='p'||obj.specialization=='P'||obj.specialization=='n'||obj.specialization=='N'||obj.specialization=='c'||obj.specialization=='C'||obj.specialization=='o'||obj.specialization=='O'))
	{
		cout<<endl<<"Wrong input. Press any key to try again "<<endl<<endl;
		getch();
	}
	}while(!(obj.specialization=='p'||obj.specialization=='P'||obj.specialization=='n'||obj.specialization=='N'||obj.specialization=='c'||obj.specialization=='C'||obj.specialization=='o'||obj.specialization=='O'));
	obj.spec();
	fout.open("doctor.dat",ios::binary|ios::app);
	fout.write((char*)&obj,sizeof(obj));
	fout.close();
	g_doc=obj;
	cout<<"Accout successfully saved. Press any key to continue";
	getch();
}

void display_doc()
{
	Doctor doc;
	char check[50];
	int flag=0;

	do
	{
		cout<<"Enter the mobile no :"<<endl;
		gets(check);
		fin.open("doctor.dat",ios::binary|ios::in);
		while(fin.read((char*)&doc,sizeof(doc)))
		{
			if(strcmp(check,doc.mobno)==0)
			{
				flag=1;
				clrscr();
				g_doc=doc;
				break;
			}
		}
		fin.close();
		if(flag==1)
		{
			cout<<"Record found!"<<endl<<endl;
			cout<<"Name : "<<doc.name<<endl;
			cout<<"Mobile no : "<<doc.mobno<<endl;
			cout<<"Specialization : ";
			doc.spec();
			doc.doc_show_appoint();
			cout<<"Press any key to continue "<<endl;
			getch();
		}
		else
		{
			clrscr();
			cout<<"Record not found!"<<endl<<"Press any key to continue ";
			getch();
			clrscr();
			return;
		}
	}while(flag!=1);

}

char pat_menu1()
{
	char choice;
	do
	{
		clrscr();
		cout<<"Press 1 for a new Patient"<<endl;
		cout<<"Press 2 for existing Patient"<<endl;
		cout<<"Press 3 to return to previous menu"<<endl;
		cin>>choice;
		if(!(choice=='1'||choice=='2'||choice=='3'))
		{
			clrscr();
			cout<<"Wrong input. Press any key to try again ";
			getch();
		}
	}while(!(choice=='1'||choice=='2'||choice=='3'));
	return choice;
}

void new_pat()
{
	Patient pat;                       //used to input data in the file
	Patient obj;                       //used to check whether similar Uni_id exists
	int flag;

	fin.open("patient.dat",ios::binary|ios::in);
	cout<<"Enter the name of the patient : ";
	gets(pat.name);
	cout<<"Enter the Mobile Number : ";
	cin>>pat.mob_no;
	while(1)
	{
	flag=0;
	pat.generate_id();
	while(fin.read((char*)&obj,sizeof(obj)))
	{
		if(obj.unique_id==pat.unique_id)
		{
			flag=1;
		}
	}
	if(flag==1)
		continue;
	else
		break;
	}

	fin.close();
	fout.open("patient.dat",ios::binary|ios::app|ios::out);
	fout.write((char*)&pat,sizeof(pat));
	fout.close();
	g_pat=pat;
	clrscr();
	cout<<"Data successfully saved"<<endl;
	cout<<"Press any key to continue";
	getch();
	clrscr();
}

void pat_login()
{
	Patient obj;
	int flag=0;
	char check[11];
	fin.open("patient.dat",ios::binary|ios::in);
	do
	{
	cout<<"Enter your mobile number"<<endl;
	cin>>check;
	while(fin.read((char*)&obj,sizeof(obj)))
	{
		if(strcmp(check,obj.mob_no)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		clrscr();
		cout<<"Record Found!"<<endl<<endl;
		cout<<"Name : "<<obj.name<<endl;
		cout<<"Mobile no : "<<obj.mob_no<<endl<<endl;
		cout<<"Press any key to continue "<<endl;
		g_pat=obj;
		getch();
	}
	else
	{
		clrscr();
		cout<<"Record not found"<<endl<<" Press any key to try again";
		getch();
		clrscr();
	}
	}while(flag!=1);
	fin.close();
}

char pat_menu2()
{
	char choice;
	do
	{
		clrscr();
		cout<<"Press 1 to book a new appointment"<<endl;
		cout<<"Press 2 to show existing appointment"<<endl;
		cout<<"Press 3 to cancel an appointment"<<endl;
		cout<<"Press 4 to modify your details"<<endl;
		cout<<"Press 5 to Logout"<<endl;
		cin>>choice;
		if(!(choice=='1'||choice=='2'||choice=='3'||choice=='4'||choice=='5'))
		{
			clrscr();
			cout<<"Wrong input. Press any key to try again ";
			getch();
		}
	}while(!(choice=='1'||choice=='2'||choice=='3'||choice=='4'||choice=='5'));
	return choice;
	}

void new_app()
{
	char spec;
	Doctor doc;
	int flag=0;
	long pos;
	do
	{
		cout<<"Enter the specialist you would like to book an appointment with"<<endl<<endl;
		cout<<"Press P for a Physician "<<endl;
		cout<<"Press N for a Neurologist"<<endl;
		cout<<"Press C for a Cardiologist"<<endl;
		cout<<"Press O for an Orthopedic"<<endl;
		cin>>spec;
		if(!(spec=='p'||spec=='P'||spec=='n'||spec=='N'||spec=='c'||spec=='C'||spec=='o'||spec=='O'))
		{
			cout<<"Wrong input. Press any key to try again "<<endl;
			getch();
		}
	}while(!(spec=='p'||spec=='P'||spec=='n'||spec=='N'||spec=='c'||spec=='C'||spec=='o'||spec=='O'));
	int i;
	for(i=0 ;i<7;i++)
	{
		fio.open("doctor.dat",ios::binary|ios::in|ios::out);
		while(fio.read((char*)&doc,sizeof(doc)))
		{
			pos=fio.tellg();
			if(tolower(doc.specialization)==tolower(spec))
			{
				if(doc.table[0][i]==0)
				{
					doc.table[0][i]=1;
					doc.table[1][i]=g_pat.unique_id;
					fio.seekp(pos-sizeof(doc));
					fio.write((char*)&doc,sizeof(doc));
					flag=1;

				}
			}
			if(flag==1)
			{
				break;
			}
		}
		fio.close();
		if(flag==1)
			break;
	}
	if(flag==1)
	{
		cout<<"Your appointment has been successfully booked with "<<doc.name<<" on ";
		doc.day(i);
	}
	else
	{
		cout<<"Currently all slots are booked"<<endl;
	}
}

void pat_show_app()
{
	Doctor doc;
	int ctr=0;
	fin.open("doctor.dat",ios::binary|ios::in);
	while(fin.read((char*)&doc,sizeof(doc)))
	{
		for(int i=0;i<7;i++)
		{
			if(doc.table[0][i]==1)
			{
				if(doc.table[1][i]==g_pat.unique_id)
				{
					ctr++;
					cout<<"Name of the doctor :"<<doc.name<<endl;
					cout<<"Day of the appointment :";
					doc.day(i);
					cout<<endl;
				}
			}
		}
	}
	cout<<"You have booked "<<ctr<<" appointments"<<endl;
	fin.close();
}

void pat_cancel_app()
{
	int ctr1=0,ctr2=0;
	int pos;
	Doctor doc;
	char choice;

	fio.open("doctor.dat",ios::binary|ios::in|ios::out);
	clrscr();
	while(fio.read((char*)&doc,sizeof(doc)))
	{
		pos=fio.tellg();
		for(int i=0;i<7;i++)
		{
			if(doc.table[0][i]==1)
			{
				if(doc.table[1][i]==g_pat.unique_id)
				{
					ctr1++;
					do
					{
						clrscr();
						cout<<"Name of the doctor :"<<doc.name<<endl;
						cout<<"Day of the appointment :";
						doc.day(i);
						cout<<endl<<"Do you want to cancel this appointment(y/n)";
						cin>>choice;
						if(!(choice=='y'||choice=='Y'||choice=='n'||choice=='N'))
						{
							clrscr();
							cout<<"Wrong input.Press any key to try again";
							getch();
						}
					}while(!(choice=='y'||choice=='Y'||choice=='n'||choice=='N'));
					if(choice=='y'||choice=='Y')
					{
						doc.table[0][i]=0;
						fio.seekg(pos-sizeof(doc));
						fio.write((char*)&doc,sizeof(doc));
						g_doc=doc;
						ctr2++;
					}
				}
			}
		}

	}
	if(ctr1==0)
	{
		clrscr();
		cout<<"You Do not have any appointment"<<endl;
		cout<<"Press any key to return to previous menu";
		getch();
		fio.close();
		return;
	}
	clrscr();
	cout<<"You had "<<ctr1<<"appointment"<<endl;
	cout<<"You have deleted "<<ctr2<<"appointment"<<endl;
	clrscr();
	cout<<"Press any key to return to the previous menu ";
	getch();
	fio.close();

}

void pat_mod_info()
{
	clrscr();
	int flag=0,pos=0;
	Patient obj;

	cout<<"Your current info is : "<<endl;
	cout<<"Name : "<<g_pat.name<<endl;
	cout<<"Mobile no : "<<g_pat.mob_no<<endl;
	cout<<"Press 1 to enter new details"<<endl;
	cout<<"Press any other key to keep the orignal details"<<endl;
	cin>>flag;

	if(flag==1)
	{
		clrscr();
		cout<<"Enter new name : ";
		gets(g_pat.name);
		cout<<"Enter new Phone no : ";
		gets(g_pat.mob_no);
		fio.open("patient.dat",ios::out|ios::in|ios::binary);
		while(fio.read((char*)&obj,sizeof(obj)))
		{
			pos=fio.tellg();
			if(g_pat.unique_id==obj.unique_id)
			{
				fio.seekp(pos-sizeof(obj));
				fio.write((char*)&g_pat,sizeof(g_pat));
				clrscr();
				cout<<"Your info was successfully Updated."<<endl;
				cout<<"Press any key to continue. ";
				getch();
				break;
			}
		}
		fio.close();
	}


}

void main()
{
	clrscr();
	char choice0;
	char choice1;
	char choice_admin;
	char choice_doc;
	char choice_pat;

	initialize();
	do
	{
		login_page();
		do
		{
			clrscr();
			choice_admin=admin_menu();
			if(choice_admin=='1')
			{
				do
				{
					clrscr();
					choice_doc=doc_menu1();
					clrscr();
					if(choice_doc=='1')
					{
						new_doc();
					}
					else if(choice_doc=='2')
					{
						display_doc();
					}
					else if(choice_doc=='3')
					{
						break;
					}
				}while(1);
			}

			if(choice_admin=='2')
			{
				do
				{
					clrscr();
					choice_pat=pat_menu1();
					if(choice_pat=='1')
					{
						new_pat();
					}
					else if(choice_pat=='2')
					{
						pat_login();
					}
					else
					{
						break;
					}

					do
					{
						clrscr();
						choice_pat=pat_menu2();
						if(choice_pat=='1')
						{
							new_app();
							getch();
						}
						else if(choice_pat=='2')
						{
							pat_show_app();
							getch();
						}
						else if(choice_pat=='3')
						{
							pat_cancel_app();
						}
						else if(choice_pat=='4')
						{
							pat_mod_info();
							getch();
						}
						else if(choice_pat=='5')
						{
							break;
						}
					}while(1);
				}while(1);
			}
			if(choice_admin=='3')
				break;
		}while(1);
	}while(1);
}
