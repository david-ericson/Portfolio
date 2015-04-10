using UnityEngine;
using System.Collections;

public class RuneRep : MonoBehaviour {

    public Mesh rune;

	// Use this for initialization
	void Start (){
	}
	
	// Update is called once per frame
	void Update () {
        //this.transform = Vector3(this.gameObject.rigidbody.position.x, this.gameObject.rigidbody.position.y + 1, this.gameObject.rigidbody.position.z);
        this.gameObject.GetComponent<MeshFilter>().mesh = rune;
        Vector3 send = new Vector3(0.0f, 200.0f * Time.deltaTime, 0.0f);
        this.gameObject.transform.Rotate(send);
	}
}
