using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TileMapGen : MonoBehaviour
{
    public GameObject tilePrefab;

    [SerializeField]int mapWidth = Main.map.width;
    [SerializeField]int mapHeight = Main.map.height;

    [SerializeField]float tileOffset = 1.45f;

    void Start()
    {
        CreateTileMap();
    }

    void CreateTileMap()
    {
        for (int x = 0; x < mapWidth; x++) {
            for (int z = 0; z < mapHeight; z++) {
                GameObject Temp = Instantiate(tilePrefab);
                Temp.transform.position = new Vector3(x * tileOffset, 0, z * tileOffset);
                SetTileInfo(Temp, x, z);
            }
        }
    }

    void SetTileInfo(GameObject Temp, int x, int z)
    {
        Temp.transform.parent = transform;
        Temp.name = x.ToString() + ", " + z.ToString();
    }
}
