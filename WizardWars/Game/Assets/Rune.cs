﻿using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Rune : MonoBehaviour {
	public  Projectile[] weapons;
    public Mesh[] swapObject;
    public float spawnTime;
    private float currTime;
	private Vector3 start, end;
	private float beta, increment;
	private Projectile weapon;
    private float tempY;
    private float bobSpeed = 1;
    private bool fireBlastRotate;
	private bool rotated;

	// Use this for initialization
	void Start () {
		start = gameObject.transform.position;
		end = start + new Vector3(0, 2, 0);
		beta = 0;
		increment = .02f;
        currTime = spawnTime;
        int test = Random.Range(0, weapons.Length);
        this.gameObject.renderer.enabled = true;
        this.gameObject.collider.enabled = true;
		weapon = weapons[test];
		weapon.Start();
		this.gameObject.GetComponent<Light>().color = new Color(weapon.runeColor.r, weapon.runeColor.g, weapon.runeColor.b, .5f);
        this.gameObject.GetComponent<MeshFilter>().mesh = swapObject[test];
        this.gameObject.GetComponent<MeshCollider>().sharedMesh = swapObject [test];
		this.gameObject.renderer.material.color = new Color(7*weapon.runeColor.r/8,7*weapon.runeColor.g/8,7*weapon.runeColor.b/8, 1.0f);

        if (weapon.name == "FireballProjectile")
		{
			rotated=false;
			transform.localScale = new Vector3 (2.0f, 2.0f, 2.0f);
		}
		else if (weapon.name == "FireblastProjectile")
		{
			rotated=false;
			transform.localScale = new Vector3 (2.0f, 2.0f, 2.0f);
		}
		else if (weapon.name == "RicochetProjectile")
		{
			rotated=false;
			transform.localScale = new Vector3 (1.2f, 1.2f, 1.2f);
		}
		else if (weapon.name == "ZapProjectile")
		{
			rotated=false;
			transform.localScale = new Vector3 (0.5f, 0.5f, 0.5f);
		}
		else if (weapon.name == "Twofer")
		{
			rotated=true;
			transform.localScale=new Vector3(2.5f,2.5f, 2.5f);
			transform.Rotate(new Vector3(0,90,0));
		}
		else if(weapon.name=="WallBulletProjectile")
		{
			rotated=true;
			transform.localScale=new Vector3(1.4f,1.4f,1.4f);
			transform.Rotate(new Vector3(0,90,0));
		}
		else if(weapon.name=="SinCosProjectile")
		{
			rotated=true;
			transform.localScale=new Vector3(2.5f,2.5f,2.5f);
			transform.Rotate(new Vector3(0,90,0));
		}
		else if(weapon.name=="ThreeRoundProjectile")
		{
			rotated=true;
			transform.localScale=new Vector3(4.0f,4.0f,4.0f);
			transform.Rotate (new Vector3(0,90,0));
		}

        tempY = Random.value * 50;
		
	}
	
	// Update is called once per frame
	void Update () {
		if (!this.gameObject.renderer.enabled)
        {
            currTime -= Time.deltaTime;
            
        } else
        {
            Bob();
        }
        if (currTime <= 0)
        {
            Reset();
        }
        
	}

    void Bob()
    {
        if (!GameManager.isPaused)
        {
            Vector3 thePosition = start;
            
            float diff = (Mathf.Sin(tempY))/4;
            
            thePosition.y += diff;

            tempY += bobSpeed * Time.deltaTime;

            transform.position = thePosition;
        }
    }
	
	void OnTriggerEnter(Collider col)
	{
		Character wizard = col.gameObject.GetComponent<Character>();
		if(wizard != null && this.gameObject.renderer.enabled)
		{
            this.gameObject.renderer.enabled = false;
            this.gameObject.collider.enabled = false;
            this.gameObject.GetComponent<Light>().color = new Color(0,0,0,0);
			weapon.owner = wizard.gameObject;
			wizard.gameObject.GetComponent<CharacterProjectile>().p = (Projectile)Instantiate(weapon);
            wizard.transform.Find("HaloPrefab").renderer.material.color = new Color(weapon.runeColor.r, weapon.runeColor.g, weapon.runeColor.b);
            wizard.transform.Find("HaloPrefab2").renderer.material.color = new Color(weapon.runeColor.r, weapon.runeColor.g, weapon.runeColor.b);
            wizard.runeRepresentation.rune=this.gameObject.GetComponent<MeshFilter>().mesh;
           
            //tempY = Random.value * 50;
		    transform.position = start;
			//weapon.Start();
		}
	}
	
	int findRune(Dictionary<Projectile, float> spawnChance, float number)
	{
		int index = -1;
		float maxVal = 0;
		for(int i=0; i<weapons.Length && index == -1; i++)
		{
			maxVal += spawnChance[weapons[i]];
			print (maxVal);
			if(maxVal > number)
			{
				index = i;
			}
		}
		//print (weapons[index].ToString());
		return index;
	}

    void Reset()
    {
    	Rune[] runes = GameObject.FindObjectsOfType<Rune>();
    	Dictionary<Projectile, float> spawnChance = new Dictionary<Projectile, float>();
    	Dictionary<Projectile, int> runeCount = new Dictionary<Projectile, int>();
    	foreach(Projectile p in weapons)
    	{
    		runeCount.Add(p, 0);
    	}
    	foreach(Rune r in runes)
    	{
    		if(r.renderer.isVisible)
    		{
    			runeCount[r.weapon]++; 
    		}
    	}
    	float totalSpawnChance = 0;
    	for(int i=0; i<weapons.Length; i++)
    	{
    		if(!spawnChance.ContainsKey(weapons[i]))
    		{
    			spawnChance.Add(weapons[i], 0);
    		}
    		spawnChance[weapons[i]] = (float)(100/weapons.Length)/(Mathf.Pow (2, runeCount[weapons[i]]));
    		print(spawnChance[weapons[i]] + " weapon type: " + weapons[i].ToString());
    		totalSpawnChance+= spawnChance[weapons[i]];
    	}
    	//print (totalSpawnChance);
        currTime = spawnTime;
        float number = Random.Range(0.0f, totalSpawnChance);
        this.gameObject.renderer.enabled = true;
        this.gameObject.collider.enabled = true;
        int test = findRune(spawnChance, number);
        //print (number);
        weapon = weapons[test];
        weapon.Start();
        this.gameObject.GetComponent<Light>().color = new Color(weapon.runeColor.r, weapon.runeColor.g, weapon.runeColor.b, .5f);
        this.gameObject.GetComponent<MeshFilter>().mesh = swapObject[test];

        if (weapon.name == "FireballProjectile")
        {
			if(rotated)
			{
				transform.Rotate(new Vector3(0,-90,0));
				rotated=false;
			}
            transform.localScale = new Vector3(2.0f, 2.0f, 2.0f);
        }
        else if (weapon.name == "FireblastProjectile")
        {
			if(rotated)
			{
				transform.Rotate(new Vector3(0,-90,0));
				rotated=false;
			}
            transform.localScale = new Vector3(2.0f, 2.0f, 2.0f);
        }
        else if (weapon.name == "RicochetProjectile")
        {
			if(rotated)
			{
				transform.Rotate(new Vector3(0,-90,0));
				rotated=false;
			}
            transform.localScale = new Vector3(1.2f, 1.2f, 1.2f);
        }
        else if (weapon.name == "ZapProjectile")
        {
			if(rotated)
			{
				transform.Rotate(new Vector3(0,-90,0));
				rotated=false;
			}
            transform.localScale=new Vector3(0.5f,0.5f,0.5f);
        }
		else if (weapon.name == "Twofer")
		{
			if(!rotated)
			{
				transform.Rotate(new Vector3(0,90,0));
				rotated=true;
			}
			transform.localScale=new Vector3(2.5f,2.5f,2.5f);
		}
		else if(weapon.name=="WallBulletProjectile")
		{
			if(!rotated)
			{
				rotated=true;
				transform.Rotate(new Vector3(0,90,0));
			}
			transform.localScale=new Vector3(1.4f,1.4f,1.4f);
		}
		else if(weapon.name=="SinCosProjectile")
		{
			if(!rotated)
			{
				transform.Rotate(new Vector3(0,90,0));
				rotated=true;
			}
			transform.localScale=new Vector3(2.5f,2.5f,2.5f);
		}
		else if(weapon.name=="ThreeRoundProjectile")
		{
			if(!rotated)
			{
				transform.Rotate(new Vector3(0,90,0));
				rotated=true;
			}
			transform.localScale=new Vector3(4.0f,4.0f,4.0f);
		}	
		this.gameObject.renderer.material.color = new Color(7*weapon.runeColor.r/8,7*weapon.runeColor.g/8,7*weapon.runeColor.b/8, 1.0f);
        tempY = Random.value * 50;
    }
}
