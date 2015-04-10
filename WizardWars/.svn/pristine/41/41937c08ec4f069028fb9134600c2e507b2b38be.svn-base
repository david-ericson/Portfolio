using UnityEngine;
using System.Collections;

public class Controller : MonoBehaviour
{
    
    public float speed = 0.5f;
    public float maxSpeed = 10.0f;
    float distToGround;
    public int characterNumber = 0;
    public float jumpPower = 15;
    public float wallJump = 0;
    public bool isWallJumping = false;
	public float wallJumpMod = 0.5f;
    float dropTimer;
    float dropTime = 0.1f;
    bool isJumping = false;
    string hmove;
    string vmove;
    string haim;
    string vaim;
    string pause;

	string aButton, bButton, xButton, utilTrigger;
    bool lastPause = false;
    string firetrigger;
    string jumpbutton;
    float hAimMod = 1.0f;
    float vAimMod = 1.0f;
    bool lastX;

    bool lastABut;

    bool inSettings = false;
    bool lastSelect = false;

    float terminalVelocity = 30.0f;

    public GameObject aiming;
    public GameSettings gs;

    float leftTimer = 0;
    float rightTimer = 0;
    float upTimer = 0;
    float downTimer = 0;

    float normalTimer = 0.25f;
    float fastTimer = 0.05f;

    void zeroAllTimers()
    {
        leftTimer = 0;
        rightTimer = 0;
        upTimer = 0;
        downTimer = 0;
    }
    
    GameObject activeAiming;

    // Use this for initialization
    void Start()
    {
        gs = (GameSettings)GameObject.FindObjectOfType<GameSettings>();
        distToGround = collider.bounds.extents.y;
        setupController();
        activeAiming = (GameObject)Instantiate (aiming, new Vector3(-1000, -1000, -1000), transform.rotation);
        GameObject.DontDestroyOnLoad(activeAiming);
    }
    
    void setupController()
    {
        int controllerNumber = characterNumber +1;
        hmove = "L_XAxis_" + (controllerNumber);
        vmove = "L_YAxis_" + (controllerNumber);
        
        haim = "R_XAxis_" + controllerNumber;
        vaim = "R_YAxis_" + controllerNumber;
        hAimMod = 1.0f;
        firetrigger = "TriggersR_" + controllerNumber;
		utilTrigger = "TriggersL_" + controllerNumber;
        jumpbutton = "LB_" + controllerNumber;
        vAimMod = 1.0f;
        pause = "Start_" + controllerNumber;

        aButton = "A_" + controllerNumber;
        bButton = "B_" + controllerNumber;
        xButton = "X_" + controllerNumber;
    }

    public Vector2 getMoveStick()
    {
        return new Vector2 (Input.GetAxis (hmove), Input.GetAxis (vmove));
        }
    
    public Vector2 getAimStick()
    {
        return new Vector2 (Input.GetAxis (haim), Input.GetAxis (vaim));
    }
    public void setCharacter(int id)
    {
        characterNumber = id;
        setupController();
    }
    
    public int getCharacter()
    {
        return characterNumber;
    }

    bool IsGrounded(float grace)
    {
        return (Physics.Raycast(new Vector3(transform.position.x - collider.bounds.extents.x, transform.position.y, transform.position.z), -Vector3.up, distToGround + grace) || 
            Physics.Raycast(new Vector3(transform.position.x + collider.bounds.extents.x, transform.position.y, transform.position.z), -Vector3.up, distToGround + grace) ||
            Physics.Raycast(new Vector3(transform.position.x, transform.position.y, transform.position.z), -Vector3.up, distToGround + grace));
    }
	bool IsOnWall(float grace)
	{
        return wallDir(grace) != 0;
    }

	int wallDir(float grace)
	{
        return wallDir(grace, 8);
    }

