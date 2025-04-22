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
    Vector3                     VEC3_M_RelativeScale;                               // Vector3; ������� ũ��(������ǥ)
    Vector3                     VEC3_M_RelativeRotation;                            // Vector3; ������� ȸ��(������ǥ); ����! Vector3 ������ ���Ϸ� �� �����̹Ƿ� Ȱ��ÿ��� 360�� ���� �����ʿ� �� ��Ŀ� XMMatrixDecompose ����ؼ� �и��ؼ� �� ���� ����� ������ Radian�̹Ƿ�, XMConvertToDegrees()�� �Ἥ ��ȯ�ʿ�!
    Vector3                     VEC3_M_RelativePosition;                            // Vector3; ������� ��ǥ(������ǥ); ����! ��ĺ�ȯ�� ������ ���Ͻ�Ű�� ���� ���� ���� ��������!
    Vector3                     VEC3_M_RelativeDirection_s[_DIRECTION_END];         // Vector3; ������� ����(���ù���)�� �� ���⺰�� �迭�� ������ ����; ����! ������� �� �θ� ������Ʈ���� ��� ������ ���ؼ� ��

    bool                        M_IsScaleDependent;                                 // bool; ������ ���� ����; �θ� ������Ʈ�� Ʈ�� ���� ���� �������� ����

    Matrix                      MAT_M_WorldMatrix;                                  // Matrix; ������� ���; ����! ��ȯ������ �� ���� �����Ƿ� ������ ������ķ� �ʱ�ȭ �ؾ���! ����! GPU�� ������ ���޽ÿ��� XMFLOAT4X4�� �Ѱܾ� ��!
    Vector3                     VEC3_M_WorldMatrixDirection_s[_DIRECTION_END];      // DS_Vector3_Direction; ������� ����; ����! ������ ���Ⱚ�� �����ؼ� ���� ������ ī�޶� �� �浹ó���� ������带 ���̱� ������; ����, �ʿ�� �ٸ� ���ڵ� ĳ���ϴ� ���� ����غ��� �͵� ���� ��

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
    inline Vector3 MF_Get_RelativeScale()                                               // Getter; Vec3_M_RelativeScale
    {
        return VEC3_M_RelativeScale;
    }

    inline  void MF_Set_RelativeScale(Vector3 _Vec3Position)                            // Setter;
    {
        VEC3_M_RelativeScale = _Vec3Position;
    }

    inline  void MF_Set_RelativeScale(float _X, float _Y, float _Z)                     // Setter;
    {
        VEC3_M_RelativeScale = Vector3(_X, _Y, _Z);
    }

    // RelativeRotation ����
    inline Vector3 MF_Get_RelativeRotation()                                            // Getter; Vec3_M_RelativeRotation
    {
        return VEC3_M_RelativeRotation;
    }

    inline  void MF_Set_RelativeRotation(Vector3 _Vec3Position)                         // Setter;
    {
        VEC3_M_RelativeRotation = _Vec3Position;
    }

    inline  void MF_Set_RelativeRotation(float _X, float _Y, float _Z)                  // Setter;
    {
        VEC3_M_RelativeRotation = Vector3(_X, _Y, _Z);
    }

    // RelativePosition ����
    inline Vector3 MF_Get_RelativePosition()                                            // Getter; Vec3_M_RelativePosition
    {
        return VEC3_M_RelativePosition;
    }

    inline  void MF_Set_RelativePosition(Vector3 _Vec3Position)                         // Setter; 
    {
        VEC3_M_RelativePosition = _Vec3Position;
    }

    inline  void MF_Set_RelativePosition(float _X, float _Y, float _Z)                  // Setter;
    {
        VEC3_M_RelativePosition = Vector3(_X, _Y, _Z);
    }

    // RelativeDirection ����
    inline Vector3 MF_Get_RelativeDirection(E_DIRECTION_TYPE _Direction)                                          // Getter; Vec3_M_RelativeDirection
    {
        return VEC3_M_RelativeDirection_s[_Direction];
    }

    // ScaleFactor ����
    inline int MF_Get_IsScaleDependent()                                                // Getter; M_IsScaleDependent
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
        return (MAT_M_WorldMatrix.Right(), MAT_M_WorldMatrix.Up(), MAT_M_WorldMatrix.Front());          // ����! Right()�� X��, Up()�� Y��, Front()�� Z�� ���̹Ƿ� ���� ����!
    }

    ////// WorldMatrixDirection ����
    inline Vector3 MF_Get_WorldMatrixDirection(E_DIRECTION_TYPE _Direction)             // Getter; MF_ConvertWorldMatrixToVectorDirection()
    {
        return VEC3_M_WorldMatrixDirection_s[_Direction];
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

#ifdef _DEBUG

    void MF_ConvertWorldMatrixToVectorRotation();                                       // �Ǽ����������� ���� ���Ұ� �Լ�

    void MF_ConvertWorldMatrixToVectorDirection();                                      // �Ǽ����������� ���� ���Ұ� �Լ�

#endif // _DEBUG


    


    // ����, Save �� Load�� ������ ��������
};

