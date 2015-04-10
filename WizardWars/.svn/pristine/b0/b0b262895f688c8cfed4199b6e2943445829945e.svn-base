using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class MovingPlatform : MonoBehaviour {

    public float maxDisplacement;
    public float moveSpeed;
    public float rotationSpeed;
    public float maxRotationAngle;
    public float startingAngle;
    public Vector3 moveDirection;
    private Vector3 originalPosition;
    private float angle;

    private List<Collider> characters = new List<Collider>();
	// Use this for initialization
	void Start () 
    {
        originalPosition = transform.position;
        angle = startingAngle;

	}
	
	// Update is called once per frame
	void Update () 
    {
        Vector3 newPosition = transform.position;

        if (((newPosition + moveDirection.normalized * moveSpeed) - originalPosition).magnitude >= maxDisplacement)
        {
            moveDirection = -moveDirection;
        }

        if (Mathf.Abs(angle) >= maxRotationAngle)
        {
            rotationSpeed = -rotationSpeed;
        }

        newPosition += moveDirection.normalized * moveSpeed * Time.deltaTime;
        angle += rotationSpeed * Time.deltaTime;

        transform.position = newPosition;
        transform.rotation = Quaternion.AngleAxis(angle, new Vector3(0,0,1));



        for(int i = 0; i < characters.Count; i++)
        {
            newPosition = characters[i].transform.position;
            
            newPosition += moveDirection.normalized * moveSpeed * Time.deltaTime;
            
            characters[i].transform.position = newPosition;

        }
	}

    void OnTriggerEnter(Collider col)
    {
        if (col.name.Contains("player"))
        {
            characters.Add(col);
        }
    }

    void OnTriggerExit(Collider col)
    {
        if (col.name.Contains("player"))
        {
            characters.Remove(col);
        }
    }
}
