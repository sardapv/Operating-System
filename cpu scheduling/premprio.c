void drawGanttChart();
void calculateProcessSequence();
int findAptProcessNumber(int);
#include<stdlib.h>
#include<stdio.h>
int numberOfProcesses,totalCPUBurstTime,*arrivalTime,*CPUBurstTime,*CPUBurstTimeCopy,*processNumber,minimumArrivalTime,*processSequenceForEachSecond,*waitingTime,*priority;
float averageWaitingTime,averageTurnAroundTime;int timeQuantum;
float averageWaitingTime=0;

/*arrays used to draw Gantt Chart*/
int *processNumberGantt,*CPUBurstTimeGantt,ganttSize;

int main()
{
	int i,j,temp;

	arrivalTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	CPUBurstTime=(int*)malloc(sizeof(int)*numberOfProcesses);
	CPUBurstTimeCopy=(int*)malloc(sizeof(int)*numberOfProcesses);
	processNumber=(int*)malloc(sizeof(int)*numberOfProcesses);
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
		printf("Priority : ");
		scanf("%d",&priority[i]);*/
		CPUBurstTimeCopy[i]=CPUBurstTime[i];
		totalCPUBurstTime+=CPUBurstTime[i];
		if(minimumArrivalTime>arrivalTime[i])
			minimumArrivalTime=arrivalTime[i];
	}
	processSequenceForEachSecond=(int*)malloc(sizeof(int)*totalCPUBurstTime);

	/* this function calculates the process sequence for each second. */

	calculateProcessSequence();
/*	printf("\nAverage Waiting Time     = %f\n",averageWaitingTime);
	printf("\nAverage Turn Around Time = %f\n\n",averageTurnAroundTime);
*/
printf("\n\n================================================ PREMPTIVE PRIORITY ====================================\n");
	drawGanttChart();
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
