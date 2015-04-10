using UnityEngine;
using System.Collections;

public class LevelWaller : MonoBehaviour {

    public GameObject cube;
	// Use this for initialization
	void Start () {
	    //Setup the walls.
        float z = Camera.main.WorldToViewportPoint(new Vector3(0, 0, 0)).z;
        float width = Mathf.Abs(Camera.main.ViewportToWorldPoint(new Vector3(0, 0, z)).x - Camera.main.ViewportToWorldPoint(new Vector3(1, 0, z)).x);
        float height = Mathf.Abs(Camera.main.ViewportToWorldPoint(new Vector3(0, 0, z)).y - Camera.main.ViewportToWorldPoint(new Vector3(0, 1, z)).y);

        Vector3 leftWall = Camera.main.ViewportToWorldPoint(new Vector3(0.0f, 0.5f, z));
        leftWall.z = 0;
        leftWall.x -= 0.25f;
        Vector3 rightWall = Camera.main.ViewportToWorldPoint(new Vector3(1.0f, 0.5f, z));
        rightWall.x += 0.25f;
        rightWall.z = 0;
        Vector3 topWall = Camera.main.ViewportToWorldPoint(new Vector3(0.5f, 1, z));
        topWall.y += 0.25f;
        topWall.z = 0;

        GameObject left = (GameObject)Instantiate(cube, leftWall, Quaternion.identity);
        left.transform.localScale = new Vector3(0.5f, height + 2, 1.0f);

        GameObject right = (GameObject)Instantiate(cube, rightWall, Quaternion.identity);
        right.transform.localScale = new Vector3(0.5f, height + 2, 1.0f);
        
        GameObject top = (GameObject)Instantiate(cube, topWall, Quaternion.identity);
        top.transform.localScale = new Vector3(width + 2, 0.5f, 1.0f);
	}
	
	// Update is called once per frame
	void Update () {
	    //Do nothing.
	}
}
