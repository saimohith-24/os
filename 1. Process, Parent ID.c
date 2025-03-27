#include<stdio.h>
#include<unistd.h>
int main()
{
printf("Process ID: %d\n", getpid() ); printf("Parent Process ID: %d\n", getpid() );
return 0;
}

Output:
Process ID: 9935
Parent Process ID: 9935
