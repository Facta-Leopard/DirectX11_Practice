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
    Vector3                     VEC3_M_RelativeScale;                               // Vector3; 상대적인 크기(로컬좌표)
    Vector3                     VEC3_M_RelativeRotation;                            // Vector3; 상대적인 회전(로컬좌표); 유의! Vector3 형식은 오일러 각 형식이므로 활용시에는 360도 각도 보정필요 및 행렬에 XMMatrixDecompose 사용해서 분리해서 쓸 때는 상관이 없으나 Radian이므로, XMConvertToDegrees()를 써서 변환필요!
    Vector3                     VEC3_M_RelativePosition;                            // Vector3; 상대적인 좌표(로컬좌표); 유의! 행렬변환시 순서를 통일시키기 위해 인자 순서 변경했음!
    Vector3                     VEC3_M_RelativeDirection_s[_DIRECTION_END];         // Vector3; 상대적인 방향(로컬방향)을 축 방향별로 배열로 가지고 있음; 유의! 월드방향 및 부모 오브젝트와의 계산 누적을 위해서 씀

    bool                        M_IsScaleDependent;                                 // bool; 스케일 조정 관련; 부모 오브젝트의 트리 구조 관련 의존성을 담음

    Matrix                      MAT_M_WorldMatrix;                                  // Matrix; 월드공간 행렬; 유의! 변환용으로 쓸 수도 있으므로 무조건 단위행렬로 초기화 해야함! 유의! GPU로 데이터 전달시에는 XMFLOAT4X4로 넘겨야 함!
    Vector3                     VEC3_M_WorldMatrixDirection_s[_DIRECTION_END];      // DS_Vector3_Direction; 월드공간 방향; 유의! 별도로 방향값만 추출해서 쓰는 이유는 카메라 및 충돌처리의 오버헤드를 줄이기 위함임; 향후, 필요시 다른 인자도 캐싱하는 것을 고려해보는 것도 좋을 듯

public:
    CLONE(C_Transform)

public:
    virtual void MF_Prepare() override;				                                	// 더미함수; 초기화 함수; 향후, 함수들 통일성을 위해 생성자에서 모듈로 써서 초기화하는 방법으로 전환도 생각하는 것이 좋을 듯

    virtual void MF_ComponentTick() override;

    virtual void MF_ComponentTickAfter() override;                                      // 더미함수; 유의! 위치계산은 Narrow Phase로 쓸 일이 없음

public:
    void MF_Bind_Transform();                                                           // Bind; 위치값은 GPU에거 값을 바꿀 필요가 없으므로, 레지스터(b#) 사용

public:
    // RelativeScale 관련
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

    // RelativeRotation 관련
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

    // RelativePosition 관련
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

    // RelativeDirection 관련
    inline Vector3 MF_Get_RelativeDirection(E_DIRECTION_TYPE _Direction)                                          // Getter; Vec3_M_RelativeDirection
    {
        return VEC3_M_RelativeDirection_s[_Direction];
    }

    // ScaleFactor 관련
    inline int MF_Get_IsScaleDependent()                                                // Getter; M_IsScaleDependent
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
        return (MAT_M_WorldMatrix.Right(), MAT_M_WorldMatrix.Up(), MAT_M_WorldMatrix.Front());          // 유의! Right()는 X축, Up()은 Y축, Front()는 Z축 값이므로 사용시 유의!
    }

    ////// WorldMatrixDirection 관련
    inline Vector3 MF_Get_WorldMatrixDirection(E_DIRECTION_TYPE _Direction)             // Getter; MF_ConvertWorldMatrixToVectorDirection()
    {
        return VEC3_M_WorldMatrixDirection_s[_Direction];
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

#ifdef _DEBUG

    void MF_ConvertWorldMatrixToVectorRotation();                                       // 실수방지용으로 만든 사용불가 함수

    void MF_ConvertWorldMatrixToVectorDirection();                                      // 실수방지용으로 만든 사용불가 함수

#endif // _DEBUG


    


    // 향후, Save 및 Load는 별도로 구성예정
};

