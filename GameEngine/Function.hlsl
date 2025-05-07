// HLSL은 #pragma once 사용이 불가능하므로, `C`스타일로 하여야 함

#ifndef _FUNCTION
#define _FUNCTION

// 유의! HLSL 내에서는 전송되는 boolean도 uint로 받는 것으로 정했으니, HLSL 내에서도 bool대신 uint를 대신 쓰는 것으로 하자!
// 유의! HLSL 내에서 함수를 선언할 때, 가급적 인자값 앞에 in, out, inout 커맨드를 명시할 수 있도록 하자!

// All Shader용
//// 해당 텍스처가 바인딩되어 있는 지를 확인하는 함수; Texture2D 메소드인 .GetDimensions()를 사용
uint HF_IsBinded(in Texture2D _Texture)
{
    uint T_uint_Width, T_uint_Height = 0;
    
    // .GetDimensions()는 너비와 높이값 중 하나만 반환할 수 있음
    _Texture.GetDimensions(T_uint_Width, T_uint_Height);
    
    // 유의! GPU의 분기예측은 CPU와 달라서, 곱셉보다는 비트마스킹을 통해서 분기예측을 히트 시키기 좋음
    // 개량버전; 오버헤드를 극한으로 줄인 버전
    return (T_uint_Width | T_uint_Height) != 0;

    // 중간 개량버전; 오버헤드를 줄인 버전
    //if (0 == (T_uint_Width | T_uint_Height))
    //    return false;
    //else
    //    return true;

    // 원래 버전
    //if ((0 == T_uint_Width) || (0 == T_uint_Height))
    //    return false;
    //else
    //    return true;
}

// Pixel Shader용
//// 흑백효과
float4 HF_BlackBoost(float4 _Color)
{
    // a값을 활용하여 세기 조절
    float T_RedIntensity = _Color.a * 0.75f;
    
    // 흑백효과
    _Color.rgb = (_Color.r + _Color.g + _Color.b) / 3.f;
 
    _Color.rgb *= _Color.a;
    
    return _Color;
}

//// 붉은효과
float4 HF_RedBoost(inout float4 _Color)
{
    // a값을 활용하여 세기 조절
    float T_RedIntensity = _Color.a * 0.5f;
    _Color.r += _Color.r * T_RedIntensity;
    
    // 초록 약화
    _Color.g *= 1.f - T_RedIntensity;
    
    // 파랑 약화
    _Color.b *= 1.f - T_RedIntensity;
    
    // a값을 활용하여 세기 조절
    _Color.rgb *= _Color.a;
    
    return _Color;
}

//// 노이즈효과
////// 상하좌우




//// 광원효과
float4 HF_CalculateColorBy_Light2D(in float4 _Matrix, inout float4 _Color)
{
    
    
    return _Color;
}

#endif