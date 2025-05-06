#include "Binding.hlsl"



// 후처리 부분
//// 색깔변화 관련
////// 흑백효과
float4 PS_PostProcess_BlackAndWhite(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t20.Sample(GPU_Sampler_s1, _INPUT.UV);
    
    // 흑백효과
    OUTPUTCOLOR.rgb = (OUTPUTCOLOR.r + OUTPUTCOLOR.g + OUTPUTCOLOR.b) / 3.f;
    
    // a값을 활용하여 세기 조절
    OUTPUTCOLOR.rgb *= OUTPUTCOLOR.a;
    
    return OUTPUTCOLOR;
}

////// 붉은효과
float4 PS_PostProcess_RedBoost(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t21.Sample(GPU_Sampler_s1, _INPUT.UV);
    
    // 붉은색 강조
    // a값을 활용하여 세기 조절
    float T_RedIntensity = OUTPUTCOLOR.a * 0.5f;
    OUTPUTCOLOR.r += OUTPUTCOLOR.r * T_RedIntensity;
    OUTPUTCOLOR.g *= 1.f - T_RedIntensity; // 초록 약화
    OUTPUTCOLOR.b *= 1.f - T_RedIntensity; // 파랑 약화

    // a값을 활용하여 세기 조절
    OUTPUTCOLOR.rgb *= OUTPUTCOLOR.a;
    
    return OUTPUTCOLOR;
}


//// 노이즈 효과관련
////// 상하좌우 흔들림
float4 PS_PostProcess_Noise0(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float2 T_UV = _INPUT.UV;
    
    // 노이즈 텍스쳐 t10이 있을 경우,
    if (Bind_Texture_Noise_t10)
    {
        // 노이즈 텍스처 샘플링
        float4 T_NoiseColor = GPU_Texture_Noise_t10.Sample(GPU_Sampler_s0, T_UV + float2(Bind_EngineTime * 0.1f, 0.f)).rgba;
        
        // UV좌표는 음수가 없으므로, -0.5f을 줘서 중앙의 기준을 잡아줌
        float2 T_NoiseUV = T_NoiseColor.xy - 0.5f; // -0.5 ~ 0.5f;       
        
        // 노이즈 강도기준 설정
        // 향후, 조절할 수 있으면 조절할 수 있도록 할 것
        T_NoiseUV *= 0.1f;
        
        // 노이즈 텍스처 a값을 강도로 사용
        T_NoiseUV *= T_NoiseColor.a;
        
        T_UV += T_NoiseUV;
        
        // UV(0.f-1.f 범위)좌표를 벗어나게 될 경우, 조정
        if (T_UV.x < 0.f || 1.f < T_UV.x 
            || T_UV.y < 0.f || 1.f < T_UV.y)
        {
            T_UV = _INPUT.UV;
        }
    }
    
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t22.Sample(GPU_Sampler_s1, T_UV);
    
    return OUTPUTCOLOR;
}

////// 좌우로만 흔들림
float4 PS_PostProcess_Noise1(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float2 T_UV = _INPUT.UV;
    
    // 노이즈 텍스쳐 t11이 있을 경우,
    if (Bind_Texture_Noise_t11)
    {
        // 노이즈 텍스처 샘플링
        float4 T_NoiseColor = GPU_Texture_Noise_t11.Sample(GPU_Sampler_s0, T_UV + float2(Bind_EngineTime * 0.1f, 0.f)).rgba;
        
        // UV좌표는 음수가 없으므로, -0.5f을 줘서 중앙의 기준을 잡아줌
        float2 T_NoiseUV = ((T_NoiseColor.x - 0.5f), 0.f); // -0.5 ~ 0.5f;       
        
        // 노이즈 강도기준 설정
        // 향후, 조절할 수 있으면 조절할 수 있도록 할 것
        T_NoiseUV *= 0.1f;
        
        // 노이즈 텍스처 a값을 강도로 사용
        T_NoiseUV *= T_NoiseColor.a;
        
        T_UV += T_NoiseUV;
        
        // UV(0.f-1.f 범위)좌표를 벗어나게 될 경우, 조정
        if (T_UV.x < 0.f || 1.f < T_UV.x 
            || T_UV.y < 0.f || 1.f < T_UV.y)
        {
            T_UV = _INPUT.UV;
        }
    }
    
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t23.Sample(GPU_Sampler_s1, T_UV);
    
    return OUTPUTCOLOR;
}

////// 상하로만 흔들림
float4 PS_PostProcess_Noise2(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float2 T_UV = _INPUT.UV;
    
    // 노이즈 텍스쳐 t12이 있을 경우,
    if (Bind_Texture_Noise_t12)
    {
        // 노이즈 텍스처 샘플링
        float4 T_NoiseColor = GPU_Texture_Noise_t12.Sample(GPU_Sampler_s0, T_UV + float2(Bind_EngineTime * 0.1f, 0.f)).rgba;
        
        // UV좌표는 음수가 없으므로, -0.5f을 줘서 중앙의 기준을 잡아줌
        float2 T_NoiseUV = float2(0.f, (T_NoiseColor.y - 0.5f)); // -0.5 ~ 0.5f;       
        
        // 노이즈 강도기준 설정
        // 향후, 조절할 수 있으면 조절할 수 있도록 할 것
        T_NoiseUV *= 0.1f;
        
        // 노이즈 텍스처 a값을 강도로 사용
        T_NoiseUV *= T_NoiseColor.a;
        
        T_UV += T_NoiseUV;
        
        // UV(0.f-1.f 범위)좌표를 벗어나게 될 경우, 조정
        if (T_UV.x < 0.f || 1.f < T_UV.x 
            || T_UV.y < 0.f || 1.f < T_UV.y)
        {
            T_UV = _INPUT.UV;
        }
    }
    
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t23.Sample(GPU_Sampler_s1, T_UV);
    
    return OUTPUTCOLOR;
}

////// 대각선으로 흔들림
float4 PS_PostProcess_Noise3(HLSL_VS_OUTPUT _INPUT) : SV_Target
{
    float2 T_UV = _INPUT.UV;
    
    // 노이즈 텍스쳐 t13이 있을 경우,
    if (Bind_Texture_Noise_t13)
    {
        // 노이즈 텍스처 샘플링
        float4 T_NoiseColor = GPU_Texture_Noise_t13.Sample(GPU_Sampler_s0, T_UV + float2(Bind_EngineTime * 0.1f, 0.f)).rgba;
        
        // UV좌표는 음수가 없으므로, -0.5f을 줘서 중앙의 기준을 잡아줌
        float2 T_NoiseUV = float2((T_NoiseColor.x - 0.5f), (T_NoiseColor.x - 0.5f)); // -0.5 ~ 0.5f;       
        
        // 노이즈 강도기준 설정
        // 향후, 조절할 수 있으면 조절할 수 있도록 할 것
        T_NoiseUV *= 0.1f;
        
        // 노이즈 텍스처 a값을 강도로 사용
        T_NoiseUV *= T_NoiseColor.a;
        
        T_UV += T_NoiseUV;
        
        // UV(0.f-1.f 범위)좌표를 벗어나게 될 경우, 조정
        if (T_UV.x < 0.f || 1.f < T_UV.x 
            || T_UV.y < 0.f || 1.f < T_UV.y)
        {
            T_UV = _INPUT.UV;
        }
    }
    
    float4 OUTPUTCOLOR = GPU_Texture_PostProcess_t23.Sample(GPU_Sampler_s1, T_UV);
    
    return OUTPUTCOLOR;
}