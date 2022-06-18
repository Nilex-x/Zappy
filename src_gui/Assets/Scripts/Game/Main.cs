using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net.Sockets;

public class Ressources {
    public int food = 0;
    public int linemate = 0;
    public int deraumere = 0;
    public int sibur = 0;
    public int mendiane = 0;
    public int phiras = 0;
    public int thystame = 0;
    public int x;
    public int y;

    public void update(string buffer)
    {
        string[] ressources = buffer.Split(' ');
        x = int.Parse(ressources[1]);
        y = int.Parse(ressources[2]);
        food = int.Parse(ressources[3]);
        linemate = int.Parse(ressources[4]);
        deraumere = int.Parse(ressources[5]);
        sibur = int.Parse(ressources[6]);
        mendiane = int.Parse(ressources[7]);
        phiras = int.Parse(ressources[8]);
        thystame = int.Parse(ressources[9]);
        Debug.Log("Updated " + x + " " + y);
    }
}

public class Player {
    public int player_nb;
    public int orientation;
    public int level;
    public Ressources content;
}

public class Team {
    public string[] name;
    public List<Player> players;
}

public class Tiles {
    public Ressources content;
}

public class Map {
    public int width;
    public int height;
    public List<List<Tiles>> tiles;
    public List<Team> teams;
    public int time_unit;
}

public class Main : MonoBehaviour
{
    public static Map map = new Map();
    public GameObject parent;
    private string response;

    public GameObject tilePrefab;

    float tileOffset = 1.45f;

    private void CreateTileMap()
    {
        map.tiles = new List<List<Tiles>>();
        for (int i = 0; i <= map.height; i++)
        {
            map.tiles.Add(new List<Tiles>());
            for (int j = 0; j <= map.width; j++)
            {
                map.tiles[i].Add(new Tiles());
                map.tiles[i][j].content = new Ressources();
                map.tiles[i][j].content.food = i;
            }
        }
        for (int x = 0; x < map.width; x++) {
            for (int z = 0; z < map.height; z++) {
                GameObject Temp = Instantiate(tilePrefab);
                Temp.transform.position = new Vector3(x * tileOffset, 0, z * tileOffset);
                SetTileInfo(Temp, x, z);
            }
        }
    }

    private void SetTileInfo(GameObject Temp, int x, int z)
    {
        Temp.transform.SetParent(parent.transform);
        Temp.name = x.ToString() + ", " + z.ToString();
    }

    private void HandleCommand(string cmd)
    {
        Debug.Log("Command: " + cmd);
        string[] content = cmd.Split(" ");

        if (cmd.StartsWith("msz ")) {
            map.width = int.Parse(content[1]);
            map.height = int.Parse(content[2]);
            Debug.Log("Updated map size : " + map.width + " " + map.height);
            CreateTileMap();
        }
        if (cmd.StartsWith("tna ")) {
            Debug.Log("New team: " + content[1]);
        }
        if (cmd.StartsWith("bct ")) {
            map.tiles[int.Parse(content[1])][int.Parse(content[2])].content.update(cmd);
        }
        if (cmd.StartsWith("sgt ")) {
            map.time_unit = int.Parse(content[1]);
        }
    }

    private void Update() {
        if (!NetworkManager.connected)
            throw new System.Exception("Error disconnected");
        try {
            string cmd = NetworkManager.ReadServer();
            if (!string.IsNullOrEmpty(cmd) && (cmd != "" || cmd != "WELCOME"))
                HandleCommand(cmd);
        } catch { }
    }

    void Start()
    {
        if (NetworkManager.connected) {
            while (NetworkManager.stream.DataAvailable)
                NetworkManager.ReadServer();
            Debug.Log("Connected");
            NetworkManager.WriteServer("msz");
            NetworkManager.WriteServer("sgt");
        } else {
            Debug.Log("Not connected");
        }
    }
}
