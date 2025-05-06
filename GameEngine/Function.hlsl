// HLSL�� #pragma once ����� �Ұ����ϹǷ�, `C`��Ÿ�Ϸ� �Ͽ��� ��

#ifndef _FUNCTION
#define _FUNCTION

// ����! HLSL �������� ���۵Ǵ� boolean�� uint�� �޴� ������ ��������, HLSL �������� bool��� uint�� ��� ���� ������ ����!
// ����! HLSL ������ �Լ��� ������ ����, ���ڰ� �տ� in, out, inout Ŀ�ǵ带 ����� �� �ֵ��� ����!

// �ش� �ؽ�ó�� ���ε��Ǿ� �ִ� ���� Ȯ���ϴ� �Լ�; Texture2D �޼ҵ��� .GetDimensions()�� ���
uint HLSL_IsBinded(in Texture2D _Texture)
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


#endif