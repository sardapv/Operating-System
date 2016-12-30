#include "myheader.h"

void init(){
		frame = calloc(SIZE,sizeof(int));
		stk = calloc(SIZE,sizeof(int));
		ref = malloc(SIZE*sizeof(int));
		addref = calloc(SIZE,sizeof(int));
		ctr = calloc(SIZE,sizeof(int));

			for (int i = 0; i < SIZE; ++i)
			frame[i] = 99;

		full=0;
		repptr=0;
		count=0;
 		f=0;
		r=1;

		//frame[i] = stk[i] = ref[i] = addref[i] = 0;
}


int flag,n,count,pg[50],modnum[50],i;
int tempo,tempo1;
void displaypages()
{int i;
	
	
	if (flag != 0)
		printf(" for %d ::    H   :: ",tempo);
	else{
		if (tempo1!= -1)
	printf("\nReplacing Page ... %d\n",tempo1);
		printf("\n for %d ::    F   :: ",tempo);
	}
	for(i=0;i<SIZE;i++)
		if (frame[i]!=-1)
			{
			printf("[ %d ]",frame[i]);
		}
	printf("\n");
}
void isfound(int data)
{
	flag=0;
	for(i=0; i< SIZE; i++){
		if(frame[i]==data){
			flag = 1;
			break;
		}
	}
}
int getfoundindex(int data){
	int foundind;
	for(i=0;i < SIZE; i++){
		if(frame[i]==data){
			foundind = i;
			break;
		}
	}
	return foundind;
}

void enhancesecondchance(){
	int s = 0,refbit[10],modbit[10],x,j;
	count = 0;

	for (i = 0;i < SIZE;i++){
		frame[i] = -1;
		refbit[i] = 0;
		modbit[i] = 0;
	}
	for(s = 0;s < n;s++){
		isfound(pg[s]);
		if(flag == 1){            //page found so no page fault
			int fin = getfoundindex(pg[s]);
			if(refbit[fin]== 0)
				refbit[fin] = 1;
			if(modnum[s]== 1)
				modbit[fin] = 1;
			else
				modbit[fin] = 0;
		}
		else{
			x = 0;
			count++;
			while(x == 0){
				for(i = 0;i < SIZE;i++){
					if((refbit[i]==0) && (modbit[i] == 0)){
						tempo1 = frame[i];
						frame[i] = pg[s];
						tempo = pg[s];
						refbit[i] = 1;
						if(modnum[s] == 1)
							modbit[i] = 1;
						else
							modbit[i] = 0;
						x = 1;
						break;
					}
				}
				if(x == 0){
					for(i = 0;i < SIZE;i++){
						if((refbit[i] == 0) && (modbit[i] == 1)){
							tempo1 = frame[i];
							frame[i] = pg[s];
							tempo = pg[s];
							refbit[i] = 1;
							if(modnum[s] == 1)
								modbit[i] = 1;
							else
								modbit[i] = 0;
							for(j = 0;j < SIZE;j++)
								if(j!=i)
									refbit[j] = 0;
							x = 1;
							break;
						}
					}
				}
				if(x == 0){
					for(i = 0;i < SIZE;i++)
						refbit[i] = 0;
				}
			}
		}

		displaypages();
	}
	printf("\n\nTotal page faults: %d\n",count);
}

int main()
{	init();
	int i;
	printf("Enter the frame Size :: ");
	scanf("%d",&SIZE);

	FILE *fp;	
	printf("\n{ ------------------------ ENHANCED SECOND CHANCE ----------------------- }\n\n");
	fp=fopen("Input.txt","r");
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&pg[i]);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&modnum[i]);
	enhancesecondchance();
	printf("\n{ ------------------ PAGE FAULTS :: %d || PAGE HITS :: %d ------------------ }\n\n",count,n-count);
	return 0;
}