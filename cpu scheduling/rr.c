void drawGanttChart();
void calculateProcessSequence();
int findAptProcessNumber(int,int,int);
#include<stdlib.h>
#include<stdio.h>
int numberOfProcesses,totalCPUBurstTime,*arrivalTime,*CPUBurstTime,*CPUBurstTimeCopy,*processNumber,minimumArrivalTime,*processSequenceForEachSecond,*waitingTime,timeQuantum;
float averageWaitingTime,averageTurnAroundTime;
float averageWaitingTime=0;

/*arrays used to draw Gantt Chart*/
int *processNumberGantt,*CPUBurstTimeGantt,ganttSize;

int main()
{
	int i,j,temp;

	printf("Enter the number of processes : ");
	scanf("%d",&numberOfProcesses);
	printf("Enter the Time Quantum : ");
	scanf("%d",&timeQuantum);
	arrivalTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	CPUBurstTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	CPUBurstTimeCopy=(int*)malloc(sizeof(int)*numberOfProcesses);
	processNumber=(int*)malloc(sizeof(int)*numberOfProcesses);
	waitingTime=(int*)malloc(sizeof(int)*numberOfProcesses);

	minimumArrivalTime=2147483647;

	for(i=0;i<numberOfProcesses;i++)
	{
		waitingTime[i]=0;
		processNumber[i]=i;
		printf("\nEnter the data for process number : %d\n",i);
		printf("\n");
		printf("Arrival Time   : ");
		scanf("%d",&arrivalTime[i]);
		printf("CPU Burst time : ");
		scanf("%d",&CPUBurstTime[i]);
		CPUBurstTimeCopy[i]=CPUBurstTime[i];
		totalCPUBurstTime+=CPUBurstTime[i];
		if(minimumArrivalTime>arrivalTime[i])
		{
			minimumArrivalTime=arrivalTime[i];
		}
	}

	/*
	   implementing bubble sort algorithm
	   sorting processes on the basis of arrival time
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

	processSequenceForEachSecond=(int*)malloc(sizeof(int)*totalCPUBurstTime);

	/* this function calculates the process sequence for each second. */

	calculateProcessSequence();
	printf("\nAverage Waiting Time     = %f\n",averageWaitingTime);
	printf("\nAverage Turn Around Time = %f\n\n",averageTurnAroundTime);

	drawGanttChart();
}

void calculateProcessSequence()
{
	int i,j,pNumber=processNumber[0],prevProcess,tempCPUBurstTime,counter=0,prevProcesss;
	for(i=minimumArrivalTime;i<totalCPUBurstTime + minimumArrivalTime;i++)
	{
		/* here i denotes the current time */
		prevProcess=pNumber;
		pNumber=findAptProcessNumber(i,pNumber,counter);
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

int findAptProcessNumber(int currentTime,int currentProcess,int time)
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

void drawGanttChart()
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
