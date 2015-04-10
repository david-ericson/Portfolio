using UnityEngine;
using System.Collections;

public class CloneCloak : Utility {

	//the number of seconds the utility will be active
	//public float lifeTime = 1;
	//public float countdown = 0;
	//public float dashSpeed = 30;
	//public override Controller controller;
	// Use this for initialization
	public GameObject clonePrefab;
	//public GameObject owningChar;

	private GameObject clo;
	private Vector3 clovel;
	public override void init()
	{
		lifeTime = 3;
		countdown = 0;
		cooldown = 3;
	}

	public override void Start()
	{
	}
	// Update is called once per frame
	public override void Update()
	{
		if (countdown > 0)
		{
			clo.rigidbody.velocity = new Vector3(clovel.x, clo.rigidbody.velocity.y, 0);
			countdown -= Time.deltaTime;
			if (countdown <= 0)
			{
				Deactivate();
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
			//Debug.Log ("Dash");
			countdown = lifeTime;
			//Controller controller = gameOb.GetComponent<Controller> ();
			
			//Need to create a new clone of yourself.
            Vector3 direction = -new Vector3(owningChar.GetComponent<Controller>().getAimStick().x, owningChar.GetComponent<Controller>().getAimStick().y, 0).normalized;
            Vector3 pos = new Vector3(owningChar.transform.position.x, owningChar.transform.position.y, .6f);
			clo = (GameObject)Instantiate(clonePrefab, pos + direction * 1.0f, Quaternion.identity);
			clo.rigidbody.velocity = new Vector3(owningChar.rigidbody.velocity.x, owningChar.rigidbody.velocity.y, owningChar.rigidbody.velocity.z);
			clo.renderer.material = new Material(owningChar.renderer.material);
            clovel = direction * owningChar.GetComponent<Controller>().speed;
			owningChar.renderer.material.color = new Color(owningChar.renderer.material.color.r, owningChar.renderer.material.color.g, owningChar.renderer.material.color.b, 1);
		}
	}
	
	public override void Deactivate()
	{
		curCooldown = cooldown;

		Destroy (clo);
		owningChar.renderer.material.color = new Color(owningChar.renderer.material.color.r, owningChar.renderer.material.color.g, owningChar.renderer.material.color.b, 1.0f);
		
	}
}
