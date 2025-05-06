// HLSL�� #pragma once ����� �Ұ����ϹǷ�, `C`��Ÿ�Ϸ� �Ͽ��� ��

#ifndef _BINDING
#define _BINDING

#include "Variable.hlsl"

// ������ ����� CPU�������� �����Ѵ�.
//// row_major ���!
//// ����, ��ȯ�� ���� ũ�ν� �÷������� ������ ��쿡�� column_major�� ��ü���� ������ �ʿ���!
//// ����! HLSL�� GLSL�� ��ȯ�� �� ��쿡�� column_major ������ ����Ͽ��� ��!

// ����! HLSL���� �ڵ����� �������شٰ� �ص�, ������ 16����Ʈ�� �������� �����Ѵ�!

// ��� ��������(b#)
// ����! ��� ��������(HLSL 5.0 ����)�� 4096���� �ִ����� Direct 11������ 14���� ��밡����!
// cbuffer ���
//// ��� �������� 0��: �ػ�
cbuffer GPU_RESOLUTION : register(b0)     // 16
{
    float2 Bind_Resolution;               // 8
    
    // Padding
    float2 PAD_Resoultion;                // 8
}

//// ��� �������� 1��: �ð�
cbuffer GPU_TIME : register(b1)     // 16
{
    float Bind_Time;                // 4
    float Bind_EngineTime;          // 4
    
    float Bind_DeltaTIme;           // 4
    float Bind_EngineDeltaTIme;     // 4
}

//// ��� �������� 2��: ��ġ
cbuffer GPU_TRANSFORM : register(b2)                    // 320: 64 * 5
{
    row_major matrix Bind_WorldMatrix;                  // 64
    row_major matrix Bind_ViewMatrix;                   // 64
    row_major matrix Bind_ProjectionMatrix;             // 64
    
    row_major matrix Bind_WorldViewMatrix;              // 64
    row_major matrix Bind_WorldViewProjectionMatrix;    // 64
}

//// ��� �������� 3��: ����
cbuffer GPU_MATERIAL : register(b3)   // 400: 16 * 25
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
    
    // 32
    // �ؽ�ó ��������(t#) ���� ���ε� ����
    //// �ؽ�ó ����
    uint Bind_Texture_t0;                   // 4
    uint Bind_Texture_t1;                   // 4
    uint Bind_Texture_t2;                   // 4
    uint Bind_Texture_t3;                   // 4
    
    //// ������ �ؽ�ó ����
    uint Bind_Texture_Noise_t10;            // 4
    uint Bind_Texture_Noise_t11;            // 4
    uint Bind_Texture_Noise_t12;            // 4
    uint Bind_Texture_Noise_t13;            // 4
}

//// ��� �������� 10��: ����
cbuffer GPU_LIGHT : register(b10)       // 16
{
    int Bind_Light2DCount;              // 4
    int Bind_Light3DCount;              // 4
    
    // Padding
    int PAD_Light2DCount;               // 4
    int PAD_Light3DCount;               // 4
}


// �ؽ�ó ��������(t#); ���� -> cbuffer GPU_MATERIAL : register(b3)
// Shader Resource View�� ����
// ����! �ؽ�ó ��������(HLSL 5.0 ����)�� �ִ� 128�� ����(DirectX 12�� ��õ������ ����)
//// Texture ����
Texture2D GPU_Texture_t0 : register(t0);
Texture2D GPU_Texture_t1 : register(t1);
Texture2D GPU_Texture_t2 : register(t2);
Texture2D GPU_Texture_t3 : register(t3);


//// Noise Texture ����
//// ������ ���� t10���� ������ ����
//// ����, Ȯ��� �������� ���� �缳��
Texture2D GPU_Texture_Noise_t10 : register(t10);
Texture2D GPU_Texture_Noise_t11 : register(t11);
Texture2D GPU_Texture_Noise_t12 : register(t12);
Texture2D GPU_Texture_Noise_t13 : register(t13);

//// PostProcess Texture ����
//// ������ ���� t20���� ��ó�� ����
//// ����, Ȯ��� �������� ���� �缳��
////// ���ȿ��
Texture2D GPU_Texture_PostProcess_t20 : register(t20);

////// ����ȿ��
Texture2D GPU_Texture_PostProcess_t21 : register(t21);

////// ������ȿ��1
Texture2D GPU_Texture_PostProcess_t22 : register(t22);

////// ������ȿ��2
Texture2D GPU_Texture_PostProcess_t23 : register(t23);


//// 2D ���� ����
//// ������ ���� t100���� ���� ����
//// ����, Ȯ��� �������� ���� �缳��
StructuredBuffer<HLSL_DS_Light2D> GPU_DS_Light2D_t100 : register(t100);
StructuredBuffer<HLSL_DS_Light2D> GPU_DS_Light2D_t101 : register(t101);

// ���÷� ��������(s#)
// Pixel Shader�� ����
// ����! ���÷� ��������(HLSL 5.0 ����)�� �ִ� 16������ ����(DirectX 12�� 2048������ ����)
//// ���÷� ����
SamplerState GPU_Sampler_s0 : register(s0);
SamplerState GPU_Sampler_s1 : register(s1);


// ������� ��������(u#)
// Compute Shader�� ����
// ����! ������� ��������(HLSL 5.0 ����)�� �ȼ� ���̴�(PS)������ 8��, ��ǻƮ ���̴�(CS)������ 64������ ����(DirectX 12�� ��õ������ ����)
//// ��ǻƮ ���̴� ����



#endif