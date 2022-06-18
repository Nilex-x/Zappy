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
    public List<List<GameObject>> tiles_obj;
    public List<Team> teams = new List<Team>();
    public int time_unit;
}

public class Main : MonoBehaviour
{
    public GameObject foodPrefab;
    public GameObject linematePrefab;
    public GameObject deraumerePrefab;
    public GameObject siburPrefab;
    public GameObject mendianePrefab;
    public GameObject phirasPrefab;
    public GameObject thystamePrefab;
    public GameObject playerPrefab;
    public GameObject eggPrefab;
    public GameObject tilePrefab;
    public GameObject parent;
    public static Map map = new Map();
    private string response;
    private static List<string> ressources_name = new List<string>{"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    enum Ressources_type { food, linemate, deraumere, sibur, mendiane, phiras, thystame };


    public int nb_teams = 0;

    float tileOffset = 1.45f;

    private List<GameObject> getRessourcesOnTile(GameObject tile, Ressources_type type)
    {
        List<GameObject> ressources = new List<GameObject>();

        foreach (Transform child in tile.transform.GetComponentInChildren<Transform>()) {
            if (child.gameObject.tag == ressources_name[(int)type]) {
                ressources.Add(child.gameObject);
            }
        }
        return ressources;
    }

    private void SpawnRessources(GameObject tile, GameObject prefab, Ressources_type type)
    {
        Vector3 randPosInTile = new Vector3(Random.Range(-tileOffset, tileOffset), 0, Random.Range(-tileOffset, tileOffset));
        string tag = ressources_name[(int)type];

        GameObject ressource = Instantiate(
            prefab,
            tile.transform.position + randPosInTile,
            Quaternion.identity
        ) as GameObject;
        ressource.tag = tag;
        ressource.transform.parent = tile.transform;
    }

    private void UpdateRessources(int x, int y, GameObject prefab, int nbr, Ressources_type type)
    {
        GameObject tile = map.tiles_obj[x][y];
        List<GameObject> pref_Ressources = getRessourcesOnTile(tile, type);

        if (pref_Ressources.Count < nbr) {
            for (int i = pref_Ressources.Count; i < nbr; i++) {
                SpawnRessources(tile, prefab, type);
            }
        } else if (pref_Ressources.Count > nbr) {
            for (int i = pref_Ressources.Count; i > nbr; i--) {
                Destroy(pref_Ressources[i - 1]);
                pref_Ressources.RemoveAt(0);
            }
        }
    }

    private void UpdateTiles(int x, int y, int food, int linemate, int deraumere, 
    int sibur, int mendiane, int phiras, int thystame)
    {
        if (x < 0 || y < 0 || x >= map.width || y >= map.height)
            return;
        Debug.Log("Updating tile : niglo : " + x + "," + y);
        UpdateRessources(x, y, foodPrefab, food, Ressources_type.food);
        UpdateRessources(x, y, linematePrefab, linemate, Ressources_type.linemate);
        UpdateRessources(x, y, deraumerePrefab, deraumere, Ressources_type.deraumere);
        UpdateRessources(x, y, siburPrefab, sibur, Ressources_type.sibur);
        UpdateRessources(x, y, mendianePrefab, mendiane, Ressources_type.mendiane);
        UpdateRessources(x, y, phirasPrefab, phiras, Ressources_type.phiras);
        UpdateRessources(x, y, thystamePrefab, thystame, Ressources_type.thystame);
    }

    private void CreateTileMap()
    {
        map.tiles_obj = new List<List<GameObject>>();
        map.tiles = new List<List<Tiles>>();
        for (int i = 0; i <= map.height; i++)
        {
            map.tiles_obj.Add(new List<GameObject>());
            map.tiles.Add(new List<Tiles>());
            for (int j = 0; j <= map.width; j++)
            {
                map.tiles[i].Add(new Tiles());
                map.tiles[i][j].content = new Ressources();
                map.tiles_obj[i].Add(Instantiate(tilePrefab));
                map.tiles_obj[i][j].transform.position = new Vector3(i * tileOffset, 0, j * tileOffset);
                SetTileInfo(map.tiles_obj[i][j], i, j);
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
            map.teams.Add(new Team());
            Debug.Log(cmd);
            //map.teams[nb_teams].name = content[1];
            nb_teams++;
        }
        if (cmd.StartsWith("bct ")) {
            UpdateTiles(
                int.Parse(content[1]),
                int.Parse(content[2]),
                int.Parse(content[3]),
                int.Parse(content[4]),
                int.Parse(content[5]),
                int.Parse(content[6]),
                int.Parse(content[7]),
                int.Parse(content[8]),
                int.Parse(content[9])
            );
            Debug.Log("Updated tile : " + content[1] + " " + content[2]);
            // map.tiles[int.Parse(content[1])][int.Parse(content[2])].content.update(cmd);
        }
        if (cmd.StartsWith("sgt ")) {
            map.time_unit = int.Parse(content[1]);
        }
    }

    private void Update() {
        if (!NetworkManager.connected)
            throw new System.Exception("Error disconnected");
        try {
            NetworkManager.WriteServer("mct");
            if (NetworkManager.stream.DataAvailable) {
                Debug.Log("RAAAAAAAAAAAAAAAAAAAAAHH");
                string cmd = NetworkManager.ReadServer();
                if (!string.IsNullOrEmpty(cmd) && (cmd != "" || cmd != "WELCOME"))
                    HandleCommand(cmd);
            }
        } catch (System.Exception e) { 
            Debug.Log("Exception : " + e.Message);
        }
    }

    void Start()
    {
        if (NetworkManager.connected) {
            while (NetworkManager.stream.DataAvailable)
                NetworkManager.ReadServer();

            map.teams = new List<Team>();

            Debug.Log("Connected");
            NetworkManager.WriteServer("msz");
        } else {
            Debug.Log("Not connected");
        }
    }
}
