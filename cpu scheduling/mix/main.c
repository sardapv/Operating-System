void fcfsGChart();
void sjfGChart();
void rrGChart();
void premprioGChart();
void nonpremprioGChart();
void calculateProcessSequence();
void rrcalculateProcessSequence();
int findAptProcessNumber(int);
int rrfindAptProcessNumber(int,int,int);

#include <stdlib.h>
#include <stdio.h>
int min(int, int []);
int temp,time,temp4,c,n,i,j,a1[20],wt[20],pr[20],bt[20],gc[20],arr_ti[20],tat[20],sum_bt=0,a=0,p=0,temp1,count;

int numberOfProcesses,totalCPUBurstTime,ganttSize,n,*processNumberGantt,*CPUBurstTimeGantt,*priority,*arrivalTime,*CPUBurstTime,*CPUBurstTimeCopy,*processNumber,minimumArrivalTime,*processSequenceForEachSecond,*waitingTime,timeQuantum;
float averageWaitingTime,averageTurnAroundTime;
float averageWaitingTime=0;

/**/
struct process
{
 char name;
 int at,bt,ct,wt,tt;
 int completed;
 float ntt;
}pro[10];
int n,currenttime[50];
int finaltime;
void sortByArrival()
{
struct process temp;
int i,j;
for(i=0;i<n-1;i++)
	for(j=i+1;j<n;j++)
	{
	 if(pro[i].at>pro[j].at)
		  {
		    temp=pro[i];
		    pro[i]=pro[j];
		    pro[j]=temp;
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

/**/

void init(){
	
	numberOfProcesses= 0,totalCPUBurstTime = 0,ganttSize = 0,n = 0;
	averageWaitingTime = 0.0;
	averageTurnAroundTime = 0.0;
}
int min(int a,int a1[20])
{
	int i,count=0;
	int temp=a1[0];
	if(a==1)
	{ temp--;}
	else
	{
		for(i=0; i<a; i++)
		{
			if(temp>a1[i])
			{
				temp=a1[i];
				count=i;}}
		temp--;}
	if(temp==0)
	{temp=500;}
	a1[count]=temp;
	return(count);  /* returning the index of array whose value is minimum*/
}

int main(){
	int i,j,temp;
	init();

	arrivalTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	CPUBurstTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	processNumber=(int*)malloc(sizeof(int)*numberOfProcesses);
	CPUBurstTimeCopy=(int*)malloc(sizeof(int)*numberOfProcesses);
	waitingTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	priority=(int*)malloc(sizeof(int)*numberOfProcesses);
	minimumArrivalTime=2147483647;
	FILE *fp;
		fp=fopen("Input.txt","r");
		fscanf(fp,"%d",&numberOfProcesses);
		for(i=0;i<numberOfProcesses;i++) {
		processNumber[i] = i;
		fscanf(fp,"%d\t%d\t%d",&arrivalTime[i],&CPUBurstTime[i],&priority[i]);
		
		}fscanf(fp,"%d",&timeQuantum);
		fclose(fp);
	for(i=0;i<numberOfProcesses;i++)
	{
	waitingTime[i]=0;
		processNumber[i]=i;

		/*printf("\nEnter the data for process number : %d\n",i);
		printf("\n");
		printf("Arrival Time   : ");
		scanf("%d",&arrivalTime[i]);
		printf("CPU Burst time : ");
		scanf("%d",&CPUBurstTime[i]);
		CPUBurstTimeCopy[i]=CPUBurstTime[i];	
		printf("Priority : ");
		scanf("%d",&priority[i]);*/
	
		totalCPUBurstTime+=CPUBurstTime[i];
		if(minimumArrivalTime>arrivalTime[i])
			minimumArrivalTime=arrivalTime[i];
	}

	int ch = 1;
	while (ch < 8){
	switch(ch) {
	case 1 :
	printf("\n================================================ FCFS ====================================================\n");

	/*
	   implementing bubble sort algorithm
	 */

	for(i=1;i<numberOfProcesses;i++)
	{
		for(j=1;j<numberOfProcesses-1;j++)
		{
			if(arrivalTime[j]>arrivalTime[j+1])
			{
				temp=arrivalTime[j];
				arrivalTime[j]=arrivalTime[j+1];
				arrivalTime[j+1]=temp;

				temp=CPUBurstTime[j];
				CPUBurstTime[j]=CPUBurstTime[j+1];
				CPUBurstTime[j+1]=temp;

				temp=processNumber[j];
				processNumber[j]=processNumber[j+1];
				processNumber[j+1]=temp;
			}
		}
	}
	ch++;

	/*for(i=0;i<numberOfProcesses;i++)
	{
		printf("P%d -> %d,%d\n",processNumber[i],arrivalTime[i],CPUBurstTime[i]);
	}*/

	fcfsGChart();
	break;
	case 2 :
	printf("\n================================================ SJFS ====================================================\n");
	for(i=1;i<numberOfProcesses;i++)
	{
		for(j=1;j<numberOfProcesses-1;j++)
		{
			if(CPUBurstTime[j]>CPUBurstTime[j+1])
			{
				temp=arrivalTime[j];
				arrivalTime[j]=arrivalTime[j+1];
				arrivalTime[j+1]=temp;

				temp=CPUBurstTime[j];
				CPUBurstTime[j]=CPUBurstTime[j+1];
				CPUBurstTime[j+1]=temp;

				temp=processNumber[j];
				processNumber[j]=processNumber[j+1];
				processNumber[j+1]=temp;
			}
		}
	}ch++;

/*	for(i=0;i<numberOfProcesses;i++)
	{
		printf("P%d -> %d,%d\n",processNumber[i],arrivalTime[i],CPUBurstTime[i]);
	}*/

	sjfGChart();
	break;

	/*case 3:

	printf("\n================================================ NONPREMPTIVE PRIORITY ====================================\n");
	for(i=1;i<numberOfProcesses;i++)
	{
		

		for(j=1;j<numberOfProcesses-1;j++)
		{
			if(priority[j]>priority[j+1])
			{
				temp=priority[j];
				priority[j]=priority[j+1];
				priority[j+1]=temp;

				temp=arrivalTime[j];
				arrivalTime[j]=arrivalTime[j+1];
				arrivalTime[j+1]=temp;

				temp=CPUBurstTime[j];
				CPUBurstTime[j]=CPUBurstTime[j+1];
				CPUBurstTime[j+1]=temp;

				temp=processNumber[j];
				processNumber[j]=processNumber[j+1];
				processNumber[j+1]=temp;
			}
		}
	}ch++;
/*	for(i=0;i<numberOfProcesses;i++)
	{
		printf("P%d -> %d,%d\n",processNumber[i],arrivalTime[i],CPUBurstTime[i]);
	}

	nonpremprioGChart();
	
	break;
	case 4 :
	printf("\n================================================ PREMPTIVE PRIORITY =======================================\n");	
	processSequenceForEachSecond=(int*)malloc(sizeof(int)*totalCPUBurstTime);

	 this function calculates the process sequence for each second. 

	calculateProcessSequence();
	premprioGChart();ch++;

	printf("\nAverage Waiting Time     = %f\n",averageWaitingTime);
	printf("\nAverage Turn Around Time = %f\n\n",averageTurnAroundTime);

		break;
*/
case 3:
		printf("\n================================================ ROUND ROBIN ==============================================\n");
		fp=fopen("Input.txt","r");
		fscanf(fp,"%d",&numberOfProcesses);
		for(i=0;i<numberOfProcesses;i++) {
		fscanf(fp,"%d\t%d\t%d",&arrivalTime[i],&CPUBurstTime[i],&priority[i]);
		
		}fscanf(fp,"%d",&timeQuantum);
		fclose(fp);

for(i=1;i<numberOfProcesses;i++)
	{
		for(j=1;j<numberOfProcesses-1;j++)
		{
			if(arrivalTime[j]>arrivalTime[j+1])
			{
				temp=arrivalTime[j];
				arrivalTime[j]=arrivalTime[j+1];
				arrivalTime[j+1]=temp;

				temp=CPUBurstTime[j];
				CPUBurstTime[j]=CPUBurstTime[j+1];
				CPUBurstTime[j+1]=temp;

				temp=processNumber[j];
				processNumber[j]=processNumber[j+1];
				processNumber[j+1]=temp;
			}
		}
	}
	processSequenceForEachSecond=(int*)malloc(sizeof(int)*totalCPUBurstTime);

	/* this function calculates the process sequence for each second. */

	rrcalculateProcessSequence();
	rrGChart();
/*	printf("\nAverage Waiting Time     = %f\n",averageWaitingTime);
	printf("\nAverage Turn Around Time = %f\n\n",averageTurnAroundTime);
	*/ch++;
	break;
	case 4:
	printf("\n================================================ SRTF ====================================================\n");
	fp=fopen("Input.txt","r");
		fscanf(fp,"%d",&n);
		for(i=0;i<n;i++) {
		fscanf(fp,"%d\t%d\t%d",&arrivalTime[i],&CPUBurstTime[i],&priority[i]);
		
		}fscanf(fp,"%d",&timeQuantum);
		fclose(fp);
	for(i=0; i<n; i++)
	{bt[i] = CPUBurstTime[i];
		sum_bt=sum_bt+bt[i];
		a1[i]=bt[i];}
	for(i=0; i<n; i++)
		pr[i]=i+1;

	for(i=0; i<n; i++)
		arr_ti[i] = arrivalTime[i];

	for(i=0; i<(n-2); i++)
	{  for(j=i; j<((n-2)-i); i++)
		{
			if(arr_ti[j]>arr_ti[j+1])
			{   temp=arr_ti[j];
				arr_ti[j]=arr_ti[j+1];
				arr_ti[j+1]=temp;
				temp=a1[j];
				a1[j]=a1[j+1];
				a1[j+1]=temp;
				temp=pr[j];
				pr[j]=pr[j+1];
				pr[j+1]=temp;
			}}}
	for(i=0; i<n; i++)
	{
		wt[i]=0;
		tat[i]=0;
	}
	for(i=0; i<=sum_bt; i++)
	{
		a++;
		if(a<5)
		{
			c=min(a,a1)+1;
			gc[i]=c;
		}
		else
		{
			c=min(5,a1)+1;
			gc[i]=c;
		}  }
	for(i=0; i<n; i++)
	{
		temp=i+1;
		time=0;
		temp1=0;
		for(j=0; j<sum_bt; j++)
		{time++;
			if(temp==gc[j])
			{
				if(temp1==0)
				{
					wt[i]=wt[i]+time-(i+1);
					temp1=j+2;
				}
				else
				{
					wt[i]=wt[i]+(j+1)-temp1;
					temp1=j+2;
				}}}}

	for(i=0; i<n; i++)
	{
		temp=0;
		for(j=0; j<sum_bt; j++)
		{
			if(i+1==gc[j])
			{
				if(temp==0)
				{
					tat[i]=tat[i]+bt[i]+j-arr_ti[i];
					temp=j+1;
				}
				else
				{
					tat[i]=tat[i]+j-temp;
					temp=j+1;
				}  }}}
	//printing the output

/*	printf("DATA IS AS FOLLOWS: \n");
	printf("Process\t Burst Time\t Arrival Time\t Waiting Time\t Turn Around Time\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t %d\t\t\t %d\t\t %d\t\t %d\n",pr[i],bt[i],arr_ti[i],wt[i],tat[i]);
	}*/
	printf("The gantt chart for the given processes is : \n\n");
	c=gc[0];
	for (i=1;i<=n;i++)
		printf("----------------");

	printf("-\n");
	printf("|\tP%d\t",gc[0]-1);
		
	for(i=1;i<sum_bt;i++)
	{
		if(gc[i]!=c)
		{printf("|\tP%d\t",gc[i]-1);
			c=gc[i];}
	}
	printf("|\n");
	for (i=1;i<=n;i++)
		printf("----------------");
	printf("-\n0\t\t");
	c=gc[0];
	for(i=1;i<=sum_bt;i++)
	{    p=p+1;
		if(gc[i]!=c)
		{printf("%d\t\t",p);
			c=gc[i];
		}
	}
	sum_bt = 0;
	for(i=1;i<=n;i++)
	{   
		sum_bt =  wt[i] + sum_bt;
	}
	/*printf("\n\nAverage Waiting Time = %d\n",sum_bt/n);*/ch++;
	break;

	case 5:
	
	printf("\n\n\n=============================================== HRRN ======================================================\n");
	int i,j,time,sum_bt=0;
 char c;
        float avgwt=0;
   fp=fopen("Input.txt","r");
		fscanf(fp,"%d",&n);
		for(i=0;i<n;i++) {
		fscanf(fp,"%d\t%d\t%d",&pro[i].at,&pro[i].bt,&priority[i]);
			pro[i].completed=0;
	        sum_bt+=pro[i].bt;
		}fscanf(fp,"%d",&timeQuantum);
		fclose(fp);
   /*for(i=0,c='A';i<n;i++,c++)
	    {
	     pro[i].name=c;
	     printf("\nEnter the arrival time and burst time of process%c: ",pro[i].name);
	      scanf("%d%d",&pro[i].at,&pro[i].bt);
	       pro[i].completed=0;
	        sum_bt+=pro[i].bt;
		
	    }*/
   sortByArrival();
   
   //printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\t Normalized TT");
     for(time=pro[0].at;time<sum_bt;)
	       {
	         
	          float hrr=-9999;
	          int loc;
	         for(i=0;i<n;i++)
			   {
			     
			      if(pro[i].at<=time && pro[i].completed!=1)
				                  {
						                float temp=(pro[i].bt + (time-pro[i].at))/pro[i].bt;
								              if(hrr < temp)
										                     {
												                     hrr=temp;
												                     loc=i;
												                    }
						            
						     }
			      }
	         
	          currenttime[loc] = time;
	          processNumber[loc] =loc;
	          time+=pro[loc].bt; 
	          pro[loc].wt=time-pro[loc].at-pro[loc].bt;
	          pro[loc].tt=time-pro[loc].at;
	          pro[loc].ntt=((float)pro[loc].tt/pro[loc].bt);
		      pro[loc].completed=1;
		      avgwt+=pro[loc].wt;
		      finaltime = time;
			}
			//printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f",pro[loc].name,pro[loc].at,pro[loc].bt,pro[loc].wt,pro[loc].tt,pro[loc].ntt);
		    
     printf("The gantt chart for the given processes is : \n");
     printchart();
    // printf("\n\nAverage Waiting Time = %f\n\n",avgwt/n);
     	printf("\n=============================================== *_* ======================================================\n");
     ch++;exit(1);
	}
}
}
void rrcalculateProcessSequence()
{
	int i,j,pNumber=processNumber[0],prevProcess,tempCPUBurstTime,counter=0,prevProcesss;
	for(i=minimumArrivalTime;i<totalCPUBurstTime + minimumArrivalTime;i++)
	{
		/* here i denotes the current time */
		prevProcess=pNumber;
		pNumber=rrfindAptProcessNumber(i,pNumber,counter);
		if(pNumber==prevProcess)
		{
			counter++;
		}
		else
			counter=1;

		CPUBurstTime[pNumber]--;
		processSequenceForEachSecond[i-minimumArrivalTime]=pNumber;
		//printf("Lavish P%d\n",pNumber);
		/*
		   claculating the waiting time of each process;
		 */
		for(j=0;j<numberOfProcesses;j++)
			if(CPUBurstTime[j]!=0 && arrivalTime[j]<=i && j!=pNumber)
				waitingTime[j]++;

	}
	/*
	   for(i=0;i<totalCPUBurstTime;i++)
	   printf("Lavish P%d\n",processSequenceForEachSecond[i]);
	 *//* claculating the size of gantt chart arrays*/
	ganttSize=1;
	prevProcess=processSequenceForEachSecond[0];
	for(i=0;i<totalCPUBurstTime;i++)
	{
		if(prevProcess!=processSequenceForEachSecond[i])
			ganttSize++;
		prevProcess=processSequenceForEachSecond[i];
	}

	/* allocating the size of gantt chart arrays */
	processNumberGantt=(int*)malloc(sizeof(int)*ganttSize);
	CPUBurstTimeGantt=(int*)malloc(sizeof(int)*ganttSize);

	/* assigning the values to Gantt Chart Arrays */
	prevProcess=processSequenceForEachSecond[0];
	tempCPUBurstTime=0;
	counter=0;
	for(i=0;i<totalCPUBurstTime;i++)
	{
		if(prevProcess!=processSequenceForEachSecond[i])
		{
			processNumberGantt[counter]=prevProcess;
			CPUBurstTimeGantt[counter]=tempCPUBurstTime;
			counter++;
			tempCPUBurstTime=0;
		}
		tempCPUBurstTime++;
		prevProcess=processSequenceForEachSecond[i];
	}

	CPUBurstTimeGantt[ganttSize-1]=tempCPUBurstTime;
	processNumberGantt[ganttSize-1]=prevProcess;


	/* calculating the averageWaitingTime and averageTurnAroundTime */
	averageWaitingTime=0;
	averageTurnAroundTime=0;
	for(i=0;i<numberOfProcesses;i++)
	{
		averageWaitingTime+=waitingTime[i];
		averageTurnAroundTime+=waitingTime[i]+CPUBurstTimeCopy[i];
	}
	averageWaitingTime=averageWaitingTime/(float)numberOfProcesses;
	averageTurnAroundTime=averageTurnAroundTime/(float)numberOfProcesses;

}

int rrfindAptProcessNumber(int currentTime,int currentProcess,int time)
{
	/* this function returns the process number that should run on currentTime. */
	/* time variable is used to indicate the time for which a process is being executed */
	int i,pNumber,answer;
	if(currentTime!=0 && (time==timeQuantum || CPUBurstTime[currentProcess]==0))
	{
		for(i=0;i<numberOfProcesses;i++)
		{   
			if(processNumber[i]==currentProcess)
			{
				if((currentProcess+1)==numberOfProcesses)
					answer=0;
				else
					answer=currentProcess+1;
				while(arrivalTime[answer]>currentTime || CPUBurstTime[answer]==0)
					answer=(answer+1)%numberOfProcesses;
				return answer;
			}
		}
	}
	else
		return currentProcess;
}

void rrGChart()
{
	const int maxWidth=100;
	int scalingFactor,i,counter,tempi,currentTime;
	printf("The gantt chart for the given processes is : \n\n");

	scalingFactor=maxWidth/totalCPUBurstTime;
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+ganttSize;i++)
		printf("-");
	printf("\n|");
	counter=0,tempi=0;
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
		if(i==CPUBurstTimeGantt[counter]*scalingFactor+tempi)
		{
			counter++;
			tempi=i;
			printf("|");
		}
		else if(i==(CPUBurstTimeGantt[counter]*scalingFactor)/2+tempi)
			printf("P%d",processNumberGantt[counter]);
		else
			printf(" ");
	printf("|");
	printf("\n");
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+ganttSize;i++)
		printf("-");
	printf("\n");

	/* printing the time labels of the gantt chart */
	counter=0;
	tempi=0;
	currentTime=minimumArrivalTime;
	printf("%d",currentTime);
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
		if(i==CPUBurstTimeGantt[counter]*scalingFactor+tempi)
		{
			tempi=i;
			currentTime+=CPUBurstTimeGantt[counter];
			averageWaitingTime+=currentTime;
			counter++;
			printf("%2d",currentTime);
		}
		else
		{
			printf(" ");
		}
	currentTime+=CPUBurstTimeGantt[counter];
	printf("%2d\n\n",currentTime);
}

void premprioGChart()
{
	const int maxWidth=100;
	int scalingFactor,i,counter,tempi,currentTime;
	printf("The gantt chart for the given processes is : \n\n");

	scalingFactor=maxWidth/totalCPUBurstTime;
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+ganttSize;i++)
		printf("-");
	printf("\n|");
	counter=0,tempi=0;
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
		if(i==CPUBurstTimeGantt[counter]*scalingFactor+tempi)
		{
			counter++;
			tempi=i;
			printf("|");
		}
		else if(i==(CPUBurstTimeGantt[counter]*scalingFactor)/2+tempi)
			printf("P%d",processNumberGantt[counter]);
		else
			printf(" ");
	printf("|");
	printf("\n");
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+ganttSize;i++)
		printf("-");
	printf("\n");

	/* printing the time labels of the gantt chart */
	counter=0;
	tempi=0;
	currentTime=minimumArrivalTime;
	printf("%d",currentTime);
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
		if(i==CPUBurstTimeGantt[counter]*scalingFactor+tempi)
		{
			tempi=i;
			currentTime+=CPUBurstTimeGantt[counter];
			averageWaitingTime+=currentTime;
			counter++;
			printf("%2d",currentTime);
		}
		else
		{
			printf(" ");
		}
	currentTime+=CPUBurstTimeGantt[counter];
	printf("%2d\n\n",currentTime);
}

