#pragma once

template<typename T>
class C_Singleton
{
private:
	C_Singleton()
	{
		// �� typedef�� ������ �𸣰���.. using�� �� �����ϱ�, �����δ� �� �ɷ� ��ü����
		// before: typedef void(*FUNC)(void);
		// after: using FUNC = void(*)(void);
		// �׸���, ���� �ڵ�� static�� �������� atexit�� ���ڸ� typedef�� �Լ������͸� �����ؼ� �Ѱ�µ�..
		// �̰� �ʿ���� ������ ���ϴ� ���⼭�� �����ϴ� �ɷ� ��������
		// ���п�, �����Լ� �� �����Լ��� ���� ������ Ȯ���� ������, �Լ��� ���α׷��� ���·� �ڵ��� ������ �� �ʹ�
		atexit(C_Singleton::MF_Destory);
	}

	~C_Singleton()
	{
		// T*ó�� �����ͷ� ���� ������ atexit()�� �ƴ϶�, ���� �Ҹ��ڿ��� ��������� �ص� ������ ���� �� ������..
	}

private:
	static T* s_Instance;

public:
	inline T* MF_GetInstance()
	{
		s_Instance = new T;
		return s_Instance;
	}

	inline void MF_Destory()
	{
		s_Instance = nullptr;
	}
};

// ���� ����� Ŭ���� ���ο����� ���ϴ� ���� �ƴϹǷ�, �ʱ�ȭ�� Ŭ���� �ۿ��� �ؾ� ��
template<typename T>
T* C_Singleton<T>::s_Instance = nullptr;