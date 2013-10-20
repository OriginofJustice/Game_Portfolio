// SampleSound.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "..\\Include\AudioManager.h"


AudioManager g_Engine;
ALuint source;

int _tmain(int argc, _TCHAR* argv[])
{
	
	g_Engine.Init();
	try
	{

		ALuint* bgm = g_Engine.m_Buffer.OggFileLoad("..\\OggData\\Opening.ogg");


		alGenSources(1, &source);
		

		if (!g_Engine.Play_Music( bgm,  source))
			throw string("Ogg refused to play.");
		while(g_Engine.StreamUpdate(bgm, source))
		{
			if (!g_Engine.IsPlay(source))
			{
				if(!g_Engine.Play_Music(bgm, source))
					throw string("Ogg abruptly stopped.");
					
				else
					cout << "Ogg stream was interrupted.\n";
			}
		}
		alDeleteSources(1, &source);
		g_Engine.m_Buffer.OggBufferClose();
		alDeleteBuffers(1, bgm );
		ALuint* bgm1 = g_Engine.m_Buffer.OggFileLoad("..\\OggData\\Prologue.ogg");


		alGenSources(1, &source);


		if (!g_Engine.Play_Music( bgm1,  source))
			throw string("Ogg refused to play.");
		while(g_Engine.StreamUpdate(bgm, source))
		{
			if (!g_Engine.IsPlay(source))
			{
				if(!g_Engine.Play_Music(bgm1, source))
					throw string("Ogg abruptly stopped.");

				else
					cout << "Ogg stream was interrupted.\n";
			}
		}
		cout << "정상적으로 종료 되었습니다.";


	}
	catch(string error)
	{
		cout << error;
		cin.get();
	}





	//// 사운드 스크립트 파일 로드 
	//g_Engine.m_Parser.AudioLoader("..\\Script\\AudioSample.jst");
	//

	//// 원하는 사운드 파일 플레이
	Source_Info* Info = NULL;
	SAFE_NEW(Info,Source_Info);
	//Info = g_Engine.m_Parser.m_pSourceInfo[0];
	Info->Position[0] = 0.0f;
	Info->Position[1] = 0.0f;
	Info->Position[2] = 0.0f;
	Info->Velocity = D3DXVECTOR3(0.0f,0.0f,0.1f);

	//ALuint  temp2 = g_Engine.m_Source.AddBGM(bgm, Info);

	////Info->Velocity[0] = 0.0f;
	////Info->Velocity[1] = 0.0f;
	////Info->Velocity[2] = 0.1f;
	//Source_Info* Info2;
	//Info2 = g_Engine.m_Parser.m_pSourceInfo[1];
	//Info2->Position[0] = 0.0f;
	//Info2->Position[1] = 0.0f;
	//Info2->Position[2] = 0.0f;

	//Info2->Velocity = D3DXVECTOR3(0.0f,0.0f,0.1f);




	//
	
	//ALuint temp2 = g_Engine.m_Source.AddSource(g_Engine.m_Parser.
	//	m_pAudioBuffer[Info2->SourceID]->Buffer,Info2);

	//char c = ' ';

	//while(c != 'q')
	//{
	//	int result;
	//	c = getche();

	//	switch(c)
	//	{
	//		case '1': 
	//			alSourcePlay(temp2); 
	//			break;
	//		//case '2':
	//		//	alSourcePlay(temp2); 
	//		//	if (result = alGetError() == AL_NO_ERROR)
	//		//	{
	//		//		int kkk =0;
	//		//	}
	//		//	break;
	//		default :
	//			break;
	//	
	//	};
	//}
	//

	g_Engine.m_Source.AllSourceDelete();
	// 사운드 스크립트 파일 릴리즈
	g_Engine.m_Buffer.AllBufferDelete();
	g_Engine.Release();
	return 0;
}

