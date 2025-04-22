#pragma once

template<typename T>
class C_Singleton
{
protected:
	C_Singleton()
	{
		// 왜 typedef를 쓰는지 모르겠음.. using이 더 나으니까, 앞으로는 이 걸로 대체하자
		// before: typedef void(*FUNC)(void);
		// after: using FUNC = void(*)(void);
		// 그리고, 기존 코드는 static을 썻음에도 atexit의 인자를 typedef로 함수포인터를 정의해서 넘겼는데,
		// static을 쓰면, 인스턴스를 통하지 않고 쓸 수 있으니 이건 필요없는 행위인 듯?
		// 여기서는 제외하는 걸로 개선하는 걸로 하자
		// 덕분에, 람다함수 및 고차함수에 대한 개념을 확실히 익혔고, 함수형 프로그래밍 형태로 코딩도 가능할 듯?
		atexit(C_Singleton::SF_Destory);
	}

	~C_Singleton()
	{
		// T*처럼 포인터로 하지 않으면 atexit()가 아니라, 직접 소멸자에서 사라지도록 해도 문제가 없을 것 같은데..
	}

protected:
	// 유의!! static인 멤버를 getter로 땡겨오려면 getter도 static이어야 함!

	inline static T* S_Instance = nullptr;

public:
	// 유의!! static인 멤버를 getter로 땡겨오려면 getter도 static이어야 함!
	inline static T* SF_Get_Instance()
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

// C++17 기준: inline static 정적 멤버는 클래스 내부에서 정의 가능
// 따라서 별도의 .cpp 파일에 정의할 필요가 없으며, 헤더에 선언/정의 모두 포함시킬 수 있음