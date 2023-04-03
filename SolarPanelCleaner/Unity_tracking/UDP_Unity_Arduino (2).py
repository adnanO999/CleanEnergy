import socket
import time
import serial

host, port = "127.0.0.1", 25001
data = "1,2,3"

# SOCK_STREAM means TCP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ser = serial.Serial("com4",9600,timeout=1)

try:
    # Connect to the server and send the data
    sock.connect((host, port))
    
    for i in range (10):
        line = ser.readline()   # read a byte
        if line:
            string = line.decode()  # convert the byte string to a unicode string
            #num = int(string) # convert the unicode string to an int
            print(string)
            data = "{},{},{}".format(string,str(i+0.5),str(i))
            print(data)
            sock.sendall(data.encode("utf-8"))
            response = sock.recv(1024).decode("utf-8")
            print (response)
            time.sleep(1)
        
        

    

finally:
    sock.close()
    ser.close()
