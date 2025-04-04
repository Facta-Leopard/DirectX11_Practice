#pragma once

template<typename T>
class C_Singleton
{
private:
	C_Singleton()
	{
		// 왜 typedef를 쓰는지 모르겠음.. using이 더 나으니까, 앞으로는 이 걸로 대체하자
		// before: typedef void(*FUNC)(void);
		// after: using FUNC = void(*)(void);
		// 그리고, 기존 코드는 static을 썻음에도 atexit의 인자를 typedef로 함수포인터를 정의해서 넘겼는데..
		// 이건 필요없는 행위인 듯하니 여기서는 제외하는 걸로 개선하자
		// 덕분에, 람다함수 및 고차함수에 대한 개념을 확실히 익혔고, 함수형 프로그래밍 형태로 코딩도 가능할 듯 싶다
		atexit(C_Singleton::MF_Destory);
	}

	~C_Singleton()
	{
		// T*처럼 포인터로 하지 않으면 atexit()가 아니라, 직접 소멸자에서 사라지도록 해도 문제가 없을 것 같은데..
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

// 정적 멤버는 클래스 내부에서만 속하는 것이 아니므로, 초기화는 클래스 밖에서 해야 함
template<typename T>
T* C_Singleton<T>::S_Instance = nullptr;