#pragma once

// WinAPI 메시지 박스를 간단히 쓰기 위함
#ifdef _DEBUG
#define POPUP_DEBUG(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)
#endif

#define POPUP(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)

// 싱글턴, 하나의 매크로 단위에서 줄넘김을 하려면 '\'를 써야 하며, 매크로의 ()안의 인자는 하나의 매크로 안에서 쓰이는 토큰이 됨
// 여기서 "friend class singleton<type>"를 쓴 이유는, 상속해서 싱글턴 패턴을 구성하여 사용할 때 접근자 private에 접근하기 위함임
// 여러 내용을 정의하는 형식이므로, 뒤에 ';'를 붙힌 것임을 유의
#define SINGLE(Class)	friend class C_Singleton<Class>; \
public: \
Class& operator = (const Class& _Other) = delete; \
Class(); \
Class(const Class& _Origin) = delete; \
~Class();