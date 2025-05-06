// HLSL은 #pragma once 사용이 불가능하므로, `C`스타일로 하여야 함

#ifndef _FUNCTION
#define _FUNCTION

// 유의! HLSL 내에서는 전송되는 boolean도 uint로 받는 것으로 정했으니, HLSL 내에서도 bool대신 uint를 대신 쓰는 것으로 하자!
// 유의! HLSL 내에서 함수를 선언할 때만, 인자값 앞에 in, out, inout 커맨드를 명시할 수 있도록 하자!

// 해당 텍스처가 바인딩되어 있는 지를 확인하는 함수; Texture2D 메소드인 .GetDimensions()를 사용
uint HLSL_IsBinded(in Texture2D _Texture)
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


#endif