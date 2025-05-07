// HLSL�� #pragma once ����� �Ұ����ϹǷ�, `C`��Ÿ�Ϸ� �Ͽ��� ��

#ifndef _FUNCTION
#define _FUNCTION

// ����! HLSL �������� ���۵Ǵ� boolean�� uint�� �޴� ������ ��������, HLSL �������� bool��� uint�� ��� ���� ������ ����!
// ����! HLSL ������ �Լ��� ������ ��, ������ ���ڰ� �տ� in, out, inout Ŀ�ǵ带 ����� �� �ֵ��� ����!

// All Shader��
//// �ش� �ؽ�ó�� ���ε��Ǿ� �ִ� ���� Ȯ���ϴ� �Լ�; Texture2D �޼ҵ��� .GetDimensions()�� ���
uint HF_IsBinded(in Texture2D _Texture)
{
    uint T_uint_Width, T_uint_Height = 0;
    
    // .GetDimensions()�� �ʺ�� ���̰� �� �ϳ��� ��ȯ�� �� ����
    _Texture.GetDimensions(T_uint_Width, T_uint_Height);
    
    // ����! GPU�� �б⿹���� CPU�� �޶�, �������ٴ� ��Ʈ����ŷ�� ���ؼ� �б⿹���� ��Ʈ ��Ű�� ����
    // ��������; ������带 �������� ���� ����
    return (T_uint_Width | T_uint_Height) != 0;

    // �߰� ��������; ������带 ���� ����
    //if (0 == (T_uint_Width | T_uint_Height))
    //    return false;
    //else
    //    return true;

    // ���� ����
    //if ((0 == T_uint_Width) || (0 == T_uint_Height))
    //    return false;
    //else
    //    return true;
}

// Pixel Shader��
//// ���ȿ��
float4 HF_BlackBoost(float4 _Color)
{
    // a���� Ȱ���Ͽ� ���� ����
    float T_RedIntensity = _Color.a * 0.75f;
    
    // ���ȿ��
    _Color.rgb = (_Color.r + _Color.g + _Color.b) / 3.f;
 
    _Color.rgb *= _Color.a;
    
    return _Color;
}

//// ����ȿ��
float4 HF_RedBoost(inout float4 _Color)
{
    // a���� Ȱ���Ͽ� ���� ����
    float T_RedIntensity = _Color.a * 0.5f;
    _Color.r += _Color.r * T_RedIntensity;
    
    // �ʷ� ��ȭ
    _Color.g *= 1.f - T_RedIntensity;
    
    // �Ķ� ��ȭ
    _Color.b *= 1.f - T_RedIntensity;
    
    // a���� Ȱ���Ͽ� ���� ����
    _Color.rgb *= _Color.a;
    
    return _Color;
}

//// ������ȿ��
////// �����¿�




//// ����ȿ��
float4 HF_CalculateColorBy_Light2D(in float4 _Matrix, inout float4 _Color)
{
    
    
    return _Color;
}

#endif