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
{struct train_info_extended train;
	FILE *fp;
	fp=fopen("file_2.dat","r");

	if(fp==NULL){printf("Cannot open file"); return;}

	while(fread(&train,sizeof(train),1,fp)==1)
	{
		printf("%d\n",train.train_no);
	}

	fclose(fp);
	return 0;
}