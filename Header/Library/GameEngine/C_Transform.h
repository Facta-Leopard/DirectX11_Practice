#pragma once
#include "C_Component.h"
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
    Vector3                     Vec3_M_RelativePosition;            // Vector3; ������� ��ǥ(�Ǵ� ������ǥ)
    Vector3                     Vec3_M_RelativeScale;               // Vector3; ������� ũ��(�Ǵ� ������ǥ)
    Vector3                     Vec3_M_RelativeRotation;            // Vector3; ������� ȸ��(�Ǵ� ������ǥ)
    Vector3                     Vec3_M_RelativeDirection;           // Vector3; ������� ����(�Ǵ� ���ù���)

    bool                        M_IsScaleDependent;                 // bool; ������ ���� ����; �θ� ������Ʈ�� Ʈ�� ���� ����

    Matrix                      MAT_M_WorldMatrix;                  // Matrix; ������� ���; ����! ��ȯ������ �� ���� �����Ƿ� ������ ������ķ� �ʱ�ȭ �ؾ���!
    Vector3                     Vec3_WorldMatrixDirection;          // Vector3; ������� ����

public:
    CLONE(C_Transform)

    virtual C_Transform* MF_Get_ComponentMyself() override                              // �ڱ��ڽ��� Ÿ�Կ� �°� ��ȯ�ϴ� �Լ�
    {
        return this;
    };

public:
    virtual void MF_Prepare() override;                                                 // �ʱ�ȭ �Լ�

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

public:
    void MF_Bind_Register();                                                            // Bind; ��ġ���� GPU���� ���� �ٲ� �ʿ䰡 �����Ƿ�, ��������(b#) ���

public:
    // RelativePosition ����
    inline Vector3 MF_Get_RelativePosition()                                            // Getter; Vec3_M_RelativePosition
    {
        return Vec3_M_RelativePosition;
    }

    inline  void MF_Set_RelativePosition(Vector3 _Vec3Position)                         // Setter; 
    {
        Vec3_M_RelativePosition = _Vec3Position;
    }

    inline  void MF_Set_RelativePosition(float _X, float _Y, float _Z)                  // Setter;
    {
        Vec3_M_RelativePosition = Vector3(_X, _Y, _Z);
    }

    // RelativeScale ����
    inline Vector3 MF_Get_RelativeScale()                                               // Getter; Vec3_M_RelativeScale
    {
        return Vec3_M_RelativeScale;
    }

    inline  void MF_Set_RelativeScale(Vector3 _Vec3Position)                            // Setter;
    {
        Vec3_M_RelativeScale = _Vec3Position;
    }

    inline  void MF_Set_RelativeScale(float _X, float _Y, float _Z)                     // Setter;
    {
        Vec3_M_RelativeScale = Vector3(_X, _Y, _Z);
    }

    // RelativeRotation ����
    inline Vector3 MF_Get_RelativeRotation()                                            // Getter; Vec3_M_RelativeRotation
    {
        return Vec3_M_RelativeRotation;
    }

    inline  void MF_Set_RelativeRotation(Vector3 _Vec3Position)                         // Setter;
    {
        Vec3_M_RelativeRotation = _Vec3Position;
    }

    inline  void MF_Set_RelativeRotation(float _X, float _Y, float _Z)                  // Setter;
    {
        Vec3_M_RelativeRotation = Vector3(_X, _Y, _Z);
    }

    // RelativeDirection ����
    inline Vector3 MF_Get_RelativeDirection()                                           // Getter; Vec3_M_RelativeDirection
    {
        return Vec3_M_RelativeDirection;
    }

    // ScaleFactor ����
    inline int MF_Get_ScaleDependent()                                                  // Getter; M_IsScaleDependent
    {
        return M_IsScaleDependent;
    }

    inline bool MF_Set_ScaleDependent(bool _InputScaleFactor)                           // Setter; 
    {
        M_IsScaleDependent = _InputScaleFactor;
    }

    // WorldMatrix ����
    //// Matrix ����ü�� ��ȯ
    inline Matrix MF_Get_WorldMatrix()                                                  // Getter; MAT_M_WorldMatrix; const ��ü �� const �޼ҵ� ȣ������ �����ʴ� ������ ��; ���� ��ü�� �ٲ㺸�� ��
    {
        return MAT_M_WorldMatrix;
    }

    //// Vector ����ü�� ��ȯ
    ////// WorldMatrixPosition ����
    inline Vector3 MF_Get_WorldMatrixPosition()                                         // Getter; MF_ConvertWorldMatrixToVectorPosition()
    {
        return MF_ConvertWorldMatrixToVectorPosition();                                     // Getter�� ����Լ�
    }

    ////// WorldMatrixScale ����
    inline Vector3 MF_Get_WorldMatrixScale()                                            // Getter; MF_ConvertWorldMatrixToVectorScale()
    {
        return MF_ConvertWorldMatrixToVectorScale();                                        // Getter�� ����Լ�
    }

    ////// WorldMatrixRotation ����
    inline Vector3 MF_Get_WorldMatrixRotation()                                         // Getter; MF_ConvertWorldMatrixToVectorRotation()
    {
        return MF_ConvertWorldMatrixToVectorRotation();                                     // Getter�� ����Լ�
    }

    ////// WorldMatrixDirection ����
    inline Vector3 MF_Get_WorldMatrixDirection()                                        // Getter; MF_ConvertWorldMatrixToVectorDirection()
    {
        return MF_ConvertWorldMatrixToVectorDirection();                                    // Getter�� ����Լ�
    }

    inline  void MF_Set_WorldMatrix(Matrix _Matrix)                                     // Setter
    {
        MAT_M_WorldMatrix = _Matrix;
    }

protected:
    // ����Լ�
    //// WorldMatrix ����
    ////// Vector3 ����ü�� ��ȯ
    Vector3 MF_ConvertWorldMatrixToVectorPosition();                                    // Getter�� ����Լ�; MF_Get_WorldMatrixPosition()�� ����

    Vector3 MF_ConvertWorldMatrixToVectorScale();                                       // Getter�� ����Լ�; MF_Get_WorldMatrixScale()�� ����

    Vector3 MF_ConvertWorldMatrixToVectorRotation();                                    // Getter�� ����Լ�; MF_Get_WorldMatrixRotation()�� ����

    Vector3 MF_ConvertWorldMatrixToVectorDirection();                                   // Getter�� ����Լ�; MF_Get_WorldMatrixDirection()�� ����






    // ����, Save �� Load�� ������ ��������
};

