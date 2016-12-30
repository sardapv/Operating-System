#include <stdio.h>
struct process
{
 char name;
 int at,bt,ct,wt,tt;
 int completed;
 float ntt;
}p[10];
int n,currenttime[50],processNumber[50];
int finaltime;
void sortByArrival()
{
struct process temp;
int i,j;
for(i=0;i<n-1;i++)
	for(j=i+1;j<n;j++)
	{
	 if(p[i].at>p[j].at)
		  {
		    temp=p[i];
		    p[i]=p[j];
		    p[j]=temp;
		   }
	}
}
void printchart(){
	int temp,j;
for(int i=0;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(currenttime[j]>currenttime[j+1])
			{
				temp=currenttime[j];
				currenttime[j]=currenttime[j+1];
				currenttime[j+1]=temp;
			}
		}
	}

int i;
 for (i = 0; i < n ; i++)
		      printf("----------------");
		  printf("-\n");
		  	for(i = 0; i < n ; i++)
			  printf("|\tP%d\t",processNumber[i]);
		    printf("|\n");
		  	for(i = 0; i < n ; i++)
		      printf("----------------");
		  printf("-\n");
		  	for(i = 0; i < n ; i++){
		  		if(i <10)
		      		printf("%d\t\t",currenttime[i]);

		  	}
		  printf("%d\n",finaltime);

     

}
void main()
{
 int i,j,time,sum_bt=0;
 char c;
        float avgwt=0;
 printf("Enter no of processes:");
  scanf("%d",&n);
   for(i=0,c='A';i<n;i++,c++)
	    {
	     p[i].name=c;
	     printf("\nEnter the arrival time and burst time of process%c: ",p[i].name);
	      scanf("%d%d",&p[i].at,&p[i].bt);
	       p[i].completed=0;
	        sum_bt+=p[i].bt;
		
	    }
   sortByArrival();
   
   //printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\t Normalized TT");
     for(time=p[0].at;time<sum_bt;)
	       {
	         
	          float hrr=-9999;
	          int loc;
	         for(i=0;i<n;i++)
			   {
			     
			      if(p[i].at<=time && p[i].completed!=1)
				                  {
						                float temp=(p[i].bt + (time-p[i].at))/p[i].bt;
								              if(hrr < temp)
										                     {
												                     hrr=temp;
												                     loc=i;
												                    }
						            
						     }
			      }
	         
	          currenttime[loc] = time;
	          processNumber[loc] = loc;
	          time+=p[loc].bt; 
	          p[loc].wt=time-p[loc].at-p[loc].bt;
	          p[loc].tt=time-p[loc].at;
	          p[loc].ntt=((float)p[loc].tt/p[loc].bt);
		      p[loc].completed=1;
		      avgwt+=p[loc].wt;
		      finaltime = time;
			}
			//printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f",p[loc].name,p[loc].at,p[loc].bt,p[loc].wt,p[loc].tt,p[loc].ntt);
		    
     printf("\nAverage waiting time:%f\n",avgwt/n);
     printchart();
}

