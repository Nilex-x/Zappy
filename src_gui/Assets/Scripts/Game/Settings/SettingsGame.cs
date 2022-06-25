using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SettingsGame : MonoBehaviour
{
    public GameObject TimeUnit;
    public GameObject Tab;
    public GameObject SettingsMenu;
    public GameObject Background;

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape)) {
            SettingsMenu.SetActive(!SettingsMenu.active);
            Background.SetActive(!Background.active);
            Tab.SetActive(false);
            TimeUnit.SetActive(!TimeUnit.active);
        }
    }
}
