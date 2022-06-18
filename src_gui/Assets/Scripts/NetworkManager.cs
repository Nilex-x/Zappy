using System.Net;
using System.Net.Sockets;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.Threading;

public class NetworkManager : MonoBehaviour
{
    private static TcpClient socket;
    public static NetworkStream stream;
    public static StreamReader reader;
    public static StreamWriter writer;
    public static bool connected = false;
    public static bool finished_read = false;
    // Start is called before the first frame update
    void Start()
    {
        DontDestroyOnLoad(this.gameObject);
    }

    private void OnDestroy() {
        writer.Close();
        reader.Close();
        stream.Close();
        socket.Close();
    }

    public static void StartClient(string host, int port) {
        socket = new TcpClient(host, port);
        stream = socket.GetStream();
        writer = new StreamWriter(stream);
        reader = new StreamReader(stream);
        writer.WriteLine("gui");
        writer.Flush();
        connected = true;
        SceneManager.LoadScene("game");
    }

    public static string ReadServer()
    {
        System.Threading.Thread.Sleep(1);
        if (!connected || !stream.DataAvailable)
            throw new System.Exception("No data to read");
        return reader.ReadLine();
    }

    public static void WriteServer(string message)
    {
        System.Threading.Thread.Sleep(1);
        if (!connected)
            throw new System.Exception("Not connected");
        writer.WriteLine(message);
        writer.Flush();
    }
}


// using System.Collections;
// using System.Collections.Generic;
// using System.Net;
// using System.Net.Sockets;
// using System;
// using System.Text;
// using System.IO;
// using System.Threading;
// using UnityEngine.SceneManagement;
// using UnityEngine;

// public class NetworkManager : MonoBehaviour
// {
//     private static TcpClient socket;
//     public static NetworkStream stream;
//     public static StreamWriter writer;
//     public static StreamReader reader;
//     public static bool connected = false;

//     void Start()
//     {
//         DontDestroyOnLoad(this.gameObject);
//     }

//     private void OnDestroy()
//     {
//         if (connected)
//         {
//             writer.Close();
//             reader.Close();
//             stream.Close();
//             socket.Close();
//             connected = false;
//         }
//     }

//     public static void StartClient(string host, int port)
//     {
//         try
//         {
//             socket = new TcpClient(host, port);
//             if (socket == null || !socket.Connected)
//             {
//                 return;
//             }
//             socket.ReceiveTimeout = 5000;
//             stream = socket.GetStream();
//             writer = new StreamWriter(stream);
//             reader = new StreamReader(stream);
//             writer.WriteLine("gui");
//             writer.Flush();
//             connected = true;
//             SceneManager.LoadScene("Game");
//         }
//         catch (Exception e)
//         {
//             Debug.Log(e.ToString());
//             return;
//         }
//     }

//     public static string ReadServer()
//     {
//         if (!connected)
//             throw new IOException();
//         if (!stream.DataAvailable)
//             throw new IOException();
//         return reader.ReadLine();
//     }
// }