#pragma once
#include "C_Component.h"

#include "global.h"

class C_Transform
    : public C_Component
{
public:
    C_Transform();

protected:
    C_Transform(const C_Transform& _Origin);

public:
    virtual ~C_Transform();

protected:
    XMVECTOR                    XM_VEC3_M_LocalScale;                               // XMVECTOR; Vector3 ���� ��; ������� ũ��(������ǥ)
    XMVECTOR                    XM_VEC3_M_LocalRotation;                            // XMVECTOR; Vector3 ���� ��; ������� ȸ��(������ǥ); ����! Vector3 ������ ���Ϸ� �� �����̹Ƿ� Ȱ��ÿ��� 360�� ���� �����ʿ� �� ��Ŀ� XMMatrixDecompose ����ؼ� �и��ؼ� �� ���� ����� ������ Radian�̹Ƿ�, XMConvertToDegrees()�� �Ἥ ��ȯ�ʿ�!
    XMVECTOR                    XM_VEC3_M_LocalPosition;                            // XMVECTOR; Vector3 ���� ��; ������� ��ǥ(������ǥ); ����! ��ĺ�ȯ�� ������ ���Ͻ�Ű�� ���� ���� ���� ��������!
    XMVECTOR                    XM_VEC3_M_LocalDirection_s[_DIRECTION_END];         // XMVECTOR; Vector3 ���� ��; ������� ����(���ù���)�� �� ���⺰�� �迭�� ������ ����; ����! ������� �� �θ� ������Ʈ���� ��� ������ ���ؼ� ��

    bool                        M_IsScaleDependent;                                    // bool; ������ ���� ����; �θ� ������Ʈ�� Ʈ�� ���� ���� �������� ����

    XMMATRIX                    XM_MAT_M_WorldMatrix;                                   // XMMATRIX; ������� ���; ����! ��ȯ������ �� ���� �����Ƿ� ������ ������ķ� �ʱ�ȭ �ؾ���! ����! GPU�� ������ ���޽ÿ��� XMFLOAT4X4�� �Ѱܾ� ��!
    XMVECTOR                    XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_END];      // XMVECTOR; Vector3 ���� ��; DS_Vector3_Direction; ������� ����; ����! ������ ���Ⱚ�� �����ؼ� ���� ������ ī�޶� �� �浹ó���� ������带 ���̱� ������; ����, �ʿ�� �ٸ� ���ڵ� ĳ���ϴ� ���� ����غ��� �͵� ���� ��

public:
    CLONE(C_Transform)

public:
    virtual void MF_Prepare() override;				                                	// �����Լ�; �ʱ�ȭ �Լ�; ����, �Լ��� ���ϼ��� ���� �����ڿ��� ���� �Ἥ �ʱ�ȭ�ϴ� ������� ��ȯ�� �����ϴ� ���� ���� ��

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;                                      // �����Լ�; ����! ��ġ����� Narrow Phase�� �� ���� ����

public:
    void MF_Bind_Transform();                                                           // Bind; ��ġ���� GPU���� ���� �ٲ� �ʿ䰡 �����Ƿ�, ��������(b#) ���

public:
    // LocalScale ����
    inline XMVECTOR MF_Get_LocalScale()                                               // Getter; Vec3_M_RelativeScale
    {
        return XM_VEC3_M_LocalScale;
    }

    // LocalRotation ����
    inline XMVECTOR MF_Get_LocalRotation()                                            // Getter; Vec3_M_RelativeRotation
    {
        return XM_VEC3_M_LocalRotation;
    }

    // LocalPosition ����
    inline XMVECTOR MF_Get_LocalPosition()                                            // Getter; Vec3_M_RelativePosition
    {
        return XM_VEC3_M_LocalPosition;
    }

    // LocalDirection ����
    inline XMVECTOR MF_Get_LocalDirection(E_DIRECTION_TYPE _Direction)                                          // Getter; Vec3_M_RelativeDirection
    {
        return XM_VEC3_M_LocalDirection_s[_Direction];
    }

    // ScaleFactor ����
    inline bool MF_Get_IsScaleDependent()                                                // Getter; M_IsScaleDependent
    {
        return M_IsScaleDependent;
    }

    // WorldMatrix ����
    //// XMMATRIX ����ü�� ��ȯ
    inline XMMATRIX MF_Get_WorldMatrix()                                                  // Getter; MAT_M_WorldMatrix; const ��ü �� const �޼ҵ� ȣ������ �����ʴ� ������ ��; ���� ��ü�� �ٲ㺸�� ��
    {
        return XM_MAT_M_WorldMatrix;
    }

    ////// WorldMatrixDirection ����
    inline XMVECTOR MF_Get_WorldMatrixDirection(E_DIRECTION_TYPE _Direction)             // Getter; MF_ConvertWorldMatrixToVectorDirection()
    {
        return XM_VEC3_M_WorldMatrixDirection_s[_Direction];
    }

public:
    inline  void MF_Set_LocalScale(XMVECTOR _XM_VEC3_Scale)                            // Setter;
    {
        XM_VEC3_M_LocalScale = _XM_VEC3_Scale;
    }

    inline  void MF_Set_LocalScale(float _X, float _Y, float _Z)                     // Setter;
    {
        XM_VEC3_M_LocalScale = XMVectorSet(_X, _Y, _Z, 0.f);
    }

    inline  void MF_Set_LocalRotation(XMVECTOR _XM_VEC3_Rotation)                         // Setter;
    {
        XM_VEC3_M_LocalRotation = _XM_VEC3_Rotation;
    }

    inline  void MF_Set_LocalRotation(float _X, float _Y, float _Z)                  // Setter;
    {
        XM_VEC3_M_LocalRotation = XMVectorSet(_X, _Y, _Z, 0.f);
    }

    inline  void MF_Set_LocalPosition(XMVECTOR _Vec3Position)                         // Setter; 
    {
        XM_VEC3_M_LocalPosition = _Vec3Position;
    }

    inline  void MF_Set_LocalPosition(float _X, float _Y, float _Z)                  // Setter;
    {
        XM_VEC3_M_LocalPosition = XMVectorSet(_X, _Y, _Z, 0.f);
    }

    inline bool MF_Set_ScaleDependent(bool _InputScaleFactor)                           // Setter; 
    {
        M_IsScaleDependent = _InputScaleFactor;
    }

    inline  void MF_Set_WorldMatrix(XMMATRIX _Matrix)                                     // Setter
    {
        XM_MAT_M_WorldMatrix = _Matrix;
    }

protected:
    // ����Լ�

    


    // ����, Save �� Load�� ������ ��������
};

