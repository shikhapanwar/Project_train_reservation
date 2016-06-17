#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max_size 300
#define no_of_trains 20


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


struct train_info_extended
{	int train_no;
	struct seat_info info_1a[7][max_size+1];
	struct seat_info info_2a[7][max_size+1];                     /*for file2*/
	struct seat_info info_3a[7][max_size+1];
	int seat_occ_1a[7];
	int seat_occ_2a[7];
	int seat_occ_3a[7];
};


int main()
{
	FILE *fp=fopen("file_1.dat","w");
	if(fp==NULL) {printf("Unable to open file"); return;}
	struct train_info train;
	int i,j,k;
	for(i=0;i<no_of_trains;i++)
	{
			printf("Enter train no.\n");

			scanf("%d",&train.train_no);
			fflush(stdin);
			printf("Enter train name\n");
			scanf("%s",train.train_name);
			fflush(stdin);
			printf("Enter from\n");
			scanf("%s",train.from);
			fflush(stdin);
			printf("Enter dep_time\n");
			scanf("%s",train.dep_time);
			fflush(stdin);
			printf("Enter to\n");
			scanf("%s",train.to);
			fflush(stdin);
			printf("Enter arr_time\n");
			scanf("%s",train.arr_time);
			fflush(stdin);

		

		fwrite(&train,sizeof(train),1,fp);

	}
	fclose(fp);
	return;

	
}
