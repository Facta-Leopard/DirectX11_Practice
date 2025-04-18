# Naming Convention for This Practice Solution
- **Made by Facta-Leopard**: [https://github.com/Facta-Leopard](https://github.com/Facta-Leopard)

## In Codebase

---

### Pointer & Reference Types
- **`CP`**: Prefix for objects wrapped by `ComPtr`.
- **`SP`**: Prefix for objects wrapped by `shared_ptr`.
- **`P`**: Prefix for raw pointers.
- **`PF`**: Prefix for function pointers.
- **`R`**: Prefix for references.

---

### Constant Types
- **`L`**: Prefix for literal constants defined by `const`.
- **`LL`**: Prefix for literal constants defined by `constexpr`.

---

### Structure & Member Types
- **`C`**: Prefix for class names.
- **`DS`**: Prefix for data structure names.
- **`US`**: Prefix for union structure names.
- **`M`**: Prefix for member variables.
- **`MF`**: Prefix for member functions.
- **`G`**: Prefix for global (extern) variables.
- **`GF`**: Prefix for global (extern) functions.
- **`S`**: Prefix for static variables, including singleton instances and cache-only objects reused per frame.
- **`SF`**: Prefix for static functions.
- **`T`**: Prefix for temporary variables.
- **`TF`**: Prefix for temporary functions.

---

### STL Container Types
- **`STL`**: Prefix for types or variables implemented using STL containers.

---

### Platform or API Specific Types
- **`H`**: Prefix for Windows HANDLE types.
- **`SDK`**: Prefix for types that are defined in the Windows SDK, such as DWORD, BOOL, HRESULT, LPARAM, and others.
- **`F`**: Prefix for FMOD classes in FMOD Library.
- **`I`**: Prefix for Using IMGUI Headers.
- **`DX`**: Prefix for DirectX-specific classes.

---

### Fixed Abbreviations
- **`E`**: Used alone for enum structures.
- **`EC`**: Used alone for `enum class`.
- **`_`**: Used alone as a suffix for enum members.
- **`Vector2`**: Used for Vector2 structure.
- **`Vector3`**: Used for Vector3 structure.
- **`Vector4`**: Used for Vector4 structure.
- **`MAT`**: Used for Matrix (4x4) structure.

---

### Array Type
- **_s**: Suffix for Fixed-size array.

---

### Enum Structure
- To reduce overhead, enum class is not used.

- Instead, to minimize duplication, an underscore (_) is used as a suffix, and all letters are written in uppercase with words separated by underscores.

---

## Naming Rule Notes

- All prefixed names should include a **trailing underscore** (`_`) to improve readability and avoid naming conflicts.  

- When wrapping `external API functions(Windows SDK or DirectX)`, keep the **original function name**, and use the right prefix(`MF_` and `GF_`, `SF_`) depending on where the function is (member, global, or static).

- This makes the code clear and helps you see which API it came from.

---

## Examples

```cpp
// Member variable of type ID3D11Device wrapped by ComPtr
// CP (ComPtr) + trailing '_' + M (Member) + trailing '_' + D (DirectX) + trailing '_'
ComPtr<ID3D11Device> CP_M_D_Device_;

// Temporary pointer to Vector3 structure
V3* T_V3_Position_;

// constexpr constant
constexpr int LL_MaxFrame_ = 60;

// Enum
enum PROJECTION_TYPE {
    _ORTHOGRAPHIC,
    _PERSPECTIVE,
};