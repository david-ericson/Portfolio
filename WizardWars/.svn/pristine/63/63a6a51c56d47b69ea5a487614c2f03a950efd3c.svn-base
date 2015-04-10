using UnityEngine;
using System.Collections;

public class TrailTimeout : MonoBehaviour {
	float timeout;
	// Use this for initialization
	void Start () {
		timeout = this.gameObject.GetComponent<TrailRenderer>().time;
	}
	
	// Update is called once per frame
	void Update () {
		if(!this.gameObject.transform.parent)
		{
			timeout -= Time.deltaTime;
			if(timeout <= 0)
			{
				Destroy(this.gameObject);
			}
		}
	}
}