void calculateProcessSequence()
{
	int i,j,pNumber,prevProcess,tempCPUBurstTime,counter,prevProcesss;
	for(i=minimumArrivalTime;i<totalCPUBurstTime + minimumArrivalTime;i++)
	{
		pNumber=findAptProcessNumber(i);
		processSequenceForEachSecond[i-minimumArrivalTime]=pNumber;
		CPUBurstTime[pNumber]--;
		/*
		   claculating the waiting time of each process;
		 */
		for(j=0;j<numberOfProcesses;j++)
			if(CPUBurstTime[j]!=0 && arrivalTime[j]<=i && j!=pNumber)
				waitingTime[j]++;

	}


	/* claculating the size of gantt chart arrays*/
	ganttSize=1;
	prevProcess=processSequenceForEachSecond[0];
	for(i=0;i<totalCPUBurstTime;i++)
	{
		if(prevProcess!=processSequenceForEachSecond[i])
			ganttSize++;
		prevProcess=processSequenceForEachSecond[i];
	}

	/* allocating the size of gantt chart arrays */
	processNumberGantt=(int*)malloc(sizeof(int)*ganttSize);
	CPUBurstTimeGantt=(int*)malloc(sizeof(int)*ganttSize);

	/* assigning the values to Gantt Chart Arrays */
	prevProcess=processSequenceForEachSecond[0];
	tempCPUBurstTime=0;
	counter=0;
	for(i=0;i<totalCPUBurstTime;i++)
	{
		if(prevProcess!=processSequenceForEachSecond[i])
		{
			processNumberGantt[counter]=prevProcess;
			CPUBurstTimeGantt[counter]=tempCPUBurstTime;
			counter++;
			tempCPUBurstTime=0;
		}
		tempCPUBurstTime++;
		prevProcess=processSequenceForEachSecond[i];
	}

	CPUBurstTimeGantt[ganttSize-1]=tempCPUBurstTime;
	processNumberGantt[ganttSize-1]=prevProcess;


	/* calculating the averageWaitingTime and averageTurnAroundTime */
	averageWaitingTime=0;
	averageTurnAroundTime=0;
	for(i=0;i<numberOfProcesses;i++)
	{
		averageWaitingTime+=waitingTime[i];
		averageTurnAroundTime+=waitingTime[i]+CPUBurstTimeCopy[i];
	}
	averageWaitingTime=averageWaitingTime/(float)numberOfProcesses;
	averageTurnAroundTime=averageTurnAroundTime/(float)numberOfProcesses;

}
int findAptProcessNumber(int currentTime)
{
	int i,min=2147483647,pNumber;
	for(i=0;i<numberOfProcesses;i++)
		if(arrivalTime[i]<=currentTime && min>priority[i] && CPUBurstTime[i]!=0)
		{
			min=priority[i];
			pNumber=i;
		}
	return pNumber;
}

