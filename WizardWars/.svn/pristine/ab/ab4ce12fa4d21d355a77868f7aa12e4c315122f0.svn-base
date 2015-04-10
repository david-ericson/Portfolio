using UnityEngine;
using System.Collections;

public class CharacterProjectile : MonoBehaviour {

	public Projectile p;
	// Use this for initialization
	void Start () {
		//p.Start();
        p = (Projectile)Instantiate(p);
        p.Start();
	}

    public int getTeamNum()
    {
        return p.getTeamNumber();
    }
	
	// Update is called once per frame
	void Update () {
		p.Update();
	}
}
