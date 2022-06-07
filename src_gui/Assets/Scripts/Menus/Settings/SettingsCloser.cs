using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SettingsCloser : MonoBehaviour
{
    public GameObject Settings;

    public void CloseSettings()
    {
        if (Settings != null)
            Settings.SetActive(false);
    }
}
