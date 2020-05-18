class helpAditiya:
    def printCheckParkingNo(self, park,customerpark):
        
        lenCustomerpark = len(customerpark)
        lenPark = len(park)
        listCustomparkPark = []
        
        if lenCustomerpark == 1:   
             return(" ".join([str(i) for i in range(lenPark)]))
                
        for i in range(lenPark-lenCustomerpark+1):
            subPark = park[i:i+lenCustomerpark]
           # print(subPark,customerpark)
            if subPark == customerpark or self.checkParkinglot(subPark,customerpark,lenCustomerpark):
                listCustomparkPark.append(str(i))
        
        return(" ".join(listCustomparkPark)) if len(listCustomparkPark)>0 else "No Match!"
            
    def checkParkinglot(self, park,customerpark,lenCustomerpark):
        """
        split string cutomerpark/2. 
        If all piece is vrong - it is correct parking lot(park), else check wrong part recursivly untill len substring is == 1.
        It mean that full substring have 1 wrong char - subPark is customerpark
        """
        
        if lenCustomerpark==1:
            return True 
            
        subLen = int((lenCustomerpark+1)/2)
        if park[:subLen] == customerpark[:subLen]:
            return self.checkParkinglot(park[subLen:],customerpark[subLen:],lenCustomerpark-subLen)
        elif park[subLen:] == customerpark[subLen:]:
            return self.checkParkinglot(park[:subLen],customerpark[:subLen],subLen)
        else:
            return False
        
        

task = helpAditiya()
for _ in range(int(input())):
    park, customerpark = input().split()
    print(task.printCheckParkingNo(park,customerpark))
