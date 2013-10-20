#include "StdAfx.h"
#include ".\listener.h"

Listener::Listener(void)
{
	for (int i = 0 ; i < 3; i++)
	{
		m_fListenerPos[i] = 0.0f;
		m_fListenerVelo[i] = 0.0f;
		for (int j = 0 ; j < 2; j++)
			m_fListenerOrien[j] = 0.0f;
	}
	m_fListenerOrien[2] = -1.0f;
	m_fListenerOrien[4] = 1.0f;
}

Listener::~Listener(void)
{
}

/**
 * \par 메소드 설명
 청취자 객체의 포지션을 셋팅한다.
 * \param *pPos 
 */
void Listener::SetListenerPos(D3DXVECTOR3 *pPos)
{
	m_fListenerPos[0] = pPos->x;
	m_fListenerPos[1] = pPos->y;
	m_fListenerPos[2] = pPos->z;
}

/**
 * \par 메소드 설명
 청취자 객체의 벨로시티를 설정한다.
 * \param pVelo 
 */
void Listener::SetListenerVelo(D3DXVECTOR3* pVelo)
{
	m_fListenerVelo[0] = pVelo->x;
	m_fListenerVelo[1] = pVelo->y;
	m_fListenerVelo[2] = pVelo->z;
}
/**
 * \par 메소드 설명
 청취자가 가르키고 있는 방향 벡터와 청취자의 업벡터를 셋팅한다
 * \param pAt 
 * \param pUp 
 */
void Listener::SetListenerOrien(D3DXVECTOR3* pAt, D3DXVECTOR3* pUp)
{
	m_fListenerOrien[0] = pAt->x;
	m_fListenerOrien[1] = pAt->y;
	m_fListenerOrien[2] = pAt->z;
	m_fListenerOrien[3] = pUp->x;
	m_fListenerOrien[4] = pUp->y;
	m_fListenerOrien[5] = pUp->z;
}

/**
 * \par 메소드 설명
 청취자의 입력 받은 정보들을 적용이 가능하게 하는 함수 
 */
void Listener::SetListener()
{
	alListenerfv(AL_POSITION, m_fListenerPos);
	alListenerfv(AL_VELOCITY, m_fListenerVelo);
	alListenerfv(AL_ORIENTATION, m_fListenerOrien);
}


