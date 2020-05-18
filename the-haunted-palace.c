#include <stdio.h>
#include <stdlib.h>
int comp(const void * a,const void *b)
{
return (*(int *)a) - (*(int *)b);
}


int min(int a,int b)
{
        return a < b ? a:b;
}

int main()
{
        int t,n;
        long ans = 0;
        int *arr;
        scanf("%d",&t);
while(t--)
{
        scanf("%d",&n);
        arr = malloc(sizeof(int)*n);
        int i;
        ans = 0;
for(i = 0; i < n; i++)
scanf("%d",arr+i);
qsort(arr,n,sizeof(int),comp);

while(n > 3)
{
ans = ans + min((2*arr[0]+arr[n-1]+arr[n-2]),(arr[0]+2*arr[1]+arr[n-1]));
n -= 2;
}
if (n == 3)
ans += (arr[0]+arr[1]+arr[2]);
else if (n == 2)
ans += arr[1];
else
ans += arr[0];
printf("%ld\n",ans);
free(arr);
}
return 0;
}
