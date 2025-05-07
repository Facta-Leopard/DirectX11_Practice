#include "Binding.hlsl"

// 老馆
HLSL_VS_OUTPUT  HF_VS_Basic(HLSL_VS_INPUT _INPUT)
{
    HLSL_VS_OUTPUT _OUTPUT = (HLSL_VS_OUTPUT) 0.f;
                
    _OUTPUT.Position = mul(float4(_INPUT.Position), Bind_WorldViewProjectionMatrix);
    _OUTPUT.WorldMatrix = mul(float4(_INPUT.Position), Bind_WorldMatrix);
    
    _OUTPUT.Color = _INPUT.Color;
    _OUTPUT.UV    = _INPUT.UV;
    
    return _OUTPUT;
}


// 饶贸府 包访
HLSL_VS_OUTPUT HF_VS_PostProcess1(HLSL_VS_INPUT _INPUT)
{
    HLSL_VS_OUTPUT _OUTPUT = (HLSL_VS_OUTPUT) 0.f;
        
    _OUTPUT.Position = float4(_INPUT.Position * 2.f);
    _OUTPUT.UV = _INPUT.UV;
    
    return _OUTPUT;
}

