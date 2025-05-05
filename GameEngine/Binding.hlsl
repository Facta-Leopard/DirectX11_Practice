// HLSL은 #pragma once 사용이 불가능하므로, `C`스타일로 하여야 함

#ifndef _BINDING
#define _BINDING

#include "Variable.hlsl"

// 무조건 행렬은 CPU기준으로 정렬한다.
//// row_major 사용!
//// 향후, 변환을 통한 크로스 플랫폼으로 개조할 경우에는 column_major로 전체적인 개조가 필요함!
//// 유의! HLSL을 GLSL로 변환을 할 경우에는 column_major 형식을 사용하여야 함!

// 상수 레지스터(b#)
// 유의! 상수 레지스터(HLSL 5.0 기준)는 4096개가 최대지만 Direct 11에서는 14개만 사용가능함!
// cbuffer 사용
//// 상수 레지스터 0번: 해상도
cbuffer GPU_RESOLUTION : register(b0)     // 16
{
    float2 Resolution;                    // 8
    
    // Padding
    float2 PAD_Resoultion;                // 8
}

//// 상수 레지스터 1번: 시간
cbuffer GPU_TIME : register(b1) // 16
{
    float Time; // 4
    float EngineTime; // 4
    
    float DeltaTIme; // 4
    float EngineDeltaTIme; // 4
}

//// 상수 레지스터 2번: 위치
cbuffer GPU_TRANSFORM : register(b2)                  // 320: 64 * 5
{
    row_major matrix WorldMatrix;                     // 64
    row_major matrix ViewMatrix;                      // 64
    row_major matrix ProjectionMatrix;                // 64
    
    row_major matrix WorldViewMatrix;                 // 64
    row_major matrix WorldViewProjectionMatrix;       // 64
}

//// 상수 레지스터 3번: 재질
cbuffer GPU_MATERIAL : register(b3)     // 400: 16 * 25
{
    // 16
    int int_0;                        // 4
    int int_1;                        // 4
    int int_2;                        // 4
    int int_3;                        // 4
    
    // 16
    float float_0;                    // 4
    float float_1;                    // 4
    float float_2;                    // 4
    float float_3;                    // 4
    
    // 32
    float2 Vector2_0;                 // 8
    float2 Vector2_1;                 // 8
    float2 Vector2_2;                 // 8
    float2 Vector2_3;                 // 8
    
    // 64
    float4 Vector4_0;                 // 16
    float4 Vector4_1;                 // 16
    float4 Vector4_2;                 // 16
    float4 Vector4_3;                 // 16
    
    // 256
    row_major Matrix Matrix_0;        // 64
    row_major Matrix Matrix_1;        // 64
    row_major Matrix Matrix_2;        // 64
    row_major Matrix Matrix_3;        // 64
    
    // 16
    int BindingTextureSlot_0;         // 4
    int BindingTextureSlot_1;         // 4
    int BindingTextureSlot_2;         // 4
    int BindingTextureSlot_3;         // 4
}

//// 상수 레지스터 10번: 광원
cbuffer GPU_LIGHT : register(b10)       // 16
{
    int Light2DCount;                   // 4
    int Light3DCount;                   // 4
    
    // Padding
    int PAD_Light2DCount;               // 4
    int PAD_Light3DCount;               // 4
}


// 텍스처 레지스터(t#)
// Shader Resource View와 관련
// 유의! 텍스처 레지스터(HLSL 5.0 기준)는 최대 128개 가능(DirectX 12는 수천개까지 가능)
//// 텍스터 관련
Texture2D GPU_Texture_t0 : register(t0);
Texture2D GPU_Texture_t1 : register(t1);
Texture2D GPU_Texture_t2 : register(t2);
Texture2D GPU_Texture_t3 : register(t3);

//// 2D 광원 관련
//// 구분을 위해 t10부터 광원 설정
//// 향후, 확장시 레지스터 범위 재설정
StructuredBuffer<HLSL_DS_Light2D> GPU_Light2D_t100 : register(t10);

//// 후처리 관련
//// 구분을 위해 t100부터 후처리 설정
//// 향후, 확장시 레지스터 범위 재설정
Texture2D GPU_PostProcessTarget : register(t100);


// 샘플러 레지스터(s#)
// Pixel Shader와 관련
// 유의! 샘플러 레지스터(HLSL 5.0 기준)는 최대 16개까지 가능(DirectX 12는 2048개까지 가능)
//// 샘플러 관련
SamplerState GPU_Sampler_s0 : register(s0);
SamplerState GPU_Sampler_s1 : register(s1);


// 언오더드 레지스터(u#)
// Compute Shader와 관련
// 유의! 언오더드 레지스터(HLSL 5.0 기준)는 픽셀 쉐이더(PS)에서는 8개, 컴퓨트 쉐이더(CS)에서는 64개까지 가능(DirectX 12는 수천개까지 가능)
//// 컴퓨트 쉐이더 관련



#endif