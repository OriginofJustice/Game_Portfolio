#pragma once

class IAudioBase
{
	virtual bool Init();
	//virtual bool Load();
	//virtual bool Unload();
	virtual bool Release();
public:
	IAudioBase(void);
	virtual ~IAudioBase(void);
};
