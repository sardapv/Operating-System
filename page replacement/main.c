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
void myfunction(){
        int i;
        for (i = 0; i < full; ++i)
        {
            printf("ref[%d] = %d",repptr,ref[i]);

        }
        printf("\n");

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
int scdisplay()
{int i;
	for(i=0;i<SIZE;i++)
		if (frame[i]!=99)
			printf("[ %d ]",frame[i]);
		printf("\n");
}

int getHitIndex(int ele)
{
	int hitind;int k;
	for(k=0; k<SIZE; k++)
	{
		if(frame[k]==ele)
		{
			hitind=k;
			break;
		}
	}
	return hitind;
}
int Hit(int data)
{int j;
	int hit=0;
	for(j=0; j<SIZE; j++)
	{
		if(frame[j]==data)
		{
			hit=1;
			break;
		}

	}

	return hit;
}
void secondchance()
{
	int i = 0;
	int ref[50];
	int repptr=0;
	int tempo;
	init();
	FILE *fp;
	fp=fopen("Input.txt","r");
		fscanf(fp,"%d",&n);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&a[i]);
	for(i=0; i<SIZE; i++)
		ref[i]=0;
	for(i=0; i<n; i++)
	{
		
		if(Hit(a[i]))
		{
			printf(" for %d ::    H   :: ",a[i]);scdisplay();	
			int hitindex=getHitIndex(a[i]);
			if(ref[hitindex]==0)
				ref[hitindex]=1;
		}
		else
		{
			count++;
			if(ref[repptr]==1)
			{
				do
				{
					ref[repptr]=0;
					repptr++;
					if(repptr==SIZE)
						repptr=0;
				}
				while(ref[repptr]!=0);
			}
			if(ref[repptr]==0)
			{
				tempo = frame[repptr];
				frame[repptr]=a[i];
				ref[repptr]=1;
				repptr++;
			}
			if(tempo!=99)
			printf("\nReplacing Page ... %d\n\n",tempo);
			printf(" for %d ::    F   :: ",a[i]);scdisplay();
		}
		if(repptr==SIZE)
			repptr=0;
	}
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
	int ch;

	FILE *fp;//For taking input from a file
	//Start
	while(ch<7){
	init();
	fp=fopen("Input.txt","r");
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&a[i]);
	fclose(fp);
	printf("++++++++++++++ PAGE REPLACEMENT SELECTION MENU +++++++++++++++\n\n\t1.FIFO\n\t2.Optimal\n\t3.LRU\n\t4.LFU\n\t5.MFU\n\t6.Second Chance\n\t7.Enhanced Secondd Chance\n");
	printf("\nEnter Choice ::");
	
	scanf("%d",&ch);
		switch (ch) {
	printf("\n{ ------------------------ FIFO ----------------------- }\n\n");
		case 1 :
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
				break;
		case 2 :
	printf("\n{ ------------------------ OPTIMAL ----------------------- }\n\n");
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
				break;
		case 3 :
	printf("\n{ ------------------------ LRU ----------------------- }\n\n");

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
				break;
		case 4 :
	printf("\n{ ------------------------ LFU ----------------------- }\n\n");
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
				break;
		case 5:
	printf("\n{ ------------------------ MFU ----------------------- }\n\n");
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
	break;
	case 6:
	printf("\n{ ------------------------ SECOND CHANCE ----------------------- }\n\n");
	secondchance();
	break;
	case 7:
	printf("\n{ ------------------------ ENHANCED SECOND CHANCE ----------------------- }\n\n");
	FILE *fp;
	fp=fopen("Input.txt","r");
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&pg[i]);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&modnum[i]);
	enhancesecondchance();
	break;
		default : 
			printf("WRONG CHOICE !! Exiting ...");
			exit(1);
				break;
	}
	printf("\n{ ------------------ PAGE FAULTS :: %d || PAGE HITS :: %d ------------------ }\n\n",count,n-count);}
	return 0;
}
