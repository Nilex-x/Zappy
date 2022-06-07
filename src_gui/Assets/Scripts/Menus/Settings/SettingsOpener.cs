using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SettingsOpener : MonoBehaviour
{
    public GameObject Settings;

    public void OpenSettings()
    {
        if (Settings != null) {
            Settings.SetActive(true);
        }
    }
}
