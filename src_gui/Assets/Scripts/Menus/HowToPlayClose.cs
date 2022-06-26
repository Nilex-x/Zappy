using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HowToPlayClose : MonoBehaviour
{
    public GameObject HowToPlay;
    public GameObject HowToPlayButton;

    public void CloseHowToPlay()
    {
        if (HowToPlay != null)
            HowToPlay.SetActive(false);
        if (HowToPlayButton != null)
            HowToPlayButton.SetActive(true);
    }
}
