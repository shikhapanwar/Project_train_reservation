#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 300
#define no_of_trains 20

/*File 1 made by Esha Lath */
struct train_info{
int train_no;
char train_name[50];
char from[50];                   /*for file 1*/
char dep_time[10];
char to[50];
char arr_time[10];
int day;
};



struct seat_info
{
	int occupied;     /*contains 0 or 1*/
	int pnr;
	char pass_name[40];
	int age;
	char gender;

};

/*File 2 made by Shikha Panwar(15MA20039)*/
struct train_info_extended
{	int train_no;
	struct seat_info info_1a[7][max_size+1];
	struct seat_info info_2a[7][max_size+1];                     /*for file2*/
	struct seat_info info_3a[7][max_size+1];
	int seat_occ_1a[7];
	int seat_occ_2a[7];
	int seat_occ_3a[7];
};

void reserve();         //this function is for reservation of the passenger in a train
void seats_available( int train_no, int coach, int date) ;
int book(int no_of_tickets, int train_no, int class, int date);
int cancel();
void print_cancellation_details(struct seat_info passenger);

/*reserve function made AND debugged by Shikha Panwar (15MA20039)*/
void reserve()
{struct train_info train;
	char source[20];        //getting source station
	char destination[20]; 
	char ch;
	int date,coach, train_no, class;
	int temp, no_of_tickets;
		printf("\nEnter Source\n\n");
		printf(" \tkgp\tKharagpur\n\t ndls\tNew Delhi\n \tcstm\tMumbai\n\t jp\tJaipur\n");
		
		while(1)
			{scanf("%s",source);
				if(strcmp(source,"hwh")==0 || strcmp(source,"ndls")==0 || strcmp(source,"cstm")==0 || strcmp(source,"kgp")==0 || strcmp(source,"jp")==0)
				{
					break;
				}
				else{
					printf("\nIncorrect station code.   Kindly enter correct source code\n");
				}
			}
		printf("\nEnter Destination\n");
		while(1)
		{
			scanf("%s",destination);
			if(strcmp(destination,"hwh")==0 || strcmp(destination,"ndls")==0 || strcmp(destination,"cstm")==0 || strcmp(destination,"kgp")==0 ||strcmp(destination,"jp")==0)
				{
					break;
				}
				else{
					printf("\nIncorrect station code, Kindly enter correct station code\n");
				}
		}
		
		FILE *fp=fopen("file_1.dat","r");

	if(fp==NULL){printf("Cannot open file\n"); return;}
	
	while(fread(&train,sizeof(train),1,fp)==1)
	{if(strcmp(train.from,source)==0 && strcmp(train.to, destination)==0)
		{train_no=train.train_no;
			printf("\n\n\t\tThe train available is :\n\t  TRAIN NO:\t %d\n \tTRAIN NAME: \t%s\n\t    SOURCE:\t %s\n \tDESTINATION: \t%s\n \tDeparture TIME:    %s\n\t ARRIVAL TIME: \t %s on day %d\n\n",train.train_no,train.train_name,train.from,train.to,train.dep_time ,train.arr_time, train.day);
			break;
		}
	}
	fclose(fp);

	printf("Enter date between 1 to 7 Aug \n(kindly enter the date in integer)\n");
	scanf("%d",&date);

	while(1)
	{
			printf("\nEnter class to check seat availabilty\n");

			while(1)
				{	printf("1. First AC\n");
					printf("2. Second AC\n");
					printf("3.Third AC\n");
					scanf("%d",&coach);
					if(coach==1 || coach==2 || coach==3)
					{
						break;
					}
					else {printf("Enter correct class no \n");
					}
			    }
		seats_available(train_no, coach, date);
		
		printf("Do you wish to know the seat availabilty in other classes? (Y/N   :  )\n(Enter Y to check availabilty in other coach & N to book ticket or exit)?\n");
		fflush(stdin);
		scanf(" %c",&ch);
		if(tolower(ch)=='y')
		{
			continue;
		}
		else{
			break;
			}
	}

	
		while(1)
			{	printf("\nDo you wish to continue booking? \n 1-Yes\n2-No, exit to main menu\n(enter 1/2)  ");
				scanf("%d",&temp);
				if(temp==2)
				{
					return;
				}
				else if(temp==1)
				{
					printf("Enter no. of tickets (in integer): ");
					scanf("%d",&no_of_tickets);
					printf("\nEnter class\n");
					while(1)
					{
							printf("1. First AC\n");
							printf("2. Second AC\n");
							printf("3.Third AC\n");
							scanf("%d",&class);
							fflush(stdin);	
							if(class==1 || class==2 || class==3)
							{
								break;
							}
							else{printf("Invalid input, please enter 1 or 2 or 3\n");}
					}
					if(book(no_of_tickets,train_no,class, date)==0)
						{printf("\nBooking successful\n");
						printf("Thank You for booking \n");
						}
					else{printf("Booking unsuccessful\n");}
					return;
					
				}
				else{printf("\nInvalid value, Enter 1 or 2\n");}
			}
return;

}
/*seats_available function made AND debugged by Shikha Panwar (15MA20039)*/