void fcfsGChart()
{
	const int maxWidth=100;
	int scalingFactor,i,counter,tempi,currentTime;
	printf("The gantt chart for the given processes is : \n\n");

	scalingFactor=maxWidth/totalCPUBurstTime;
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
	{
		printf("-");
	}
	printf("\n|");
	counter=0,tempi=0;
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
	{
		if(i==CPUBurstTime[counter]*scalingFactor+tempi)
		{
			counter++;
			tempi=i;
			printf("|");
		}
		else if(i==(CPUBurstTime[counter]*scalingFactor)/2+tempi)
		{
			printf("P%d",processNumber[counter]);
		}
		else
		{
			printf(" ");
		}

	}
	printf("|");
	printf("\n");
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
	{
		printf("-");
	}
	printf("\n");

	/* printing the time labels of the gantt chart */
	counter=0;
	tempi=0;
	currentTime=minimumArrivalTime;
	printf("%d",currentTime);
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
	{
		if(i==CPUBurstTime[counter]*scalingFactor+tempi)
		{

			tempi=i;
			currentTime+=CPUBurstTime[counter];
			averageWaitingTime+=currentTime;
			counter++;
			printf("%2d",currentTime);
		}
		else
		{
			printf(" ");
		}
	}
	currentTime+=CPUBurstTime[counter];

	printf("%2d\n\n",currentTime);
	averageWaitingTime=averageWaitingTime/numberOfProcesses;
	//printf("Average waiting Time : %f\n",averageWaitingTime);
}
void sjfGChart()
{
	const int maxWidth=100;
	int scalingFactor,i,counter,tempi,currentTime;
	printf("The gantt chart for the given processes is : \n\n");

	scalingFactor=maxWidth/totalCPUBurstTime;
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
	{
		printf("-");
	}
	printf("\n|");
	counter=0,tempi=0;
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
	{
		if(i==CPUBurstTime[counter]*scalingFactor+tempi)
		{
			counter++;
			tempi=i;
			printf("|");
		}
		else if(i==(CPUBurstTime[counter]*scalingFactor)/2+tempi)
		{
			printf("P%d",processNumber[counter]);
		}
		else
		{
			printf(" ");
		}

	}
	printf("|");
	printf("\n");
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
	{
		printf("-");
	}
	printf("\n");

	/* printing the time labels of the gantt chart */
	counter=0;
	tempi=0;
	currentTime=minimumArrivalTime;
	printf("%d",currentTime);
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
	{
		if(i==CPUBurstTime[counter]*scalingFactor+tempi)
		{

			tempi=i;
			currentTime+=CPUBurstTime[counter];
			averageWaitingTime+=currentTime;
			counter++;
			printf("%2d",currentTime);
		}
		else
		{
			printf(" ");
		}
	}
	currentTime+=CPUBurstTime[counter];

	printf("%2d\n\n",currentTime);
	averageWaitingTime=averageWaitingTime/numberOfProcesses;
	averageTurnAroundTime=averageWaitingTime+totalCPUBurstTime/numberOfProcesses;
/*
	printf("Average waiting Time     : %f\n",averageWaitingTime);
	printf("Average Turn Around Time : %f\n",averageTurnAroundTime);*/}

