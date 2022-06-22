using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SettingsCloser : MonoBehaviour
{
    public GameObject Settings;
    public GameObject SettingsButton;
    public GameObject GameName;
    public GameObject MainMenu;
    public GameObject InputMenu;

    public void CloseSettings()
    {
        if (Settings != null)
            Settings.SetActive(false);
        if (SettingsButton != null)
            SettingsButton.SetActive(true);
        if (GameName != null)
            GameName.SetActive(true);
        if (!MainMenu.active)
            InputMenu.SetActive(true);
    }
}