    int wallDir(float grace, int count)
    {
        float x = transform.position.x;
        float z = transform.position.z;
        float y = transform.position.y - distToGround + 0.1f;
        float inc = (2.0f * (distToGround - 0.1f)) / (float)count;
        RaycastHit rh;

        for (int i =0; i < count; i ++)
        {
            if (Physics.Raycast(new Vector3(x, y + i * inc, z), Vector3.left, out rh, distToGround + grace))
            {
                if (!(rh.collider.gameObject.name.Contains("Rune") || rh.collider.gameObject.name == "spickeTrap"))
                {
                    return 1;
                }
            }
        }

        for (int i =0; i < count; i ++)
        {
            if (Physics.Raycast(new Vector3(x, y + i * inc, z), Vector3.right, out rh, distToGround + grace))
            {
                if (!(rh.collider.gameObject.name.Contains("Rune") || rh.collider.gameObject.name == "spickeTrap"))
                {
                    return -1;
                }
            }
        }

        return 0;

    }

    bool AllXAreEqual(Collision col)
    {
        //bool foundDisparity = false;
        float x = col.contacts [0].point.x;
        for (int i =1; i < col.contacts.Length; i ++)
        {
            if (Mathf.Abs(col.contacts [i].point.x - x) > float.Epsilon)
            {
                //Debug.Log("False");
                return false;
            }
        }
        //Debug.Log("True");
        return true;
    }

    void OnCollisionEnter(Collision col)
    {
        if (col.gameObject.name.Contains("Rune"))
        {
            return;
        }
        Vector3 relativePosition = transform.InverseTransformPoint(col.contacts [0].point);
        //Debug.Log (col.contacts.Length);
        //Debug.Log (col.contacts[0].point + " , " + col.contacts[1].point);
        //Actual position is probably... the greatest value in relativePosition... Maybe.

        if (IsOnWall(0.01f) && !IsGrounded(0.1f))
        {
            //The wall is to the right or the left and not above or below. Do a bounce thing to wall jump.
			//wallJump = wallDir (0.01f);
            //isWallJumping = true;
            isJumping = true;
        } 
		else
        {
            wallJump = 0;
            isWallJumping = false;
            isJumping = false;
        }
    }

