#pragma once
// 유의! \ 뒤에 공백이 붙으면 매크로 구문 자체가 맛이 감을 조심!
// 존나 그지같은 문법이네

// WinAPI 메시지 박스를 간단히 쓰기 위함
#ifdef _DEBUG
#define POPUP_DEBUG(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)
#endif

#define POPUP(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)

// 싱글턴, 하나의 매크로 단위에서 줄넘김을 하려면 '\'를 써야 하며, 매크로의 ()안의 인자는 하나의 매크로 안에서 쓰이는 토큰이 됨
// 여기서 "friend class singleton<type>"를 쓴 이유는, 상속해서 싱글턴 패턴을 구성하여 사용할 때 접근자 private에 접근하기 위함임
// 여러 내용을 정의하는 형식이므로, 뒤에 ';'를 붙힌 것임을 유의
#define SINGLE(Class)                                       \
friend class C_Singleton<Class>;                            \
public:                                                     \
Class();                                                    \
Class(const Class& _Origin) = delete;                       \
Class& operator = (const Class& _Other) = delete;           \
~Class();

// 클론
#define CLONE(Class)	                    \
virtual Class* MF_Clone() override          \
{                                           \
	return new Class(*this);                \
}

// Component 종류에 따른 자식 Component 포인터 반환하는 매크로
#define GETCOMPONENTBYTYPE(Class, _COMPONENT)                           \
Class* MF_Get##Class##()                                                \
{                                                                       \
    return (Class*)P_M_OwnerObject->P_M_Component_s[_COMPONENT];        \
}

// Deep Copy Macro
// 향후, 구현 및 기재예정
// 깊은 복사는 범위기반 for문은 못 쓴다는 점 유의해서 만들어야 겠음

// Heap Memory Free Macro
//// STL Version
// 범위기반 For문 이용; Swift 범위기반 문 응용
#define DELETEALL_STL(STL)         \
for (auto& Element : STL)       \
{                               \
    delete Element;             \
}                               \
STL.clear();

//// Fixed Array Version
#define DELETEALL_FIXEDARRAY_HEAP(FixedArray, _END)    \
for (int i = 0; i < _END; ++i)                      \
{                                                   \
    if (FixedArray[i] != nullptr)                   \
    {                                               \
        delete FixedArray[i];                       \
        FixedArray[i] = nullptr;                    \
    }                                               \
}