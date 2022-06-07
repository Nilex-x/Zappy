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

    def validate_connection(self):
        self.writeBuff = ""

    def serverCommunication(self, selectRes):
        if (selectRes == 1):
            res = clientLib.read_server(self.socket)
            result = ctypes.cast(res, ctypes.c_char_p)
            self.readBuff = result.value.decode('utf-8')
            print(self.readBuff)
        return 0

    def mainLoop(self):
        run = 1
        while (run > -1):
            run = clientLib.client_select()
            print(run)
            self.serverCommunication(run)
            self.writeBuff = input("INPUT: ")
            if (self.writeBuff != "wait"):
                self.writeBuff += '\n'
                clientLib.test(self.writeBuff.encode('utf-8'))
        return 0


def manageFlags(av):
    if (len(av) == 1 and av[0] == "-help"):
        print("USAGE: ./zappy_ai -p port -n name -h machine")
        print("\tport is the port number")
        print("\tname is the name of the team")
        print("\tmachine is the name of the machine; localhost by default")
        return 1
    if (len(av) != 6):
        return -1
    if (av[0] != "-p" or av[2] != "-n" or av[4] != "-h"):
        return -1
    if (not av[1].isdigit()):
        return -1
    return 0

def main():
    av = argv[1:]
    flags = manageFlags(av)
    if (flags < 0):
        print("wrong args")
        return 84
    if (flags == 1):
        return 0
    port = int(av[1])
    teamName = av[3]
    teamName += '\n'
    myIp = av[5].encode('utf-8')
    mySocket = clientLib.create_client(ctypes.c_char_p(myIp), ctypes.c_int(port))
    if (mySocket < 0 or clientLib.init_info(ctypes.c_int(mySocket)) < 0):
        print("failed connection")
        return 84
    myClient = clientInfo(mySocket)
    clientLib.test(teamName.encode('utf-8'))
    myClient.mainLoop()
    return 0

if __name__ == '__main__':
    cLib = pathlib.Path().absolute() / "src_client/client/clientLib.so"
    clientLib = ctypes.CDLL(cLib)
    clientLib.read_server.argtypes = [ctypes.c_int]
    clientLib.read_server.restype = ctypes.POINTER(ctypes.c_char)
    main()
