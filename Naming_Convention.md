# Naming Convention for This Practice Solution
- **Made by Facta-Leopard**: [https://github.com/Facta-Leopard](https://github.com/Facta-Leopard)

## In Codebase

---

### Pointer & Reference Types
- **`CP_`**: Prefix for objects wrapped by `ComPtr`.
- **`SP_`**: Prefix for objects wrapped by `shared_ptr`.
- **`P_`**: Prefix for raw pointers.
- **`PF_`**: Prefix for function pointers.
- **`R_`**: Prefix for references.

---

### Constant Types
- **`L_`**: Prefix for literal constants defined by `const`.
- **`LL_`**: Prefix for literal constants defined by `constexpr`.

---

### Structure & Member Types
- **`C_`**: Prefix for class names.
- **`DS_`**: Prefix for data structure names.
- **`US_`**: Prefix for union structure names.
- **`M_`**: Prefix for member variables.
- **`MF_`**: Prefix for member functions.
- **`G_`**: Prefix for global (extern) variables.
- **`GF_`**: Prefix for global (extern) functions.
- **`S_`**: Prefix for static variables, including singleton instances and cache-only objects reused per frame.
- **`SF_`**: Prefix for static functions.
- **`T_`**: Prefix for temporary variables.
- **`TF_`**: Prefix for temporary functions.

---

### Fixed Abbreviations
- **`E_`**: Used alone for enum structures.
- **`EC_`**: Used alone for `enum class`.
- **`_`**: Used alone as a suffix for enum members.
- **`VEC2_`**: Used for Vector2 structure. Represents the data form, not memory alignment.
- **`VEC3_`**: Used for Vector3 structure. Represents the data form, not memory alignment.
- **`VEC4_`**: Used for Vector4 structure. Represents the data form, not memory alignment.

---

### Array Type
- **_s**: Suffix for Fixed-size array.

---

### Enum Structure
- To reduce overhead, enum class is not used.

- Instead, to minimize duplication, an underscore (_) is used as a suffix, and all letters are written in uppercase with words separated by underscores.

---

### STL Container Types
- **`STL_`**: Prefix for types or variables implemented using STL containers.

---

### Platform or API Specific Types
- **`H_`**: Prefix for Windows HANDLE types.
- **`SDK_`**: Prefix for types that are defined in the Windows SDK, such as DWORD, BOOL, HRESULT, LPARAM, and others.
- **`F_`**: Prefix for FMOD classes in FMOD Library.
- **`I_`**: Prefix for Using IMGUI Headers.
- **`DX_`**: Prefix for DirectX-specific classes.
- **`FL_`**: Prefix for FL_IMAGE_PACKER functions.(https://github.com/Facta-Leopard/FL_IMAGE_PACKER)

---

### SIMD-Compatible Types (DirectXMath)
- **`XM_VEC2_`**: Prefix for computational vectors using XMVECTOR with 2-float semantics.
- **`XM_VEC3_`**: Prefix for computational vectors using XMVECTOR with 3-float semantics.
- **`XM_VEC4_`**: Prefix for computational vectors using XMVECTOR with full 4-float usage.
- **`XM_MAT_`**: Prefix for matrix types using XMMATRIX.

---

### GPU Transfer-Compatible Types (Memory-Aligned Structures)
- **`XM_INT2_`**: Prefix for GPU-aligned transfer structures based on XMINT2.
- **`XM_INT3_`**: Prefix for GPU-aligned transfer structures based on XMINT3.
- **`XM_INT4_`**: Prefix for GPU-aligned transfer structures based on XMINT4.

- **`XM_UINT2_`**: Prefix for GPU-aligned transfer structures based on XMUINT2.
- **`XM_UINT3_`**: Prefix for GPU-aligned transfer structures based on XMUINT3.
- **`XM_UINT4_`**: Prefix for GPU-aligned transfer structures based on XMUINT4.

- **`XM_FLOAT2_`**: Prefix for GPU-aligned transfer structures based on XMFLOAT2.
- **`XM_FLOAT3_`**: Prefix for GPU-aligned transfer structures based on XMFLOAT3.
- **`XM_FLOAT4_`**: Prefix for GPU-aligned transfer structures based on XMFLOAT4.
- **`XM_FLOAT4X4_`**: Prefix for GPU-aligned transfer structures based on XMFLOAT4X4.

---

### GPU Binding Types
- **`GPU_`**: Prefix for all GPU-bound resources(buffers, textures, views, etc.).
- **`PAD_`**: Prefix for Padding variable.

---

### HLSL Types

#### HLSL Variable Type
- **`HLSL_DS_`**: Prefix for all structure defined in HLSL.
- **`HLSL_`**: Prefix for all structure defined in HLSL.

#### HLSL Function Type

* **`HF_`**: Prefix for all functions written in HLSL.

#### HLSL Shader Types

* **`HF_VS_`**: Prefix for HLSL functions specifically used in Vertex Shaders.
* **`HF_PS_`**: Prefix for HLSL functions specifically used in Pixel Shaders.
* **`HF_GS_`**: Prefix for HLSL functions specifically used in Geometry Shaders.
* **`HF_HS_`**: Prefix for HLSL functions specifically used in Hull Shaders.
* **`HF_DS_`**: Prefix for HLSL functions specifically used in Domain Shaders.
* **`HF_CS_`**: Prefix for HLSL functions specifically used in Compute Shaders.

---

## Location Naming Rule

- For position/direction identifiers (UVs, Anchors, Alignment, Rects, etc.), always `follow Western-style naming order`.

- `Vertical direction (Top/Bottom) must come first`, followed by horizontal (Left/Right).

### Examples

- `TopLeft`, `BottomRight`

---

## Naming Rule Notes

- When wrapping `external API functions(Windows SDK or DirectX)`, keep the **original function name**, and use the right prefix(`MF_` and `GF_`, `SF_`) depending on where the function is (member, global, or static).

- This makes the code clear and helps you see which API it came from.

---

## Examples

```cpp
// Member variable of type ID3D11Device wrapped by ComPtr
// CP (ComPtr) + trailing '_' + DX (DirectX) + trailing '_' + M (Member) + trailing '_'
ComPtr<ID3D11Device> CP_DX_M_Device_;

// constexpr constant
constexpr int LL_MaxFrame_ = 60;

// Enum
enum PROJECTION_TYPE {
    _ORTHOGRAPHIC,
    _PERSPECTIVE,
};