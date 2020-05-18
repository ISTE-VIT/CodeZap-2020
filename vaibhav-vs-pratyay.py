def getSum( BITree, index): 
    sum = 0  
    
    while (index > 0): 

        sum += BITree[index] 

        index -= index & (-index) 

    return sum
 
def updateBIT(BITree, n, index, val): 

    while (index <= n): 

        BITree[index] += val 

        index += index & (-index) 

def getInvCount(arr, n): 

    invcount = 0 

    maxElement = max(arr) 

    BIT = [0] * (maxElement + 1) 
    for i in range(n - 1, -1, -1): 

        invcount += getSum(BIT, arr[i] - 1) 
        updateBIT(BIT, maxElement, arr[i], 1) 
    return invcount 
    
# Driver code 
t=int(input())
for _ in range(t): 
    n,X=map(int,input().split())
    arr=list(map(int,input().split()))
    shifts=getInvCount(arr, n)
    if shifts>X:
        print("Pratyay")
    else:
        print("Vaibhav")
