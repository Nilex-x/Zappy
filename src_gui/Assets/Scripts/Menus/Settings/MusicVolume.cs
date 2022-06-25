using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MusicVolume : MonoBehaviour
{
    public AudioSource audio;

    private float musicVolume = 1f;

    void Update()
    {
        audio.volume = musicVolume;
    }

    public void updateVolume(float volume)
    {
        musicVolume = volume;
    }
}