void seats_available(int train_no, int coach, int date)   // printsthe available seat in that coach  on that date
{struct train_info_extended train;
	
	FILE *fp=fopen("file_2.dat","r");
	if(fp==NULL){printf("Cannot open file\n"); return;}
	
	switch(coach)
	{
		case 1:while(fread(&train,sizeof(train),1,fp)==1)
			{

				if(train.train_no==train_no)
				{
					printf("\nSeats available=%d\n\n", (max_size-train.seat_occ_1a[date-1]));
					fclose(fp); 
					return;
				}
			}
			
		break;

		case 2:while(fread(&train,sizeof(train),1,fp)==1)
			{if(train.train_no==train_no)
				{
					printf("\nSeats available=%d\n\n",(max_size- train.seat_occ_2a[date-1]));
					fclose(fp); 
					return;
				}

			}
		break;

		case 3:while(fread(&train,sizeof(train),1,fp)==1)
			{if(train.train_no==train_no)
				{
					printf("\nSeats available=%d\n\n", (max_size - train.seat_occ_3a[date-1]));
					fclose(fp); 
					return;
				}

			}
		break;

		default: printf("\nWrong input values\n");
		
	}
}


/*bookfunction made AND debugged by Shikha Panwar (15MA20039)*/
int book(int no_of_tickets, int train_no, int class, int date)
			{char name[40];int c;


				FILE *ft=fopen("ticket.txt","w");
				if(ft==NULL){printf("Cannot open file"); return;}
				struct train_info train_type1;
				FILE *f_file1=fopen("file_1.dat","r");
				if(f_file1==NULL){printf("Cannot open file"); return;}
				while(fread(&train_type1,sizeof(train_type1),1,f_file1)==1)
						{
							if(train_type1.train_no==train_no)
							{
								break;
							}
						}
				fclose(f_file1);
				fprintf(ft, "\t %s - %d\n", train_type1.train_name,train_type1.train_no);
				fprintf(ft, "Serial no.\tPNR\tName\tAge\tGender\tSeat No.\n");
				FILE *fp=fopen("file_2.dat","r");
				if(fp==NULL){printf("Cannot open file"); return;}
				struct train_info_extended tr[no_of_trains], train;
				int index[no_of_tickets];
				int l=0, i=0, j, k;
				if(fp==NULL){printf("Cannot open file"); return;}
switch(class)
{
	case 1: {			while(fread(&train,sizeof(train),1,fp)==1)
				{ 
					tr[i]=train;
					
					if(tr[i].train_no==train_no)
					{
						if(max_size- train.seat_occ_1a[date-1]<no_of_tickets)
						{
							printf("Sorry enough seats not available\n");
							return;
						}
						for(j=0;j<no_of_tickets;j++)
						{
							for(k=1;k<=max_size;k++)
							{
								if(tr[i].info_1a[date-1][k].occupied==0)
								{	tr[i].info_1a[date-1][k].occupied=1;
									printf("\n\nEnter details of passenger %d\n",j+1);
									
									printf("\nEnter name of passenger %d\n",j+1);
									
									do{
									    c = getchar();
									}while(c != EOF && c != '\n');
									fgets(tr[i].info_1a[date-1][k].pass_name, 40, stdin);
									tr[i].info_1a[date-1][k].pass_name[strcspn(tr[i].info_1a[date-1][k].pass_name, "\n")] = '\0';
									fflush(stdin);
									printf("\nEnter age of passenger %d\n",j+1);
									scanf("%d",&tr[i].info_1a[date-1][k].age);
									fflush(stdin);
									printf("\nEnter gender of passenger %d(F/M)\n",j+1);
									scanf(" %c",&tr[i].info_1a[date-1][k].gender);
									fprintf(ft, "%d\t%s\t%d\t%c\t%d\n",j+1, tr[i].info_1a[date-1][k].pass_name, tr[i].info_1a[date-1][k].age, tr[i].info_1a[date-1][k].gender, k);
									index[l++]=k;
									tr[i].seat_occ_1a[date-1]++;
									break;
								}
							}
						}
						for(l=0;l<no_of_tickets;l++)
							{tr[i].info_1a[date-1][index[l]].pnr=index[0]+train_no*1000+class*100000000; 
								printf("pnr=%d\n",tr[i].info_1a[date-1][index[l]].pnr);
								fprintf(ft, "\nPNR= %d", tr[i].info_1a[date-1][index[l]].pnr);
							}
					}
					i++;
				}

				fclose(fp);


				FILE *fs=fopen("file_2.dat", "w");


				if(fs==NULL){printf("Cannot open file"); return;}
				for(i=0;i<no_of_trains;i++)
				{fwrite(&tr[i],sizeof(train),1,fs);
				}
				fclose(fs);
				fclose(ft);
				return 0;
			}


case 2: {			while(fread(&train,sizeof(train),1,fp)==1)
				{
					tr[i]=train;
					if(tr[i].train_no==train_no)
					{
						if(max_size- train.seat_occ_2a[date-1]<no_of_tickets)
						{
							printf("Sorry enough seats not available\n");
							return;
						}
						for(j=0;j<no_of_tickets;j++)
						{
							for(k=1;k<=max_size;k++)
							{
								if(tr[i].info_2a[date-1][k].occupied==0)
								{	tr[i].info_2a[date-1][k].occupied=1;
									printf("\n\nEnter details of passenger %d\n",j+1);
									fflush(stdin);
									printf("\nEnter name of passenger %d\n",j+1);

									do{
									    c = getchar();
									}while(c != EOF && c != '\n');
									fgets(tr[i].info_2a[date-1][k].pass_name, 40, stdin);
									tr[i].info_2a[date-1][k].pass_name[strcspn(tr[i].info_2a[date-1][k].pass_name, "\n")]='\0';
									printf("\nEnter age of passenger %d\n",j+1);
									scanf("%d",&tr[i].info_2a[date-1][k].age);
									fflush(stdin);
									printf("\nEnter gender of passenger %d(F/M)\n",j+1);
									scanf(" %c",&tr[i].info_2a[date-1][k].gender);
									fprintf(ft, "%d\t%s\t%d\t%c\t%d\n",j+1,tr[i].info_2a[date-1][k].pass_name, tr[i].info_2a[date-1][k].age, tr[i].info_2a[date-1][k].gender, k);
									index[l++]=k;
									tr[i].seat_occ_2a[date-1]++;
									break;
								}
							}
						}
						for(l=0;l<no_of_tickets;l++)
							{tr[i].info_2a[date-1][index[l]].pnr=index[0]+train_no*1000+class*100000000; 
								printf("pnr=%d\n",tr[i].info_2a[date-1][index[l]].pnr);
								fprintf(ft, "\nPNR= %d", tr[i].info_2a[date-1][index[l]].pnr);
							}
					}
					i++;
				}

				fclose(fp);


				FILE *fs=fopen("file_2.dat", "w");


				if(fs==NULL){printf("Cannot open file"); return;}
				for(i=0;i<no_of_trains;i++)
				{fwrite(&tr[i],sizeof(train),1,fs);
				}
				fclose(fs);
				fclose(ft);
				return 0;
			}

case 3: {			while(fread(&train,sizeof(train),1,fp)==1)
				{
					tr[i]=train;
					if(tr[i].train_no==train_no)
					{
						if(max_size- train.seat_occ_3a[date-1]<no_of_tickets)
						{
							printf("Sorry enough seats not available\n");
							return;
						}
						for(j=0;j<no_of_tickets;j++)
						{
							for(k=1;k<=max_size;k++)
							{
								if(tr[i].info_3a[date-1][k].occupied==0)
								{	tr[i].info_3a[date-1][k].occupied=1;
									printf("\n\nEnter details of passenger %d\n",j+1);
									fflush(stdin);
									printf("\nEnter name of passenger %d\n",j+1);
									
									do{
									    c = getchar();
									}while(c != EOF && c != '\n');
									fgets(tr[i].info_3a[date-1][k].pass_name, 40, stdin);
									tr[i].info_3a[date-1][k].pass_name[strcspn(tr[i].info_3a[date-1][k].pass_name, "\n")] = '\0';
									printf("\nEnter age of passenger %d\n",j+1);
									scanf("%d",&tr[i].info_3a[date-1][k].age);
									fflush(stdin);
									printf("\nEnter gender of passenger %d(F/M)\n",j+1);
									scanf(" %c",&tr[i].info_3a[date-1][k].gender);
									fprintf(ft, "%d\t%s\t%d\t%c\t%d\n",j+1,tr[i].info_3a[date-1][k].pass_name, tr[i].info_3a[date-1][k].age, tr[i].info_3a[date-1][k].gender, k);
									index[l++]=k;
									tr[i].seat_occ_3a[date-1]++;
									break;
								}
							}
						}
						for(l=0;l<no_of_tickets;l++)
							{tr[i].info_3a[date-1][index[l]].pnr=index[0]+train_no*1000+class*100000000; 
								printf("pnr=%d\n",tr[i].info_3a[date-1][index[l]].pnr);
								fprintf(ft, "\nPNR= %d", tr[i].info_3a[date-1][index[l]].pnr);
							}
					}
					i++;
				}

				fclose(fp);
				fclose(ft);


				FILE *fs=fopen("file_2.dat", "w");


				if(fs==NULL){printf("Cannot open file"); return;}
				for(i=0;i<no_of_trains;i++)
				{fwrite(&tr[i],sizeof(train),1,fs);
				}
				fclose(fs);
				return 0;
			}

}
}

