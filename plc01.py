import time
from machine import Pin
from machine import SPI

cs = Pin(2, Pin.OUT)    # create output pin on GPIO0
cs2 = Pin(0, Pin.OUT) 
out_en = Pin(4, Pin.OUT) 
hspi = SPI(1, baudrate=10000000, polarity=0, phase=0)
wbuf = bytearray(2)      # create a buffer
rbuf = bytearray(2) # create a buffer
wbuf2 = bytearray(2)      
rbuf2 = bytearray(2) 

udata = 0
out_en.on()
  
while True:
  cs.off()                 # set pin to "on" (high) level
  hspi.write_readinto(wbuf, rbuf) # write buf to MOSI and read MISO back into buf
  cs.on()
  udata = udata + 1
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
  wbuf2[1] = parityData
  wbuf2[0] = udata
  cs2.off()
  hspi.write_readinto(wbuf2, rbuf2)
  cs2.on()
  time.sleep(.02)
  #print(bin(rbuf[0]))
