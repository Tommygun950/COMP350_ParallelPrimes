#include <stdio.h>
#include <stdlib.h>

int isprime(int n)
{
	for(int i=2; i<n; i++)
		if(n%i==0)
			return 0;
	return 1;
}

int main(int argc, char* argv[])
{
	int start=atoi(argv[1]);
	int end=atoi(argv[2]);
	printf("\tcount primes instance starting at %d and ending at %d\n",start,end-1);
	int count=0;
	for(int p=start; p<end; p++)
		if(isprime(p))
			count++;
	printf("\tcount primes instance for %d to %d is %d\n",start,end-1,count);
	return count;
}
