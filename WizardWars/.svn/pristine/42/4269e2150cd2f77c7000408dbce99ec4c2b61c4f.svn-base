using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class GameManager : MonoBehaviour {
	
    public static float startingTime;

	private bool alreadyAtMenu;
	public float currentTime;
	private GUIStyle timerStyle, counterStyle, winStyle;
	private Character[] players;
	public GameObject[] spawnPoints;
    public Material[] materials;
    public static int gameType;
	private static GameManager me;
    public static int playerWhoPaused = -1;
    public static bool isPaused = false;
    public GameObject juggernautLight;
    public static bool isLoaded = true;
    private float trackTime;
    public static bool gameIsStarted = true;
    public static int maxScore;
    public int currentMaxScore;
    public GameObject counterText;
    public GameObject counterTextOrig;

    public MenuSettings gameSetPrefab;
    public static MenuSettings gameSet;

    private float fadeLerp = 1.0f;
    private float fadeSpeed = 1.0f;
    private bool transitionOver = false;

    private float beginTimerCountdown = 3.2f;
	// Use this for initialization
	void Start () {
		alreadyAtMenu = false;
		me = this;
        trackTime = 0;
		currentTime = startingTime;
		timerStyle = new GUIStyle();
		counterStyle = new GUIStyle();
		winStyle = new GUIStyle();
		timerStyle.fontSize = 25;
		counterStyle.fontSize = 45;
		winStyle.fontSize = 35;
		timerStyle.normal.textColor = Color.white;
		counterStyle.normal.textColor = Color.red;
		winStyle.normal.textColor = Color.white;
        maxScore = 0;
        counterTextOrig = counterText;
		
		GameObject.DontDestroyOnLoad(this.gameObject);


        gameSet = (MenuSettings)Instantiate(gameSetPrefab);
        GameObject.DontDestroyOnLoad(gameSet.gameObject);
        gameSet.gameManager = me;
	}

	
	public static void randomizeSpawn(Character c)
	{
		for(int i=0; i<me.players.Length; i++)
		{
			Character player = me.players[i].GetComponent<Character>();
			if(player == c)
			{
				Vector3 spawn = me.spawnPoints[Random.Range(0, me.spawnPoints.Length)].transform.position;
				Vector3 vpLoc = Camera.main.WorldToViewportPoint(spawn);
				while(vpLoc.x < 0 || vpLoc.x > 1 || vpLoc.y < 0 || vpLoc.y > 1)
				{
					spawn = me.spawnPoints[Random.Range(0, me.spawnPoints.Length)].transform.position;
					vpLoc = Camera.main.WorldToViewportPoint(spawn);
				}
				player.setSpawn(spawn);
                player.gameType= gameType;
                if(gameType==1)
                {
                    player.gameType=i;
                }
			}
		}
	}
	
	public static void setGamemode(int gamemode)
	{
		GameManager.gameType = gamemode;
	}

    public static void Pause(int characterNumber)
    {
	    if(GameObject.FindObjectOfType<MenuSystem>() == null)
	    {
	        if (playerWhoPaused != characterNumber)
	        {
	            if (!isPaused)
	            {
	                print("pause");
	                Time.timeScale = 0;
	                playerWhoPaused = characterNumber;
	                isPaused = true;
                    gameSet.show = true;
	            }
	        } 
	        else
	        {
	            if(isPaused)
	            {
	                print("unpause");
	                Time.timeScale = 1;
	                playerWhoPaused = -1;
	                isPaused = false;
                    gameSet.show = false;
	            }
	        }
        }
    }
    
    public static void setPlayers(Character[] players)
    {
    	me.players = players;
    }
    
    public static void hardReset()
    {
	    if(me)
	    {
    		me.Restart();
    	}
    }
    
    void OnLevelWasLoaded(int level)
    {

        currentMaxScore = 0;


        if (!GameObject.FindObjectOfType<MenuSystem>())
        {
            beginTimerCountdown = 3;
            transitionOver = false;
            fadeLerp = 1.0f;
            counterText = (GameObject)Instantiate(counterTextOrig, Camera.main.transform.position + (Camera.main.transform.forward * 10), Quaternion.identity);
            Destroy(counterText, beginTimerCountdown);
            gameIsStarted = false;
        } 
        else
        {
            fadeLerp = 0.0f;
            transitionOver = true;
            gameIsStarted = true;
        }

        GameManager.gameSet.show = false;

	    if(level != 0)
	    {
	    	Restart();
    	}
    }
	
	public static Character getPlayer(int playerId)
	{
		Character ret = null;
        if (me.players != null)
        {
            foreach (Character p in me.players)
            {
                if (p.getId() == playerId)
                {
                    ret = p;
                }
            }
        }
		return ret;
	}
	
	public static void UnpauseThisGodForsakenGame()
	{
		isPaused = false;
		Time.timeScale = 1;
		playerWhoPaused = -1;
	}
	
	// Update is called once per frame
	void Update ()
    {
        guiTexture.color = new Color(guiTexture.color.r, guiTexture.color.g, guiTexture.color.b, fadeLerp);
        if (!transitionOver)
        {
            fadeLerp -= fadeSpeed * Time.deltaTime;
            
            if (fadeLerp <= 0.0f)
            {
                transitionOver = true;
                guiTexture.color = new Color(guiTexture.color.r, guiTexture.color.g, guiTexture.color.b, 0.0f);
            }
        }

		if (GameObject.FindObjectOfType<MenuSystem> () && !alreadyAtMenu)
		{
			GameObject getSound=GameObject.Find("SoundManager");
			SoundManager SM=getSound.GetComponent<SoundManager>();
			MusicManager MM=SM.musicPlayer.GetComponent<MusicManager>();
			MM.playMenu();
			alreadyAtMenu=true;
		}

        if (beginTimerCountdown > 0 && !GameObject.FindObjectOfType<MenuSystem>())
        {
			if(alreadyAtMenu)
			{
				GameObject getSound=GameObject.Find("SoundManager");
				SoundManager SM=getSound.GetComponent<SoundManager>();
				MusicManager MM=SM.musicPlayer.GetComponent<MusicManager>();
				MM.playGame();
				alreadyAtMenu=false;
			}

            beginTimerCountdown -= Time.deltaTime;
            counterText.GetComponent<TextMesh>().text = "" + ((int)beginTimerCountdown + 1);
            gameIsStarted = false;
        }
        else
        {
            gameIsStarted = true;
            if(Camera.main.GetComponent<MarathonCamera>())
            {
                Camera.main.GetComponent<MarathonCamera>().StartMoving();
            }
    		if(currentTime == startingTime)
    		{

    			Character[] objects = GameObject.FindObjectsOfType<Character>();
    			players = new Character[objects.Length];
    			for(int i=0; i<objects.Length; i++)
    			{
                    if (true || players[i].renderer.isVisible)
                    {
    	                players[i] = objects[i];
    	                players[i].gameType=GameManager.gameType;
                    if(GameManager.gameType==2)
    	                {
    	                    players[i].teamNum=i%2;
    	                }
    	                else
    	                {
    	                	players[i].teamNum = i;
    	                }
    	                int check=(players[i].teamNum*4)+i;
                        if (check < me.materials.Length)
                        {
    	                 Material mCheck=me.materials[check];
    	                players[i].GetComponent<MeshRenderer>().material=new Material(mCheck);
    	                players[i].baseColor=players[i].GetComponent<MeshRenderer>().material.color;
                        }
                    }
    			}
    			GameObject[] spawns = GameObject.FindGameObjectsWithTag("SpawnPoint");
    			spawnPoints = new GameObject[spawns.Length];
    			spawnPoints = spawns;
    		}
            gameIsStarted = true;
            
            Character[] characters = GameObject.FindObjectsOfType<Character>();

            for(int i = 0; i < characters.Length; i++)
            {
                if(currentMaxScore < characters[i].getNumKills())
                {
                    currentMaxScore = characters[i].getNumKills();
                }
            }

            if (!GameObject.FindObjectOfType<MenuSystem>())
            {
                if(currentTime > 0 && currentMaxScore < maxScore)
        		{
        			currentTime -= Time.deltaTime;
        		}
                else
        		{
                    gameSet.show = true;

        			foreach (Character c in players) {
        				c.setInvincible(true);
        			}
        		}
            }

            trackTime += Time.deltaTime;
            if (gameType == 3 && !GameObject.FindObjectOfType<MenuSystem>())
            {
                for(int i=0; i<players.Length; i++)
                {
                    if(players[i].isJuggernaut)
                    {
                        if(trackTime>1)
                        {
                            players[i].alterNumKills(1);
                            trackTime=0;
                        }
                        juggernautLight.transform.position=players[i].transform.position;
                    }
                }
            }

    		if(Input.GetKeyDown(KeyCode.Space))
    		{
    			Restart();
    		}
        }
	}
	
	public static void SetupForGame()
	{
        me.currentTime = GameManager.startingTime;
		 
	}
	
	void Restart () 
	{
		currentTime = startingTime;
        int i = 0;
        MarathonCamera mc = Camera.main.GetComponent<MarathonCamera>();
        if(mc != null)
        {
            if (mc.setup)
            {
        	    ((MarathonCamera)(Camera.main.GetComponent<MarathonCamera>())).resetCam();
            }
        }
        spawnPoints = GameObject.FindGameObjectsWithTag("SpawnPoint");
        if(players != null)
        {
			foreach(Character c in players)
			{
	            //randomizeSpawn(c);
				c.setInvincible(false);
				c.Restart();
	            i++;
			}
			if(gameType==3 && !GameObject.FindObjectOfType<MenuSystem>())
			{
				players[Random.Range(0, players.Length)].isJuggernaut=true;
				juggernautLight=((GameObject)Instantiate(juggernautLight));
			}
		}
	}
	
	public int[] nabBestPlayer()
	{
		int highestKills = -1;
		List<int> indices = new List<int>();
        if(GameManager.gameType==1 || GameManager.gameType==3)
		{
			foreach(Character c in players)
			{
				if(c.getNumKills() > highestKills)
				{
					highestKills = c.getNumKills();
					indices.Clear();
					indices.Add(c.getId()+1);
				}
				else if(c.getNumKills() == highestKills)
				{
					indices.Add(c.getId()+1);
				}
			}
		}

        if (GameManager.gameType == 2)
		{
			int[] team=new int[4];
			int[] playersOnATeam=new int[4];
			for(int i=0; i<players.Length; i++)
			{
				if(players[i].teamNum==0)
				{
					team[0]+= players[i].getNumKills();
					playersOnATeam[0]++;
				}
				else if(players[i].teamNum==1)
				{
					team[1]+=players[i].getNumKills();
					playersOnATeam[1]++;
				}
				else if(players[i].teamNum==2)
				{
					team[2]+=players[i].getNumKills();
					playersOnATeam[2]++;
				}
				else if(players[i].teamNum==3)
				{
					team[3]+=players[i].getNumKills();
					playersOnATeam[3]++;
				}
			}

			for(int i=0; i<team.Length; i++)
			{
				if(team[i]>highestKills)
				{
					highestKills=team[i];
					indices.Clear ();
					indices.Add(i);
				}
				else if(team[i]==highestKills)
				{
					indices.Add(i);
				}
			}
		}
		return indices.ToArray();
	}
	
	void OnGUI()
	{
		MenuSystem menu = GameObject.FindObjectOfType<MenuSystem>();
		if(menu == null)
		{
		int minutes = (int)(currentTime/60);
		int seconds = (int)(currentTime - minutes*60);
		string secondsString = (seconds < 10)?"0"+seconds:""+seconds;
		
        GUI.Box(new Rect((3*Screen.width/8),10,100,20), "Time Remaining " + (float.IsInfinity(currentTime)? ": All of it" : (minutes+":"+secondsString)), timerStyle);
		int width = 80;
		int height = 40;

        int guiCounter = 0;

        if (GameManager.gameType == 2)
        {
            int[] team=new int[4];
            int[] playersOnATeam=new int[4];
            for(int i=0; i<players.Length; i++)
            {
                if(players[i].teamNum==0)
                {
                    team[0]+= players[i].getNumKills();
                    playersOnATeam[0]++;
                }
                else if(players[i].teamNum==1)
                {
                    team[1]+=players[i].getNumKills();
                    playersOnATeam[1]++;
                }
                else if(players[i].teamNum==2)
                {
                    team[2]+=players[i].getNumKills();
                    playersOnATeam[2]++;
                }
                else if(players[i].teamNum==3)
                {
                    team[3]+=players[i].getNumKills();
                    playersOnATeam[3]++;
                }
            }
            for(int i=0; i<4; i++)
            {
                if(playersOnATeam[i]>0)
                {
                    switch(guiCounter)
                    {
                        case 0:
                            counterStyle.normal.textColor = new Color(1.0f,0.0f,0.0f,1.0f);
                            GUI.Box(new Rect(0, height,width,height), "");
                            GUI.Box(new Rect(0,height,width,height), ""+team[i], counterStyle);
                            break;
                        case 1:
                            counterStyle.normal.textColor = new Color(0.0f,0.0f,1.0f,1.0f);
                            GUI.Box(new Rect(Screen.width-width, height, width, height), "");
                            GUI.Box(new Rect(Screen.width-width, height, width, height), ""+team[i], counterStyle);
                            break;
                        case 2:
                            counterStyle.normal.textColor = new Color(0.0f,1.0f,0.0f,1.0f);
                            GUI.Box(new Rect(0, Screen.height-(2*height), width, height), "");
                            GUI.Box(new Rect(0, Screen.height-(2*height), width, height), ""+team[i], counterStyle);
                            break;
                        case 3:
                            counterStyle.normal.textColor = new Color(0.0f,1.0f,1.0f,1.0f);
                            GUI.Box(new Rect(Screen.width-width, Screen.height-(2*height), width, height), "");
                            GUI.Box(new Rect(Screen.width-width, Screen.height-(2*height), width, height), ""+team[i], counterStyle);
                            break;
                    }
                    guiCounter++;
                }
            }
        }
		else if(players.Length > 0)
		{
            Color c = players[0].baseColor;

			counterStyle.normal.textColor = new Color(c.r,c.g,c.b,1.0f);
			int numKills = players[0].getNumKills();
			
			GUI.Box(new Rect(0, height,width,height), "");
			GUI.Box(new Rect(0,height,width,height), ""+numKills, counterStyle);
            guiCounter++;

            int firstTeam=players[0].teamNum;
			
			if(players.Length > 1)
			{
                c = players[1].baseColor;
                
                counterStyle.normal.textColor = new Color(c.r,c.g,c.b,1.0f);
				numKills = players[1].getNumKills();
				

                if(players[1].teamNum==firstTeam)
                {
                    
                }
                else
                {
                    switch(guiCounter)
                    {
                        case 1:
                            GUI.Box(new Rect(0, Screen.height-(2*height), width, height), "");
                            GUI.Box(new Rect(0, Screen.height-(2*height), width, height), ""+numKills, counterStyle);
                            break;
                        case 2:
                            GUI.Box(new Rect(Screen.width-width, height, width, height), "");
                            GUI.Box(new Rect(Screen.width-width, height, width, height), ""+numKills, counterStyle);
                            break;
                        case 3:
                            GUI.Box(new Rect(Screen.width-width, Screen.height-(2*height), width, height), "");
                            GUI.Box(new Rect(Screen.width-width, Screen.height-(2*height), width, height), ""+numKills, counterStyle);
                            break;
                    }
                    guiCounter++;
                }

                int secondTeam=players[1].teamNum;

				if(players.Length > 2)
				{
                    c = players[2].baseColor;
                    
                    counterStyle.normal.textColor = new Color(c.r,c.g,c.b,1.0f);
					numKills = players[2].getNumKills();
					
                    if(players[2].teamNum==firstTeam || players[2].teamNum==secondTeam)
                    {
                        
                    }
                    else
                    {
                        switch(guiCounter)
                        {
                            case 1:
                                GUI.Box(new Rect(0, Screen.height-(2*height), width, height), "");
                                GUI.Box(new Rect(0, Screen.height-(2*height), width, height), ""+numKills, counterStyle);
                                break;
                            case 2:
                                GUI.Box(new Rect(Screen.width-width, height, width, height), "");
                                GUI.Box(new Rect(Screen.width-width, height, width, height), ""+numKills, counterStyle);
                                break;
                            case 3:
                                GUI.Box(new Rect(Screen.width-width, Screen.height-(2*height), width, height), "");
                                GUI.Box(new Rect(Screen.width-width, Screen.height-(2*height), width, height), ""+numKills, counterStyle);
                                break;
                        }
                        guiCounter++;
                    }

                    int thirdTeam=players[2].teamNum;

					if(players.Length > 3)
					{
                        c = players[3].baseColor;
                        
                        counterStyle.normal.textColor = new Color(c.r,c.g,c.b,1.0f);
						numKills = players[3].getNumKills();
						
                        if(players[3].teamNum==firstTeam || players[3].teamNum==secondTeam || players[3].teamNum==thirdTeam)
                        {
                            
                        }
                        else
                        {
                            switch(guiCounter)
                            {
                                case 1:
                                    GUI.Box(new Rect(0, Screen.height-(2*height), width, height), "");
                                    GUI.Box(new Rect(0, Screen.height-(2*height), width, height), ""+numKills, counterStyle);
                                    break;
                                case 2:
                                    GUI.Box(new Rect(Screen.width-width, height, width, height), "");
                                    GUI.Box(new Rect(Screen.width-width, height, width, height), ""+numKills, counterStyle);
                                    break;
                                case 3:
                                    GUI.Box(new Rect(Screen.width-width, Screen.height-(2*height), width, height), "");
                                    GUI.Box(new Rect(Screen.width-width, Screen.height-(2*height), width, height), ""+numKills, counterStyle);
                                    break;
                            }
                            guiCounter++;
                        }
					}
				}
			}
		}
		if(isPaused)
		{
            /*
			Color c = GameManager.getPlayer(playerWhoPaused).baseColor;
			counterStyle.normal.textColor = c;
			GUI.Label(new Rect((int)(3*Screen.width/8), (int)(3*Screen.height/8)+winStyle.fontSize, 100, 20), "PAUSED", counterStyle);
			if(GUI.Button(new Rect((int)(3*Screen.width/8), (int)(6*Screen.height/8), 150, 30), "Back to Main Menu"))
			{
				Character.resetId();
                GameManager.UnpauseThisGodForsakenGame();
				Application.LoadLevel("MainMenu");
			}
            */
		}

        Character[] characters = GameObject.FindObjectsOfType<Character>();
        
        for(int i = 0; i < characters.Length; i++)
        {
            if(currentMaxScore < characters[i].getNumKills())
            {
                currentMaxScore = characters[i].getNumKills();
            }
        }
		if(false && (currentTime <= 0 || currentMaxScore >= maxScore))
		{
			int[] topPlayers = nabBestPlayer();
			if(gameType==1 || gameType==3)
			{
				for(int i=0; i<topPlayers.Length; i++)
				{
            	    Color c = GameManager.getPlayer(topPlayers[i]-1).baseColor;
	        	    
	        	    winStyle.normal.textColor = new Color(c.r,c.g,c.b,1.0f);
					GUI.TextField(new Rect((int)(3*Screen.width/8), (int)(3*Screen.height/8)+i*winStyle.fontSize, 100, 20), "Player "+topPlayers[i]+" Wins!!!", winStyle);
				}
			}
			else if(gameType==2)
			{
				for(int i=0; i<topPlayers.Length; i++)
				{
					if(topPlayers[i]==0)
					{
						Color c=new Color(255,0,0);
						winStyle.normal.textColor=new Color(c.r,c.g,c.b, 1.0f);
						GUI.TextField (new Rect((int)(3*Screen.width/8), (int)(3*Screen.height/8)+i*winStyle.fontSize, 100, 20), "Red Team Wins!!!", winStyle);
					}
					else if(topPlayers[i]==1)
					{
						Color c=new Color(0,0,255);
						winStyle.normal.textColor=new Color(c.r,c.g,c.b, 1.0f);
						GUI.TextField (new Rect((int)(3*Screen.width/8), (int)(3*Screen.height/8)+i*winStyle.fontSize, 100, 20), "Blue Team Wins!!!", winStyle);
					}
					else if(topPlayers[i]==2)
					{
						Color c=new Color(0,255,0);
						winStyle.normal.textColor=new Color(c.r,c.g,c.b, 1.0f);
						GUI.TextField (new Rect((int)(3*Screen.width/8), (int)(3*Screen.height/8)+i*winStyle.fontSize, 100, 20), "Green Team Wins!!!", winStyle);
					}
					else if(topPlayers[i]==3)
					{
						Color c=new Color(255,255,0);
						winStyle.normal.textColor=new Color(c.r,c.g,c.b, 1.0f);
						GUI.TextField (new Rect((int)(3*Screen.width/8), (int)(3*Screen.height/8)+i*winStyle.fontSize, 100, 20), "Yellow Team Wins!!!", winStyle);
					}
				}
			}
			if(GUI.Button(new Rect((int)(3*Screen.width/8), (int)(6*Screen.height/8), 150, 30), "Back to Main Menu"))
			{
				Character.resetId();
				Application.LoadLevel("MainMenu");
			}
		}
		}
	}
}
