#pragma once
// ����! \ �ڿ� ������ ������ ��ũ�� ���� ��ü�� ���� ���� ����!
// ���� �������� �����̳�

// WinAPI �޽��� �ڽ��� ������ ���� ����
//// ����, �αױ�� �߰��� ���� �� �� �ֵ��� �ϸ� ���� ��
#ifdef _DEBUG
#define POPUP_DEBUG(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION);
#endif

#define POPUP(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION);

// �̱���, �ϳ��� ��ũ�� �������� �ٳѱ��� �Ϸ��� '\'�� ��� �ϸ�, ��ũ���� ()���� ���ڴ� �ϳ��� ��ũ�� �ȿ��� ���̴� ��ū�� ��
// ���⼭ "friend class singleton<type>"�� �� ������, ����ؼ� �̱��� ������ �����Ͽ� ����� �� ������ private�� �����ϱ� ������
// ���� ������ �����ϴ� �����̹Ƿ�, �ڿ� ';'�� ���� ������ ����
#define SINGLE(Class)                                       \
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

// ���� ������ ���� ��ũ��
#define DELETE_COPY_CONSTRUCTOR(Class) Class

// Component ������ ���� �ڽ� Component ������ ��ȯ�ϴ� ��ũ��
#define GETCOMPONENTBYTYPE(Class, _COMPONENT)                           \
Class* MF_Get_##Class##()                                                \
{                                                                       \
    return (Class*)P_M_OwnerObject->P_M_Component_s[_COMPONENT];        \
}

// Deep Copy Macro
// ����, ���� �� ���翹��
// ���� ����� ������� for���� �� ���ٴ� �� �����ؼ� ������ ����

// Heap Memory Free Macro
//// STL Version
////// ������� for�� �̿�; Swift ������� �� ����
#define DELETEALL_STL(STL)      \
for (auto& Element : STL)       \
{                               \
    delete Element;             \
}                               \
STL.clear();

//// STL Map Version
////// ������� for�� �̿�; Swift ������� �� ����
#define DELETEALL_STL_MAP(STL)      \
for (auto& Element : STL)           \
{                                   \
    if (nullptr != Element.second)	\
    {                               \
        delete Element.second;      \
        Element.second = nullptr;   \
    }                               \
}                                   \
STL.clear();

//// Fixed Array Version
#define DELETEALL_FIXEDARRAY_HEAP(FixedArray, _END)     \
for (int i = 0; i < _END; ++i)                          \
{                                                       \
    if (FixedArray[i] != nullptr)                       \
    {                                                   \
        delete FixedArray[i];                           \
        FixedArray[i] = nullptr;                        \
    }                                                   \
}


// ���ν����� ���� �����
// ���̺귯������ constexpr�� ���Ұ��ϹǷ� ���⿡ ����
//// �ٸ� ������ ���
////// Unreal Engine | 0.0001f ���� ����
////// Unity Engine | 0.0001f ���� �� ���
////// ���� ����� ���� ��� ������ ����Ͽ� 0.001f�� ������ �Ѵ�
#define G_LL_ZeroScaleFloat 0.001f