using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SettingsCloser : MonoBehaviour
{
    public GameObject Settings;
    public GameObject SettingsButton;
    public GameObject GameName;

    public void CloseSettings()
    {
        if (Settings != null)
            Settings.SetActive(false);
        if (SettingsButton != null)
            SettingsButton.SetActive(true);
        if (GameName != null)
            GameName.SetActive(true);
    }
}