void nonpremprioGChart()
{
	const int maxWidth=100;
	int scalingFactor,i,counter,tempi,currentTime;
	printf("The gantt chart for the given processes is : \n\n");

	scalingFactor=maxWidth/totalCPUBurstTime;
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
	{
		printf("-");
	}
	printf("\n|");
	counter=0,tempi=0;
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
	{
		if(i==CPUBurstTime[counter]*scalingFactor+tempi)
		{
			counter++;
			tempi=i;
			printf("|");
		}
		else if(i==(CPUBurstTime[counter]*scalingFactor)/2+tempi)
		{
			printf("P%d",processNumber[counter]);
		}
		else
		{
			printf(" ");
		}

	}
	printf("|");
	printf("\n");
	for(i=0;i<scalingFactor*totalCPUBurstTime+2+numberOfProcesses;i++)
	{
		printf("-");
	}
	printf("\n");

	/* printing the time labels of the gantt chart */
	counter=0;
	tempi=0;
	currentTime=minimumArrivalTime;
	printf("%d",currentTime);
	for(i=0;i<scalingFactor*totalCPUBurstTime;i++)
	{
		if(i==CPUBurstTime[counter]*scalingFactor+tempi)
		{

			tempi=i;
			currentTime+=CPUBurstTime[counter];
			averageWaitingTime+=currentTime;
			counter++;
			printf("%2d",currentTime);
		}
		else
		{
			printf(" ");
		}
	}
	currentTime+=CPUBurstTime[counter];

	printf("%2d\n\n",currentTime);
	averageWaitingTime=averageWaitingTime/numberOfProcesses;
	averageTurnAroundTime=averageWaitingTime+totalCPUBurstTime/numberOfProcesses;

/*	printf("Average waiting Time     : %f\n",averageWaitingTime);
	printf("Average Turn Around Time : %f\n",averageTurnAroundTime);*/
			}	


