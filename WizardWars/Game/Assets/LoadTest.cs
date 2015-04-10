using UnityEngine;
using System.Collections;

public class LoadTest : MonoBehaviour {

	// Use this for initialization
	void Start () {
		//DISCLAIMER: Incredibly janky
		GameManager go = GameObject.FindObjectOfType<GameManager>();
		if(!go)
		{
			Application.LoadLevel(0);
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
