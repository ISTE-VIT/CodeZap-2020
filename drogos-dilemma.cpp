#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    //code
    int t; cin>>t;
    while(t--){
        int n,m; cin>>n>>m; int arr1[n+1],arr2[m+1];
        for(int x=0; x<n; x++) cin>>arr1[x];
        arr1[n]=0;
        for(int y=0; y<m; y++) cin>>arr2[y];
        arr2[m]=0;
        int i=0,j=0,sum1=0,sum2=0,tsum=0,l1=0,l2=0;

        while(i<n && j<m){
            if(arr1[i]<arr2[j]){
                sum1+=arr1[i];
                i++;
            }
            else if(arr2[j]<arr1[i]){
                sum2+=arr2[j];
                j++;
            }
            else{
                if(arr1[i]==arr1[i+1]){
                    sum1+=arr1[i];
                    i++;
                }
                else if(arr2[j]==arr2[j+1]){
                    sum2+=arr2[j];
                    j++;
                }
                else{
                    tsum=tsum+max(sum1,sum2)+arr1[i];
                    sum1=0; sum2=0;
                    i++; j++;
                }
                l1=i; l2=j;
            }
            //cout<<"tsum:"<<tsum<<endl;
        }

        sum1=0;sum2=0;
        while(l1<n){
            sum1+=arr1[l1];
            l1++;
        }
        while(l2<m){
            sum2+=arr2[l2];
            l2++;
        }
        tsum+=max(sum1,sum2);
        cout<<tsum<<endl;
    }
    return 0;
}
