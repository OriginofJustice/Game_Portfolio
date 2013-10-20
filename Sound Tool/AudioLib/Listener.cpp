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
 * \par �޼ҵ� ����
 û���� ��ü�� �������� �����Ѵ�.
 * \param *pPos 
 */
void Listener::SetListenerPos(D3DXVECTOR3 *pPos)
{
	m_fListenerPos[0] = pPos->x;
	m_fListenerPos[1] = pPos->y;
	m_fListenerPos[2] = pPos->z;
}

/**
 * \par �޼ҵ� ����
 û���� ��ü�� ���ν�Ƽ�� �����Ѵ�.
 * \param pVelo 
 */
void Listener::SetListenerVelo(D3DXVECTOR3* pVelo)
{
	m_fListenerVelo[0] = pVelo->x;
	m_fListenerVelo[1] = pVelo->y;
	m_fListenerVelo[2] = pVelo->z;
}
/**
 * \par �޼ҵ� ����
 û���ڰ� ����Ű�� �ִ� ���� ���Ϳ� û������ �����͸� �����Ѵ�
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
 * \par �޼ҵ� ����
 û������ �Է� ���� �������� ������ �����ϰ� �ϴ� �Լ� 
 */
void Listener::SetListener()
{
	alListenerfv(AL_POSITION, m_fListenerPos);
	alListenerfv(AL_VELOCITY, m_fListenerVelo);
	alListenerfv(AL_ORIENTATION, m_fListenerOrien);
}


