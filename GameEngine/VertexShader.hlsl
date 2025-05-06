#include "Binding.hlsl"

HLSL_VS_OUTPUT HF_VS_PostProcess1(HLSL_VS_INPUT _INPUT)
{
    HLSL_VS_OUTPUT _OUTPUT = (HLSL_VS_OUTPUT) 0.f;
        
    _OUTPUT.Position = float4(_INPUT.Position * 2.f);
    _OUTPUT.UV = _INPUT.UV;
    
    return _OUTPUT;
}