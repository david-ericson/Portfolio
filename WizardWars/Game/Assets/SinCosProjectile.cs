﻿using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class SinCosProjectile : Projectile {
	 List<SinCosBullet> bullets;
	
	class SinCosBullet
	{
		public Magic sinBullet, cosBullet;
		public Vector3 startSin, startCos;
		public Vector2 normal;
		public Vector3 myDir;
		public bool sinTrailDisabled;
		public bool cosTrailDisabled;
		public float sinDist, cosOffset, sinOffset;
		public float cosDist;
		public SinCosBullet()
		{
			sinTrailDisabled = false;
			cosTrailDisabled = false;
			sinDist = 0;
			cosDist = 0;
		}
		public void Update()
		{
			if(sinBullet)
			{
				sinDist += sinBullet.Speed * Time.deltaTime;
				float sinmag =0.1f * (Mathf.Sin (4.0f*sinDist)+1.1f);
				Vector2 temp = normal * sinmag;
				Vector3 newPos = startSin + (myDir*sinDist + new Vector3(temp.x, temp.y, 0));
				if((newPos - sinBullet.transform.position).magnitude > 10)
				{
					Vector2 tempSin = normal*sinOffset;
					Vector3 whereAt = Camera.main.WorldToViewportPoint((sinDist*myDir)+startSin);
					float xVal = (Mathf.Abs(newPos.x - sinBullet.transform.position.x) > 2)?(whereAt.x > .5f?.01f:.99f):whereAt.x;
					float yVal = (Mathf.Abs(newPos.y - sinBullet.transform.position.y) > 2)?(whereAt.y > .5f?.01f:.99f):whereAt.y;
					startSin = Camera.main.ViewportToWorldPoint(new Vector3(xVal, yVal, whereAt.z));
					//startSin += new Vector3(tempSin.x, tempSin.y, 0);
					//Vector3 tmp = Camera.main.WorldToViewportPoint(startSin + (myDir * sinDist));
					//startSin = (Camera.main.ViewportToWorldPoint(new Vector3(tmp.x > 0.5? 0.01f : 0.99f, tmp.y, tmp.z)));
					//startSin += new Vector3(0, sinBullet.renderer.bounds.size.y/2+.05f, 0);
		            sinDist = 0;
				}
				else
				{
					sinBullet.transform.position = newPos;
				}
		
				
				//new Vector3((myDir*xVal).x+normal.x*sinVal, (float)((myDir*xVal).y+normal.y*sinVal), (myDir*xVal).z);
			}
			if(cosBullet)
			{
				cosDist += cosBullet.Speed * Time.deltaTime;
				float cosMag = -.1f*(Mathf.Sin(3.0f*cosDist)-1.1f);
				Vector2 temp = normal * cosMag;
				Vector3 newPos = startCos + (myDir*cosDist + new Vector3(temp.x, temp.y, 0));
				if((newPos - cosBullet.transform.position).magnitude > 10)
				{
					Vector2 tempCos = normal*cosOffset;
					Vector3 whereAt = Camera.main.WorldToViewportPoint(cosDist*myDir+startCos);
					float xVal = (Mathf.Abs(newPos.x - cosBullet.transform.position.x) > 2)?(whereAt.x > .5f?.01f:.99f):whereAt.x;
					float yVal = (Mathf.Abs(newPos.y - cosBullet.transform.position.y) > 2)?(whereAt.y > .5f?.01f:.99f):whereAt.y;
					startCos = Camera.main.ViewportToWorldPoint(new Vector3(xVal, yVal, whereAt.z));
					//startCos += new Vector3(tempCos.x, tempCos.y, 0);
					//Vector3 tmp = Camera.main.WorldToViewportPoint(startCos + (myDir * cosDist));
					//startCos = (Camera.main.ViewportToWorldPoint(new Vector3(tmp.x > 0.5? 0.01f : 0.99f, tmp.y, tmp.z)));
					//startCos += new Vector3(0, - sinBullet.renderer.bounds.size.y/2-.05f, 0);
					cosDist = 0;
				}
				else
				{
					cosBullet.transform.position = newPos;
				}
				/*
			dist += cosBullet.Speed * Time.deltaTime;
			float sinmag =0.25f * (Mathf.Cos (3.0f*dist)+1.1f);
			Vector2 temp = normal * sinmag;
			cosBullet.transform.position = startSin + (myDir*dist + new Vector3(temp.x, temp.y, 0));
			*/
			}
		}
	};
	// Use this for initialization
	public override void Start () {
		coolDownTimer = bullet.coolDown;
		if(owner != null)
		{
			Material m = owner.renderer.material;
			bullet.gameObject.renderer.material = owner.renderer.material;
		}
		bullets = new List<SinCosBullet>();
	}
	
	public override int getTeamNumber()
	{
		return owner.GetComponent<Character>().teamNum;
	}
	
	// Update is called once per frame
	public override void Update ()
	{
		for(int i=0; i<bullets.Count; i++)
		{
			bullets[i].Update();
		}
		coolDownTimer += Time.deltaTime;
		
		
	}
	
	public override void Fire(Vector2 dir)
	{
		if (coolDownTimer >= bullet.coolDown) 
		{
			SinCosBullet scBullet = new SinCosBullet();
			scBullet.sinBullet = (Magic)Instantiate (bullet, owner.transform.position + (new Vector3 (dir.normalized.x, dir.normalized.y, 0.0f)), owner.transform.rotation);
			scBullet.sinBullet.gameObject.renderer.material = owner.renderer.material;
			scBullet.sinBullet.gameObject.renderer.material.color = owner.GetComponent<Character>().baseColor;
			
			scBullet.sinBullet.rigidbody.velocity = dir.normalized;
			scBullet.sinBullet.characterNumber=((Controller)owner.GetComponent("Controller")).getCharacter();
			Vector3 sinPos = scBullet.sinBullet.transform.position;
			scBullet.cosBullet = (Magic)Instantiate (bullet, owner.transform.position + (new Vector3 (dir.normalized.x, dir.normalized.y, 0.0f)), owner.transform.rotation);
			scBullet.cosBullet.gameObject.renderer.material = owner.renderer.material;
			scBullet.cosBullet.gameObject.renderer.material.color = owner.GetComponent<Character>().baseColor;
			scBullet.cosBullet.rigidbody.velocity = dir.normalized;
			scBullet.cosBullet.characterNumber=((Controller)owner.GetComponent("Controller")).getCharacter();
			scBullet.cosOffset = -1.35f*scBullet.sinBullet.renderer.bounds.size.y;
			scBullet.sinOffset = 1.35f*scBullet.sinBullet.renderer.bounds.size.y;
			
			coolDownTimer=0;
			
			scBullet.normal = new Vector2(-dir.y, dir.x);
			scBullet.normal = scBullet.normal.normalized;
			
			scBullet.myDir = new Vector3(dir.x, dir.y, sinPos.z);
			scBullet.myDir = scBullet.myDir.normalized;
			Vector2 tempCos = scBullet.normal*scBullet.cosOffset;
			Vector2 tempSin = scBullet.normal*scBullet.sinOffset;
			scBullet.cosBullet.transform.position = (sinPos+new Vector3(tempCos.x, tempCos.y, 0));
			scBullet.sinBullet.transform.position = sinPos+new Vector3(tempSin.x, tempSin.y, 0);
			scBullet.startSin = scBullet.sinBullet.transform.position;
			scBullet.startCos = scBullet.cosBullet.transform.position;
			//Destroy(scBullet.sinBullet);
			bullets.Add(scBullet);

            scBullet.sinBullet.GetComponentInChildren<TrailRenderer>().material.SetColor("_TintColor", owner.GetComponent<Character>().baseColor);
            scBullet.sinBullet.GetComponentInChildren<ParticleSystem>().startColor = owner.renderer.material.color;
            scBullet.cosBullet.GetComponentInChildren<TrailRenderer>().material.SetColor("_TintColor", owner.GetComponent<Character>().baseColor);
            scBullet.cosBullet.GetComponentInChildren<ParticleSystem>().startColor = owner.renderer.material.color;
		}
	}
}