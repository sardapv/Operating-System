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

int mfuLongestopt()
{int i,max;
	max=0;//The increment of counter value here is same as that for of LFU
	for(i=0;i<SIZE;i++)//The page with maximum frequency is selected
		if(ctr[max]<ctr[i])
			max=i;
	repptr=max;
	return repptr;
}
int mfuPagerep(int ele)
{
	int temp;
	repptr=mfuLongestopt();
	temp=frame[repptr];
	frame[repptr]=ele;
	ctr[repptr]=1;
	return temp;   
}

int mfuPagefault(int ele)
{if(full!=SIZE)
	{ctr[full]++;
		frame[full++]=ele;
	}
	else
		printf("\nReplacing page ... %d\n\n",mfuPagerep(ele));//Displaying of victim page
}
int mfuSearch(int ele)
{int i,flag;
	flag=0;
	if(full!=0)
	{
		for(i=0;i<full;i++)
			if(ele==frame[i])
			{   flag=1;ctr[i]++;
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
	{f=i;
		if(mfuSearch(a[i])!=1)
		{mfuPagefault(a[i]);
			printf(" for %d ::    F   :: ",a[i]);display();	
			count++;
		}else
		{
		printf(" for %d ::    H   :: ",a[i]);display();
		}
	}
	return 0;
	}