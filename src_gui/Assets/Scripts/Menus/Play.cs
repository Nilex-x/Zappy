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
        if (ip_valid && port_valid) {
            try {
                errorMessage.GetComponent<TextMeshProUGUI>().text = "";
                NetworkManager.StartClient(ip, int.Parse(port));
            } catch (SocketException e) {
                errorMessage.GetComponent<TextMeshProUGUI>().text = "Error while creating the socket";
                Debug.Log("SocketException: " + e);
            } catch (System.Exception e) {
                Debug.Log("ArgumentNullException: " + e);
                errorMessage.GetComponent<TextMeshProUGUI>().text = e.ToString();
            }
        } else {
            Debug.Log("Error ip is " + ip_valid);
            Debug.Log("Error port is " + port_valid);
            errorMessage.GetComponent<TextMeshProUGUI>().text = "Error, IP: " + ip + " Port: " + port;
        }
    }

}
