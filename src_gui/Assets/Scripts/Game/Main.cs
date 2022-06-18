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
    public string name;
    public int nb_players = 0;
    public List<Player> players;
}

public class Tiles {
    public Ressources content;
}

public class Map {
    public int width;
    public int height;
    public List<List<Tiles>> tiles;
    public List<Team> teams = new List<Team>();
    public int time_unit;
}

public class Main : MonoBehaviour
{
    public static Map map = new Map();
    public GameObject parent;
    private string response;

    public GameObject tilePrefab;

    public int nb_teams = 0;

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

    private void GeneratePlayer(string[] content)
    {
        string[] player_tag = content[1].Split("#");

        for (int i_team = 0; i_team < nb_teams; i_team++) {
            if (map.teams[i_team].name == content[6]) {
                map.teams[i_team].players.Add(new Player());
                map.teams[i_team].players[map.teams[i_team].nb_players].player_nb = int.Parse(player_tag[1]);
                map.teams[i_team].players[map.teams[i_team].nb_players].orientation = int.Parse(content[4]);
                map.teams[i_team].players[map.teams[i_team].nb_players].level = int.Parse(content[5]);
                map.teams[i_team].players[map.teams[i_team].nb_players].ressources = new Ressources();
                map.teams[i_team].players[map.teams[i_team].nb_players].ressources.x = int.Parse(content[2]);
                map.teams[i_team].players[map.teams[i_team].nb_players].ressources.y = int.Parse(content[3]);
                map.teams[i_team].nb_players++;
                break;
            }
        }
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
            map.teams.Add(new Team());
            Debug.Log("Ho mais allo fratelo");
            map.teams[nb_teams].players = new List<Player>();
            //map.teams[nb_teams].name = content[1];
            nb_teams++;
        }
        if (cmd.StartsWith("bct ")) {
            map.tiles[int.Parse(content[1])][int.Parse(content[2])].content.update(cmd);
        }
        if (cmd.StartsWith("sgt ")) {
            map.time_unit = int.Parse(content[1]);
        }
        if (cmd.StartsWith("pnw ")) {
            GeneratePlayer(content);
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

            map.teams = new List<Team>();

            Debug.Log("Connected");
            NetworkManager.WriteServer("msz");
            NetworkManager.WriteServer("tna");
            NetworkManager.WriteServer("sgt");
        } else {
            Debug.Log("Not connected");
        }
    }
}
