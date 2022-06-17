using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net.Sockets;

class Client
{
    public TcpClient client;
    public NetworkStream stream;
}

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
}

public class Main : MonoBehaviour
{
    private Client client = new Client();
    public static Map map = new Map();
    public GameObject parent;
    private string buffer;
    private string response;

    public GameObject tilePrefab;

    float tileOffset = 1.45f;

    private void CreateTileMap()
    {
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

    private void sendToServer(string message)
    {
        byte[] response = new byte[256];
        string resp = "";
        byte[] data = System.Text.Encoding.ASCII.GetBytes(message);

        buffer = string.Empty;
        client.stream.Write(data, 0, data.Length);
        client.stream.Read(response, 0, response.Length);
        buffer = System.Text.Encoding.ASCII.GetString(response).ToString();
        while (client.stream.DataAvailable) {
            client.stream.Read(response, 0, response.Length);
            resp = System.Text.Encoding.ASCII.GetString(response).ToString();
            buffer = buffer.Replace("\0", string.Empty);
            for (int i = 0; i < resp.Length; i++) {
                buffer += (char)resp[i];
            }
        }
    }

    private void GenerateTileMap()
    {
        sendToServer("msz\n");
        string []response = buffer.Split(" ");
        Debug.Log(buffer);
        map.width = int.Parse(response[1]) + 1;
        map.height = int.Parse(response[2]) + 1;
        Debug.Log("Generated map");
        map.tiles = new List<List<Tiles>>();
        for (int i = 0; i < map.height; i++)
        {
            map.tiles.Add(new List<Tiles>());
            for (int j = 0; j < map.width; j++)
            {
                map.tiles[i].Add(new Tiles());
                map.tiles[i][j].content = new Ressources();
                map.tiles[i][j].content.food = i;
            }
        }
    }

    private void doMainLoop()
    {
        try {
            GenerateTileMap();
            sendToServer("tna\n");
            foreach (string team in buffer.Split("\n")) {
                Debug.Log("Team: " + team);
            }
            Debug.Log("Generated Team");
            CreateTileMap();
        } catch (System.Exception e) {
            Debug.Log(e);
        }
    }

    void Start()
    {
        client.stream = Play.stream;
        client.client = Play.client;
        if (client.client.Connected) {
            Debug.Log("Connected");
            doMainLoop();
        } else {
            Debug.Log("Not connected");
        }
    }
}
