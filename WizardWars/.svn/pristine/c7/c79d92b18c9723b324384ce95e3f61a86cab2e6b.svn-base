using UnityEngine;
using System.Collections;

[RequireComponent(typeof(AudioSource))]
public class MusicManager : MonoBehaviour {

	public AudioClip menuMusic;
	public AudioClip gameMusic;
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
	
	public void playMenu()
	{
		audio.loop = true;
		audio.clip = menuMusic;
		audio.Play ();
	}
	public void playGame()
	{
		audio.loop = true;
		audio.clip = gameMusic;
		audio.Play();
	}
}
