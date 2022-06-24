using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Environnement {
    public List<GameObject> details;
    public int nb_details = 0;
}

public class MapGeneration : MonoBehaviour
{
    public static GameObject EnvironnementHandler;
    public static GameObject MainIsland;
    public static GameObject MainIslandGround;
    public static GameObject Rock1;
    public static GameObject Rock2;
    public static GameObject Rock3;
    public static GameObject RockLarge;
    public static GameObject SmallRock;
    public static GameObject MountainTall;
    public static GameObject Drake;
    public static GameObject GodRock;
    public static GameObject RockTall;
    public static GameObject RockMedium;
    public static GameObject MountainSlopping;
    public static GameObject FlyingShip;

    public static Environnement environnement = new Environnement();

    private static void generateMainIsland(int maxMapTiles, float TileOffset, int mapTilesX, int mapTilesY)
    {
        environnement.details = new List<GameObject>();
        environnement.details.Add(Instantiate(MainIsland));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2, 0, (float)(mapTilesY * TileOffset)/2);
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(maxMapTiles * 0.3f, maxMapTiles * 0.3f, maxMapTiles * 0.3f);
            environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Main Island";
        environnement.nb_details++;
        environnement.details.Add(Instantiate(MainIslandGround));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2, 0.1f, (float)(mapTilesY * TileOffset)/2);
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(maxMapTiles * 0.35f, maxMapTiles * 0.35f, maxMapTiles * 0.35f);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Main Island Ground";
        environnement.nb_details++;
    }

    public static void generateEnvironnement(int mapTilesX, int mapTilesY, float TileOffset)
    {
        int maxMapTiles = 0;
        float scaleModify = 1.25f;
    
        if (mapTilesX > mapTilesY)
            maxMapTiles = mapTilesX;
        else
            maxMapTiles = mapTilesY;
        if (maxMapTiles >= 20)
            scaleModify = 1 + (maxMapTiles/10) * 0.25f;
        generateMainIsland(maxMapTiles, TileOffset, mapTilesX, mapTilesY);
        environnement.details.Add(Instantiate(Rock1));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (105 * scaleModify), -10, (float)(mapTilesY * TileOffset)/2 - (75 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(35, 35, 35);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock1));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (160 * scaleModify), -20, (float)(mapTilesY * TileOffset)/2 - (60 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(35, 35, 35);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, 80, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(SmallRock));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (170 * scaleModify), 60, (float)(mapTilesY * TileOffset)/2 - (60 * scaleModify));
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Island Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock3));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (30 * scaleModify), -10, (float)(mapTilesY * TileOffset)/2 - (200 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(70, 70, 70);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, 60, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(GodRock));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (60 * scaleModify), 109, (float)(mapTilesY * TileOffset)/2 - (210 * scaleModify));
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, -20, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "God Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock2));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (330 * scaleModify), 50, (float)(mapTilesY * TileOffset)/2 - (380 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(90, 90, 90);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, -90, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(MountainTall));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (30 * scaleModify), -25, (float)(mapTilesY * TileOffset)/2 - (500 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(2, 2, 2);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock2));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (290 * scaleModify), 75, (float)(mapTilesY * TileOffset)/2 - (355 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(125, 125, 125);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock3));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (370 * scaleModify), 30, (float)(mapTilesY * TileOffset)/2 - (280 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(90, 70, 90);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, -45, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Drake));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (220 * scaleModify), 110, (float)(mapTilesY * TileOffset)/2 - (480 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(0.5f, 0.5f, 0.5f);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, 80, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Drake";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock3));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2, -10, (float)(mapTilesY * TileOffset)/2 + (200 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(150, 50, 90);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, 0, 10);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock1));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (140 * scaleModify), 0, (float)(mapTilesY * TileOffset)/2 + (70 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(35, 35, 35);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, 0, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(FlyingShip));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (140 * scaleModify), 250, (float)(mapTilesY * TileOffset)/2 + (70 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(0.3f, 0.3f, 0.3f);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, -30, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "FlyingShip";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(MountainSlopping));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (290 * scaleModify), -49, (float)(mapTilesY * TileOffset)/2 + (100 * scaleModify));
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock2));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (280 * scaleModify), 80, (float)(mapTilesY * TileOffset)/2 + (460 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(75, 75, 75);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(RockLarge));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (330 * scaleModify), -40, (float)(mapTilesY * TileOffset)/2 - (55 * scaleModify));
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock2));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (550 * scaleModify), 0, (float)(mapTilesY * TileOffset)/2 + (70 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(75, 75, 75);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(30, 0, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(MountainTall));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (460 * scaleModify), -322, (float)(mapTilesY * TileOffset)/2 + (450 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(3, 3, 3);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(Rock2));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (90 * scaleModify), 0, (float)(mapTilesY * TileOffset)/2 + (500 * scaleModify));
        environnement.details[environnement.nb_details].transform.localScale =
            new Vector3(75, 75, 75);
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, 180, 40);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(RockMedium));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (200 * scaleModify), -30, (float)(mapTilesY * TileOffset)/2 - (140 * scaleModify));
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, 0, 180);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;

        environnement.details.Add(Instantiate(RockTall));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 + (190 * scaleModify), -18, (float)(mapTilesY * TileOffset)/2 - (80 * scaleModify));
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, 0, 190);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Mountain";
        environnement.nb_details++;
    }
}
