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
int fifoPagerep(int ele)
{
	int temp;

	temp=frame[repptr];
	frame[repptr]=ele;
	repptr++;//The pointer moves to the next frame since the current frame became the newest
	if(repptr==SIZE)
		repptr=0;
	return temp;   //Returns the victim page
}
int fifoPagefault(int ele)
{if(full!=SIZE)
	frame[full++]=ele;//Untill all the frames fill, there is no call for page replacement
	else
		printf("\nReplacing page ... %d\n\n",fifoPagerep(ele));//Displaying of victim page
}

int fifoSearch(int ele)//This would search and return the flag that tells whether the page is already //present in the frame or not
{int i,flag;
	flag=0;
	if(full!=0)
	{
		for(i=0;i<full;i++)
			if(ele==frame[i])
			{   flag=1;
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
		if(fifoSearch(a[i])!=1)
		{fifoPagefault(a[i]);
			printf(" for %d ::    F   :: ",a[i]);display();	
			count++;
		}else
		{
		printf(" for %d ::    H   :: ",a[i]);display();
		}
	}
	return 0;
	}

