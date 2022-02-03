/*
 * File:			Wave.h
 * Programmer:		Emily Goodwin
 * Project:			GAS A3
 * Description:		Contains the class definition for wave.h 
 *  taken from https://www.codeproject.com/Articles/29676/CWave-A-Simple-C-Class-to-Manipulate-WAV-Files
 * First Version:	April 10, 2019
 */

#pragma once

#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <tchar.h>

using namespace std;

#pragma comment(lib, "winmm.lib")

#pragma pack(1)
typedef struct __WAVEDESCR
{
	BYTE riff[4];
	DWORD size;
	BYTE wave[4];

} _WAVEDESCR, *_LPWAVEDESCR;

typedef struct __WAVEFORMAT
{
	BYTE id[4];
	DWORD size;
	SHORT format;
	SHORT channels;
	DWORD sampleRate;
	DWORD byteRate;
	SHORT blockAlign;
	SHORT bitsPerSample;

} _WAVEFORMAT, *_LPWAVEFORMAT;
#pragma pack()

/*
* Class	cWave
* Desc:	Models a wave.
*/
class CWave
{
public:
	CWave(void);
	virtual ~CWave(void);

public:
	// Public methods
	bool Load(LPCWSTR lpszFilePath);
	bool Save(LPTSTR lpszFilePath);
	bool Play();
	bool Stop();
	bool Pause();
	bool Mix(CWave& wave);
	bool IsValid()				{return (m_lpData != NULL);}
	bool IsPlaying()			{return (!m_bStopped && !m_bPaused);}
	bool IsStopped()			{return m_bStopped;}
	bool IsPaused()				{return m_bPaused;}
	LPBYTE GetData()			{return m_lpData;}
	DWORD GetSize()				{return m_dwSize;}
	SHORT GetChannels()			{return m_Format.channels;}
	DWORD GetSampleRate()		{return m_Format.sampleRate;}
	SHORT GetBitsPerSample()	{return m_Format.bitsPerSample;}

private:
	// Pribate methods
	bool Open(SHORT channels, DWORD sampleRate, SHORT bitsPerSample);
	bool Close();
	bool static CALLBACK WaveOut_Proc(HWAVEOUT hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

private:
	// Private members
	_WAVEDESCR m_Descriptor;
	_WAVEFORMAT m_Format;
	LPBYTE m_lpData;
	DWORD m_dwSize;
	HWAVEOUT m_hWaveout;
	WAVEHDR m_WaveHeader;
	bool m_bStopped;
	bool m_bPaused;
};
