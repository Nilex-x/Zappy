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
    "phiras": 2,
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

directions = {
    1 : "Forward",
    2 : "Forward",
    3 : "Left",
    4 : "Left",
    5 : "Left",
    6 : "Right",
    7 : "Right",
    8 : "Forward",
}



# ---------------------- AI ----------------------

class clientIA:
    def __init__(self):
        self.myId = -2
        self.nbClients = -1
        self.team = None
        self.height = -1
        self.width = -1
        self.alive = True
        self.nbMeeting = 1
        self.nbArrived = 1 # arrivés
        self.isCalled = False # rejoins le point d'incantation
        self.hasArrived = False # est arrivé
        self.isCalling = False # attend suffisement d'allié pour incanter
        self.elevation = False
        self.uturn = 0
        self.fork = False
        self.following = -1
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

    def handleMessages(self, servMsg):
        if self.incantation or self.lvl == 1:
            return 0
        try:
            msg = servMsg.split(",")
            content = msg[1].split(":")
            target = content[1].split(".")
            sendTeam = target[0]
            sendId = int(target[1])
            sendLvl = int(target[2])
            direction = int(msg[0].split()[1])
            if (sendLvl != self.lvl) or (sendTeam != self.team):
                return 0

            if content[0].find("here") >= 0:
                if self.isCalling and sendId > self.myId:
                    return 0
                if self.isCalling and sendId < self.myId:
                    self.nbMeeting = 1
                    self.nbArrived = 1
                    self.following = sendId
                    self.isCalling = False
                    self.isCalled = True
                    self.ejected()
                    self.toSend.put("Broadcast coming:" + self.team + "." + str(self.myId) + "." + str(self.lvl))
                    self.toSend.put("Broadcast cancel:" + self.team + "." + str(self.myId) + "." + str(self.lvl))
                if self.isCalled and not self.hasArrived:
                    if self.following > sendId:
                        self.following = sendId
                        self.toSend.put("Broadcast coming:" + self.team + "." + str(self.myId) + "." + str(self.lvl))
                    if direction == 0:
                        self.ejected()
                        self.toSend.put("Broadcast arrived:" + self.team + "." + str(self.myId) + "." + str(self.lvl))
                        self.hasArrived = True
                        return 0
                    if direction == 5:
                        self.uturn += 1
                    if direction == 1 and self.uturn == 3:
                        self.toSend.put("Right")
                        self.uturn = 0
                    self.toSend.put(directions[direction])

                if not self.isCalled:
                    if self.ressources["food"] >= 30:
                        self.ejected()
                        self.toSend.put("Broadcast coming:" + self.team + "." + str(self.myId) + "." + str(self.lvl))
                        self.isCalling = False
                        self.isCalled = True
                        self.following = sendId

            elif content[0].find("cancel") >= 0 and self.isCalled and self.following == sendId:
                self.isCalled = False
                self.hasArrived = False
                self.following = -1

            elif content[0].find("coming") >= 0 and self.isCalling:
                self.nbMeeting += 1

            elif content[0].find("arrived") >= 0 and self.isCalling:
                self.nbArrived += 1

            elif content[0].find("feed") >= 0 and self.isCalling:
                self.nbArrived -= 1
                self.nbMeeting -= 1
            return 0
        except:
            return 0


    def checkRessourceForLevel(self):
        for lvl in range(0, 7):
            if (self.lvl == lvl+1):
                for r in self.ressources:
                    if (r == "food"):
                        continue
                    if (upLvl[lvl][r] > self.ressources[r]):
                        return r
        return (None)


    def findPathToTile(self, tile_needed):
        if tile_needed == 0:
            return (1)
        left_tile = 1
        middle_tile = 2
        right_tile = 3
        reset = 0
        for levels in range(1, self.lvl + 1):
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
        food = 30
        if self.lvl >= 6:
            food = 40
        srvMsg = srvMsg[1:-1]
        inv = srvMsg.split(",")
        for rsc in inv:
            a = rsc.split()
            self.ressources[a[0]] = int(a[1])
        if self.ressources["food"] >= 10 and self.fork:
            self.toSend.put("Fork")
            self.fork = False
        if self.lvl != 8 and self.checkRessourceForLevel() == None and self.ressources["food"] >= food:
            self.isCalling = True
        if self.isCalling and self.ressources["food"] <= 5:
            self.isCalling = False
            self.nbArrived = 1
            self.nbMeeting = 1
            self.fork = True
            self.toSend.put("Broadcast cancel:" + self.team + "." + str(self.myId) + "." + str(self.lvl))
        if self.hasArrived and self.ressources["food"] <= 5:
            self.hasArrived = False
            self.isCalled = False
            self.toSend.put("Broadcast feed:" + self.team + "." + str(self.myId) + "." + str(self.lvl))

    # def setRessourcesFromTile(self, look_list, t):
    #     tile = {
    #     "linemate": 0,
    #     "deraumere": 0,
    #     "sibur": 0,
    #     "mendiane": 0,
    #     "phiras": 0,
    #     "thystame": 0
    #     }
    #     ress = look_list[t].split()
    #     for i in ress:
    #         if i == "food" or i == "player":
    #             continue
    #         tile[i] += 1
    #     for i in ressources:
    #         if tile[i] < upLvl[self.lvl - 1][i]:
    #             self.toSend.put("Set " + i)

    def setRessources(self):
        for i in ressources:
            if upLvl[self.lvl - 1][i] > 0:
                j = upLvl[self.lvl - 1][i]
                while j > 0:
                    self.toSend.put("Set " + i)
                    j -= 1

    def checkTile(self, ressource):
        self.toSend.put("Take " + ressource)
        self.ressources[ressource] += 1
        if self.checkRessourceForLevel() == None:
            if self.lvl == 1:
                self.toSend.put("Set linemate")
                self.toSend.put("Incantation")
        self.ressources[ressource] -= 1

    def rmRedundantChar(self, srvMsg):
        x = 'x'
        res = ""
        for i in srvMsg:
            if not (i == ',' and x == ','):
                res += i
            else:
                res += "empty,"
            x = i
        return res

    def look(self, srvMsg):
        ressource = None
        if self.isCalling or self.isCalled:
            return 0
        i = 0
        srvMsg = srvMsg[1:-1]
        srvMsg = self.rmRedundantChar(srvMsg)
        look_list = srvMsg.split(",")
        if self.lvl != 8:
            ressource = self.checkRessourceForLevel()
        if (self.ressources["food"] < 40):
            ressource = "food"
        if ressource == None:
            self.toSend.put("Forward")
            return 0
        for x in look_list:
            if x.find(ressource) >= 0:
                if self.findPathToTile(i) and self.lvl != 8:
                    # self.toSend.put("Take " + ressource)
                    self.checkTile(ressource)
                    return 1
                break
            i += 1
        self.toSend.put("Forward")
        return 0


    def ejected(self):
        while (not self.toSend.empty()):
            self.toSend.get()
        return 1


    def serverResponse(self, srvMsg):
        if srvMsg == None:
            return 1
        if srvMsg == "dead":
            return -1
        if srvMsg.find("eject") >= 0:
            return self.ejected()
        if srvMsg.find("message") >= 0:
            if self.myId != -2:
                return self.handleMessages(srvMsg)
        if self.myId == -2:
            if self.currentCmd == "Connect_nbr":
                self.myId = int(srvMsg)
            else:
                return 0
        curr = self.currentCmd.split()[0]
        if self.currentCmd == "Take Food":
            if srvMsg == "ko":
                self.toSend.put("Right")
        if srvMsg == "Elevation underway":
            self.nbArrived = 1
            self.nbMeeting = 1
            self.isCalling = False
            self.incantation = True
            self.isCalled = False
            self.hasArrived = False
            return 1
        if srvMsg.find("Current level") >= 0:
            self.incantation = False
            self.lvl = int(srvMsg.split()[2])
            print("Level up " + str(self.lvl))
            if self.currentCmd != "Incantation":
                return 1
        if self.incantation and srvMsg == "ko":
            self.incantation = False
            if self.currentCmd != "Incantation":
                return 1
        if curr == "Look":
            self.look(srvMsg)
        elif curr == "Inventory":
            self.inventory(srvMsg)
        elif curr == "Connect_nbr":
            self.nbPlayers = int(srvMsg)


        if self.cmds.empty():
            self.currentCmd = "Nothing"
        else:
            self.currentCmd = self.cmds.get()
        return 1

    def checkAction(self):
        if self.incantation:
            return "wait"
        if (self.nbArrived >= self.nbMeeting) and self.isCalling and (self.nbMeeting >= upLvl[self.lvl - 1]["player"]):
            self.ejected()
            self.setRessources()
            return ("Incantation")
        if self.isCalling:
            self.toSend.put("Inventory")
            self.toSend.put("Right")
            self.toSend.put("Right")
            self.toSend.put("Right")
            self.toSend.put("Right")
            action = ("Broadcast here:" + self.team + "." + str(self.myId) + "." + str(self.lvl))
            return action
        if self.hasArrived:
            self.toSend.put("Inventory")
        if self.isCalled:
            return "wait"
        self.toSend.put("Inventory")
        return "Look"

    def actionAi(self):
        if self.currentCmd == "Connect_nbr":
            return "wait"
        if self.myId < 0:
            self.currentCmd = "Connect_nbr"
            return "Connect_nbr"
        action = "wait"
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
            if self.readBuff == "end":
                print("dead")
                return -1
            self.readBuff = self.readBuff[:-1]
            for x in self.readBuff.split("\n"):
                if self.ai.serverResponse(x) < 0:
                    print("error")
                    return -1
        return 0

    def mainLoop(self):
        run = 1
        while (run > -1):
            self.writeBuff = self.ai.actionAi()
            self.readBuff = None
            if (self.writeBuff != "wait"):
                self.writeBuff += '\n'
                clientLib.test(self.writeBuff.encode('utf-8'))
            run = clientLib.client_select()
            if self.serverCommunication(run) < 0:
                return -1
        return 0


    def getPosnTeam(self):
        servMsg = self.readBuff.split("\n")
        if self.readBuff.find("ko") != -1 and self.readBuff.find("unknown team") != -1:
            exit(84)
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

def manageFlags(port, teamName):
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
    manageFlags(port, teamName)
    if (myIp == None):
        myIp = "127.0.0.1"
    mySocket = clientLib.create_client(ctypes.c_char_p(myIp.encode('utf-8')), ctypes.c_int(int(port)))
    if ((mySocket < 0) or (clientLib.init_info(ctypes.c_int(mySocket)) < 0)):
        print("failed connection")
        return 84
    myClient = clientInfo(mySocket)
    myClient.connection(teamName)
    myClient.ai.team = teamName[:-1]
    myClient.mainLoop()
    return 0

if __name__ == '__main__':
    cLib = pathlib.Path().absolute() / "src_client/client/clientLib.so"
    clientLib = ctypes.CDLL(cLib)
    clientLib.read_server.argtypes = [ctypes.c_int]
    clientLib.read_server.restype = ctypes.POINTER(ctypes.c_char)
    main()
