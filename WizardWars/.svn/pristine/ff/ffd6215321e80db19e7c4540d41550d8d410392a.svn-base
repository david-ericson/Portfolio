using UnityEngine;
using System.Collections;

public class Fireblast : Projectile {

	float screenWidth;
	float screenHeight;

	// Use this for initialization
	public override void Start () {
		float z = Camera.main.WorldToViewportPoint (new Vector3(0, 0, 0)).z;
		screenWidth =Mathf.Abs(Camera.main.ViewportToWorldPoint(new Vector3(0, 0, z)).x - (Camera.main.ViewportToWorldPoint(new Vector3(1, 0, z)).x));
		screenHeight =Mathf.Abs(Camera.main.ViewportToWorldPoint(new Vector3(0, 0, z)).y - (Camera.main.ViewportToWorldPoint(new Vector3(0, 1, z)).y));

		coolDownTimer = bullet.coolDown;
		runeColor = new Color(1.0f, .5f, 0);
		if(owner != null)
		{
			Material m = owner.renderer.material;
			bullet.gameObject.renderer.material = owner.renderer.material;
		}
	}

    public override int getTeamNumber()
    {
        return owner.GetComponent<Character>().teamNum;
    }
	
	// Update is called once per frame
	public override void Update ()
	{
		coolDownTimer += Time.deltaTime;
		//Fire (new Vector2 (0.0f, 1.0f));
	}
	
	public override void Fire(Vector2 dir)
	{
		if (coolDownTimer >= bullet.coolDown) {
            GameObject getSound=GameObject.Find("SoundManager");
            SoundManager SM=getSound.GetComponent<SoundManager>();
            SM.playFireBallExplosion();

			Vector2 start = new Vector2(1, 0);
            int count = 16;
			for(int i=0; i<count; i++)
			{
				Vector3 myDir = new Vector3(start.x, start.y, 0)*0.8f;
				myDir = Quaternion.Euler(0, 0, i*(360/count))*myDir;
				Magic clone = (Magic)Instantiate (bullet, owner.transform.position + myDir, owner.transform.rotation);

                if (i == 0)
                {
                    ParticleSystem g = (ParticleSystem)Instantiate(clone.onCollisionEffect, owner.transform.position, Quaternion.identity);
					ParticleSystem f=(ParticleSystem)Instantiate (clone.onCollisionEffect, new Vector3(owner.transform.position.x+screenWidth, owner.transform.position.y, owner.transform.position.z), Quaternion.identity);
					ParticleSystem d=(ParticleSystem)Instantiate (clone.onCollisionEffect, new Vector3(owner.transform.position.x-screenWidth, owner.transform.position.y, owner.transform.position.z), Quaternion.identity);
					ParticleSystem s=(ParticleSystem)Instantiate (clone.onCollisionEffect, new Vector3(owner.transform.position.x, owner.transform.position.y+screenHeight, owner.transform.position.z), Quaternion.identity);
					ParticleSystem a=(ParticleSystem)Instantiate (clone.onCollisionEffect, new Vector3(owner.transform.position.x, owner.transform.position.y-screenHeight, owner.transform.position.z), Quaternion.identity);
					
					Destroy(f.gameObject, clone.onCollisionEffect.duration);
					Destroy(d.gameObject, clone.onCollisionEffect.duration);
					Destroy(s.gameObject, clone.onCollisionEffect.duration);
					Destroy(a.gameObject, clone.onCollisionEffect.duration);
                    Destroy(g.gameObject, clone.onCollisionEffect.duration);
                }

				clone.gameObject.renderer.material = owner.renderer.material;
                clone.gameObject.renderer.material.color = owner.GetComponent<Character>().baseColor;

				clone.rigidbody.velocity = new Vector2(myDir.x, myDir.y).normalized;
				clone.characterNumber=((Controller)owner.GetComponent("Controller")).getCharacter();
				coolDownTimer=0;
			}
		}
	}
}
