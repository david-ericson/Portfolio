﻿using UnityEngine;
using System.Collections;

public class MarathonCamera : MonoBehaviour {


    public float movementSpeed;
    public Vector3 endPos;
    public GameObject background;
    Vector3 backStart;
    Vector3 backEnd;
    Vector3 startPos;
    Vector3 diff;
    Vector3 ostartPos;
    Vector3 oendPos;
    Vector3 backDiff;
    public bool setup = false;
    float curLerp = 0;
    bool moving = false;
	// Use this for initialization
	void Start () {
        startPos = transform.position;
        diff = endPos - startPos;

        backStart = background.transform.position;
        backEnd = (new Vector3(backStart.x + (endPos.x-startPos.x)*0.55f, backStart.y, backStart.z));
        backDiff = backEnd - backStart;
        ostartPos = startPos;
        oendPos = endPos;
        setup = true;
	}
	
    public void resetCam()
    {
        transform.position = ostartPos;
        startPos = ostartPos;
        endPos = oendPos;
        diff = endPos - startPos;
        curLerp = 0;

    }

    public void StartMoving()
    {
        moving = true;
    }

	// Update is called once per frame
	void Update () {
        if (moving)
        {
            curLerp += movementSpeed * Time.deltaTime;
            transform.position = startPos + (curLerp * diff);
            //background.transform.position = backStart + (curLerp * backDiff);
            if (curLerp > 1)
            {
                Vector3 tmp = endPos;
                endPos = startPos;
                startPos = tmp;
                diff = endPos - startPos;
                curLerp = 0;

                Vector3 tmpb = backEnd;
                backEnd = backStart;
                backStart = tmpb;
                backDiff = backEnd - backStart;
            }
        }
	}
}