using UnityEngine;
using System.Collections;

public abstract class Utility : MonoBehaviour{


	public float lifeTime;
	public Controller controller;
	public Rigidbody rigidBody;
	public float countdown;
	public float cooldown;
	public GameObject owningChar;
	protected float curCooldown;
	// Use this for initialization

    public abstract void Update();
    public abstract void Start();

	// Update is called once per frame
	public abstract void init();
	//public abstract void customUpdate ();

	public abstract void Activate ();

	public abstract void Deactivate ();
}
