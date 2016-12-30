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

int LRstackopt(int p)//The input to this function is the referenced page
{int temp;
	int i;
	for(i=0;i<n;i++)
		if(stk[i]==p)
			break;
	temp=stk[i];//Storing the referenced value in temp
	while(i!=SIZE-1)//Moving the other elements so that the TOP is empty
	{stk[i]=stk[i+1];i++;
	}
	stk[i]=temp;//Storing the element in the TOP from temp
}
int lruPagerep(int ele)
{
	int temp;
	repptr=stk[0];//Always the victim page is selected as the first element of stack
	temp=frame[repptr];
	frame[repptr]=ele;
	LRstackopt(repptr);//Now the page that is brought is the latest referenced one, so it is moved to TOP
	return temp;   
}
int lruPagefault(int ele)
{if(full!=SIZE)
	{stk[full]=full;//First stack is populated till all the pages are full
		frame[full++]=ele;}
	else
		printf("\nReplacing page ... %d\n\n",lruPagerep(ele));//Displaying of victim page
}
int lruSearch(int ele)
{int i,flag;
	flag=0;
	if(full!=0)
	{
		for(i=0;i<full;i++)
			if(ele==frame[i])
			{   flag=1;LRstackopt(i);//When ever reference is made, but pae fault doesn't occur, the referenced page is moved to TOP
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
		if(lruSearch(a[i])!=1)
		{lruPagefault(a[i]);
			printf(" for %d ::    F   :: ",a[i]);display();	
			count++;
		}else
		{
		printf(" for %d ::    H   :: ",a[i]);display();
		}
	}
	return 0;
	}