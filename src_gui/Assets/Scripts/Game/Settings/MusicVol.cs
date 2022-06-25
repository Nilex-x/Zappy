using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MusicVol : MonoBehaviour
{

    private float musicVolume = 1f;

    void Update()
    {
        AudioSource audio = GameObject.Find("Music").GetComponent<AudioSource>();

        audio.volume = musicVolume;
    }

    public void updateVolume(float volume)
    {
        musicVolume = volume;
    }
}
