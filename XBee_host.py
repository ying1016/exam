import serial
import time

# XBee setting
serdev = '/dev/tty.usbserial-AC00CJUR'
s = serial.Serial(serdev, 9600, timeout=3)

s.write('+++'.encode())
char = s.read(3)
print('Enter AT mode.')
print(char.decode())

s.write('ATMY 0x101\r\n'.encode())
char = s.read(3)
print('Set MY 0x101.')
print(char.decode())

s.write('ATDL 0x10\r\n'.encode())
char = s.read(3)
print('Set DL 0x10.')
print(char.decode())

s.write('ATID 0x1010\r\n'.encode())
char = s.read(3)
print('Set PAN ID 0x1010.')
print(char.decode())

s.write('ATWR\r\n'.encode())
char = s.read(3)
print('Write config.')
print(char.decode())

s.write('ATCN\r\n'.encode())
char = s.read(3)
print('Exit AT mode.')
print(char.decode())

print('')
print('Start Communication')
send = 'start'
while 1:
    send = input()
    print(send)
    # send to remote
    s.write(send.encode())        
    line = s.read(20)
    print(line.decode())
    print('')

s.close()
