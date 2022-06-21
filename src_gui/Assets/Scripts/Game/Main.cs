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
    public string name;
    public int nb_players = 0;
    public List<Player> players;
    public List<GameObject> playersObj;
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
    private int count = 0;
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
    public GameObject tileParent;
    public GameObject playerModel;
    public GameObject playerParent;
    public GameObject CameraRig;
    public static Map map = new Map();
    private string response;
    private static List<string> ressources_name = new List<string>{"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    enum Ressources_type { food, linemate, deraumere, sibur, mendiane, phiras, thystame };

    public int nb_teams = 0;

    float TileOffset = 5.73f;

    float mainSpeed = 50f;
    float shiftAdd = 75f;
    float maxShift = 175f;
    float camSens = 0.25f;
    private Vector3 lastMouse = new Vector3(255, 255, 255);
    private float totalRun= 1.0f;

    private Vector3 GetBaseInput() {
        Vector3 p_Velocity = new Vector3();
        if (Input.GetKey (KeyCode.Z)){
            p_Velocity += new Vector3(0, 0 , 1);
        }
        if (Input.GetKey (KeyCode.S)){
            p_Velocity += new Vector3(0, 0, -1);
        }
        if (Input.GetKey (KeyCode.Q)){
            p_Velocity += new Vector3(-1, 0, 0);
        }
        if (Input.GetKey (KeyCode.D)){
            p_Velocity += new Vector3(1, 0, 0);
        }
        return p_Velocity;
    }
    private void CamMovement()
    {
        lastMouse = Input.mousePosition - lastMouse ;
        lastMouse = new Vector3(-lastMouse.y * camSens, lastMouse.x * camSens, 0 );
        lastMouse = new Vector3(transform.eulerAngles.x + lastMouse.x , transform.eulerAngles.y + lastMouse.y, 0);
        transform.eulerAngles = lastMouse;
        lastMouse = Input.mousePosition;
       
        Vector3 p = GetBaseInput();
        if (p.sqrMagnitude > 0){
            if (Input.GetKey (KeyCode.LeftShift)){
                totalRun += Time.deltaTime;
                p  = p * totalRun * shiftAdd;
                p.x = Mathf.Clamp(p.x, -maxShift, maxShift);
                p.y = Mathf.Clamp(p.y, -maxShift, maxShift);
                p.z = Mathf.Clamp(p.z, -maxShift, maxShift);
            } else {
                totalRun = Mathf.Clamp(totalRun * 0.5f, 1f, 1000f);
                p = p * mainSpeed;
            }
            p = p * Time.deltaTime;
            Vector3 newPosition = transform.position;
            if (Input.GetKey(KeyCode.Space)){
                transform.Translate(p);
                newPosition.x = transform.position.x;
                newPosition.z = transform.position.z;
                transform.position = newPosition;
            } else {
                transform.Translate(p);
            }
        }
    }

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
        Vector3 randPosInTile = new Vector3(Random.Range(-(TileOffset/2), (TileOffset/2)), 1f, Random.Range(-(TileOffset/2), (TileOffset/2)));
        string tag = ressources_name[(int)type];

        GameObject ressource = Instantiate(
            prefab,
            tile.transform.position + randPosInTile,
            Quaternion.identity
        ) as GameObject;
        if (tag == "sibur" || tag == "mendiane" || tag == "linemate" || tag == "phiras") {
            ressource.transform.eulerAngles = new Vector3(90, 0, 0);
        }
        ressource.transform.localScale = new Vector3(5f, 5f, 5f);
        ressource.tag = tag;
        ressource.transform.parent = tile.transform;
    }

    private void UpdateRessources(int x, int y, GameObject prefab, int nbr, Ressources_type type)
    {
        List<GameObject> pref_Ressources = getRessourcesOnTile(map.tiles_obj[x][y], type);

        if (pref_Ressources.Count < nbr) {
            for (int i = pref_Ressources.Count; i < nbr; i++) {
                SpawnRessources(map.tiles_obj[x][y], prefab, type);
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
        Debug.Log("Updating tile : " + x + "," + y);
        UpdateRessources(x, y, foodPrefab, food, Ressources_type.food);
        UpdateRessources(x, y, linematePrefab, linemate, Ressources_type.linemate);
        UpdateRessources(x, y, deraumerePrefab, deraumere, Ressources_type.deraumere);
        UpdateRessources(x, y, siburPrefab, sibur, Ressources_type.sibur);
        UpdateRessources(x, y, mendianePrefab, mendiane, Ressources_type.mendiane);
        UpdateRessources(x, y, phirasPrefab, phiras, Ressources_type.phiras);
        UpdateRessources(x, y, thystamePrefab, thystame, Ressources_type.thystame);
    }

    private void setRigPosition()
    {
        CameraRig.transform.position = new Vector3((float)(map.tiles.Count * TileOffset)/2, 0, -TileOffset);
    }

    private void CreateTileMap()
    {
        map.tiles_obj = new List<List<GameObject>>();
        map.tiles = new List<List<Tiles>>();
        for (int i = 0; i < map.width; i++)
        {
            map.tiles_obj.Add(new List<GameObject>());
            map.tiles.Add(new List<Tiles>());
            for (int j = 0; j < map.height; j++)
            {
                map.tiles[i].Add(new Tiles());
                map.tiles[i][j].content = new Ressources();
                map.tiles_obj[i].Add(Instantiate(tilePrefab));
                map.tiles_obj[i][j].transform.position = new Vector3(i * TileOffset, 0, j * TileOffset);
                SetTileInfo(map.tiles_obj[i][j], i, j);
            }
        }
        setRigPosition();
    }

    private void SetTileInfo(GameObject Temp, int x, int z)
    {
        Temp.transform.SetParent(tileParent.transform);
        Temp.name = x.ToString() + ", " + z.ToString();
    }

    private void SetPlayerInfo(GameObject Temp, string teamName, string playerTag)
    {
        Temp.transform.SetParent(playerParent.transform);
        Temp.name = teamName + ", " + playerTag;
    }

    private void GeneratePlayer(string[] content)
    {
        string[] playerTag = content[1].Split("#");

        Debug.Log("New Player connected : Tag " + playerTag[1]);
        for (int i_team = 0; i_team < nb_teams; i_team++) {
            if (map.teams[i_team].name == content[6]) {
                map.teams[i_team].players.Add(new Player());
                map.teams[i_team].players[map.teams[i_team].nb_players].player_nb = int.Parse(playerTag[1]);
                map.teams[i_team].players[map.teams[i_team].nb_players].orientation = int.Parse(content[4]);
                map.teams[i_team].players[map.teams[i_team].nb_players].level = int.Parse(content[5]);
                map.teams[i_team].players[map.teams[i_team].nb_players].content = new Ressources();
                map.teams[i_team].players[map.teams[i_team].nb_players].content.x = int.Parse(content[2]);
                map.teams[i_team].players[map.teams[i_team].nb_players].content.y = int.Parse(content[3]);
                map.teams[i_team].playersObj.Add(Instantiate(playerModel));
                SetPlayerInfo(map.teams[i_team].playersObj[map.teams[i_team].nb_players], content[6], playerTag[1]);
                map.teams[i_team].playersObj[map.teams[i_team].nb_players].transform.position =
                    new Vector3(map.teams[i_team].players[map.teams[i_team].nb_players].content.x * TileOffset,
                        1.9f, map.teams[i_team].players[map.teams[i_team].nb_players].content.y * TileOffset);
                map.teams[i_team].playersObj[map.teams[i_team].nb_players].transform.eulerAngles =
                    new Vector3(0, 90 * (map.teams[i_team].players[map.teams[i_team].nb_players].orientation - 1), 0);
                map.teams[i_team].nb_players++;
                map.teams[i_team].nb_players++;
                break;
            }
        }
    }

    private void UpdatePlayer(string cmd)
    {
        string[] content = cmd.Split(" ");
    
        for (int i_team = 0; i_team < nb_teams; i_team++) {
            for (int i_player = 0; i_player < map.teams[i_team].nb_players; i_player++) {
                if (map.teams[i_team].players[i_player].playerTag == content[1]) {
                    map.teams[i_team].players[i_player].x = int.Parse(content[2]);
                    map.teams[i_team].players[i_player].y = int.Parse(content[3]);
                    map.teams[i_team].players[i_player].orientation = int.Parse(content[4]);
                    map.teams[i_team].playersObj[i_player].transform.position =
                        new Vector3(map.teams[i_team].players[i_player].content.x * TileOffset,
                            1.9f, map.teams[i_team].players[i_player].content.y * TileOffset);
                    map.teams[i_team].playersObj[i_player].transform.eulerAngles =
                        new Vector3(0, 90 * (map.teams[i_team].players[i_player].orientation - 1), 0);
                    break;
                }
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
            map.teams[nb_teams].players = new List<Player>();
            map.teams[nb_teams].playersObj = new List<GameObject>();
            map.teams[nb_teams].name = content[1];
            Debug.Log("New Team : " + map.teams[nb_teams].name);
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
        }
        if (cmd.StartsWith("sgt ")) {
            map.time_unit = int.Parse(content[1]);
        }
        if (cmd.StartsWith("pnw "))
            GeneratePlayer(content);
        if (cmd.StartsWith("ppo "))
            UpdatePlayer(content);
    }

    private void Update() {
        if (count > 1) {
            if (!NetworkManager.connected)
                throw new System.Exception("Error disconnected");
            try {
            if (NetworkManager.stream.DataAvailable) {
                    string cmd = NetworkManager.ReadServer();
                    HandleCommand(cmd);
                }
            } catch (System.Exception e) {
                Debug.Log("Exception : " + e.Message);
            }
        } else {
            count++;
        }
        CamMovement();
    }

    void Start()
    {
        Cursor.visible = false;
        if (NetworkManager.connected) {
            map.teams = new List<Team>();
            Debug.Log("Connected");
        } else {
            Debug.Log("Not connected");
        }
    }
}
