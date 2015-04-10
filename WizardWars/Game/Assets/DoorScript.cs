using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class DoorScript : MonoBehaviour 
{
    public string sceneName;
    public Utility dashUtil;





	// Use this for initialization
	void Start () 
    {
	
	}
	
	// Update is called once per frame
	void Update () 
    {

	}

    public void GoToLevel()
    {
        GameObject.Find("MenuSystem").GetComponent<MenuSystem>().GoToLevel(sceneName);
    }
}
