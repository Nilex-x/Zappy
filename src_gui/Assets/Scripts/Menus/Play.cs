using System.Text.RegularExpressions;
using UnityEngine;
using TMPro;
using System.Net.Sockets;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;

public class Play : MonoBehaviour
{
    private bool ip_valid;
    private bool port_valid;
    private string ip;
    private string port;
    private string input;
    public static TcpClient client;
    public static NetworkStream stream;
    public GameObject errorMessage_ip;
    public GameObject errorMessage_port;
    public GameObject errorMessage;

    void Start() {
        
    }
    void Update() {
        
    }

    public void ReadStringInput_ip(string s) {
        input = s;
        Regex ip_reg = new Regex(@"^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$", RegexOptions.IgnoreCase);
        
        if (ip_reg.IsMatch(input)) {
            ip = input;
            ip_valid = true;
            errorMessage_ip.GetComponent<TextMeshProUGUI>().text = "";
            Debug.Log("IP: " + ip);
        } else {
            ip_valid = false;
            errorMessage_ip.GetComponent<TextMeshProUGUI>().text = "Invalid IP";
            Debug.Log("Invalid input");
        }
    }
public void ReadStringInput_port(string s) {
        input = s;
        Regex port_reg = new Regex(@"^([1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$", RegexOptions.IgnoreCase);
        
        if (port_reg.IsMatch(input)) {
            port = input;
            port_valid = true;
            errorMessage_port.GetComponent<TextMeshProUGUI>().text = "";
            Debug.Log("Port: " + port);
        } else {
            port_valid = false;
            errorMessage_port.GetComponent<TextMeshProUGUI>().text = "Invalid port";
            Debug.Log("Invalid input");
        }
    }

    public void PlayGame(string s) {
        string message = "/login \"" + s +"\"";
        if (ip_valid && port_valid) {                                           //check if everything is valid before trying to connect
            try {
                errorMessage.GetComponent<TextMeshProUGUI>().text = "";
                client = new TcpClient(ip, int.Parse(port));                    //create client and connect to server 
                byte[] data = System.Text.Encoding.ASCII.GetBytes(message);     //send message
                stream = client.GetStream();                                    //get stream (equivalent to get the file descriptor)
                stream.Write(data, 0, data.Length);                             //write data to stream (equivalent to write(fd, message, strlen(message)))
                Debug.Log("Sent: " + message);
                data = new byte[256];                                           //create new buffer for the answer
                string response = string.Empty;
                int bytes = stream.Read(data, 0, data.Length);                  //read answer from stream (equivalent to read(fd, buffer, sizeof(buffer)))
                response = System.Text.Encoding.ASCII.GetString(data, 0, bytes);//convert answer to string
                Debug.Log("Received:" + response);
                SceneManager.LoadScene("Game");                                 //load game scene
            } catch (System.ArgumentNullException e) {                          //if an argument is null
                Debug.Log("ArgumentNullException: " + e);
                errorMessage.GetComponent<TextMeshProUGUI>().text = "Error, ArgumentNullException";
            } catch (SocketException e) {                                       //if a socket error occurs
                errorMessage.GetComponent<TextMeshProUGUI>().text = "Error while creating the socket";
                Debug.Log("SocketException: " + e);
            }
        } else {
            Debug.Log("Not ok");
            Debug.Log(ip_valid);
            Debug.Log(port_valid);
            errorMessage.GetComponent<TextMeshProUGUI>().text = "Error, IP: " + ip + " Port: " + port;
        }
    }

}
