using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System.Net.Sockets; 

public static class RectMovement {
    public static void SetLeft(this RectTransform rt, float left)
    {
        rt.offsetMin = new Vector2(left, rt.offsetMin.y);
    }
 
    public static void SetRight(this RectTransform rt, float right)
    {
        rt.offsetMax = new Vector2(-right, rt.offsetMax.y);
    }
 
    public static void SetTop(this RectTransform rt, float top)
    {
        rt.offsetMax = new Vector2(rt.offsetMax.x, -top);
    }
 
    public static void SetBottom(this RectTransform rt, float bottom)
    {
        rt.offsetMin = new Vector2(rt.offsetMin.x, bottom);
    }
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
    public int playerTag;
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
    public GameObject EnvironnementHandler;
    public GameObject MainIsland;
    public GameObject MainIslandGround;
    public GameObject Rock1;
    public GameObject Rock2;
    public GameObject Rock3;
    public GameObject RockLarge;
    public GameObject SmallRock;
    public GameObject MountainTall;
    public GameObject Drake;
    public GameObject GodRock;
    public GameObject RockTall;
    public GameObject RockMedium;
    public GameObject MountainSlopping;
    public GameObject FlyingShip;

    public GameObject level2;
    public GameObject level3;
    public GameObject level4;
    public GameObject level5;
    public GameObject level6;
    public GameObject level7;
    public GameObject level8;

    private List<GameObject> levels = new List<GameObject>();

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
    public GameObject time_unit_txt;
    public GameObject tab;
    public GameObject tab_team1;
    public GameObject tab_team2;
    public GameObject tab_player;
    public static Map map = new Map();
    private string response;
    private static List<string> ressources_name = new List<string>{"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    enum Ressources_type { food, linemate, deraumere, sibur, mendiane, phiras, thystame };
    public int nb_teams = 0;
    float TileOffset = 5.73f;
    bool send_data = false;

    float mainSpeed = 25f;
    float shiftAdd = 50f;
    float maxShift = 125f;
    float camSens = 0.25f;
    private Vector3 lastMouse = new Vector3(255, 255, 255);
    private float totalRun= 1.0f;
    private bool tab_show = false;
    private int tab_page = 0;
    private int page_nbr = 0;
    private bool created_tab = false;
    private bool switched_tab = false;
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
                if (transform.position.y >= 4) {
                    p = p * totalRun * shiftAdd;
                    p.x = Mathf.Clamp(p.x, -maxShift, maxShift);
                    p.y = Mathf.Clamp(p.y, -maxShift, maxShift);
                    p.z = Mathf.Clamp(p.z, -maxShift, maxShift);
                }
            } else {
                if (transform.position.y >= 3) {
                    totalRun = Mathf.Clamp(totalRun * 0.5f, 1f, 1000f);
                    p = p * mainSpeed;
                }
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
        if (tag == "food" || tag == "thystame")
            ressource.transform.position = ressource.transform.position - new Vector3(0, 0.2f, 0);
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
        MapGeneration.EnvironnementHandler = EnvironnementHandler;
        MapGeneration.MainIsland = MainIsland;
        MapGeneration.MainIslandGround = MainIslandGround;
        MapGeneration.Rock1= Rock1;
        MapGeneration.Rock2 = Rock2;
        MapGeneration.Rock3 = Rock3;
        MapGeneration.RockLarge = RockLarge;
        MapGeneration.SmallRock = SmallRock;
        MapGeneration.MountainTall = MountainTall;
        MapGeneration.Drake = Drake;
        MapGeneration.GodRock = GodRock;
        MapGeneration.RockTall = RockTall;
        MapGeneration.RockMedium = RockMedium;
        MapGeneration.MountainSlopping = MountainSlopping;
        MapGeneration.FlyingShip = FlyingShip;
        MapGeneration.generateEnvironnement(map.tiles.Count, map.tiles[0].Count, TileOffset);
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

        tab_show = true;
        Debug.Log("New Player connected : Tag " + playerTag[1]);
        for (int i_team = 0; i_team < nb_teams; i_team++) {
            if (map.teams[i_team].name == content[6]) {
                map.teams[i_team].players.Add(new Player());
                map.teams[i_team].players[map.teams[i_team].nb_players].playerTag = int.Parse(playerTag[1]);
                map.teams[i_team].players[map.teams[i_team].nb_players].orientation = int.Parse(content[4]);
                map.teams[i_team].players[map.teams[i_team].nb_players].level = int.Parse(content[5]);
                map.teams[i_team].players[map.teams[i_team].nb_players].content = new Ressources();
                map.teams[i_team].players[map.teams[i_team].nb_players].content.x = int.Parse(content[2]);
                map.teams[i_team].players[map.teams[i_team].nb_players].content.y = int.Parse(content[3]);
                map.teams[i_team].playersObj.Add(Instantiate(playerModel));
                SetPlayerInfo(map.teams[i_team].playersObj[map.teams[i_team].nb_players], content[6], playerTag[1]);
                map.teams[i_team].playersObj[map.teams[i_team].nb_players].transform.position =
                    new Vector3(map.teams[i_team].players[map.teams[i_team].nb_players].content.x * TileOffset,
                        0.6f, map.teams[i_team].players[map.teams[i_team].nb_players].content.y * TileOffset);
               if (map.teams[i_team].players[map.teams[i_team].nb_players].orientation == 1)
                        map.teams[i_team].playersObj[map.teams[i_team].nb_players].transform.eulerAngles =
                            new Vector3(0, -90, 0);
                    else if (map.teams[i_team].players[map.teams[i_team].nb_players].orientation == 3)
                        map.teams[i_team].playersObj[map.teams[i_team].nb_players].transform.eulerAngles =
                            new Vector3(0, 90, 0);
                    else
                        map.teams[i_team].playersObj[map.teams[i_team].nb_players].transform.eulerAngles =
                            new Vector3(0, 90 * (map.teams[i_team].players[map.teams[i_team].nb_players].orientation), 0);
                map.teams[i_team].nb_players++;
                break;
            }
        }
    }

