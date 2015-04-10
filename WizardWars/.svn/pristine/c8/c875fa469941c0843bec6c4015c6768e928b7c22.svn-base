using UnityEngine;
using System.Collections;

public class Reflect : Utility {

    public float dashSpeed = 30;
    public GameObject shieldPrefab;

    GameObject s;
    //public override Controller controller;
    // Use this for initialization
    public override void init()
    {
        lifeTime = .2f;
        countdown = 0;
        cooldown = .75f;
    }

    public override void Start()
    {
    }
    
    // Update is called once per frame
    public override void Update()
    {
        if (countdown > 0)
        {
            countdown -= Time.deltaTime;
            if (countdown <= 0)
            {
                Deactivate();       
            }
        }
        if (s != null)
        {
            Vector2 temp = new Vector2(rigidBody.position.x, rigidBody.position.y) + (-controller.getAimStick().normalized * .5f);
            s.transform.position = new Vector3(temp.x, temp.y, 0);
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
            //Debug.Log ("Dash");
            countdown = lifeTime;
            //Controller controller = gameOb.GetComponent<Controller> ();
            Vector2 position = new Vector2( rigidBody.position.x, rigidBody.position.y) + (-controller.getAimStick().normalized * .5f);
            Vector2 perp = controller.getAimStick().normalized;
            //perp = new Vector2(-perp.y, perp.x);
            float angle = Mathf.Atan2(perp.y, perp.x);

            s = (GameObject)Instantiate (shieldPrefab, new Vector3(position.x, position.y, 0), Quaternion.identity);// Quaternion.Euler(0, 0, Mathf.Rad2Deg * angle)); 
            s.transform.Rotate(new Vector3(0,0,1), Mathf.Rad2Deg * angle);

            Destroy (s, lifeTime);
        }
    }
    
    public override void Deactivate()
    {
        Debug.Log("Deactivate");
        curCooldown = cooldown;
        //rigidBody.useGravity = true;
        //rigidBody.velocity = Vector2.zero;
    }
}