/*cancel function made AND debugged by Shikha Panwar (15MA20039)*/
int cancel()   // returns 0 on success of cancellation 
{int pnr;
char name[40];
int c;
int flag=0;
printf("\nEnter pnr number\n");
scanf("%d",&pnr);
printf("\nEnter name\n");

do{ c = getchar();
	}while(c != EOF && c != '\n');
	fgets(name, 40, stdin);
	name[strcspn(name, "\n")]='\0';								
	FILE *fp=fopen("file_2.dat","r");  /*Choose appropriate file*/
	if(fp==NULL){printf("Cannot open file"); return;}
	struct train_info_extended tr[no_of_trains], train;

int i=0, j, k;
	while(fread(&train,sizeof(train),1,fp)==1)
	{tr[i]=train;
		/*edit the required entry here using if statement*/
		if(flag==1) continue;
				for(k=0; k<7; k++)					
				{	if(flag==1) break;
					for(j=1; j<=max_size; j++)
					{
						if(tr[i].info_1a[k][j].pnr==pnr && strcmp(tr[i].info_1a[k][j].pass_name,name)==0){
							tr[i].info_1a[k][j].pnr=0;
							tr[i].info_1a[k][j].occupied=0;
							tr[i].seat_occ_1a[k]--;
							print_cancellation_details(tr[i].info_1a[k][j]);
							printf("Reservation Cancelled\n\n");
							flag=1;
							break;
						}
					}

					if(flag==1) break;
					for(j=1; j<=max_size; j++)
					{
						if(tr[i].info_2a[k][j].pnr==pnr && strcmp(tr[i].info_2a[k][j].pass_name,name)==0){
							tr[i].info_2a[k][j].pnr=0;
							tr[i].info_2a[k][j].occupied=0;
							tr[i].seat_occ_2a[k]--;
							/*print_cancellation_details(struct seat_info passenger)
							print_cancellation_details(tr[i].info_2a[k][j])*/
							print_cancellation_details(tr[i].info_2a[k][j]);
							printf("Reservation Cancelled\n\n");
							flag=1;
							break;
						}
					}
					if(flag==1) break;
					for(j=1; j<=max_size; j++)
					{
						if(tr[i].info_3a[k][j].pnr==pnr && strcmp(tr[i].info_3a[k][j].pass_name,name)==0){
							tr[i].info_3a[k][j].pnr=0;
							tr[i].info_3a[k][j].occupied=0;
							tr[i].seat_occ_3a[k]--;
							print_cancellation_details(tr[i].info_3a[k][j]);
							printf("Reservation Cancelled\n\n");
							flag=1;
							break;
						}
					}
				}

		i++;
	}
	fclose(fp);


	FILE *fp2=fopen("file_2.dat", "w");


	for(i=0;i<no_of_trains;i++)
	{fwrite(&tr[i],sizeof(train),1,fp);
	}
	fclose(fp2);
if(flag==0){
printf("\nCancellation unsuccesful!\n");
return 1;
}
else return 0;
}

/*print_cancellation_details function made AND debugged by Shikha Panwar (15MA20039)*/
 void print_cancellation_details(struct seat_info passenger)
{
	FILE *fp=fopen("Cancellation_detail.txt","w");
	fprintf(fp, "NAME:\t%s\nAGE:\t%d\nYour reserved seat has been cancelled!", passenger.pass_name, passenger.age);
	fclose(fp);
return;	

}

/*main function made by Subham Rajgaria*/
int main()
{

	int i;
	int flag=0;
	while(1)
	{
		printf("1.Reserve\n");
		printf("2.Cancel\n");
		printf("3.Exit\n");
		printf("Please choose an option\n");
		scanf("%d",&i);
		switch(i)
		{
			case 1:reserve();
			break;
			case 2:cancel();
			break;
			case 3:flag=1;
			break;
			default:printf("Wrong choice, please enter again\n");
		}
		if(flag==1)
			break;
	}
	
}
