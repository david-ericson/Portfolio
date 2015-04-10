using UnityEngine;
using System.Collections;

public class MenuSettings : MonoBehaviour {

    enum MenuElement {ME_REPLAY, ME_TOMENU};

    public Texture background;
    public Texture selector;

    public Texture GameOverTexture;

    public bool show = false;

    public int visibleLastFrame = 0;

    MenuElement curElement = MenuElement.ME_REPLAY;
    Color origColor;
    public GameManager gameManager;

    public GUIStyle menuStyle;

    int updateNumber = 0;

    const float backgroundPercentHeight = 0.4f;

    const float labelPercentHeight = 0.07f;

    void OnGUI()
    {
        if (show)
        {

            origColor = menuStyle.normal.textColor;
            ///Background texture.
            float screenWidth = Camera.main.pixelWidth;
            float screenHeight = Camera.main.pixelHeight;
            float halfWidth = Camera.main.pixelWidth / 2;
            float halfHeight = Camera.main.pixelHeight / 2;
            float halfBackWidth = halfHeight * 0.4f;
            float gameOverWidth = halfWidth;
            float gameOverHeight = halfHeight * 0.4f;

            GUI.DrawTexture(new Rect(halfWidth - halfBackWidth, halfHeight - halfBackWidth, halfBackWidth * 2, halfBackWidth * 2), background);

            float labelPosInc = halfBackWidth * 2 / 5;
            float curLabelY = halfHeight - halfBackWidth + labelPosInc;

            float labelHeight = halfBackWidth * 2 / 6;
            float labelWidth = halfBackWidth - 20;

            float labelX = (halfWidth - (halfBackWidth / 2)) - (labelWidth / 2);
            float buttonX = (halfWidth + (halfBackWidth / 2)) - (labelWidth / 2);

            Rect replayRect = new Rect(halfWidth - labelWidth / 2, halfHeight + halfBackWidth / 2 - labelHeight / 2 - labelHeight, labelWidth, labelHeight);
            Rect menuRect = new Rect(halfWidth - labelWidth / 2, halfHeight + halfBackWidth / 2 - labelHeight / 2, labelWidth, labelHeight);
            
            //Selector

            switch (curElement)
            {
                case MenuElement.ME_REPLAY:
                    GUI.DrawTexture(replayRect, selector);
                    break;
                case MenuElement.ME_TOMENU:
                    GUI.DrawTexture(menuRect, selector);
                    break;
            }

            //labels
            GUI.Label(replayRect, "Replay", menuStyle);
            GUI.Label(menuRect, "Menu", menuStyle);

            Character[] characters = GameObject.FindObjectsOfType<Character>();
            gameManager.currentMaxScore = 0;
            for(int i = 0; i < characters.Length; i++)
            {
                if(gameManager.currentMaxScore < characters[i].getNumKills())
                {
                    gameManager.currentMaxScore = characters[i].getNumKills();
                }
            }
            //Winner stuff.
            if (gameManager.currentTime <= 0 || gameManager.currentMaxScore >= GameManager.maxScore)
		    {
                GUI.DrawTexture(new Rect(halfWidth - gameOverWidth / 2, halfHeight / 4, gameOverWidth, gameOverHeight), GameOverTexture);

                Rect playerScoreRect =  new Rect(halfWidth - labelWidth / 2, halfHeight - labelHeight / 2 - halfBackWidth / 2, labelWidth, labelHeight);

			    int[] topPlayers = gameManager.nabBestPlayer();
                if (GameManager.gameType == 1 || GameManager.gameType == 3)
			    {
				    for(int i=0; i<topPlayers.Length; i++)
				    {
            	        Color c = GameManager.getPlayer(topPlayers[i]-1).baseColor;

                        menuStyle.normal.textColor = new Color(c.r, c.g, c.b, 1.0f);
                        GUI.TextField(playerScoreRect, "Player " + topPlayers[i] + " Wins!!!", menuStyle);
				    }
			    }
			    else if(GameManager.gameType==2)
			    {
				    for(int i=0; i<topPlayers.Length; i++)
				    {
					    if(topPlayers[i]==0)
					    {
						    Color c=new Color(255,0,0);
                            menuStyle.normal.textColor = new Color(c.r, c.g, c.b, 1.0f);
                            GUI.TextField(new Rect(playerScoreRect.left, playerScoreRect.top + i * playerScoreRect.height, playerScoreRect.width, playerScoreRect.height), "Red Team Wins!!!", menuStyle);
					    }
					    else if(topPlayers[i]==1)
					    {
						    Color c=new Color(0,0,255);
                            menuStyle.normal.textColor = new Color(c.r, c.g, c.b, 1.0f);
                            GUI.TextField(new Rect(playerScoreRect.left, playerScoreRect.top + i * playerScoreRect.height, playerScoreRect.width, playerScoreRect.height), "Blue Team Wins!!!", menuStyle);
					    }
					    else if(topPlayers[i]==2)
					    {
						    Color c=new Color(0,255,0);
                            menuStyle.normal.textColor = new Color(c.r, c.g, c.b, 1.0f);
                            GUI.TextField(new Rect(playerScoreRect.left, playerScoreRect.top + i * playerScoreRect.height, playerScoreRect.width, playerScoreRect.height), "Green Team Wins!!!", menuStyle);
					    }
					    else if(topPlayers[i]==3)
					    {
						    Color c=new Color(255,255,0);
                            menuStyle.normal.textColor = new Color(c.r, c.g, c.b, 1.0f);
                            GUI.TextField(new Rect(playerScoreRect.left, playerScoreRect.top + i * playerScoreRect.height, playerScoreRect.width, playerScoreRect.height), "Yellow Team Wins!!!", menuStyle);
					    }
				    }
			    }
		    }
            menuStyle.normal.textColor = origColor;
        }
    }

	// Use this for initialization
	void Start () {
	    
	}
	
	// Update is called once per frame
	void Update () {
	
        updateNumber ++;
        if (show)
        {
            visibleLastFrame = 5;
        } else
        {
            visibleLastFrame --;
        }
	}

    public void toggleVisible()
    {
        show = !show;
    }

    public void aPressed()
    {
        if (curElement == MenuElement.ME_REPLAY)
        {
            GameManager.hardReset();
            gameManager.currentMaxScore = 0;
            Character[] characters = FindObjectsOfType<Character>();
            for(int i =0;i < characters.Length; i ++)
            {
                characters[i].Restart();
            }
            GameManager.UnpauseThisGodForsakenGame();
            show = false;
        }

        if (curElement == MenuElement.ME_TOMENU)
        {
            Character.resetId();
            show = false;
            Application.LoadLevel("MainMenu");
        }
    }

    public void MenuSelectionUp()
    {
        //Moves the currently selected value up one.
        switch (curElement)
        {
            case MenuElement.ME_TOMENU:
                curElement = MenuElement.ME_REPLAY;
                break;
            case MenuElement.ME_REPLAY:
                curElement = MenuElement.ME_TOMENU;
                break;
        }
    }

    public void MenuSelectionDown()
    {
        //Moves the currently selected value up one.
        switch (curElement)
        {
            case MenuElement.ME_TOMENU:
                curElement = MenuElement.ME_REPLAY;
                break;
            case MenuElement.ME_REPLAY:
                curElement = MenuElement.ME_TOMENU;
                break;
        }
    }

}
