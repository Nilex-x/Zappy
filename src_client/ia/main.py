#!/usr/bin/env python3
##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## main
##


import ctypes
from gettext import find
import pathlib
import getopt
import enum
from queue import Queue
from re import A
from sys import *
from turtle import left

ressources = ["linemate","deraumere", "sibur", "mendiane", "phiras", "thystame"]

def findPathToTileFromBroadcast(clientInfo, direction):
    if (direction == 1):
        clientInfo.toSend.put("Forward\n")
    if (direction == 3):
        clientInfo.toSend.put("Left\n")
        clientInfo.toSend.put("Forward\n")
    if (direction == 5):
        clientInfo.toSend.put("Left\n")
        clientInfo.toSend.put("Left\n")
        clientInfo.toSend.put("Forward\n")
    if (direction == 7):
        clientInfo.toSend.put("Right\n")
        clientInfo.toSend.put("Forward\n")
    return (0)
        

def findPathToTile(clientInfo, tile_needed):
    if tile_needed == 0:
        return (1)
    left_tile = 1
    middle_tile = 2
    right_tile = 3
    action = "Forward"
    temp = clientInfo.toSend
    for levels in range(1, clientInfo.lvl + 1):
        print(tile_needed, left_tile, middle_tile, right_tile)
        if (tile_needed < middle_tile and tile_needed >= left_tile):
            clientInfo.toSend.put("Forward\n")
            clientInfo.toSend.put("Left\n")
            print("Forward")
            print("Left")
            for t in range(0, middle_tile-tile_needed):
                print("Forward")
                clientInfo.toSend.put("Forward\n")
            return (1)
        elif (tile_needed > middle_tile and tile_needed <= right_tile):
            clientInfo.toSend.put("Forward\n")
            clientInfo.toSend.put("Right\n")
            print("Forward")
            print("Right")
            for t in range(0, tile_needed-middle_tile):
                print("Forward")
                clientInfo.toSend.put("Forward\n")
            return (1)
        else:
            print(action)
            clientInfo.toSend.put("Forward\n")
        if (tile_needed == middle_tile):
            return (1)
        left_tile += 2*levels+1
        middle_tile += 2*levels+2
        right_tile += 2*levels+3
    clientInfo.toSend = temp
    return (0)
        


# ---------------------- NEEDED ----------------------

upLvl = [
    {
    "player": 1,
    "linemate": 1
    },
    {
    "player": 2,
    "linemate": 1,
    "deraumere": 1,
    "sibur": 1
    },
    {
    "player": 2,
    "linemate": 2,
    "sibur": 1,
    "phiras": 1
    },
    {
    "player": 4,
    "linemate": 1,
    "deraumere": 1,
    "sibur": 2,
    "phiras": 1
    },
    {
    "player": 4,
    "linemate": 1,
    "deraumere": 2,
    "sibur": 1,
    "mendiane": 3
    },
    {
    "player": 6,
    "linemate": 1,
    "deraumere": 2,
    "sibur": 3,
    "phiras": 1
    },
    {
    "player": 6,
    "linemate": 2,
    "deraumere": 2,
    "sibur": 2,
    "mendiane": 2,
    "phiras": 2,
    "thystame": 1
    }
]

def checkRessourceForLevel(iaLvl, inventory):
    for lvl in range(0, 8):
        if (iaLvl == lvl+1):
            for r in inventory: 
                if (r == "food"):
                    continue
                if (upLvl[lvl][r] > inventory[r]):
                    return r
    return (None)

# ---------------------- AI ----------------------

class clientIA:
    def __init__(self):
        self.nbClients = -1
        self.height = -1
        self.width = -1
        self.alive = True
        self.nbPlayers = 1
        self.lvl = 1
        self.N = None
        self.M = None
        self.dir = 0
        self.toSend = Queue(maxsize=0)
        self.cmds = Queue(maxsize=9)
        self.currentCmd = "Nothing"
        self.isMeeting = False
        self.nbMeeting = 1
        self.hasArrived = False
        self.ressources = {
            "food": 10,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }


    def inventory(self, srvMsg):
        srvMsg = srvMsg[1:-1]
        inv = srvMsg.split(",")
        for rsc in inv:
            a = rsc.split()
            self.ressources[a[0]] = int(a[1])

    def look(self, srvMsg):
        if srvMsg == None:
            return
        srvMsg = srvMsg[1:-1]
        print(srvMsg)
        look_list = srvMsg.split(",")
        print("look = ",  look_list)
        ressource = checkRessourceForLevel(self.lvl, self.ressources)
        if (self.ressources["food"] < 8 or ressource == None):
            ressource = "food"
        tile_needed = -1
        i = 0
        for l in look_list:
            if l.find(ressource) != -1:
                tile_needed = i
            i += 1
        if not findPathToTile(self, tile_needed):
            print("Not found...")
            self.toSend.put("Forward\n")

    def ejected(self):
        while (not self.cmds.empty()):
            self.cmds.get()
        return 1

    def handleMessage(self, message):
        self.dir = int(message[8])
        self.M = message[11:]

    def serverResponse(self, srvMsg):
        if srvMsg == None:
            return 1
        srvMsg = srvMsg[:-1]
        if srvMsg == "dead":
            return -1
        if srvMsg.find("eject") >= 0:
            return self.ejected()
        if srvMsg.find("message") >= 0:
            return self.handleMessage(srvMsg)
        curr = self.currentCmd.split()[0]
        if curr == "Look":
            self.look(srvMsg)
        elif curr == "Inventory":
            self.inventory(srvMsg)
        elif curr == "Connect_nbr":
            self.nbPlayers = int(srvMsg)
        elif curr == "Incantation":
            if srvMsg == "Elevation underway":
                return 1
            else:
                self.lvl = int(srvMsg[14])
        if self.cmds.empty():
            self.currentCmd = "Nothing"
        else:
            self.currentCmd = self.cmds.get()
        return 1

    def actionAi(self):
        if self.toSend.empty():
            if self.cmds.empty():
                action = input("Input: ")
                if (action == "wait"):  #temp
                    return action       #temp
                self.toSend.put(action)
            else:
                return "wait"
        if not self.cmds.full():
            action = self.toSend.get()
            self.cmds.put(action)
        if self.currentCmd == "Nothing":
            self.currentCmd = self.cmds.get()
        return action





