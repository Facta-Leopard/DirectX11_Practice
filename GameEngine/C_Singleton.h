#pragma once

template<typename T>
class C_Singleton
{
protected:
	C_Singleton()
	{
		// �� typedef�� ������ �𸣰���.. using�� �� �����ϱ�, �����δ� �� �ɷ� ��ü����
		// before: typedef void(*FUNC)(void);
		// after: using FUNC = void(*)(void);
		// �׸���, ���� �ڵ�� static�� �������� atexit�� ���ڸ� typedef�� �Լ������͸� �����ؼ� �Ѱ�µ�,
		// static�� ����, �ν��Ͻ��� ������ �ʰ� �� �� ������ �̰� �ʿ���� ������ ��?
		// ���⼭�� �����ϴ� �ɷ� �����ϴ� �ɷ� ����
		// ���п�, �����Լ� �� �����Լ��� ���� ������ Ȯ���� ������, �Լ��� ���α׷��� ���·� �ڵ��� ������ ��?
		atexit(C_Singleton::SF_Destory);
	}

	~C_Singleton()
	{
		// T*ó�� �����ͷ� ���� ������ atexit()�� �ƴ϶�, ���� �Ҹ��ڿ��� ��������� �ص� ������ ���� �� ������..
	}

private:
	// ����!! static�� ����� getter�� ���ܿ����� getter�� static�̾�� ��!
	static T* S_Instance; // Template T*

public:
	// ����!! static�� ����� getter�� ���ܿ����� getter�� static�̾�� ��!
	static T* SF_GetInstance()
	{
		if (nullptr == S_Instance)
		{
			S_Instance = new T;
		}
		return S_Instance;
	}

	static void SF_Destory()
	{
		if (nullptr != S_Instance)
		{
			delete S_Instance;
	}	
		S_Instance = nullptr;
	}
};

// ���� ����� Ŭ���� ���ο����� ���ϴ� ���� �ƴϹǷ�, �ʱ�ȭ�� Ŭ���� �ۿ��� �ؾ� ��
// �׸��� ���ø��̹Ƿ� ������Ͽ��� ��
// �ٵ�, ���� ���ϸ��� .cpp�� ����� �� ������ ����? ����? ���غҰ���
template<typename T>
T* C_Singleton<T>::S_Instance = nullptr;