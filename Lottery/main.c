#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sayi_uret()
{
    int i,j,a[6],temp;
    for(i=0;i<6;i++)
        a[i]=rand()%49+1;
    for(i=0;i<6;i++)
    {
                    for(j=0;j<6;j++)
                    {
                                    if(a[i]>a[j])
                                        a[i]=a[i];
                                    else
                                    {
                                        temp=a[i];
                                        a[i]=a[j];
                                        a[j]=temp;
                                    }
                    }
    }                        
    for(i=0;i<6;i++)
    if(a[i]<10)
        printf(" %d  ",a[i]);
        else
        printf("%d  ",a[i]);
}
int main()
{
  printf("                      Welcome to Lottery Game\n\n");
  int i,j;
  srand(time(0));
  printf("                  How Many Colomns Do You Want :");
  scanf("%d",&j);
  printf("\n");
  if(j<100)
  {
           for(i=0;i<j;i++)
           {
                           if(i<9)
                           {
                           printf("%d. colomn :   ",i+1);
                           }
                           else
                           {
                           printf("%d. colomn :  ",i+1);
                           }
                           sayi_uret();
                           printf("\n\n");
                                  
           }
  }
  else
     printf("                Please Enter The Numbers Less Than 100\n");
  system("PAUSE");	
  return 0;
}
