using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartButton : MonoBehaviour
{
    public GameObject StartMenu;
    public GameObject InputMenu;

    public void ChangeStartScene()
    {
        if (StartMenu != null)
            StartMenu.SetActive(false);
        if (InputMenu != null)
            InputMenu.SetActive(true);
    }
}
