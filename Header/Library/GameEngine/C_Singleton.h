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
	static T* S_Instance;

public:
	static T* SF_GetInstance()
	{
		S_Instance = new T;
		return S_Instance;
	}

	static void MF_Destory()
	{
		S_Instance = nullptr;
	}
};

// ���� ����� Ŭ���� ���ο����� ���ϴ� ���� �ƴϹǷ�, �ʱ�ȭ�� Ŭ���� �ۿ��� �ؾ� ��
template<typename T>
T* C_Singleton<T>::S_Instance = nullptr;