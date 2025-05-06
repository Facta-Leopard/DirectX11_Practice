// HLSL은 #pragma once 사용이 불가능하므로, `C`스타일로 하여야 함

#ifndef _VARIABLE
#define _VARIABLE

// HLSL은 boolean이 없으므로, BOOL로 받는 값을 uint로 받아서 쓰는 것으로 한다.

// Structure
struct HLSL_DS_Particle
{
    // 물리 관련
    float4 LocalPos;                // 16; 소유 오브젝트로 부터의 상대 좌표
    float4 WorldPos;                // 16; 파티클의 월드 좌표
    float4 WorldInitScale;          // 16; 파티클 스폰 크기
    float4 WorldScale;              // 16; 파티클 월드 크기
    float4 Color;                   // 16; 파티클 색상

    // 강체 관련
    float4 Force;                   // 16; 파티클에 주어지고 있는 힘의 총합
    float4 Velocity;                // 16; 파티클 속도
    float Mass;                     // 16; 파티클 질량
        
    // 노이즈 관련
    float3 NoiseForceDir;           // 12; 적용된 Noise Forec 의 방향
    float NoiseForceAccTime;        // 4; Noise Force 텀에 도달하는 누적 시간
    
    // 시간 관련
    float Age;                      // 4; 파티클 나이, Age 가 Life 에 도달하면 수명이 다한 것
    float Life;                     // 4; 파티클 최대 수명
    float NormalizedAge;            // 4; 전체 수명 대비, 현재 Age 비율. 자신의 Age 를 Life 대비 정규화 한 값

    // 속성 관련
    uint Active;                    // 4; 파티클 활성화 여부; BOOL로 받은 값을 받아서 쓰는 용도
    
    int PAD_Padding[3];             // 12; 
};

struct HLSL_DS_Particle_Desc
{
    // 초기값 관련
    //// 입자
    int SpawnCount;                         // 4; 입자 개수
    float SpawnRate;                        // 4; 초당 파티클 생성량
    float4 StartColor;                      // 16; 초기 파티클 색상
    float3 MinScale;                        // 12; 생성 시 최소 크기
    float3 MaxScale;                        // 12; 생성 시 최대 크기
    float MinLife;                          // 4; 생성 시 최소 주기
    float MaxLife;                          // 4; 생성 시 최대 주기
    uint SpawnShape;                        // 4; Box(0), Sphere(1)
    float3 SpawnShapeScale;                 // 12; 스폰 크기
    uint SpaceType;                         // 4; Local(0), World(1)
    
    //// 블록
    uint BlockSpawnShape;                   // 4; Box(0), Sphere(1)
    float3 BlockSpawnShapeScale;            // 12; SpawnShapeScale.x == Radius
    
    // 스폰 관련
    //// 버스트
    uint SpawnBurstCount;                   // 4; Burst시 발생시키는 Particle 수
    uint SpawnBurstRepeat;                  // 4; Burst 횟수
    float SpawnBurstRepeatTime;             // 4; Burst 간격
    
    // 물리 관련
    //// 크기
    float StartScale;                       // 4; 시작 크기
    float EndScale;                         // 4; 끝 크기

    //// 속도
    ////// 가속
    uint AddVelocityType;                   // 4; Random(0), FromCenter(1), ToCenter(2), Fixed(4) 
    float3 AddVelocityFixedDirection;       // 12; 가속 방향
    float AddMinimumSpeed;                  // 4; 최소 추가 속도
    float AddMaximumSpeed;                  // 4; 최대 추가 속도
            
    ////// 감속 모듈
    float DecelNormalizedAge;               // 4; 감속 속도
    float LimitSpeed;                       // 4; 제한 속도
    
    // 노이즈 관련
    float NoiseForceTerm;                   // 4; Noise Force 변경 텀
    float NoiseForceScale;                  // 4; Noise Force 크기
    
    // 렌더링 관련
    float4 EndColor;                        // 16; 파티클 최종 색상    
    uint FadeOut;                           // 4; ㅠㅔ이드아웃 여부 Off(0), On(1)
    float StartRatio;                       // 4; FadeOut 효과가 시작되는 Normalized Age 지점
    uint VelocityAlignment;                 // 4; 속도 정렬 여부 Off(0), On(1)
    uint CrossMesh;                         // 4; 십자형태 메쉬 추가 여부 Off(0), On(1)
    
    // 추가 데이터
    float3 ObjectWorldPosition;             // 12;
    
    int Module[7]; // 28;
};

struct HLSL_DS_Light2D          // 64; 16 * 4
{
    int LightType;              // 4; 광원 종류
    
    float3 WorldPos;            // 12; 광원 위치
    
    float4 Color;               // 16;광원 색상; 유의! Alpha 값을 강도(Intensity)로 사용!; 향후, 후처리에 블룸(Bloom) 등 효과에 이용할 시 사용할 수 있음
    
    float Radius;               // 4; 광원 범위, 반경
    
    float3 Direction;           // 12; 광원의 방향
    
    float Angle;                // 4; 광원 각도(스포트 라이트)
    
    float3 PAD_Padding;         // 12; 패딩
};


// Shader Only
// 유의! 자동으로 정렬해주는 거 말고, 수동으로 메모리 정렬을 맞춰서 사용하는 것에 주의를 맞춘다!
//// Vertex 전용
///// Vertex In
struct HLSL_DS_Vertex_INPUT
{
    // 유의! 향후 변환의 용이성 및 통일성을 위해 위치정보를 xyz가 아닌 xyzw로 썼음!
    // 향후, xyz를 제외한 w값을 어찌 활용할 지 생각해보는 것이 좋을 듯
    float4 vPos : Position;
    float4 vUV  : UVPosition;
};

////// Vertex Out
struct HLSL_DS_Vertex_OUTPUT
{
    float4 vPos : Position;
    float4 vUV  : UVPosition;
};



// Variable


#endif