# ---------------------- NETWORK ----------------------

class clientInfo:
    def __init__(self, mySocket):
        self.socket = mySocket
        self.connected = 0
        self.readBuff = None
        self.writeBuff = None
        self.ai = clientIA()


    def serverCommunication(self, selectRes):
        if (selectRes == 1):
            res = clientLib.read_server(self.socket)
            result = ctypes.cast(res, ctypes.c_char_p)
            self.readBuff = result.value.decode('utf-8')
            if self.readBuff == "end":
                return -1
            if self.ai.serverResponse(self.readBuff) < 0:
                return -1
            print(self.readBuff)
        return 0

    def mainLoop(self):
        run = 1
        while (run > -1):
            run = clientLib.client_select()
            if self.serverCommunication(run) < 0:
                print("server error")
                return -1
            self.writeBuff = self.ai.actionAi()
            self.readBuff = None


#            self.serverCommunication(run)
            #if (self.ai.isMeeting == True and self.ai.hasArrived == True):
            #    self.ai.toSend.put("Broadcast meeting\n")
                    
            if (self.writeBuff == "Look"):
                self.ai.look(self.readBuff)
                resrc_string = ""
                print(self.ai.ressources)
                for i in range(0,6):
                    resrc_string += str(self.ai.ressources[ressources[i]]) + " "
                print(resrc_string)
                self.ai.toSend.put("Broadcast inventory " + resrc_string + "\n")
                
            #if (self.readBuff.find("message")):
                #if (self.readBuff.find("inventory")):
                #    res = []
                #    for r in self.readBuff.split(" "):
                #        if (r == "Broadcast" or r == "inventory"):
                #            continue
                #        res.append(int(r))
                #    print("res = ", res)
                #    inventory = []
                #    for i in range(0, 6):
                #        inventory.append(res[i] + self.ai.ressources[i])
                #    if checkRessourceForLevel(self.ai.lvl, inventory) == None:
                #        self.ai.toSend.put("Broadcast meeting\n")
                #        self.ai.isMeeting = True
                #        self.ai.hasArrived = True
                #if (self.readBuff.find("meeting")):
                #    direction = int(self.readBuff.split(" ")[1])
                #    self.ai.isMeeting = True
                #    if (direction != 0):
                #        findPathToTileFromBroadcast(self, direction)
                #    else:
                #        self.ai.hasArrived = True
                #        self.ai.toSend.put("Broadcast arrived\n")
                #
                #if(self.readBuff.find("arrived") and int(self.readBuff.split(" ")[1]) == 0):
                #    self.ai.nbMeeting += 1
                #    if (self.ai.nbMeeting == upLvl[self.ai.lvl]["player"]):
                #        self.ai.toSend.put("Incantation\n")
                #        self.ai.nbMeeting = 1
                #        self.ai.hasArrived = False
                #        self.ai.isMeeting = False
                
            if (self.writeBuff != "wait"):
                self.writeBuff += '\n'
                clientLib.test(self.writeBuff.encode('utf-8'))
            self.readBuff = None
        return 0


    def getPosnTeam(self):
        servMsg = self.readBuff.split("\n")
        for i in servMsg:
            splited = i.split()
            if ((len(splited) == 1) and (splited[0].isdigit())):
                self.ai.nbClients = int(splited[0])
            if ((len(splited) == 2) and (splited[0].isdigit()) and (splited[1].isdigit())):
                self.ai.width = int(splited[0])
                self.ai.height = int(splited[1])
        if (self.ai.nbClients >= 0 and self.ai.width >= 0 and self.ai.height >= 0):
            self.connected = 1

    def connection(self, team):
        clientLib.test(team.encode('utf-8'))
        while (not self.connected):
            res = clientLib.client_select()
            self.serverCommunication(res)
            if (self.readBuff != None):
                self.getPosnTeam()


# ---------------------- BEGIN PROGRAM ----------------------

def manageFlags(port, teamName, myIp):
    if (port == None or teamName == None):
        print("wrong flags")
        exit(84)
    if (not port.isdigit()):
        print("wrong port")
        exit(84)

def displayHelp():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport is the port number")
    print("\tname is the name of the team")
    print("\tmachine is the name of the machine; localhost by default")
    exit(0)

def main():
    port = None
    myIp = None
    teamName = None
    av = argv[1:]

    if (len(av) == 1 and av[0] == "-help"):
        displayHelp()
    try:
        opts, args = getopt.getopt(av, '-p:-n:-h:')
    except:
        print("Wrong flag")
        return 84
    for opt, arg in opts:
        if opt in ("-p"):
            port = arg
        elif opt in ("-n"):
            teamName = arg + '\n'
        elif opt in ("-h"):
            myIp = arg
    manageFlags(port, teamName, myIp)
    if (myIp == None):
        myIp = "127.0.0.1"
    mySocket = clientLib.create_client(ctypes.c_char_p(myIp.encode('utf-8')), ctypes.c_int(int(port)))
    if ((mySocket < 0) or (clientLib.init_info(ctypes.c_int(mySocket)) < 0)):
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
