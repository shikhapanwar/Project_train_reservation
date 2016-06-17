#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define max_size 300
#define no_of_trains 20

struct seat_info
{
	int occupied;     /*contains 0 or 1*/
	int pnr;
	char pass_name[40];
	int age;
	char gender;
};
struct train_info
{	int train_no;
	struct seat_info info_1a[7][max_size+1];
	struct seat_info info_2a[7][max_size+1];
	struct seat_info info_3a[7][max_size+1];
	int seat_occ_1a[7];
	int seat_occ_2a[7];
	int seat_occ_3a[7];
};


int main()
{
	FILE *fp=fopen("file_2.dat","w");
	if(fp==NULL) {printf("Unable to open file"); return;}
	struct train_info train;
	int i,j,k;
	for(i=0;i<no_of_trains;i++)
	{
			printf("Enter train no.\n");
			scanf("%d",&train.train_no);
		for(k=0;k<7;k++)
		{
			for(j=1;j<=max_size;j++)
			{	train.info_1a[k][j].occupied=0;
				train.info_2a[k][j].occupied=0;
				train.info_3a[k][j].occupied=0;
				strcpy(train.info_1a[k][j].pass_name,"NAme_it_is");
			}
		


		train.seat_occ_1a[k]=0;
		train.seat_occ_2a[k]=0;
		train.seat_occ_3a[k]=0;
		}

		fwrite(&train,sizeof(train),1,fp);

	}
	fclose(fp);
	return;

	
}
