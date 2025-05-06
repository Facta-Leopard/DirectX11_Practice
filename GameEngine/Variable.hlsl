// HLSL�� #pragma once ����� �Ұ����ϹǷ�, `C`��Ÿ�Ϸ� �Ͽ��� ��

#ifndef _VARIABLE
#define _VARIABLE

// HLSL�� boolean�� �����Ƿ�, BOOL�� �޴� ���� uint�� �޾Ƽ� ���� ������ �Ѵ�.

// Structure
struct HLSL_DS_Particle
{
    // ���� ����
    float4 LocalPos;                // 16; ���� ������Ʈ�� ������ ��� ��ǥ
    float4 WorldPos;                // 16; ��ƼŬ�� ���� ��ǥ
    float4 WorldInitScale;          // 16; ��ƼŬ ���� ũ��
    float4 WorldScale;              // 16; ��ƼŬ ���� ũ��
    float4 Color;                   // 16; ��ƼŬ ����

    // ��ü ����
    float4 Force;                   // 16; ��ƼŬ�� �־����� �ִ� ���� ����
    float4 Velocity;                // 16; ��ƼŬ �ӵ�
    float Mass;                     // 16; ��ƼŬ ����
        
    // ������ ����
    float3 NoiseForceDir;           // 12; ����� Noise Forec �� ����
    float NoiseForceAccTime;        // 4; Noise Force �ҿ� �����ϴ� ���� �ð�
    
    // �ð� ����
    float Age;                      // 4; ��ƼŬ ����, Age �� Life �� �����ϸ� ������ ���� ��
    float Life;                     // 4; ��ƼŬ �ִ� ����
    float NormalizedAge;            // 4; ��ü ���� ���, ���� Age ����. �ڽ��� Age �� Life ��� ����ȭ �� ��

    // �Ӽ� ����
    uint Active;                    // 4; ��ƼŬ Ȱ��ȭ ����; BOOL�� ���� ���� �޾Ƽ� ���� �뵵
    
    int PAD_Padding[3];             // 12; 
};

struct HLSL_DS_Particle_Desc
{
    // �ʱⰪ ����
    //// ����
    int SpawnCount;                         // 4; ���� ����
    float SpawnRate;                        // 4; �ʴ� ��ƼŬ ������
    float4 StartColor;                      // 16; �ʱ� ��ƼŬ ����
    float3 MinScale;                        // 12; ���� �� �ּ� ũ��
    float3 MaxScale;                        // 12; ���� �� �ִ� ũ��
    float MinLife;                          // 4; ���� �� �ּ� �ֱ�
    float MaxLife;                          // 4; ���� �� �ִ� �ֱ�
    uint SpawnShape;                        // 4; Box(0), Sphere(1)
    float3 SpawnShapeScale;                 // 12; ���� ũ��
    uint SpaceType;                         // 4; Local(0), World(1)
    
    //// ���
    uint BlockSpawnShape;                   // 4; Box(0), Sphere(1)
    float3 BlockSpawnShapeScale;            // 12; SpawnShapeScale.x == Radius
    
    // ���� ����
    //// ����Ʈ
    uint SpawnBurstCount;                   // 4; Burst�� �߻���Ű�� Particle ��
    uint SpawnBurstRepeat;                  // 4; Burst Ƚ��
    float SpawnBurstRepeatTime;             // 4; Burst ����
    
    // ���� ����
    //// ũ��
    float StartScale;                       // 4; ���� ũ��
    float EndScale;                         // 4; �� ũ��

    //// �ӵ�
    ////// ����
    uint AddVelocityType;                   // 4; Random(0), FromCenter(1), ToCenter(2), Fixed(4) 
    float3 AddVelocityFixedDirection;       // 12; ���� ����
    float AddMinimumSpeed;                  // 4; �ּ� �߰� �ӵ�
    float AddMaximumSpeed;                  // 4; �ִ� �߰� �ӵ�
            
    ////// ���� ���
    float DecelNormalizedAge;               // 4; ���� �ӵ�
    float LimitSpeed;                       // 4; ���� �ӵ�
    
    // ������ ����
    float NoiseForceTerm;                   // 4; Noise Force ���� ��
    float NoiseForceScale;                  // 4; Noise Force ũ��
    
    // ������ ����
    float4 EndColor;                        // 16; ��ƼŬ ���� ����    
    uint FadeOut;                           // 4; �Ф��̵�ƿ� ���� Off(0), On(1)
    float StartRatio;                       // 4; FadeOut ȿ���� ���۵Ǵ� Normalized Age ����
    uint VelocityAlignment;                 // 4; �ӵ� ���� ���� Off(0), On(1)
    uint CrossMesh;                         // 4; �������� �޽� �߰� ���� Off(0), On(1)
    
    // �߰� ������
    float3 ObjectWorldPosition;             // 12;
    
    int Module[7]; // 28;
};

struct HLSL_DS_Light2D          // 64; 16 * 4
{
    int LightType;              // 4; ���� ����
    
    float3 WorldPos;            // 12; ���� ��ġ
    
    float4 Color;               // 16;���� ����; ����! Alpha ���� ����(Intensity)�� ���!; ����, ��ó���� ���(Bloom) �� ȿ���� �̿��� �� ����� �� ����
    
    float Radius;               // 4; ���� ����, �ݰ�
    
    float3 Direction;           // 12; ������ ����
    
    float Angle;                // 4; ���� ����(����Ʈ ����Ʈ)
    
    float3 PAD_Padding;         // 12; �е�
};


// Shader Only
// ����! �ڵ����� �������ִ� �� ����, �������� �޸� ������ ���缭 ����ϴ� �Ϳ� ���Ǹ� �����!
//// Vertex ����
///// Vertex In
struct HLSL_DS_Vertex_INPUT
{
    // ����! ���� ��ȯ�� ���̼� �� ���ϼ��� ���� ��ġ������ xyz�� �ƴ� xyzw�� ����!
    // ����, xyz�� ������ w���� ���� Ȱ���� �� �����غ��� ���� ���� ��
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