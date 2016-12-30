
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int SIZE ;
int *frame;

int full=0;//To check whether all frames are filled
int a[21],n;//To take the input of reference string
//int frame[SIZE];//This is for frames
int repptr=0;//The pointer for the page that needs to be replaced
int count=0;//For counting number of page faults

/*lfu++*/
int *ctr;
int repptr;

/*lru++*/
int *stk;

/*lrucounter++*/
static int f=0;//This is a counter that keeps track of current time

/*mfu++*/
//static int f;

/*opt++*/

/*sc++*/
int *ref;

/*esc++*/
char r=1;
unsigned char *addref;

int Search(int ele);
int display();
int Pagerep(int ele);
int Pagefault(int ele);


