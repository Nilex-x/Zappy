using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackMenu : MonoBehaviour
{
    public GameObject Settings;
    public GameObject StartMenu;
    public GameObject InputMenu;

    public void BackToMenu()
    {
        if (Settings != null)
            Settings.SetActive(false);
        if (InputMenu != null)
            InputMenu.SetActive(false);
        if (StartMenu != null)
            StartMenu.SetActive(true);
    }
}
