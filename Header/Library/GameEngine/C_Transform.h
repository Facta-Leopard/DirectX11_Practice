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
    XMVECTOR                    XM_VEC3_M_RelativeScale;                               // XMVECTOR; Vector3 ���� ��; ������� ũ��(������ǥ)
    XMVECTOR                    XM_VEC3_M_RelativeRotation;                            // XMVECTOR; Vector3 ���� ��; ������� ȸ��(������ǥ); ����! Vector3 ������ ���Ϸ� �� �����̹Ƿ� Ȱ��ÿ��� 360�� ���� �����ʿ� �� ��Ŀ� XMMatrixDecompose ����ؼ� �и��ؼ� �� ���� ����� ������ Radian�̹Ƿ�, XMConvertToDegrees()�� �Ἥ ��ȯ�ʿ�!
    XMVECTOR                    XM_VEC3_M_RelativePosition;                            // XMVECTOR; Vector3 ���� ��; ������� ��ǥ(������ǥ); ����! ��ĺ�ȯ�� ������ ���Ͻ�Ű�� ���� ���� ���� ��������!
    XMVECTOR                    XM_VEC3_M_RelativeDirection_s[_DIRECTION_END];         // XMVECTOR; Vector3 ���� ��; ������� ����(���ù���)�� �� ���⺰�� �迭�� ������ ����; ����! ������� �� �θ� ������Ʈ���� ��� ������ ���ؼ� ��

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
    // RelativeScale ����
    inline XMVECTOR MF_Get_RelativeScale()                                               // Getter; Vec3_M_RelativeScale
    {
        return XM_VEC3_M_RelativeScale;
    }

    // RelativeRotation ����
    inline XMVECTOR MF_Get_RelativeRotation()                                            // Getter; Vec3_M_RelativeRotation
    {
        return XM_VEC3_M_RelativeRotation;
    }

    // RelativePosition ����
    inline XMVECTOR MF_Get_RelativePosition()                                            // Getter; Vec3_M_RelativePosition
    {
        return XM_VEC3_M_RelativePosition;
    }

    // RelativeDirection ����
    inline XMVECTOR MF_Get_RelativeDirection(E_DIRECTION_TYPE _Direction)                                          // Getter; Vec3_M_RelativeDirection
    {
        return XM_VEC3_M_RelativeDirection_s[_Direction];
    }

    // ScaleFactor ����
    inline int MF_Get_IsScaleDependent()                                                // Getter; M_IsScaleDependent
    {
        return M_IsScaleDependent;
    }

    // WorldMatrix ����
    //// Matrix ����ü�� ��ȯ
    inline XMMATRIX MF_Get_WorldMatrix()                                                  // Getter; MAT_M_WorldMatrix; const ��ü �� const �޼ҵ� ȣ������ �����ʴ� ������ ��; ���� ��ü�� �ٲ㺸�� ��
    {
        return XM_MAT_M_WorldMatrix;
    }

    //// Vector ����ü�� ��ȯ
    ////// WorldMatrixScale ����
    inline XMVECTOR MF_Get_WorldMatrixScale()                                            // Getter; MF_ConvertWorldMatrixToVectorScale()
    {
        return XM_VEC3_M_RelativeScale;
    }

    ////// WorldMatrixRotation ����
    inline XMVECTOR MF_Get_WorldMatrixRotation()                                         // Getter; MF_ConvertWorldMatrixToVectorRotation()
    {
        return XM_VEC3_M_RelativeRotation;
    }

    ////// WorldMatrixPosition ����
    inline XMVECTOR MF_Get_WorldMatrixPosition()                                         // Getter; MF_ConvertWorldMatrixToVectorPosition()
    {
        return XM_VEC3_M_RelativePosition;
    }

    ////// WorldMatrixDirection ����
    inline XMVECTOR MF_Get_WorldMatrixDirection(E_DIRECTION_TYPE _Direction)             // Getter; MF_ConvertWorldMatrixToVectorDirection()
    {
        return XM_VEC3_M_WorldMatrixDirection_s[_Direction];
    }

public:
    inline  void MF_Set_RelativeScale(XMVECTOR _Vec3Position)                            // Setter;
    {
        XM_VEC3_M_RelativeScale = _Vec3Position;
    }

    inline  void MF_Set_RelativeScale(float _X, float _Y, float _Z)                     // Setter;
    {
        XM_VEC3_M_RelativeScale = XMVectorSet(_X, _Y, _Z, 0.f);
    }

    inline  void MF_Set_RelativeRotation(XMVECTOR _Vec3Position)                         // Setter;
    {
        XM_VEC3_M_RelativeRotation = _Vec3Position;
    }

    inline  void MF_Set_RelativeRotation(float _X, float _Y, float _Z)                  // Setter;
    {
        XM_VEC3_M_RelativeRotation = XMVectorSet(_X, _Y, _Z, 0.f);
    }

    inline  void MF_Set_RelativePosition(XMVECTOR _Vec3Position)                         // Setter; 
    {
        XM_VEC3_M_RelativePosition = _Vec3Position;
    }

    inline  void MF_Set_RelativePosition(float _X, float _Y, float _Z)                  // Setter;
    {
        XM_VEC3_M_RelativePosition = XMVectorSet(_X, _Y, _Z, 0.f);
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

