using UnityEngine;
using System.Collections;

[RequireComponent(typeof(AudioSource))]
public class SoundManager : MonoBehaviour {

    public AudioClip walk;
    public AudioClip dash;
    public AudioClip fireBallLaunch;
    public AudioClip fireBallExplosion;
    public AudioClip Landing;
    public AudioClip Lightning;
    public AudioClip MagicMissileLaunch;
    public AudioClip RicochetteBounce;
    public AudioClip RicochetteLaunch;
    public AudioClip ZapLaunch;
    public AudioClip Jump;
    public AudioClip[] dying;
    public AudioSource musicPlayer;

    public static SoundManager soundCall;

	// Use this for initialization
	void Start () {
        GameObject.DontDestroyOnLoad(this.gameObject);
        musicPlayer=(AudioSource)Instantiate(musicPlayer);
        musicPlayer.loop = true;
        musicPlayer.Play();
        GameObject.DontDestroyOnLoad(musicPlayer);
	}
	
	// Update is called once per frame
	void Update () {
        if (!musicPlayer)
        {
            musicPlayer = (AudioSource)Instantiate(musicPlayer);
            musicPlayer.Play();
        }
	}

    public void playWalk()
    {
        audio.PlayOneShot(walk);
    }
    public void playDash()
    {
        audio.PlayOneShot(dash);
    }
    public void playDying()
    {
        int soundPlay=Random.Range(0, dying.Length);
        audio.PlayOneShot(dying[soundPlay]);
    }
    public void playFireBallLaunch()
    {
        audio.PlayOneShot(fireBallLaunch);
    }
    public void playFireBallExplosion()
    {
        audio.PlayOneShot(fireBallExplosion);
    }
    public void playLand()
    {
        audio.PlayOneShot(Landing);
    }
    public void playLightning()
    {
        audio.PlayOneShot(Lightning);
    }
    public void playMagicMissileLaunch()
    {
        audio.PlayOneShot(MagicMissileLaunch);
    }
    public void playRicochetteBounce()
    {
        audio.PlayOneShot(RicochetteBounce);
    }
    public void playRicochetteLaunch()
    {
        audio.PlayOneShot(RicochetteLaunch);
    }
    public void playZap()
    {
        audio.PlayOneShot(ZapLaunch);
    }
    public void playJump()
    {
        audio.PlayOneShot(Jump);
    }
}