    bool fired = false;
    float lastAng = 90.0f;
    //Update is called once per frame
    void Update()
    {
        //Menu stuff.

        if (inSettings)
        {
            float hor = Input.GetAxis(hmove);
            float vert = Input.GetAxis(vmove);

            if (hor <= 0.8f && hor >= -0.8f && vert <= 0.8f && vert >= -0.8f)
            {
                zeroAllTimers();
            } else
            {
                if (hor > 0.8f && rightTimer <= 0)
                {
                    rightTimer = rightTimer == -10 ? fastTimer : normalTimer;
                    gs.MenuSelectionRight();
                }
                if (rightTimer > 0)
                {
                    rightTimer -= Time.deltaTime;
                    if (rightTimer < 0)
                    {
                        rightTimer = -10;
                    }
                }
                if (hor < -0.8f && leftTimer <= 0)
                {
                    leftTimer = leftTimer == -10 ? fastTimer : normalTimer;
                    gs.MenuSelectionLeft();
                }
                if (leftTimer > 0)
                {
                    leftTimer -= Time.deltaTime;
                    if (leftTimer < 0)
                    {
                        leftTimer = -10;
                    }
                }
                if (vert > 0.8f && upTimer <= 0)
                {
                    upTimer = upTimer == -10 ? fastTimer : normalTimer;
                    gs.MenuSelectionUp();
                }
                
                if (upTimer > 0)
                {
                    upTimer -= Time.deltaTime;
                    if (upTimer < 0)
                    {
                        upTimer = -10;
                    }
                }
                if (vert < -0.8f && downTimer <= 0)
                {
                    downTimer = downTimer == -10 ? fastTimer : normalTimer;
                    gs.MenuSelectionDown();
                }
                
                if (downTimer > 0)
                {
                    downTimer -= Time.deltaTime;
                    if (downTimer < 0)
                    {
                        downTimer = -10;
                    }
                }
            }

            if (Input.GetButton(aButton) && !lastABut)
            {
                lastABut = true;
                gs.aPressed();
                inSettings = gs.show;
            }
            if (!Input.GetButton(aButton))
            {
                lastABut = false;
            }

            if (Input.GetButton(pause) && !lastPause)
            {
                lastPause = true;
                gs.toggleVisible();
                inSettings = false;
            }
            if (!Input.GetButton(pause))
            {
                lastPause = false;
            }

        } else if (gs == null || !gs.show)
        {
            if (GameManager.gameIsStarted)
            {
                if (GameManager.getPlayer(characterNumber))
                {
                    activeAiming.renderer.material = GameManager.getPlayer(characterNumber).GetComponent<MeshRenderer>().material;
                }

                checkInGameMenu();
                
                if (!GameManager.gameSet.show && !GameManager.isPaused)
                {
                    Utility u = (Utility)(GetComponentInParent<Character>().util);
                    float hor = Input.GetAxis(hmove);
                    //Debug.Log ("Wall left: " + IsWallLeft() + " , " + "Wall right: " + IsWallRight() + " , " + "jumping : " + isJumping);

                    float ang = hor > 0 ? 90 : hor == 0 ? lastAng : 270;
                    transform.rotation = Quaternion.Euler(new Vector3(0, ang, 0));
                    lastAng = ang;

                    if ((!(u is Dash) || u.countdown <= 0) && !isWallJumping)
                    {
                        float wd = wallDir(0.01f);
                        if (((hor > 0 && wd < 0) || (hor < 0 && wd > 0)))
                        {
                            hor = 0;
                        }
                        rigidbody.velocity = (new Vector3(maxSpeed * hor, rigidbody.velocity.y, 0));

                        /*
                    if (Mathf.Abs(hor) > 0.2f && wallDir(0.01f) != 0 && Mathf.Sign(wallDir(0.01f)) != Mathf.Sign(hor))
                    {
                        dropTimer = dropTime;
                    }
                    */
                    }
                    /*
    		if (Mathf.Abs(rigidbody.velocity.x) > maxSpeed) {
    			rigidbody.velocity = new Vector3(maxSpeed * Mathf.Sign (rigidbody.velocity.x), rigidbody.velocity.y, 0);
    				}
            */
                    transform.position = new Vector3(transform.position.x, transform.position.y, 0);

                    Vector2 aim = new Vector2(Input.GetAxis(haim) * hAimMod, Input.GetAxis(vaim) * vAimMod);
                    float trigger = Input.GetAxis(firetrigger);
                    if (!GetComponent<Character>().isDead)
                    {
                        if ((aim.sqrMagnitude > 0.2f || GetComponent<CharacterProjectile>().p is Fireblast) && !fired && trigger > 0.5f)
                        {
                            fired = true;
                            //Debug.Log("Player Fire " + characterNumber);
                            GetComponentInParent<CharacterProjectile>().p.bullet.GetComponent<Magic>().owningChar = gameObject;
                            GetComponent<CharacterProjectile>().p.Fire(aim);
                        }
                    }
                    if (dropTimer > 0)
                    {
                        dropTimer -= Time.deltaTime;
                    }

                    //if (trigger >= -0.5) {
                    fired = false;
                    // }

                    int tcount = 0;
                    //Utility calls.
                    if (Input.GetAxis (utilTrigger) >= 0.5f)
                    {
                
                        if (u.countdown <= 0)
                        {
                            //Debug.Log ("Trigger thing" + tcount++);
                    
                            //Debug.Log ("Activate thing.");
                            u.Activate();
                        }
                    }

                    if (aim.sqrMagnitude > 0.2f)
                    {
                        activeAiming.transform.position = transform.position + new Vector3(aim.normalized.x, aim.normalized.y, 0) * 0.7f;
                    
                    } else
                    {
                        activeAiming.transform.position = new Vector3(-1000, -1000, -1000);
                    }

                    if ((Input.GetAxis(vmove) < -0.5f))
                    {
                        dropTimer = 0;
                        rigidbody.velocity += Physics.gravity * Time.deltaTime * 3;
                    }

                    if ((!isJumping) && IsGrounded(0.01f) && (Input.GetAxis(vmove) > 0.5))
                    {
                        //Debug.Log(characterNumber);
                        isJumping = true;
                        rigidbody.velocity = new Vector3(rigidbody.velocity.x, jumpPower, 0.0f);
                    }

                    /*
                if (dropTimer > 0 && IsOnWall(0.01f))
                {
                    rigidbody.velocity = new Vector3(rigidbody.velocity.x, 0, rigidbody.velocity.z);
                    rigidbody.useGravity = false;
    			
                } else
                {
                    rigidbody.useGravity = true;
                }
                */
                    /*
                if ((dropTimer > 0 && IsOnWall(0.01f) && !IsGrounded(0.01f) && (Input.GetAxis(vmove) > 0.7) && Mathf.Abs(Input.GetAxis(hmove)) < Input.GetAxis(vmove)))
                {
                    int wallJumpDirection = wallDir(0.01f);
    			
                    rigidbody.velocity = new Vector3(jumpPower * wallJumpDirection * wallJumpMod, jumpPower, 0);
    			
                    if (wallJumpDirection != 0)
                    {
                        isWallJumping = true;
                        transform.position += new Vector3(wallJumpDirection / 3, 0, 0);
                    }
                }
                */
                    if (rigidbody.velocity.y > jumpPower)
                    {
                        rigidbody.velocity = new Vector3(rigidbody.velocity.x, jumpPower, rigidbody.velocity.z);
                    }

                    if (rigidbody.velocity.y < -terminalVelocity)
                    {
                        rigidbody.velocity = new Vector3(rigidbody.velocity.x, -terminalVelocity, rigidbody.velocity.z);
                    }

                    bool grounded = IsGrounded(0.01f);
                    if (!isJumping && !grounded)
                    {
                        isJumping = true;
                    }
                    if (grounded)
                    {
                        isJumping = false;      
                    }
                    //isJumping = true;
                }

                ///Pausing.
                if (Input.GetButton(pause))
                {
                    //GameManager.Pause(characterNumber);
                    if (!lastPause)
                    {
                        GameManager.Pause(characterNumber);

                        if (GameObject.FindObjectOfType<MenuSystem>())
                        {
                            if (!gs.show || inSettings)
                            {
                                gs.toggleVisible();
                                inSettings = gs.show;
                            }
                        }
                    }

                    lastPause = true;
                } else
                {
                    lastPause = false;
                }

                //Door code.
                if (Input.GetButton(xButton) && !lastX)
                {
                    GetComponent<Character>().CheckForDoor();
                    lastX = true;
                }
                if (!Input.GetButton(xButton))
                {
                    lastX = false;
                }
            }
        }
    }

