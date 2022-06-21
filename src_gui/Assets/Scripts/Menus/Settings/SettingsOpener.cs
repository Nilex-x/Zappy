using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SettingsOpener : MonoBehaviour
{
    public GameObject Settings;
    public GameObject SettingsButton;
    public GameObject GameName;

    public void OpenSettings()
    {
        if (Settings != null)
            Settings.SetActive(true);
        if (SettingsButton != null)
            SettingsButton.SetActive(false);
        if (GameName != null)
            GameName.SetActive(false);
    }
}
