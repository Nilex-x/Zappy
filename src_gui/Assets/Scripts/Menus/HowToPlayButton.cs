using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HowToPlayButton : MonoBehaviour
{
    public GameObject HowToPlay;
    public GameObject Button;

    public void OpenHowToPlay()
    {
        if (HowToPlay != null)
            HowToPlay.SetActive(true);
        if (Button != null)
            Button.SetActive(false);
    }
}
