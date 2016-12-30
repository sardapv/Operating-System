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
int main (){

	init();
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

	secondchance();
	return 0;
}
