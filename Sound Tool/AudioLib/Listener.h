#pragma once


//-----------------------

/**
 * \ingroup AudioLib
 *
 *
 * \par requirements
 * Windows XP\n
 * DirectX 9.0c\n
 * OpenAL Driver Install
 *
 * \version 1.0
 * first version
 *
 * \date 2007-09-16
 *
 * \author 정의원
 *
 * \par 
 * 
 * \brief 
 청취자 용 클래스
 청취자의 위치및 기본 정보들을 셋팅한다. 
 *
 */
class Listener
{
public:
	ALfloat	m_fListenerPos[3];
	ALfloat	m_fListenerVelo[3];
	ALfloat m_fListenerOrien[6];
public:
	void SetListenerPos(D3DXVECTOR3* pPos);
	void SetListenerVelo(D3DXVECTOR3* pVelo);
	void SetListenerOrien(D3DXVECTOR3* pAt, D3DXVECTOR3* pUp);

	void SetListener();
public:
	Listener(void);
	virtual ~Listener(void);
};