    private void UpdatePlayer(string[] content)
    {    
        for (int i_team = 0; i_team < nb_teams; i_team++) {
            for (int i_player = 0; i_player < map.teams[i_team].nb_players; i_player++) {
                if (map.teams[i_team].players[i_player].playerTag == int.Parse(content[1])) {
                    map.teams[i_team].players[i_player].content.x = int.Parse(content[2]);
                    map.teams[i_team].players[i_player].content.y = int.Parse(content[3]);
                    map.teams[i_team].players[i_player].orientation = int.Parse(content[4]);
                    map.teams[i_team].playersObj[i_player].transform.position =
                        new Vector3(map.teams[i_team].players[i_player].content.x * TileOffset,
                            0.6f, map.teams[i_team].players[i_player].content.y * TileOffset);
                    if (map.teams[i_team].players[i_player].orientation == 1)
                        map.teams[i_team].playersObj[i_player].transform.eulerAngles =
                            new Vector3(0, -90, 0);
                    else if (map.teams[i_team].players[i_player].orientation == 3)
                        map.teams[i_team].playersObj[i_player].transform.eulerAngles =
                            new Vector3(0, 90, 0);
                    else
                        map.teams[i_team].playersObj[i_player].transform.eulerAngles =
                            new Vector3(0, 90 * (map.teams[i_team].players[i_player].orientation), 0);
                    break;
                }
            }
        }
    }


