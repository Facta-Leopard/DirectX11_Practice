#include "Binding.hlsl"



// ��ó�� �κ�
//// ����ȭ ����
////// ���ȿ��
float4 PS_PostProcess_BlackAndWhite(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t20.Sample(GPU_Sampler_s1, _INPUT.UV);
    
    // ���ȿ��
    OUTPUTCOLOR.rgb = (OUTPUTCOLOR.r + OUTPUTCOLOR.g + OUTPUTCOLOR.b) / 3.f;
    
    // a���� Ȱ���Ͽ� ���� ����
    OUTPUTCOLOR.rgb *= OUTPUTCOLOR.a;
    
    return OUTPUTCOLOR;
}

////// ����ȿ��
float4 PS_PostProcess_RedBoost(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t21.Sample(GPU_Sampler_s1, _INPUT.UV);
    
    // ������ ����
    // a���� Ȱ���Ͽ� ���� ����
    float T_RedIntensity = OUTPUTCOLOR.a * 0.5f;
    OUTPUTCOLOR.r += OUTPUTCOLOR.r * T_RedIntensity;
    OUTPUTCOLOR.g *= 1.f - T_RedIntensity; // �ʷ� ��ȭ
    OUTPUTCOLOR.b *= 1.f - T_RedIntensity; // �Ķ� ��ȭ

    // a���� Ȱ���Ͽ� ���� ����
    OUTPUTCOLOR.rgb *= OUTPUTCOLOR.a;
    
    return OUTPUTCOLOR;
}


//// ������ ȿ������
////// �����¿� ��鸲
float4 PS_PostProcess_Noise0(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float2 T_UV = _INPUT.UV;
    
    // ������ �ؽ��� t10�� ���� ���,
    if (Bind_Texture_Noise_t10)
    {
        // ������ �ؽ�ó ���ø�
        float4 T_NoiseColor = GPU_Texture_Noise_t10.Sample(GPU_Sampler_s0, T_UV + float2(Bind_EngineTime * 0.1f, 0.f)).rgba;
        
        // UV��ǥ�� ������ �����Ƿ�, -0.5f�� �༭ �߾��� ������ �����
        float2 T_NoiseUV = T_NoiseColor.xy - 0.5f; // -0.5 ~ 0.5f;       
        
        // ������ �������� ����
        // ����, ������ �� ������ ������ �� �ֵ��� �� ��
        T_NoiseUV *= 0.1f;
        
        // ������ �ؽ�ó a���� ������ ���
        T_NoiseUV *= T_NoiseColor.a;
        
        T_UV += T_NoiseUV;
        
        // UV(0.f-1.f ����)��ǥ�� ����� �� ���, ����
        if (T_UV.x < 0.f || 1.f < T_UV.x 
            || T_UV.y < 0.f || 1.f < T_UV.y)
        {
            T_UV = _INPUT.UV;
        }
    }
    
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t22.Sample(GPU_Sampler_s1, T_UV);
    
    return OUTPUTCOLOR;
}

////// �¿�θ� ��鸲
float4 PS_PostProcess_Noise1(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float2 T_UV = _INPUT.UV;
    
    // ������ �ؽ��� t11�� ���� ���,
    if (Bind_Texture_Noise_t11)
    {
        // ������ �ؽ�ó ���ø�
        float4 T_NoiseColor = GPU_Texture_Noise_t11.Sample(GPU_Sampler_s0, T_UV + float2(Bind_EngineTime * 0.1f, 0.f)).rgba;
        
        // UV��ǥ�� ������ �����Ƿ�, -0.5f�� �༭ �߾��� ������ �����
        float2 T_NoiseUV = ((T_NoiseColor.x - 0.5f), 0.f); // -0.5 ~ 0.5f;       
        
        // ������ �������� ����
        // ����, ������ �� ������ ������ �� �ֵ��� �� ��
        T_NoiseUV *= 0.1f;
        
        // ������ �ؽ�ó a���� ������ ���
        T_NoiseUV *= T_NoiseColor.a;
        
        T_UV += T_NoiseUV;
        
        // UV(0.f-1.f ����)��ǥ�� ����� �� ���, ����
        if (T_UV.x < 0.f || 1.f < T_UV.x 
            || T_UV.y < 0.f || 1.f < T_UV.y)
        {
            T_UV = _INPUT.UV;
        }
    }
    
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t23.Sample(GPU_Sampler_s1, T_UV);
    
    return OUTPUTCOLOR;
}

////// ���Ϸθ� ��鸲
float4 PS_PostProcess_Noise2(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float2 T_UV = _INPUT.UV;
    
    // ������ �ؽ��� t12�� ���� ���,
    if (Bind_Texture_Noise_t12)
    {
        // ������ �ؽ�ó ���ø�
        float4 T_NoiseColor = GPU_Texture_Noise_t12.Sample(GPU_Sampler_s0, T_UV + float2(Bind_EngineTime * 0.1f, 0.f)).rgba;
        
        // UV��ǥ�� ������ �����Ƿ�, -0.5f�� �༭ �߾��� ������ �����
        float2 T_NoiseUV = float2(0.f, (T_NoiseColor.y - 0.5f)); // -0.5 ~ 0.5f;       
        
        // ������ �������� ����
        // ����, ������ �� ������ ������ �� �ֵ��� �� ��
        T_NoiseUV *= 0.1f;
        
        // ������ �ؽ�ó a���� ������ ���
        T_NoiseUV *= T_NoiseColor.a;
        
        T_UV += T_NoiseUV;
        
        // UV(0.f-1.f ����)��ǥ�� ����� �� ���, ����
        if (T_UV.x < 0.f || 1.f < T_UV.x 
            || T_UV.y < 0.f || 1.f < T_UV.y)
        {
            T_UV = _INPUT.UV;
        }
    }
    
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t23.Sample(GPU_Sampler_s1, T_UV);
    
    return OUTPUTCOLOR;
}

////// �밢������ ��鸲
float4 PS_PostProcess_Noise3(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float2 T_UV = _INPUT.UV;
    
    // ������ �ؽ��� t13�� ���� ���,
    if (Bind_Texture_Noise_t13)
    {
        // ������ �ؽ�ó ���ø�
        float4 T_NoiseColor = GPU_Texture_Noise_t13.Sample(GPU_Sampler_s0, T_UV + float2(Bind_EngineTime * 0.1f, 0.f)).rgba;
        
        // UV��ǥ�� ������ �����Ƿ�, -0.5f�� �༭ �߾��� ������ �����
        float2 T_NoiseUV = float2((T_NoiseColor.x - 0.5f), (T_NoiseColor.x - 0.5f)); // -0.5 ~ 0.5f;       
        
        // ������ �������� ����
        // ����, ������ �� ������ ������ �� �ֵ��� �� ��
        T_NoiseUV *= 0.1f;
        
        // ������ �ؽ�ó a���� ������ ���
        T_NoiseUV *= T_NoiseColor.a;
        
        T_UV += T_NoiseUV;
        
        // UV(0.f-1.f ����)��ǥ�� ����� �� ���, ����
        if (T_UV.x < 0.f || 1.f < T_UV.x 
            || T_UV.y < 0.f || 1.f < T_UV.y)
        {
            T_UV = _INPUT.UV;
        }
    }
    
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t23.Sample(GPU_Sampler_s1, T_UV);
    
    return OUTPUTCOLOR;
}