    void checkInGameMenu()
    {
        if (GameManager.gameSet.show)
        {
            float hor = Input.GetAxis(hmove);
            float vert = Input.GetAxis(vmove);

            if (hor <= 0.8f && hor >= -0.8f && vert <= 0.8f && vert >= -0.8f)
            {
                zeroAllTimers();
            }
            else
            {

                if (vert > 0.8f && upTimer <= 0)
                {
                    upTimer = upTimer == -10 ? fastTimer : normalTimer;
                    GameManager.gameSet.MenuSelectionUp();
                }

                if (upTimer > 0)
                {
                    upTimer -= Time.deltaTime;
                    if (upTimer < 0)
                    {
                        upTimer = -10;
                    }
                }
                if (vert < -0.8f && downTimer <= 0)
                {
                    downTimer = downTimer == -10 ? fastTimer : normalTimer;
                    GameManager.gameSet.MenuSelectionDown();
                }

                if (downTimer > 0)
                {
                    downTimer -= Time.deltaTime;
                    if (downTimer < 0)
                    {
                        downTimer = -10;
                    }
                }
            }

            if (Input.GetButton(aButton) && !lastABut)
            {
                lastABut = true;
                GameManager.gameSet.aPressed();
            }
            if (!Input.GetButton(aButton))
            {
                lastABut = false;
            }
        }
    }
}
