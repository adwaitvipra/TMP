/*
 * TOWER OF HANOI
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void TOH(int n , int src, int aux, int dest)
{
	if(n>0)
	{	//Move n-1 disks from src to aux using dest as auxillary tower
		TOH(n-1, src, dest, aux);
		//Move one remaining disk from src to dest
		printf("%d %d %d\n", src, aux, dest);
		//Move n-1 disks from aux to dest using src as auxillay tower
		TOH(n-1, aux, src, dest);
	}
	return ;
}

int main(int argc, char const *argv[])
{
	int number = atoi(argv[1]);

	TOH(number, 1, 2, 3);
	return 0;
}


