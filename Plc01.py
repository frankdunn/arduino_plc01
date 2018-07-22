def parityCalc(udata):
     P0 = udata^(udata>>1)
     P0 = P0 ^(P0 >> 2)
     P0 = P0 ^(P0 >> 4)
     P0 = P0 & 0x01
     P1 = udata^(udata>>2)
     P1 = P1 ^ (P1 >> 4)
     P2 = P1 & 0x01
     P1 = P1 & 0x02
     P1 = P1 >> 1
     nP0 = (~P0) & 0x01
     parityData = (P2<<3)|(P1<<2)|(P0<<1)|nP0 
     return parityData
