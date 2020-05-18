def print_rangoli(size):
    x=(size*2-1)*2-1
    for i in range(size):
        print('-'*((x-((i*2+1)*2-1))//2),end="")
        for j in range(size,size-i-1,-1):
            print(chr(96+j),end="")
            if(j!=size-i):
                print("-",end="")
        if size-i+1<size+1:
            print("-",end="")
        for j in range(size-i+1,size+1):
            print(chr(96+j),end="")
            if(j!=size):
                print("-",end="")
        print('-'*((x-((i*2+1)*2-1))//2))
    for i in range(size-2,-1,-1):
        print('-'*((x-((i*2+1)*2-1))//2),end="")
        for j in range(size,size-i-1,-1):
            print(chr(96+j),end="")
            if(j!=size-i):
                print("-",end="")
        if size-i+1<size+1:
            print("-",end="")
        for j in range(size-i+1,size+1):
            print(chr(96+j),end="")
            if(j!=size):
                print("-",end="")
        print('-'*((x-((i*2+1)*2-1))//2))
if __name__ == '__main__':
    n = int(input())
    print_rangoli(n)
