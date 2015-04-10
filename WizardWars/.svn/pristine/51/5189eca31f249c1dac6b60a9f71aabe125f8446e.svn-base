using UnityEngine;
using System.Collections;

public class GameSettings : MonoBehaviour {

    enum GameMode {GM_FFA, GM_TEAMS, GM_ARCHMAGE};

    enum MenuElement {ME_GAMEMODE, ME_TIME, ME_SCORE, ME_AIGHT};

    const int TIME_INCREMENT = 15;
    GameMode gm = GameMode.GM_FFA;
    int timeLimitInSeconds = 2 * 60;
    int scoreLimit;

    public Texture background;
    public Texture selector;
    public bool show = false;

    public int visibleLastFrame = 0;

    MenuElement curElement = MenuElement.ME_GAMEMODE;

    public GameManager gameManager;

    public GUIStyle menuStyle;

    int updateNumber = 0;

    const float backgroundPercentHeight = 0.4f;

    const float labelPercentHeight = 0.07f;

    void OnGUI()
    {
       
        if (show)
        {
            ///Background texture.
            float screenWidth = Camera.main.pixelWidth;
            float screenHeight = Camera.main.pixelHeight;
            float halfWidth = Camera.main.pixelWidth / 2;
            float halfHeight = Camera.main.pixelHeight / 2;
            float halfBackWidth = halfHeight * 0.4f;
            GUI.DrawTexture(new Rect(halfWidth - halfBackWidth, halfHeight - halfBackWidth, halfBackWidth * 2, halfBackWidth * 2), background);

            float labelPosInc = halfBackWidth * 2 / 5;
            float curLabelY = halfHeight - halfBackWidth + labelPosInc;

            float labelHeight = halfBackWidth * 2 / 6;
            float labelWidth = halfBackWidth - 20;

            float labelX = (halfWidth - (halfBackWidth / 2)) - (labelWidth / 2);
            float buttonX = (halfWidth + (halfBackWidth / 2)) - (labelWidth / 2);

            //Labels of the options.
            GUI.Label(new Rect(labelX, curLabelY, labelWidth, labelHeight), "Game Mode", menuStyle);

            Rect gmlRect = new Rect(labelX, curLabelY, labelWidth, labelHeight);
            Rect gmRect = new Rect(buttonX, curLabelY, labelWidth, labelHeight);
            curLabelY += labelPosInc;

            GUI.Label(new Rect(labelX, curLabelY, labelWidth, labelHeight), "Time Limit", menuStyle);
            Rect tllRect = new Rect(labelX, curLabelY, labelWidth, labelHeight);
            Rect tlRect = new Rect(buttonX, curLabelY, labelWidth, labelHeight);
            curLabelY += labelPosInc;
            GUI.Label(new Rect(labelX, curLabelY, labelWidth, labelHeight), "Score Limit", menuStyle);
            Rect scorelRect = new Rect(labelX, curLabelY, labelWidth, labelHeight);
            Rect scoreRect = new Rect(buttonX, curLabelY, labelWidth, labelHeight);
            curLabelY += labelPosInc;

            Rect aightRect = new Rect(halfWidth - (labelWidth / 2), curLabelY, labelWidth, labelHeight);
            
            //Selector

            switch (curElement)
            {
                case MenuElement.ME_AIGHT:
                    GUI.DrawTexture(aightRect, selector);
                    break;
                case MenuElement.ME_GAMEMODE:
                    GUI.DrawTexture(gmRect, selector);
                    break;
                case MenuElement.ME_SCORE:
                    GUI.DrawTexture(scoreRect, selector);
                    break;
                case MenuElement.ME_TIME:
                    GUI.DrawTexture(tlRect, selector);
                    break;
            }

            //Labels.

            GUI.Label(gmRect, getGameModeString(), menuStyle);
            GUI.Label(tlRect, getTimeLimitString(), menuStyle);
            GUI.Label(scoreRect, getScoreString(), menuStyle);
            GUI.Label(aightRect, "A'ight", menuStyle);
        }
    }


    string getTimeLimitString()
    {
        int minutes = (int)(timeLimitInSeconds / 60);
        int seconds = timeLimitInSeconds % 60;
        if (timeLimitInSeconds == 0)
        {
            return "Infinite";
        }

        return minutes + ":" + (seconds < 10? "0" : "") + seconds;
    }


    string getScoreString()
    {
        if (scoreLimit == 0)
        {
            return "Infinite";
        }
        return scoreLimit.ToString();
    }

