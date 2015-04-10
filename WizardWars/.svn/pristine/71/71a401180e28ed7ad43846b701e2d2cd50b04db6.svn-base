using UnityEngine;
using System.Collections;

public class Dash : Utility
{

    //the number of seconds the utility will be active
    //public float lifeTime = 1;
    //public float countdown = 0;
    public float dashSpeed = 30;
    bool inActive = true;
    //public override Controller controller;
    // Use this for initialization
    public override void init()
    {
        lifeTime = .2f;
        countdown = 0;
        cooldown = 1;
    }
    
	public override void Start()
    {
        GameObject.DontDestroyOnLoad(controller);
        GameObject.DontDestroyOnLoad(owningChar);
        GameObject.DontDestroyOnLoad(rigidBody);
	}
    // Update is called once per frame
    public override void Update()
    {
        if (countdown > 0)
        {
            countdown -= Time.deltaTime;
            if (countdown <= 0)
            {
                if(!inActive)
                {
                    Deactivate();  
                }
            }
        }

        if (curCooldown > 0)
        {
            curCooldown -= Time.deltaTime;
        }
    }

    public override void Activate()
    {
        if (curCooldown <= 0)
        {
            inActive = false;
            GameObject getSound=GameObject.Find("SoundManager");
            SoundManager SM=getSound.GetComponent<SoundManager>();
            SM.playDash();
            //Debug.Log ("Dash");
            countdown = lifeTime;
            //Controller controller = gameOb.GetComponent<Controller> ();

            if (controller.getMoveStick().x > 0)
            {
                rigidBody.useGravity = false;
                rigidBody.velocity = new Vector2(dashSpeed, 0);
            }
            if (controller.getMoveStick().x < 0)
            {
                rigidBody.useGravity = false;
                rigidBody.velocity = new Vector2(-dashSpeed, 0);
            }
        }
    }

    public override void Deactivate()
    {
        curCooldown = cooldown;
        rigidBody.useGravity = true;
        rigidBody.velocity = Vector2.zero;
    }
}
