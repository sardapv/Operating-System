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
int optLongestopt()
{int temp[SIZE];
	memset(temp,0,SIZE*sizeof(int));/*This is for checking the occurence of nearest possible future pages, considering no page is nearest in the beginning*/
	int c=0;//Counter to break the loop once we get two nearest future pages
	int id,i,k,j=SIZE;
	id=0;
	for(i=f+1;i<n;i++)//Checking from the current time of use till the end of string for future references
	{  for(k=0;k<j;k++)  //Checking whether a page occurs in future or not
		{   if(a[i]==frame[k])
			{if(temp[k]!=1)
				{temp[k]=1;
					c++;
				}

				break;}}
		if(c==(SIZE-1))
			break;//Once we get two future pages then we may break
	}
	id=(SIZE-1);
	while(id!=0)
	{if(temp[id]==0)//Checking for the page which is not the nearest future reference
		break;
		id--;
	}
	repptr=id;
	return repptr;//Returning the replacement pointer with the value of victim page
}
int display()//To display the elements of the frame
{int i;
	for(i=0;i<full;i++)
		printf("[ %d ]",frame[i]);
		printf("\n");
}

int optPagerep(int ele)
{
	int temp;
	repptr=optLongestopt();
	temp=frame[repptr];
	frame[repptr]=ele;
	return temp;   
}
int optPagefault(int ele)
{if(full!=SIZE)
	frame[full++]=ele;
	else {
		printf("\nReplacing page ... %d\n\n",optPagerep(ele));//Displaying of victim page
		//Pagerep(ele);}
	}
}
int optSearch(int ele)
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
	{f=i;
		if(optSearch(a[i])!=1)
		{optPagefault(a[i]);
			printf(" for %d ::    F   :: ",a[i]);display();	
			count++;
		}else
		{
		printf(" for %d ::    H   :: ",a[i]);display();
		}
	}
	return 0;
	}