    string getGameModeString()
    {
        switch (gm)
        {
            case GameMode.GM_ARCHMAGE:
                return "Arch Mage";
            case GameMode.GM_FFA:
                return "FFA";
            case GameMode.GM_TEAMS:
                return "Teams";
        }
        return "BROKEN";
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

       
        if (updateNumber == 2)
        {
            int type = GameManager.gameType;
            switch (type)
            {
                case 1:
                    gm = GameMode.GM_FFA;
                    break;
                case 2:
                    gm = GameMode.GM_TEAMS;
                    break;
                case 3:
                    gm = GameMode.GM_ARCHMAGE;
                    break;
            }

            timeLimitInSeconds = 0;//(int)GameManager.startingTime;
            if (timeLimitInSeconds > 1000)
            {
                timeLimitInSeconds = 0;
            }
            scoreLimit = GameManager.maxScore;
            if (scoreLimit == int.MaxValue)
            {
                scoreLimit = 0;
            }
        }

        if (updateNumber > 2)
        {
            GameManager.startingTime = timeLimitInSeconds == 0 ? 1000.0f : timeLimitInSeconds;
            GameManager.maxScore = scoreLimit == 0? int.MaxValue : scoreLimit;
            GameManager.gameType = gm == GameMode.GM_FFA? 1 : (gm == GameMode.GM_TEAMS ? 2 : 3);
        }
	}

    public void toggleVisible()
    {
        show = !show;
    }

    public void aPressed()
    {
        if (curElement == MenuElement.ME_AIGHT)
        {
            show = false;
        }
    }

    void increaseGameMode()
    {
        switch (gm)
        {
            case GameMode.GM_ARCHMAGE:
                gm = GameMode.GM_FFA;
                break;
            case GameMode.GM_FFA:
                gm = GameMode.GM_TEAMS;
                break;
            case GameMode.GM_TEAMS:
                gm = GameMode.GM_ARCHMAGE;
                break;
        }
    }

    void decreaseGameMode()
    {
        switch (gm)
        {
            case GameMode.GM_ARCHMAGE:
                gm = GameMode.GM_TEAMS;
                break;
            case GameMode.GM_FFA:
                gm = GameMode.GM_ARCHMAGE;
                break;
            case GameMode.GM_TEAMS:
                gm = GameMode.GM_FFA;
                break;
        }
    }


    public void MenuSelectionUp()
    {
        //Moves the currently selected value up one.
        switch (curElement)
        {
            case MenuElement.ME_AIGHT:
                curElement = MenuElement.ME_SCORE;
                break;
            case MenuElement.ME_SCORE:
                curElement = MenuElement.ME_TIME;
                break;
            case MenuElement.ME_TIME:
                curElement = MenuElement.ME_GAMEMODE;
                break;
            case MenuElement.ME_GAMEMODE:
                curElement = MenuElement.ME_AIGHT;
                break;
        }
    }

    public void MenuSelectionDown()
    {
        //Moves the currently selected value up one.
        switch (curElement)
        {
            case MenuElement.ME_AIGHT:
                curElement = MenuElement.ME_GAMEMODE;
                break;
            case MenuElement.ME_SCORE:
                curElement = MenuElement.ME_AIGHT;
                break;
            case MenuElement.ME_TIME:
                curElement = MenuElement.ME_SCORE;
                break;
            case MenuElement.ME_GAMEMODE:
                curElement = MenuElement.ME_TIME;
                break;
        }
    }


    public void MenuSelectionRight()
    {
        //Moves the currently selected value up one.
        switch (curElement)
        {
            case MenuElement.ME_SCORE:
                scoreLimit ++;
                break;
            case MenuElement.ME_TIME:
                timeLimitInSeconds += TIME_INCREMENT;
                break;
            case MenuElement.ME_GAMEMODE:
                increaseGameMode();
                break;
            default:
                break;
        }
    }
    public void MenuSelectionLeft()
    {
        //Moves the currently selected value up one.
        switch (curElement)
        {
            case MenuElement.ME_SCORE:
                scoreLimit --;
                scoreLimit = Mathf.Clamp(scoreLimit, 0, int.MaxValue);
                break;
            case MenuElement.ME_TIME:
                timeLimitInSeconds -= TIME_INCREMENT;
                timeLimitInSeconds = Mathf.Clamp(timeLimitInSeconds, 0, int.MaxValue);
                break;
            case MenuElement.ME_GAMEMODE:
                decreaseGameMode();
                break;
            default:
                break;
        }
    }



}
