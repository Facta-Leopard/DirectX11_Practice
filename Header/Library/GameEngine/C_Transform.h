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
    XMVECTOR                    XM_VEC3_M_LocalScale;                               // XMVECTOR; Vector3 값만 씀; 상대적인 크기(로컬좌표)
    XMVECTOR                    XM_VEC3_M_LocalRotation;                            // XMVECTOR; Vector3 값만 씀; 상대적인 회전(로컬좌표); 유의! Vector3 형식은 오일러 각 형식이므로 활용시에는 360도 각도 보정필요 및 행렬에 XMMatrixDecompose 사용해서 분리해서 쓸 때는 상관이 없으나 Radian이므로, XMConvertToDegrees()를 써서 변환필요!
    XMVECTOR                    XM_VEC3_M_LocalPosition;                            // XMVECTOR; Vector3 값만 씀; 상대적인 좌표(로컬좌표); 유의! 행렬변환시 순서를 통일시키기 위해 인자 순서 변경했음!
    XMVECTOR                    XM_VEC3_M_LocalDirection_s[_DIRECTION_END];         // XMVECTOR; Vector3 값만 씀; 상대적인 방향(로컬방향)을 축 방향별로 배열로 가지고 있음; 유의! 월드방향 및 부모 오브젝트와의 계산 누적을 위해서 씀

    bool                        M_IsScaleDependent;                                    // bool; 스케일 조정 관련; 부모 오브젝트의 트리 구조 관련 의존성을 담음

    XMMATRIX                    XM_MAT_M_WorldMatrix;                                   // XMMATRIX; 월드공간 행렬; 유의! 변환용으로 쓸 수도 있으므로 무조건 단위행렬로 초기화 해야함! 유의! GPU로 데이터 전달시에는 XMFLOAT4X4로 넘겨야 함!
    XMVECTOR                    XM_VEC3_M_WorldMatrixDirection_s[_DIRECTION_END];      // XMVECTOR; Vector3 값만 씀; DS_Vector3_Direction; 월드공간 방향; 유의! 별도로 방향값만 추출해서 쓰는 이유는 카메라 및 충돌처리의 오버헤드를 줄이기 위함임; 향후, 필요시 다른 인자도 캐싱하는 것을 고려해보는 것도 좋을 듯

public:
    CLONE(C_Transform)

public:
    virtual void MF_Prepare() override;				                                	// 더미함수; 초기화 함수; 향후, 함수들 통일성을 위해 생성자에서 모듈로 써서 초기화하는 방법으로 전환도 생각하는 것이 좋을 듯

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;                                      // 더미함수; 유의! 위치계산은 Narrow Phase로 쓸 일이 없음

public:
    void MF_Bind_Transform();                                                           // Bind; 위치값은 GPU에거 값을 바꿀 필요가 없으므로, 레지스터(b#) 사용

public:
    // LocalScale 관련
    inline XMVECTOR MF_Get_LocalScale()                                               // Getter; Vec3_M_RelativeScale
    {
        return XM_VEC3_M_LocalScale;
    }

    // LocalRotation 관련
    inline XMVECTOR MF_Get_LocalRotation()                                            // Getter; Vec3_M_RelativeRotation
    {
        return XM_VEC3_M_LocalRotation;
    }

    // LocalPosition 관련
    inline XMVECTOR MF_Get_LocalPosition()                                            // Getter; Vec3_M_RelativePosition
    {
        return XM_VEC3_M_LocalPosition;
    }

    // LocalDirection 관련
    inline XMVECTOR MF_Get_LocalDirection(E_DIRECTION_TYPE _Direction)                                          // Getter; Vec3_M_RelativeDirection
    {
        return XM_VEC3_M_LocalDirection_s[_Direction];
    }

    // ScaleFactor 관련
    inline bool MF_Get_IsScaleDependent()                                                // Getter; M_IsScaleDependent
    {
        return M_IsScaleDependent;
    }

    // WorldMatrix 관련
    //// XMMATRIX 구조체로 반환
    inline XMMATRIX MF_Get_WorldMatrix()                                                  // Getter; MAT_M_WorldMatrix; const 객체 및 const 메소드 호출방식은 하지않는 것으로 함; 구조 자체를 바꿔보는 중
    {
        return XM_MAT_M_WorldMatrix;
    }

    ////// WorldMatrixDirection 관련
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
    // 모듈함수

    


    // 향후, Save 및 Load는 별도로 구성예정
};

