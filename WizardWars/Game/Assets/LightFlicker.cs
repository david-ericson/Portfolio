using UnityEngine;
using System.Collections;

public class LightFlicker : MonoBehaviour {

    private bool goingUp = false;
	
    public float max = 1.5f;
    public float min = .5f;
    public float flickerSpeed = 0.75f;
	void Start () 
    {
        goingUp = Random.value > .5f;
        //startingInsensity = GetComponentInChildren<Light>().intensity;
        //dumb = Random.value * 3;
	}
	
	// Update is called once per frame
	void Update () 
    {
        //float offset = (Mathf.Sin(dumb)/3) + .25f;
        //
        //if (offset < max)
        //{
        //    offset = max;
        //}
        //GetComponentInChildren<Light>().intensity = startingInsensity + offset;
        //
        //dumb += offsetDelta * Time.deltaTime;

        if (goingUp)
        {
            GetComponentInChildren<Light>().intensity += (flickerSpeed + (Random.value / 10.0f)) * Time.deltaTime;
        }
        else
        {
            GetComponentInChildren<Light>().intensity -= (flickerSpeed + (Random.value / 10.0f)) * Time.deltaTime;
        }

        if (GetComponentInChildren<Light>().intensity >= max)
        {
            goingUp = false;
        }
        if (GetComponentInChildren<Light>().intensity <= min)
        {
            goingUp = true;
        }
	}
}
