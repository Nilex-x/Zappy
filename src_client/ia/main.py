#!/usr/bin/env python3
##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## main
##


import ctypes
import pathlib
import getopt
from sys import *

class clientIA:
    def __init__(self):
        self.nbClients = -1
        self.posX = 0
        self.posY = 0
        self.rsr = []
        self.n = 0
        self.O = 1
        self.L = 0
        self.e = 0
        self.T = 0
        self.N = None
        self.R = 0
        self.M = None
        self.i = 0

class clientInfo:
    def __init__(self, mySocket):
        self.socket = mySocket
        self.connected = 0
        self.readBuff = ""
        self.writeBuff = ""
        self.ai = clientIA()

    def getPosnTeam(self):
        servMsg = self.readBuff.split("\n")
        for i in servMsg:
            splited = i.split()
            if ((len(splited) == 1) and (splited[0].isdigit())):
                self.ai.nbClients = int(splited[0])
            if ((len(splited) == 2) and (splited[0].isdigit()) and (splited[1].isdigit())):
                self.ai.posX = int(splited[0])
                self.ai.posY = int(splited[1])
        if (self.ai.nbClients >= 0 and self.ai.posX >= 0 and self.ai.posY >= 0):
            self.connected = 1

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
            self.serverCommunication(run)
            self.writeBuff = input("INPUT: ")
            if (self.writeBuff != "wait"):
                self.writeBuff += '\n'
                clientLib.test(self.writeBuff.encode('utf-8'))
        return 0

    def connection(self, team):
        clientLib.test(team.encode('utf-8'))
        while (not self.connected):
            res = clientLib.client_select()
            self.serverCommunication(res)
            self.getPosnTeam()


def manageFlags(port, teamName, myIp):
    if (not port.isdigit()):
        print("wrong port")
        exit(84)
    if (port == None or teamName == None):
        print("wrong flags")
        exit(84)
    if (myIp == None):
        myIp = "127.0.0.1"
    teamName += '\n'

def displayHelp():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport is the port number")
    print("\tname is the name of the team")
    print("\tmachine is the name of the machine; localhost by default")

def main():
    port = None
    myIp = None
    teamName = None

    try:
        opts, args = getopt.getopt(argv[1:], '-p:-n:-h:', "help")
    except:
        print("Wrong flag")
        return 84
    for opt, arg in opts:
        if opt in ["-help"]:
            displayHelp()
            exit(84)
        elif opt in ["-p"]:
            port = arg
        elif opt in ["-n"]:
            teamName = arg
        elif opt in ["-h"]:
            myIp = arg.encode('utf-8')

    manageFlags(port, teamName, myIp)
    mySocket = clientLib.create_client(ctypes.c_char_p(myIp), ctypes.c_int(int(port)))
    if (mySocket < 0 or clientLib.init_info(ctypes.c_int(mySocket)) < 0):
        print("failed connection")
        return 84
    myClient = clientInfo(mySocket)
    myClient.connection(teamName)
    myClient.mainLoop()
    return 0

if __name__ == '__main__':
    cLib = pathlib.Path().absolute() / "src_client/client/clientLib.so"
    clientLib = ctypes.CDLL(cLib)
    clientLib.read_server.argtypes = [ctypes.c_int]
    clientLib.read_server.restype = ctypes.POINTER(ctypes.c_char)
    main()
