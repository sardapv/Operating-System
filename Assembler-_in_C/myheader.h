#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *mp,*ip,*tp,*fp,*llp,*pt;

typedef struct symbol{
	int symbol_no;
	char symbol_name[10];
	int symbol_addr;
}symbol;

typedef struct litral{
	int litral_no;
	char litral_name[10];
	int litral_addr;
}litral;

int pooltable[64];
void generate_mc();
void accept();
/*for pass1*/

FILE *sp, *tp;
char INS[][7] = {"START","END","LTORG","EQU","ORIGIN"};
char ASD[][6] ={"MOVER","MOVEM","ADD","SUB","MUL","DIV"};
char reg[][5] = {"AREG","BREG","CREG","DREG"};
char declstat[][3] = {"DC","DS"};
int POOLTAB [10];
int countl = 0,counts = 0,countp=0,p;

symbol s[64];
litral l[64]; // for both of the passes

int search_in_INS(char tok1[16]);
int search_in_ASD(char tok1[16]);
int search_in_reg(char tok1[16]);
int search_in_DL(char tok1[16]);
int search_in_symbol_tab(char tok1[16], int counts);
int litral_value(char tok2[16]);
void pass1();
void display_symbol_table();
void display_litral_table();
void display_Pool_Tab();
