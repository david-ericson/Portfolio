using UnityEngine;
using System.Collections;

public class SpikeTrap : MonoBehaviour {

	// Use this for initialization
	void Start () 
    {
	
	}
	
	// Update is called once per frame
	void Update () 
    {
	
	}

    void OnTriggerEnter(Collider col)
    {
        Character c = col.GetComponent<Character>();
        if (c != null)
        {
            if(!c.getInvincible())
            {
				if(c.gameType==3)
				{
					int curScore=c.getNumKills();
					curScore=curScore/2;
					c.alterNumKills(-curScore);
				}
				else
				{
                	c.alterNumKills(-1);
				}
                c.Kill();
            }
        }
    }
}
