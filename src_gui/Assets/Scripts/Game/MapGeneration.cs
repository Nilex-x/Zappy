using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Environnement {
    public List<GameObject> details;
    public int nb_details = 0;
}

public class MapGeneration : MonoBehaviour
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

    public static Environnement environnement = new Environnement();

    private void generateMainIsland(int maxMapTiles, float TileOffset, int mapTilesX, int mapTilesY)
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

    public void generateEnvironnement(int mapTilesX, int mapTilesY, float TileOffset)
    {
        int maxMapTiles = 0;
        float scaleModify = 1;
    
        if (mapTilesX > mapTilesY)
            maxMapTiles = mapTilesX;
        else
            maxMapTiles = mapTilesY;
        if (maxMapTiles >= 20)
            scaleModify += (maxMapTiles/10) * 0.25f;
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

        environnement.details.Add(Instantiate(RockLarge));
        environnement.details[environnement.nb_details].transform.position =
            new Vector3((float)(mapTilesX * TileOffset)/2 - (60 * scaleModify), 109, (float)(mapTilesY * TileOffset)/2 - (210 * scaleModify));
        environnement.details[environnement.nb_details].transform.eulerAngles = new Vector3(0, -20, 0);
        environnement.details[environnement.nb_details].transform.SetParent(EnvironnementHandler.transform);
        environnement.details[environnement.nb_details].name = "Island Mountain";
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
            new Vector3((float)(mapTilesX * TileOffset)/2 - (80 * scaleModify), -25, (float)(mapTilesY * TileOffset)/2 - (460 * scaleModify));
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
    }
}
