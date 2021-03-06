﻿using UnityEngine;
using System.Collections;

public class FireBall : Projectile {

    // Use this for initialization
    public override void Start () {
        coolDownTimer = bullet.coolDown;
        
        if (owner != null)
        {
            Material m = owner.renderer.material;
            bullet.gameObject.renderer.material = owner.renderer.material;
        }
    }

    public override int getTeamNumber()
    {
        return owner.GetComponent<Character>().teamNum;
    }
    
    public override void Fire(Vector2 dir)
    {
        if (coolDownTimer >= bullet.coolDown) {
            GameObject getSound=GameObject.Find("SoundManager");
            SoundManager SM=getSound.GetComponent<SoundManager>();
            SM.playFireBallLaunch();

            Magic clone = (Magic)Instantiate (bullet, owner.transform.position + (new Vector3 (dir.normalized.x * .9f, dir.normalized.y, 0.0f) * 0.65f), owner.transform.rotation);

            clone.gameObject.renderer.material = owner.renderer.material;
            clone.gameObject.renderer.material.color = owner.GetComponent<Character>().baseColor;

            clone.rigidbody.velocity = dir.normalized;
            clone.rigidbody.useGravity = true;
            clone.characterNumber=((Controller)owner.GetComponent("Controller")).getCharacter();
            coolDownTimer=0;
        }
    }
    
    // Update is called once per frame
    public override void Update ()
    {
        coolDownTimer += Time.deltaTime;
        //Fire (new Vector2 (0.0f, 1.0f));
    }
}