    private void UpdatePlayerLevel(string[] content)
    {
        for (int i_team = 0; i_team < nb_teams; i_team++) {
            for (int i_player = 0; i_player < map.teams[i_team].nb_players; i_player++) {
                if (map.teams[i_team].players[i_player].playerTag == int.Parse(content[1])) {
                    map.teams[i_team].players[i_player].level += 1;
                    foreach (Transform player in playerParent.GetComponentsInChildren<Transform>()) {
                        if (player.name.ToString().IndexOf(",") != -1) {
                            string team = player.name.Split(",")[0];
                            int tag = int.Parse(player.name.Split(",")[1]);

                            if (team == map.teams[i_team].name && tag == map.teams[i_team].players[i_player].playerTag) {
                                map.teams[i_team].playersObj.Add(Instantiate(levels[map.teams[i_team].players[i_player].level - 2]));
                                map.teams[i_team].playersObj[map.teams[i_team].playersObj.Count - 1].transform.position =  player.transform.position;
                                map.teams[i_team].playersObj[map.teams[i_team].playersObj.Count - 1].transform.SetParent(playerParent.transform);
                                map.teams[i_team].playersObj[map.teams[i_team].playersObj.Count - 1].name = player.name;
                                Destroy(player.gameObject);
                                map.teams[i_team].playersObj.Remove(player.gameObject);
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    private void UpdatePlayerInventory(string[] content) {
        for (int i_team = 0; i_team < nb_teams; i_team++) {
            for (int i_player = 0; i_player < map.teams[i_team].nb_players; i_player++) {
                if (map.teams[i_team].players[i_player].playerTag == int.Parse(content[1])) {
                    map.teams[i_team].players[i_player].content.x = int.Parse(content[2]);
                    map.teams[i_team].players[i_player].content.y = int.Parse(content[3]);
                    map.teams[i_team].players[i_player].content.food = int.Parse(content[4]);
                    map.teams[i_team].players[i_player].content.linemate = int.Parse(content[5]);
                    map.teams[i_team].players[i_player].content.deraumere = int.Parse(content[6]);
                    map.teams[i_team].players[i_player].content.sibur = int.Parse(content[7]);
                    map.teams[i_team].players[i_player].content.mendiane = int.Parse(content[8]);
                    map.teams[i_team].players[i_player].content.phiras = int.Parse(content[9]);
                    map.teams[i_team].players[i_player].content.thystame = int.Parse(content[10]);
                    break;
                }
            }
        }
    }

    private void change_time_unit()
    {
        time_unit_txt.GetComponent<TextMeshProUGUI>().text = "Time unit: " + map.time_unit;
    }

    private void ArrowsTimeUnit()
    {
        int augment = 1;

        if (Input.GetKey(KeyCode.RightArrow) && !Input.GetKey(KeyCode.Tab)) {
            send_data = true;
            map.time_unit += augment;
            change_time_unit();
        }
        if (Input.GetKey(KeyCode.LeftArrow) && !Input.GetKey(KeyCode.Tab)) {
            send_data = true;
            map.time_unit -= augment;
            change_time_unit();
        }
        if (Input.GetKeyUp(KeyCode.LeftArrow) || Input.GetKeyUp(KeyCode.RightArrow) && !Input.GetKey(KeyCode.Tab)) {
            Debug.Log("Time unit : " + map.time_unit);
            NetworkManager.WriteServer("sst " + map.time_unit);
            NetworkManager.WriteServer("sgt");
        }
    }

    private void UpdateTab()
    {
        page_nbr = Mathf.CeilToInt(map.teams.Count / 2.0f);
        int last_page_content = map.teams.Count % 2;
        int offset = 0;
        int team_name = 1;

        if (created_tab)
            return;
        for (int i = 0; i < page_nbr; i++, offset++, team_name++) {
            GameObject tab_1 = Instantiate(tab_team1) as GameObject;
            tab_1.transform.SetParent(tab.transform, false);
            tab_1.transform.position = new Vector3(
                tab_1.transform.position.x + offset * Screen.width, 
                tab_1.transform.position.y, 
                tab_1.transform.position.z
            );
            tab_1.name = map.teams[team_name*2-2].name;
            tab_1.transform.Find("team_name").GetComponent<TextMeshProUGUI>().text = tab_1.name;
            GameObject tab_2;
            if (i+1 != page_nbr) {
                tab_2 = Instantiate(tab_team2) as GameObject;
                tab_2.transform.SetParent(tab.transform, false);
                tab_2.transform.position = new Vector3(
                    tab_2.transform.position.x + offset * Screen.width, 
                    tab_2.transform.position.y, 
                    tab_2.transform.position.z
                );
                tab_2.name = map.teams[team_name*2-1].name;
                tab_2.transform.Find("team_name").GetComponent<TextMeshProUGUI>().text = tab_2.name;
            } else {
                if (last_page_content != 1) {
                    tab_2 = Instantiate(tab_team2) as GameObject;
                    tab_2.transform.SetParent(tab.transform, false);
                    tab_2.transform.position = new Vector3(
                        tab_2.transform.position.x + offset * Screen.width, 
                        tab_2.transform.position.y, 
                        tab_2.transform.position.z
                    );
                    tab_2.name = map.teams[team_name*2-1].name;
                    tab_2.transform.Find("team_name").GetComponent<TextMeshProUGUI>().text = tab_2.name;
                }
            }
        }
        if (map.teams.Count != 0)
            created_tab = true;
    }

    private GameObject player_already_exist(Player player, Transform[] child, Transform reference, int pos) {
        foreach (Transform obj in child) {
            foreach (Transform obj_child in obj.GetComponentsInChildren<Transform>()) {
                if (obj_child.name == player.playerTag.ToString()) {
                    return obj_child.gameObject;
                }
            }
        }
        GameObject new_obj = Instantiate(tab_player) as GameObject;
        new_obj.name = player.playerTag.ToString();
        new_obj.transform.SetParent(reference, false);
        new_obj.transform.localPosition = new Vector3(new_obj.transform.localPosition.x, new_obj.transform.localPosition.y - pos*100, new_obj.transform.localPosition.z);
        new_obj.transform.Find("food").GetComponent<TextMeshProUGUI>().text = "10";
        return new_obj;
    }

    private void UpdatePlayerInTabs()
    {
        foreach (Team team in map.teams) {
            foreach (Transform child in tab.GetComponentsInChildren<Transform>()) {
                if (child.name == team.name) {
                    if (team.nb_players < 0)
                        return;
                    for (int i = 0; i < team.nb_players; i++) {
                        GameObject player = player_already_exist(team.players[i], tab.GetComponents<Transform>(), child, i);
                        player.transform.Find("player_id").GetComponent<TextMeshProUGUI>().text = team.players[i].playerTag.ToString();
                        player.transform.Find("player_lvl").GetComponent<TextMeshProUGUI>().text = team.players[i].level.ToString();
                        player.transform.Find("food").GetComponent<TextMeshProUGUI>().text = team.players[i].content.food.ToString();
                        player.transform.Find("linemate").GetComponent<TextMeshProUGUI>().text = team.players[i].content.linemate.ToString();
                        player.transform.Find("deraumere").GetComponent<TextMeshProUGUI>().text = team.players[i].content.deraumere.ToString();
                        player.transform.Find("sibur").GetComponent<TextMeshProUGUI>().text = team.players[i].content.sibur.ToString();
                        player.transform.Find("mendiane").GetComponent<TextMeshProUGUI>().text = team.players[i].content.mendiane.ToString();
                        player.transform.Find("phiras").GetComponent<TextMeshProUGUI>().text = team.players[i].content.phiras.ToString();
                        player.transform.Find("thystame").GetComponent<TextMeshProUGUI>().text = team.players[i].content.thystame.ToString();
                    }
                }
            }
        }
    }

    private void switch_tab_page(int value)
    {
        if (tab_page + value < 0 || tab_page + value >= page_nbr)
            return;
        tab_page = tab_page + value;
        Vector3 pos = new Vector3(tab_page * -Screen.width + Screen.width/2, tab.transform.position.y, tab.transform.position.z);
        tab.transform.position = pos;
    }

    private void TabShow()
    {
        if (Input.GetKey(KeyCode.Tab)) {
            if (Input.GetKey(KeyCode.RightArrow) && !switched_tab) {
                switched_tab = true;
                switch_tab_page(1);
            }
            if (Input.GetKey(KeyCode.LeftArrow) && !switched_tab) {
                switched_tab = true;
                switch_tab_page(-1);
            }
            if (Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyDown(KeyCode.RightArrow)) {
                switched_tab = false;
            }
            UpdateTab();
            UpdatePlayerInTabs();
            tab.SetActive(true);
        } else {
            tab.SetActive(false);
        }
    }

    private void KillPlayer(string playerTag)
    {
        GameObject Temp;
        bool next = false;

        for (int i_team = 0; i_team < nb_teams; i_team++) {
            for (int i_player = 0; i_player < map.teams[i_team].nb_players; i_player++) {
                if (map.teams[i_team].players[i_player].playerTag == int.Parse(playerTag)) {
                    map.teams[i_team].players.RemoveAt(i_player);
                    Temp = map.teams[i_team].playersObj[i_player];
                    map.teams[i_team].playersObj.Remove(Temp);
                    Destroy(Temp);
                    map.teams[i_team].nb_players--;
                }
                foreach (Transform players in tab.GetComponentsInChildren<Transform>()) {
                    if (players.name == map.teams[i_team].name) {
                        foreach (Transform player in players.GetComponentsInChildren<Transform>()) {
                            if (player.name == playerTag) {
                                Destroy(player.gameObject);
                                next = true;
                            }
                            if (next == true) {
                                foreach(Team team in map.teams) {
                                    if (team.name == map.teams[i_team].name && player.name != map.teams[i_team].name) {
                                        player.position = new Vector3(player.position.x, player.position.y + 50, player.position.z);
                                    }
                                }
                            }
                        }
                    }
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
        if (cmd.StartsWith("sgt ") || cmd.StartsWith("sst ")) {
            map.time_unit = int.Parse(content[1]);
            change_time_unit();
        }
        if (cmd.StartsWith("pnw "))
            GeneratePlayer(content);
        if (cmd.StartsWith("ppo "))
            UpdatePlayer(content);
        if (cmd.StartsWith("pin "))
            UpdatePlayerInventory(content);
        if (cmd.StartsWith("plv "))
            UpdatePlayerLevel(content);
        if (cmd.StartsWith("pdi "))
            KillPlayer(content[1]);
    }

    private void Update() {
        // CamMovement();
        ArrowsTimeUnit();
        TabShow();
        if (count > 1) {
            if (!NetworkManager.connected)
                throw new System.Exception("Error disconnected");
            try {
                if (!NetworkManager.stream.DataAvailable)
                    return;
                string cmd = NetworkManager.ReadServer();
                HandleCommand(cmd);
            } catch (System.Exception e) {
                Debug.Log("Exception : " + e.Message);
            }
        } else {
            count++;
        }
    }

void Start()
    {
        Cursor.visible = false;
        if (NetworkManager.connected) {
            map.teams = new List<Team>();
            levels.Add(level2);
            levels.Add(level3);
            levels.Add(level4);
            levels.Add(level5);
            levels.Add(level6);
            levels.Add(level7);
            levels.Add(level8);
            Debug.Log("Connected");
        } else {
            Debug.Log("Not connected");
        }
    }
}
