#pragma once
// ����! \ �ڿ� ������ ������ ��ũ�� ���� ��ü�� ���� ���� ����!
// ���� �������� �����̳�

// WinAPI �޽��� �ڽ��� ������ ���� ����
#ifdef _DEBUG
#define POPUP_DEBUG(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)
#endif

#define POPUP(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)

// �̱���, �ϳ��� ��ũ�� �������� �ٳѱ��� �Ϸ��� '\'�� ��� �ϸ�, ��ũ���� ()���� ���ڴ� �ϳ��� ��ũ�� �ȿ��� ���̴� ��ū�� ��
// ���⼭ "friend class singleton<type>"�� �� ������, ����ؼ� �̱��� ������ �����Ͽ� ����� �� ������ private�� �����ϱ� ������
// ���� ������ �����ϴ� �����̹Ƿ�, �ڿ� ';'�� ���� ������ ����
#define SINGLE(Class)                                       \
friend class C_Singleton<Class>;                            \
public:                                                     \
Class();                                                    \
Class(const Class& _Origin) = delete;                       \
Class& operator = (const Class& _Other) = delete;           \
~Class();

// Ŭ��
#define CLONE(Class)	                    \
virtual Class* MF_Clone() override          \
{                                           \
	return new Class(*this);                \
}

// Component ������ ���� �ڽ� Component ������ ��ȯ�ϴ� ��ũ��
#define GETCOMPONENTBYTYPE(Class, _COMPONENT)                           \
Class* MF_Get##Class##()                                                \
{                                                                       \
    return (Class*)P_M_OwnerObject->P_M_Component_s[_COMPONENT];        \
}

// Deep Copy Macro
// ����, ���� �� ���翹��
// ���� ����� ������� for���� �� ���ٴ� �� �����ؼ� ������ ����

// Heap Memory Free Macro
//// STL Version
// ������� For�� �̿�; Swift ������� �� ����
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