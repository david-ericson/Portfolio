﻿using UnityEngine;
using System.Collections;

public class Phase : Utility {

    public override void init()
    {
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
            owningChar.rigidbody.useGravity = false;
            owningChar.rigidbody.velocity = Vector3.zero;
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
            ((Character)owningChar.GetComponent<Character>()).setInvincible(true);
            owningChar.rigidbody.velocity = Vector3.zero;
            owningChar.rigidbody.collider.enabled = false;
            owningChar.rigidbody.useGravity = false;
            countdown = lifeTime;
        }
    }
    
    public override void Deactivate()
    {
        ((Character)owningChar.GetComponent<Character>()).setInvincible(false);
        owningChar.rigidbody.collider.enabled = true;
        owningChar.rigidbody.useGravity = true;
        curCooldown = cooldown;
    }
}
