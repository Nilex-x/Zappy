using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackMenu : MonoBehaviour
{
    public GameObject Settings;
    public GameObject StartMenu;
    public GameObject InputMenu;
    public GameObject GameName;
    public GameObject SettingsButton;

    public void BackToMenu()
    {
        if (Settings != null)
            Settings.SetActive(false);
        if (InputMenu != null)
            InputMenu.SetActive(false);
        if (StartMenu != null)
            StartMenu.SetActive(true);
        if (SettingsButton != null)
            SettingsButton.SetActive(true);
        if (GameName != null)
            GameName.SetActive(true);
    }
}
