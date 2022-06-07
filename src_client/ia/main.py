#!/usr/bin/env python3
##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## main
##


import ctypes
import pathlib
from sys import *

class clientInfo:
    def __init__(self, mySocket):
        self.socket = mySocket
        self.readBuff = ""
        self.writeBuff = ""


def serverCommunication(selectRes, info):
    if (selectRes == 1):
        res = clientLib.read_server(info.socket)
        result = ctypes.cast(res, ctypes.c_char_p)
        info.readBuff = result.value.decode('utf-8')
    return 0

def mainLoop(myClient):
    while (1):
        serverCommunication(clientLib.client_select(), myClient)
        myClient.writeBuff = input("INPUT: ")
        if (myClient.writeBuff != "wait"):
            myClient.writeBuff += '\n'
            clientLib.test(myClient.writeBuff.encode('utf-8'))
    return 0

def main():
    av = argv[1:]
    port = int(av[1])
    myIp = av[0].encode('utf-8')
    mySocket = clientLib.create_client(ctypes.c_char_p(myIp), ctypes.c_int(port))
    if (clientLib.init_info(ctypes.c_int(mySocket)) < 0):
        return -1
    myClient = clientInfo(mySocket)
    mainLoop(myClient)
    return 0

if __name__ == '__main__':
    cLib = pathlib.Path().absolute() / "src_client/client/clientLib.so"
    clientLib = ctypes.CDLL(cLib)
    clientLib.read_server.argtypes = [ctypes.c_int]
    clientLib.read_server.restype = ctypes.POINTER(ctypes.c_char)
    main()
