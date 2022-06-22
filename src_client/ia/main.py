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
from queue import Queue
from sys import *

ressources = ["linemate","deraumere", "sibur", "mendiane", "phiras", "thystame"]

def findPathToTileFromBroadcast(clientInfo, direction):
    if (direction == 1):
        clientInfo.toSend.put("Forward")
    if (direction == 3):
        clientInfo.toSend.put("Left")
        clientInfo.toSend.put("Forward")
    if (direction == 5):
        clientInfo.toSend.put("Left")
        clientInfo.toSend.put("Left")
        clientInfo.toSend.put("Forward")
    if (direction == 7):
        clientInfo.toSend.put("Right")
        clientInfo.toSend.put("Forward")
    return (0)


# ---------------------- NEEDED ----------------------

upLvl = [
    {
    "player": 1,
    "linemate": 1,
    "deraumere": 0,
    "sibur": 0,
    "mendiane": 0,
    "phiras": 0,
    "thystame": 0
    },
    {
    "player": 2,
    "linemate": 1,
    "deraumere": 1,
    "sibur": 1,
    "mendiane": 0,
    "phiras": 0,
    "thystame": 0
    },
    {
    "player": 2,
    "linemate": 2,
    "sibur": 1,
    "phiras": 1,
    "deraumere": 0,
    "mendiane": 0,
    "thystame": 0
    },
    {
    "player": 4,
    "linemate": 1,
    "deraumere": 1,
    "sibur": 2,
    "phiras": 1,
    "mendiane": 0,
    "thystame": 0
    },
    {
    "player": 4,
    "linemate": 1,
    "deraumere": 2,
    "sibur": 1,
    "mendiane": 3,
    "phiras": 0,
    "thystame": 0
    },
    {
    "player": 6,
    "linemate": 1,
    "deraumere": 2,
    "sibur": 3,
    "phiras": 1,
    "mendiane": 0,
    "thystame": 0
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



# ---------------------- AI ----------------------

class clientIA:
    def __init__(self):
        self.nbClients = -1
        self.height = -1
        self.width = -1
        self.alive = True
        self.nbMeeting = 1
        self.isMeeting = False
        self.hasArrived = False
        self.lvl = 1
        self.N = None
        self.M = None
        self.dir = 0
        self.drop = 0
        self.incantation = False
        self.toSend = Queue(maxsize=0)
        self.cmds = Queue(maxsize=9)
        self.currentCmd = "Nothing"
        self.commonInventory = {
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.ressources = {
            "food": 10,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }



    def checkRessourceForLevel(self):
        for lvl in range(0, 7):
            if (self.lvl == lvl+1):
                for r in self.ressources:
                    if (r == "food"):
                        continue
                    if (upLvl[lvl][r] > self.ressources[r]):
                        print("need ",upLvl[lvl][r], self.ressources[r], r, self.lvl)
                        return r

        return (None)
    def findPathToTile(self, tile_needed):
        print("TILE: ", tile_needed)
        if tile_needed == 0:
            return (1)
        left_tile = 1
        middle_tile = 2
        right_tile = 3
        action = "Forward"
        reset = 0
        for levels in range(1, self.lvl + 1):
            print(tile_needed, left_tile, middle_tile, right_tile)
            if (tile_needed < middle_tile and tile_needed >= left_tile):
                self.toSend.put("Forward")
                self.toSend.put("Left")
                for t in range(0, middle_tile-tile_needed):
                    self.toSend.put("Forward")
                return (1)
            elif (tile_needed > middle_tile and tile_needed <= right_tile):
                self.toSend.put("Forward")
                self.toSend.put("Right")
                for t in range(0, tile_needed-middle_tile):
                    self.toSend.put("Forward")
                return (1)
            else:
                self.toSend.put("Forward")
            if (tile_needed == middle_tile):
                return (1)
            left_tile += 2*levels+1
            middle_tile += 2*levels+2
            right_tile += 2*levels+3
            reset +=1
        for i in range (0, reset):
            print("remove =", self.toSend.get())
        
        return (0)

    def inventory(self, srvMsg):
        srvMsg = srvMsg[1:-1]
        inv = srvMsg.split(",")
        for rsc in inv:
            a = rsc.split()
            self.ressources[a[0]] = int(a[1])

    # def look(self, srvMsg, drop):
    #     print("SERV in LOOK: ", srvMsg)
    #     srvMsg = srvMsg[1:-1]
    #     look_list = srvMsg.split(",")
    #     #when ai has arrived to meeting, he needs to drop all the needed ressources
    #     if drop == 1:
    #         res = []
    #         for ress in look_list[0].split(" "):
    #             res.append(int(ress))
    #         for i in range(1, 7):
    #             for j in range (0, self.ressources[i] - res[i-1]):
    #                 self.toSend.put("Set " + ressources[i])
    #         self.drop = 0
    #         return 1
    #     ressource = checkRessourceForLevel(self.lvl, self.ressources)
    #     if (self.ressources["food"] < 8 or ressource == None):
    #         ressource = "food"
    #     tile_needed = -1
    #     i = 0
    #     for l in look_list:
    #         if l.find(ressource) != -1:
    #             tile_needed = i
    #             break
    #         i += 1
    #     if not self.findPathToTile(tile_needed):
    #         print("Not found...")
    #         self.toSend.put("Forward")
    #     else:
    #         self.ressources[ressource] += 1
    #         if ressource != "food":
    #             self.commonInventory[ressource] += 1
    #         if (checkRessourceForLevel(self.lvl, self.commonInventory) == None):
    #             self.toSend.put("Broadcast meeting " + str(self.lvl))
    #             self.ressources[ressource] -= 1
    #             self.commonInventory[ressource] -= 1
    #             self.isMeeting = True
    #             self.hasArrived = True
    #             print("Enter")
    #         else:
    #             self.toSend.put("Take " + ressource)
    #             if ressource != "food":
    #                 self.toSend.put("Broadcast inventory " + ressource)
    #     return 0

    def checkTile(self, ressource):
        self.ressources[ressource] += 1
        if self.checkRessourceForLevel() == None:
            self.toSend.put("Incantation")
        else:
            self.toSend.put("Take " + ressource)
        self.ressources[ressource] -= 1


    def look(self, srvMsg):
        i = 0
        srvMsg = srvMsg[1:-1]
        look_list = srvMsg.split(",")
        ressource = self.checkRessourceForLevel()
        if (self.ressources["food"] < 8 or ressource == None):
            ressource = "food"
        print("ressource = [" + ressource + "]")
        for x in look_list:
            if x.find(ressource) >= 0:
                if self.findPathToTile(i):
                    print("found path")
                    self.checkTile(ressource)
                    return 1
                break
            i += 1
        self.toSend.put("Forward")
        return 0


    def ejected(self):
        while (not self.cmds.empty()):
            self.toSend.get()
        return 1

    def handleMessage(self, message):
        self.dir = int(message[8])
        self.M = message[11:]
        if (message.find("inventory") != -1):
            res = message.split(",")[1].split(" ")[1]
            self.commonInventory[res] += 1

        if (message.find("meeting") != -1):
            direction = int(message.split(",")[1].split(" ")[1])
            self.isMeeting = True
            if (direction != 0):
                findPathToTileFromBroadcast(self, direction)
            else:
                self.hasArrived = True
                self.toSend.put("Broadcast arrived")
                self.drop = 1

        if (message.find("incantation") != -1 and int(message.split(",")[1].split(" ")[1]) == 0):
            self.toSend.put("Incantation")
            self.nbMeeting = 1
            self.hasArrived = False
            self.isMeeting = False

        if(message.find("arrived") != -1 and int(message.split(",")[1].split(" ")[1]) == 0):
            self.nbMeeting += 1
            if (self.nbMeeting == upLvl[self.lvl-1]["player"]):
                self.toSend.put("Broadcast incantation")
                self.toSend.put("Incantation")
                self.nbMeeting = 1
                self.hasArrived = False
                self.isMeeting = False

    def serverResponse(self, srvMsg):
        print("SRVMSG: [" + srvMsg + "]")
        if srvMsg == None:
            return 1
        if srvMsg == "dead":
            return -1
        if srvMsg.find("eject") >= 0:
            return self.ejected()
        if srvMsg.find("message") >= 0:
            return self.handleMessage(srvMsg)
        curr = self.currentCmd.split()[0]
        # if srvMsg == "ok" or srvMsg == "ko":
        #     if self.cmds.empty():
        #         self.currentCmd = "Nothing"
        #     else:
        #         self.currentCmd = self.cmds.get()
        #     return 1
        if curr == "Look":
            # self.look(srvMsg, self.drop)
            self.look(srvMsg)
        elif curr == "Inventory":
            self.inventory(srvMsg)
        elif curr == "Connect_nbr":
            self.nbPlayers = int(srvMsg)
        elif curr == "Incantation":
            if srvMsg == "Elevation underway":
                return 1
            elif srvMsg.find("Current level") != -1:
                print("LEVEL UP ëâëëäëäßëäëäëäëßäëäëäëßäëäëë", srvMsg)
                self.lvl = self.lvl + 1

        if self.cmds.empty():
            self.currentCmd = "Nothing"
        else:
            self.currentCmd = self.cmds.get()
        return 1

    # def checkAction(self):
    #     self.toSend.put("Inventory")
        
    #     if self.isMeeting:
    #         if self.hasArrived:
    #             action = "Broadcast meeting " + str(self.lvl)
    #         if not self.hasArrived and self.ressources["food"] >= 8:
    #             action = "Look"
    #     else:
    #         action = "Look"

    #     if self.isMeeting and self.hasArrived and self.nbMeeting >= upLvl[self.lvl-1]["player"]:
    #             self.toSend.put("Broadcast incantation")
    #             action = "Incantation"
    #             self.nbMeeting = 1
    #             self.hasArrived = False
    #             self.isMeeting = False
    #     print("action = ", action)
    #     return (action)

    def checkAction(self):
        self.toSend.put("Inventory")
        action = "Look"
        return action

    def actionAi(self):
        if self.toSend.empty():
            if self.cmds.empty() and self.currentCmd == "Nothing":
                action = self.checkAction()
                # action = input("> ")
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
            print("[" + self.readBuff + "]")
            if self.readBuff == "end":
                print("error")
                return -1
            self.readBuff = self.readBuff[:-1]
            for x in self.readBuff.split("\n"):
                if self.ai.serverResponse(x) < 0:
                    print("dead")
                    return -1
        return 0

    def mainLoop(self):
        run = 1
        while (run > -1):
            run = clientLib.client_select()
            if self.serverCommunication(run) < 0:
                return -1
            self.writeBuff = self.ai.actionAi()
            self.readBuff = None
            if (self.writeBuff != "wait"):
                self.writeBuff += '\n'
                clientLib.test(self.writeBuff.encode('utf-8'))
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
