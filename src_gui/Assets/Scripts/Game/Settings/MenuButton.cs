using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MenuButton : MonoBehaviour
{
    public void BackToMenu()
    {
        foreach (GameObject o in Object.FindObjectsOfType<GameObject>())
            Destroy(o);
        Destroy (GameObject.Find("Music"));
        SceneManager.LoadScene("menu");
    }
}
