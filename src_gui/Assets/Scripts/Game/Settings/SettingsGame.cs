using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SettingsGame : MonoBehaviour
{
    public GameObject TimeUnit;
    public GameObject Tab;
    public GameObject SettingsMenu;
    public GameObject Background;
    private bool state = false;

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape)) {
            state = !state;
            if (state) {
                Cursor.lockState = CursorLockMode.None;
            } else if (!state) {
                Cursor.lockState = CursorLockMode.Locked;
            }
            SettingsMenu.SetActive(!SettingsMenu.active);
            Background.SetActive(!Background.active);
            Tab.SetActive(false);
            TimeUnit.SetActive(!TimeUnit.active);
        }
    }
}
