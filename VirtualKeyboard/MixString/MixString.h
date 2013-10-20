// MixString.h

#pragma once

#include "MixStringClass/Key_Input.h"


namespace MixString {

	public ref class CMixStirng
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		CMixStirng();
		virtual ~CMixStirng();

	private :
		Virtual_Keyboard::CKey_Input		*		m_pKeyInput;

	public:
		// 문자열 리턴
		System::String ^		getString();

		// 아스키 코드 입력
		void					asciiCodeInput( int code );

		// 백스페이스
		void					BackSpace();
		// 스페이스
		void					Space();

		// 한영 전환


		// 한글 자음 입력
		void					AddKoreanJaum( int index );

		// 한글 모음 입력
		void					AddKoreanMoum( int index );
	};
}
