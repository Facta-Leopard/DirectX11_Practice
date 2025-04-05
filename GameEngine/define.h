#pragma once

// WinAPI �޽��� �ڽ��� ������ ���� ����
#ifdef _DEBUG
#define POPUP_DEBUG(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)
#endif

#define POPUP(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)

// �̱���, �ϳ��� ��ũ�� �������� �ٳѱ��� �Ϸ��� '\'�� ��� �ϸ�, ��ũ���� ()���� ���ڴ� �ϳ��� ��ũ�� �ȿ��� ���̴� ��ū�� ��
// ���⼭ "friend class singleton<type>"�� �� ������, ����ؼ� �̱��� ������ �����Ͽ� ����� �� ������ private�� �����ϱ� ������
// ���� ������ �����ϴ� �����̹Ƿ�, �ڿ� ';'�� ���� ������ ����
#define SINGLE(Class)	friend class C_Singleton<Class>; \
public: \
Class& operator = (const Class& _Other) = delete; \
Class(); \
Class(const Class& _Origin) = delete; \
~Class();