#pragma once

// ����ŷ� ���� ���� WinAPI �޽��� �ڽ��� ������ ���� ����
// ����� �ÿ��� �۵��ϵ��� �ۼ�
#ifdef _DEBUG
#define POPUP(title, message) MessageBox(nullptr, message, title, MB_OK | MB_ICONINFORMATION)
#else
#define POPUP(title, message)
#endif

// �̱���, �ϳ��� ��ũ�� �������� �ٳѱ��� �Ϸ��� '\'�� ��� �ϸ�, ��ũ���� ()���� ���ڴ� �ϳ��� ��ũ�� �ȿ��� ���̴� ��ū�� ��
// ���⼭ "friend class singleton<type>"�� �� ������, ����ؼ� �̱��� ������ �����Ͽ� ����� �� ������ private�� �����ϱ� ������
// ���� ������ �����ϴ� �����̹Ƿ�, �ڿ� ';'�� ���� ������ ����
#define SINGLE(_type)	friend class C_Singleton<_type>; \
_type& operator = (const _type& _Other) = delete; \
_type(); \
_type(const _type& _Origin) = delete; \
~_type();