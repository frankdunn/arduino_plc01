import time
from machine import Pin , SPI
import Plc01

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
  wbuf2[1] = Plc01.parityCalc(udata)
  wbuf2[0] = udata
  cs2.off()
  hspi.write_readinto(wbuf2, rbuf2)
  cs2.on()
  time.sleep(.02)
  #print(bin(rbuf[0]))
