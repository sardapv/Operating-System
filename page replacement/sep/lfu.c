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

int display()//To display the elements of the frame
{int i;
	for(i=0;i<full;i++)
		printf("[ %d ]",frame[i]);
		printf("\n");
}

int lfuLongestopt()
{int i,min;

	min=0;
	for(i=0;i<SIZE;i++)//The page with least frequency is selected as victim
		if(ctr[min]>ctr[i])
			min=i;
	repptr=min;
	return repptr;
}
int lfuPagerep(int ele)
{
	int temp;
	repptr=lfuLongestopt();//The victim page is selected with the help of a function
	temp=frame[repptr];
	frame[repptr]=ele;
	ctr[repptr]=1;//A new page is brought, hence it's counter is set to 1
	return temp;   
}
	int lfuPagefault(int ele)
{if(full!=SIZE)
	{ctr[full]++;//The counters will increase initially for all frames till they are full
		frame[full++]=ele;
	}
	else
		printf("\nReplacing page ... %d\n\n",lfuPagerep(ele));//Displaying of victim page
}
int lfuSearch(int ele)
{int i,flag;
	flag=0;
	if(full!=0)
	{
		for(i=0;i<full;i++)
			if(ele==frame[i])
			{   flag=1;ctr[i]++;//Whenever a reference is made the counter is incremented
				break;
			}}
	return flag;   
}
int main()
{	init();
	int i;
	printf("Enter the frame Size :: ");
	scanf("%d",&SIZE);
	int ch;

	FILE *fp;//For taking input from a file
	//Start

	init();
	fp=fopen("Input.txt","r");
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&a[i]);
	fclose(fp);
	
	printf("\n{ ------------------------ FIFO ----------------------- }\n\n");
				for(i=0;i<n;i++)
	{
		if(lfuSearch(a[i])!=1)
		{lfuPagefault(a[i]);
			printf(" for %d ::    F   :: ",a[i]);display();	
			count++;
		}else
		{
		printf(" for %d ::    H   :: ",a[i]);display();
		}
	}
	return 0;
	}