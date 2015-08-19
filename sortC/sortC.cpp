// sort.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#define MAX 10

int _tmain(int argc, _TCHAR* argv[])
{
	int a[MAX]={5,1,8,7,9,4,6,3,2,10};
	int b[sizeof(a) / sizeof(int)]={};
    int i;
    void insertion(int*a,int n);//函数声明
    void selection(int *a, int n);
	void bubble(int *a, int n);
    void quick(int *a, int low,int high);
	int su_sum(int n);
	void shell(int *a, int n);
    void merge(int *a,int *b, int first, int last);
	int fibonacci_iteration(int n);
    int fibonacci_recurrence(int n);
		
	printf("%d \n",su_sum(MAX));
	printf("%d \n",fibonacci_iteration(MAX));
	printf("%d \n",fibonacci_recurrence(MAX));
    //insertion(a,MAX);
    //selection(a, MAX);
	//bubble(a,MAX);
	//quick(a,0,MAX-1);
	//shell(a,MAX);
	merge(a,b,0,MAX);
	printf("after:\n");
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    getchar();
	return 0;
}


int fibonacci_iteration(int n)
{
	int f0=1,f1=1;
	int fibo;
	if(n==1||n==2)
		return 1;
	else
	{
for(int i=3;i<=n;i++)
{
fibo=f0+f1;
f0=f1;
f1=fibo;
}
return fibo;
	}
}

int fibonacci_recurrence(int n)
{
if (n==1||n==2)
return 1;
else
return (fibonacci_recurrence(n-1)+fibonacci_recurrence(n-2));
}

int su_sum(int n) //求1到n里素数之和
{
int i,j;
int sum;
sum=0;

for (i=2; i<=n; i++)
{
  // 为什么是sqrt(i)，思考一下 
  for (j=2; j<=i/2; j++)
  {
   // i被j整除，显然不是素数了 
   if (i%j == 0) break;
  }
  // i不能被2~sqrt(i)间的数整除,素数也 
  if (j > i/2)
  {
   sum += i;
  }
}
return sum;
}


void insertion(int *a, int n)
{
	int i,j,key;
	for(i=1;i<n;i++)
	{
		key=a[i];
		for(j=i;j>0&&a[j-1]>key;j--)
		{		
			a[j]=a[j-1];
		}
	    a[j]=key;
	}
}
void selection(int *a, int n)
{
	int i,j,min_index;
	for(i=0;i<n-1;i++)
	{
		min_index=i;
		for(j=i+1;j<n;j++)
		{
			if(a[min_index]>a[j])
			{
			min_index=j;
			}
		}
		if(min_index!=i)
		{
			int temp=a[min_index];
            a[min_index]=a[i];
			a[i]=temp;
		}
	}
}
void bubble(int *a, int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{	
			int temp=a[j];
			a[j]=a[j+1];
			a[j+1]=temp;
			}
		}
	}
}

static int partition(int *a, int low, int high)
{
int pivot=a[low];
while(low<high)
{
	while(low<high&&pivot<a[high])high--;
	a[low]=a[high];
	while(low<high&&pivot>=a[low])low++;
	a[high]=a[low];
}
a[low]=pivot;
return low;
}
void quick(int *a, int low,int high)
{
	int loc=0;
	if(low<high)
	{
		loc=partition(a,low,high);
	    quick(a,low,loc-1);
		quick(a,loc+1,high);
	}
}

void shell(int *a, int n)
{
	int i,j,temp,group;
	for(group=n/2;group>0;group/=2)
	{
		for(i=group;i<n;i++)
		{
			for(j=i-group;j>=0;j-=group)
				if(a[j]>a[j+group])
				{
					temp=a[j];
					a[j]=a[j+group];
					a[j+group]=temp;
				}
		}
	}
}

void merge_util(int *a,int *b,int first, int mid,int last)
{
	int i=first,j=mid,k=0;
	while(i<mid&&j<last)
		if(a[i]<a[j])
			b[k++]=a[i++];
		else
			b[k++]=a[j++];

	while(i<mid)
		b[k++]=a[i++];
	while(j<last)
		b[k++]=a[j++];

	for(int v=0;v<k;v++)
		a[first+v]=b[v];
}

void merge(int *a, int *b, int first, int last)
{
	if(first+1<last)
	{
		int mid=(first+last)/2;
		//printf("%d,%d,%d",first,mid,last);
		merge(a,b,first,mid);
		merge(a,b,mid,last);
		merge_util(a,b,first,mid,last);
	}
}