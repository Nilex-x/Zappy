##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## main
##

#!/usr/bin/env python3

import ctypes
import pathlib
from sys import *

class clientInfo:
    def __init__(self, mySocket):
        self.socket = mySocket
        self.read = 1
        self.write = 0
        self.sendMessage = ""
    
    def clientSelect(self):
        ctypes.Structure

def mainLoop(myClient):
    while (1):
        inp = input("INPUT: ")
        send = inp.encode('utf-8')
        clientL.write_to_serv(ctypes.c_char_p(send), ctypes.c_int(myClient.socket))
    return 0

def main():
    av = argv[1:]
    port = int(av[1])
    myIp = av[0].encode('utf-8')
    mySocket = clientL.create_client(ctypes.c_char_p(myIp), ctypes.c_int(port))
    myClient = clientInfo(mySocket)

    mainLoop(myClient)
    return 0

if __name__ == '__main__':
    clientLib = pathlib.Path().absolute() / "../client/clientLib.so"
    clientL = ctypes.CDLL(clientLib)
    main()
