// MixString.h

#pragma once

#include "MixStringClass/Key_Input.h"


namespace MixString {

	public ref class CMixStirng
	{
		// TODO: ���⿡ �� Ŭ������ ���� �޼��带 �߰��մϴ�.
	public:
		CMixStirng();
		virtual ~CMixStirng();

	private :
		Virtual_Keyboard::CKey_Input		*		m_pKeyInput;

	public:
		// ���ڿ� ����
		System::String ^		getString();

		// �ƽ�Ű �ڵ� �Է�
		void					asciiCodeInput( int code );

		// �齺���̽�
		void					BackSpace();
		// �����̽�
		void					Space();

		// �ѿ� ��ȯ


		// �ѱ� ���� �Է�
		void					AddKoreanJaum( int index );

		// �ѱ� ���� �Է�
		void					AddKoreanMoum( int index );
	};
}
