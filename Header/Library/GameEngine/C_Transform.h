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
    Vector3                     Vec3_M_RelativePosition;            // Vector3; 상대적인 좌표(또는 로컬좌표)
    Vector3                     Vec3_M_RelativeScale;               // Vector3; 상대적인 크기(또는 로컬좌표)
    Vector3                     Vec3_M_RelativeRotation;            // Vector3; 상대적인 회전(또는 로컬좌표)
    Vector3                     Vec3_M_RelativeDirection;           // Vector3; 상대적인 방향(또는 로컬방향)

    bool                        M_IsScaleDependent;                 // bool; 스케일 조정 관련; 부모 오브젝트의 트리 구조 관련

    Matrix                      MAT_M_WorldMatrix;                  // Matrix; 월드공간 행렬; 유의! 변환용으로 쓸 수도 있으므로 무조건 단위행렬로 초기화 해야함!
    Vector3                     Vec3_WorldMatrixDirection;          // Vector3; 월드공간 방향

public:
    CLONE(C_Transform)

    virtual C_Transform* MF_Get_ComponentMyself() override                              // 자기자신을 타입에 맞게 반환하는 함수
    {
        return this;
    };

public:
    virtual void MF_Prepare() override;                                                 // 초기화 함수

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;

public:
    void MF_Bind_Register();                                                            // Bind; 위치값은 GPU에거 값을 바꿀 필요가 없으므로, 레지스터(b#) 사용

public:
    // RelativePosition 관련
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

    // RelativeScale 관련
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

    // RelativeRotation 관련
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

    // RelativeDirection 관련
    inline Vector3 MF_Get_RelativeDirection()                                           // Getter; Vec3_M_RelativeDirection
    {
        return Vec3_M_RelativeDirection;
    }

    // ScaleFactor 관련
    inline int MF_Get_ScaleDependent()                                                  // Getter; M_IsScaleDependent
    {
        return M_IsScaleDependent;
    }

    inline bool MF_Set_ScaleDependent(bool _InputScaleFactor)                           // Setter; 
    {
        M_IsScaleDependent = _InputScaleFactor;
    }

    // WorldMatrix 관련
    //// Matrix 구조체로 반환
    inline Matrix MF_Get_WorldMatrix()                                                  // Getter; MAT_M_WorldMatrix; const 객체 및 const 메소드 호출방식은 하지않는 것으로 함; 구조 자체를 바꿔보는 중
    {
        return MAT_M_WorldMatrix;
    }

    //// Vector 구조체로 반환
    ////// WorldMatrixPosition 관련
    inline Vector3 MF_Get_WorldMatrixPosition()                                         // Getter; MF_ConvertWorldMatrixToVectorPosition()
    {
        return MF_ConvertWorldMatrixToVectorPosition();                                     // Getter용 모듈함수
    }

    ////// WorldMatrixScale 관련
    inline Vector3 MF_Get_WorldMatrixScale()                                            // Getter; MF_ConvertWorldMatrixToVectorScale()
    {
        return MF_ConvertWorldMatrixToVectorScale();                                        // Getter용 모듈함수
    }

    ////// WorldMatrixRotation 관련
    inline Vector3 MF_Get_WorldMatrixRotation()                                         // Getter; MF_ConvertWorldMatrixToVectorRotation()
    {
        return MF_ConvertWorldMatrixToVectorRotation();                                     // Getter용 모듈함수
    }

    ////// WorldMatrixDirection 관련
    inline Vector3 MF_Get_WorldMatrixDirection()                                        // Getter; MF_ConvertWorldMatrixToVectorDirection()
    {
        return MF_ConvertWorldMatrixToVectorDirection();                                    // Getter용 모듈함수
    }

    inline  void MF_Set_WorldMatrix(Matrix _Matrix)                                     // Setter
    {
        MAT_M_WorldMatrix = _Matrix;
    }

protected:
    // 모듈함수
    //// WorldMatrix 관련
    ////// Vector3 구조체로 반환
    Vector3 MF_ConvertWorldMatrixToVectorPosition();                                    // Getter용 모듈함수; MF_Get_WorldMatrixPosition()에 쓰임

    Vector3 MF_ConvertWorldMatrixToVectorScale();                                       // Getter용 모듈함수; MF_Get_WorldMatrixScale()에 쓰임

    Vector3 MF_ConvertWorldMatrixToVectorRotation();                                    // Getter용 모듈함수; MF_Get_WorldMatrixRotation()에 쓰임

    Vector3 MF_ConvertWorldMatrixToVectorDirection();                                   // Getter용 모듈함수; MF_Get_WorldMatrixDirection()에 쓰임






    // 향후, Save 및 Load는 별도로 구성예정
};

