using UnityEngine;
using System.Collections;

public class Shield : MonoBehaviour {

    public int characterNumber;
    public Material materialOfParent;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    void OnTriggerEnter(Collider col)
    {
        Magic m = col.gameObject.GetComponent<Magic>();

        if (m != null)
        {
            m.rigidbody.velocity = -m.rigidbody.velocity;
            m.characterNumber = characterNumber;
            m.renderer.material = materialOfParent;
        }
    }
}
