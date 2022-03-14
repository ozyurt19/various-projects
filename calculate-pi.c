#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
double pi;
int t=0,m,c=0,s=0;
printf("enter the number of try=>\n");
scanf("%d",&m);
for (;t<m;t++){
int x,y;
srand(time(NULL)); 
x=-100+rand()%200;
y=-100+rand()%200;
if (((x*x)+(y*y))<=10000){
	s++;
	c++;
}
else {
	s++;
}
}
pi=((4*c)/s);
printf("%lf",pi);
return 0;

}


