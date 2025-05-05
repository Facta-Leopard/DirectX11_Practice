# General Programming Guidelines
- **Made by Facta-Leopard**: [https://github.com/Facta-Leopard](https://github.com/Facta-Leopard)

## The One Who Recompiled an Old Dream. Yes, It's Me!

- All design decisions are made with `low-level hardware optimization` in mind, focusing not only on compiler output but on `how the CPU executes instructions, manages branches, handles caches, and traverses memory`.

- This mindset is why I chose to begin programming with `C` and `C++`, aiming for full control over execution rather than relying on abstraction.

- (But, I'm a `APPLE BITCH`, so i wnat to develop with `MetalAPI` via `SWIFT`.

- It is also the reason I began programming through `GAME DEVELOPMENT`, a field where `logic`, `system architecture`, and `creative expression` come together as one.

- Always `consider separating` `debug code` from `release code` to reduce performance impact and avoid unintended behaviors in production builds.

---

## 1. Key Considerations

- Regularly update and validate transformation matrices to avoid discrepancies during gameplay or simulation.

- Maintain separation of concerns when handling transformations, ensuring that each system (rendering, physics, and so on.) has access to the required data without interference.

- Use `quaternion-based matrices` for `GPU-side` `transforms` and `vector-based logic` for `CPU-side` `collision` checks to reduce overhead.

- Code should be `easy to read first`.

- But if better performance is possible without making it too messy, go for performance.

---

## 2. Function Optimization

### 2.1 Function Return Style

- Prefer `RVO(Return Value Optimization)` style when returning objects.

- Return values should be directly constructed without temporary variables.

- However, if code gets too messy or error-prone, `NRVO(Named RVO)` can be used instead.

- I tend to make frequent typos, so I intentionally mix `RVO` and `NRVO`.

- In such cases, I always leave a comment explaining the choice.

### 2.2 Function Overloading & Wrapping

- If multiple overloads perform the **same task** but receive **different forms of input**, consider **wrapping them internally** to reduce redundancy.

- This improves **maintainability** and keeps core logic in a single place.

- Wrapping also helps avoid **code duplication** when dealing with repetitive setup code, such as **DirectX buffer creation** (e.g., using `ByteWidth` vs. `ElementSize × ElementCount`).

- **Wrappers have little to no runtime overhead**, as modern compilers usually **inline** them.

- Use this pattern unless overloads require **completely different behaviors**.

### 2.3 Use Parameters Instead of Member Variables Within Functions

- **If the value is used inside the function, use the parameter. Not the member.**

- Even if the value is saved to a member variable, that doesn’t matter.

- If it’s used in the same function, `the parameter must be used` first.

- `Using parameters is faster` because the CPU can reach them directly.

- Member variables are for things that stay around and matter across functions.

---

## 3. Memory Considerations

- Use `clear` and `predictable` memory layouts.

- Try to avoid `unnecessary heap allocations` in `performance-critical areas`.

- If a value is `used repeatedly inside a loop` or a `frequently called function`, `use static variables to cache` it instead of recalculating.

###  Caution: Smart Pointer Using

- **`ONLY PASS `shared_ptr` IF THE MEMBER IS `shared_ptr`**

- I made an overload like `MF_Set_Texture(C_Texture&& _Texture)` to pass raw objects and wrap them with `shared_ptr` inside the setter.

- But `the object had copy/move constructors deleted`, so i did `make_shared(std::move(_Texture))` and, it `passed compile`.

- But, `errors occured during Run-Time`.

- So, i tried to work around it with `shared_ptr<C_Texture>(&_Texture)` and `ended up hitting a dangling pointer bug`.

- I even tried defining a move constructor overload, I had thought `I was being smart`.

- I was a `fucking idiot` who totally screwed myself.

### Lesson: if the member is a shared_ptr, just pass a shared_ptr  

- **`NEVER BREAK OR REBUILD SMART POINTER` JUST TO PASS THEM AROUND!**

- **ONLY ASSIGN ONE SMART POINTER TO ANOTHER TO MANAGE REF COUNTS SAFELY!**

- **I EXPERIENCED THE HELL OF DEBUGGING OF THOSE!**

---

## 4. Buffer Compatibility(CPU <-> GPU)

- When `sending data from CPU to GPU`, `avoid using C++ types` like bool, char, or short, and instead `use Windows SDK types` like BOOL or UINT that match HLSL alignment.

- These can `cause alignment issues` because `bool in C++ is usually 1 byte`.

- But `HLSL treats all scalar variables (including bool) as 4 bytes`.

- This `mismatch` can result in wrong values being read by the shader or silent bugs.

- To `avoid this`, always use `Windows SDK types BOOL(alias of int, 4 bytes)`, UINT, FLOAT, XMINT#, XMUINT# XMFLOAT#, XMFLOAT4X4 and so on.

- These types are all aligned to 4-byte boundaries and are safe to use with GPU constant buffers.

### 4.1 Constant Buffer Data Scope

- Data transferred from CPU to GPU (e.g., tTransform, tGlobal, etc.) should be declared as global variables, not as static members of a class.

- Global variables have fixed memory addresses and CPU access have advanced faster.

- They stay in contiguous memory, improving CPU cache hit rate and GPU upload efficiency.

- Scattering constant data across multiple static class members leads to fragmented memory and cache misses.

### 4.2 Rule

- Group all GPU-bound data into a single struct.

- Expose that struct as a global instance.

- Prefix with G_ to indicate global scope.

- This layout is cache-friendly, upload-efficient, and structure-clean.

### 4.3. Reference

#### 4.3.1 Reference: Microsoft Docs - Packing Rules for Constant Buffers

[Microsoft Docs - Packing Rules for Constant Buffers](https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-packing-rules)

### 4.3.2 Reference: Microsoft Docs - Shader Constants

[Microsoft Docs - Shader Constants](https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-constants)

---

## 5. Transformation Optimization (SIMD / XMMATRIX)

- Use `XMMATRIX` for matrix calculations `on the CPU only`.

- It is `optimized with SIMD instructions` using `128-bit registers`.

- It gives `a significant speed boost` for operations like world `matrix updates`, `skeletal animation`, and `inverse matrix calculation`.

- DO NOT SEND `XMMATRIX` TO THE GPU DIRECTLY.

- Its `internal format(XMVECTOR[4])` is `designed for fast CPU computation`, `not for GPU constant buffers`.

- `To send matrix data to the GPU`, convert the result into a GPU-safe structure like `XMFLOAT4X4` or `SimpleMath::Matrix` using XMStoreFloat4x4().

### CPU vs GPU Matrix Structure Comparison

- Use `XMMATRIX` for calculation,  
- Then store to `XMFLOAT4X4` using `XMStoreFloat4x4()` before uploading to GPU.

#### XMMATRIX (SIMD-Optimized, CPU Only)

```cpp
typedef struct XMMATRIX
{
    XMVECTOR r[4];  // 4 x 128-bit SIMD registers (total: 64 bytes)
} XMMATRIX;
```

- Each `XMVECTOR` = 4 floats (SIMD register, 128 bits)
- Total size = 64 bytes
- Designed for **fast CPU-side math** using SIMD
- Cannot be sent to GPU directly (incompatible memory layout)

#### XMFLOAT4X4 (GPU-Friendly, Flat Memory)

```cpp
typedef struct XMFLOAT4X4
{
    float m[4][4];  // 16 floats, flat layout (total: 64 bytes)
} XMFLOAT4X4;
```

- Perfectly matches HLSL `float4x4` layout
- Used for **safe and reliable GPU transfers**
- Can be filled using `XMStoreFloat4x4()` from an `XMMATRIX`
- Not optimized for CPU math (use only for storage/transfer)

---

#### Summary Table

| Feature            | `XMMATRIX`            | `XMFLOAT4X4`         |
|--------------------|------------------------|------------------------|
| Internal Type      | `XMVECTOR[4]` (SIMD)   | `float[4][4]`         |
| Size               | 64 bytes               | 64 bytes               |
| CPU SIMD Math      |   Yes                 |   No                  |
| GPU Transfer Safe  |   No                  |   Yes                 |
| Usage Scenario     | CPU matrix operations  | Constant buffer upload |

#### Performance Comparison Table: 100,000 iterations

| Method                  | Time       | Speed      |
|-------------------------|------------|------------|
| `float[4][4]` loops     | 1.7717 sec | Base       |
| `XMMATRIX` (SIMD)       | 0.1461 sec | **12.13× faster** |

- `XMFLOAT4X4` IS NOT IN SIMD.

---

## 6. Class Member Declaration Order

To maintain consistency and readability, all class members should follow the order below:

1. **`friend` declarations** (if applicable) 
   - Use only when necessary, to grant specific access privileges.

2. **Constructors**  
   - Default and parameterized constructors.

3. **Copy constructors** (if applicable) 
   - Copy and move constructors.

4. **Destructor**  
   - Prefer virtual destructor when polymorphism is used.

5. **Singleton macros** (if applicable)  
   - For singleton-style classes.

6. **Member variables**  (if applicable)
   - All member variables prefixed with `M_`.

7. **Static member variables** (if applicable)
   - The actual definition must be written in the `.cpp` file (right after constructor/destructor), not in the constructor body or initializer list.

8. **Clone method**  (if applicable)
   - Example: `MF_Clone()` for duplicating the instance.

9. **Callback functions** (if applicable)
   - Functions acting as callbacks should follow the naming convention `MF_CallBack_`. The name should end with `MF_CallBack_` to indicate its role as a callback function.

10. **Abstract methods (`virtual`)**  (if applicable)
   - All pure virtual functions declared here.

11. **Binding-related** methods (if applicable)
   - Functions related to GPU register bindings, such as `MF_Bind()`, `MF_Bind()`, and so on.

12. **Initialization and frame-based methods**  (if applicable)
   - `MF_Initialize()`, `MF_Prepare()`,  
     followed by `MF_Progress()`, `MF_Update()`, `MF_Tick()`.

13. **Getters**  
    - For all Getters uses the `inline` keyword to optimize performance, reduce function call overhead, and maintain the naming convention `MF_Get_X()`.
    - This makes the code more efficient by directly accessing the member variables, improving performance without extra cost.
    - But, don't use `inline` for `virtual getters`.
    - Because `Inline works at compile time` and `virtual works at runtime`.
    - They don't fit together conceptually.

14. **Setters**
    - Decide `inline` `case by case`.
    - I once added `inline` to a setter and got `circular include errors`.
    - It happened because `the setter needed another class definition`.
    - **SO NOW, I DO NOT USE `inline` WHEN IT NEEDS OTHER CLASS TYPES.**
    - **I JUST MOVE IT TO THE `.cpp` FILE.**
    - **I EXPERIENCED THE HELL-TIME OF DEBUGGING OF THOSE!**

15. **Attach and Detach functions**
    - Functions to attach or detach elements or components should follow the naming convention `MF_Attach_` and `MF_Detach_`.

16. **Public/Internal methods**  
    - Main logic and behavior functions.

17. **Modularized private/internal methods**  (if applicable)
    - Small helper methods and decomposed logic units.

18. **Template methods** (if applicable)
    - Declare all function templates at the end of the class definition.
    - **DO NOT EVEN FUCKING TRY TO SPECIALIZE A MEMBER TEMPLATE FUNCTION JUST TO CHANGE ITS RETURN TYPE.**
    - **HOW DO I KNOW? BECAUSE I HAVE FUCKING TRY TO FUCK AND FUCK IT IN!**

### it is important to maintain clear separation based on access specifiers.

- For example, if there are multiple public members within the public section, or if there are redundant members in the protected or private sections, each section should still be clearly separated.

- Even in cases of redundancy, ensure that access specifiers are used clearly to maintain consistency and readability in the class structure.

---

## 7. Scale Handling Guidelines

### 7.1. Negative Scale Values

- When using **negative scale values**, exercise caution, particularly when interacting with libraries or systems that rely on positional data (e.g., physics engines, collision detection). Negative scales may lead to unexpected behaviors such as flipped geometries or incorrect transformations.

### 7.2. Zero Scale Values
- **Scale values of 0** can lead to issues such as rendering failures or incorrect matrix transformations. It is recommended to either **clamp** the scale to a small positive value or implement **exception handling** to prevent these errors. This ensures that objects with scale set to 0 do not cause unexpected behavior in the system.

---

## 8. General Guidelines for Transformations

- **World transformation matrices** should be updated consistently when position, rotation, or scale changes.

- Handle transformations separately for rendering and physics calculations, ensuring proper synchronization between the two.

- Always ensure that transformations are applied in the correct order (usually Scale → Rotation → Translation).

---

## 9. Collision Calculation Policy

### 9.1. Collision Flow Overview

Get calculation type -> Decide which axes to ignore and if it's 2D or 3D -> Check center distance to filter out obvious misses -> If needed, do a more accurate SAT check -> Final result handling

### 9.2. Summary

- Each stage has its own collision calculation type(`enum or other Structure`).

- This type(`collision calculation type`) fully controls how collision checks will run during that frame.

- First, center distance is used to quickly remove non-colliding objects.

- SAT is only used when checked or customed.

- Inspired by `functional programming`, collision logic uses `lazy evaluation` and view-based caching to reduce redundant work.

### 9.3. Collision Pair Storage Policy

- `std::unordered_map` is used to store collision pair states, offering scalability and fast lookup for increasing collision objects.

- This helps reduce overhead and provides faster lookups during frame-by-frame collision checks.

- Key pairs are stored as simple `ULARGE_INTEGER` types(Windows SDK) to avoid alignment issues and `#pragma pack(#)`.

- However, since `ULARGE_INTEGER` is a union structure, **always use its internal `ULONGLONG` member `QuadPart` when using it as a hash key or a unique value**.  

- If `POINT` is used instead, it may cause problems during physics calculations like those in StarCraft 1 because the `USHORT` values inside its union can only go up to `65535`.

- Due to `this limit`, adding more colliders may fail because of `overflow` or `malfunction`.

- This keeps the structure clean, easy to manage, and better aligned with `SIMD`(CPU-level vector instructions such as SSE, AVX, and NEON).

### 9.4. View-Aware Caching Policy

- `To skip useless calculations`, the engine chooses what to convert based on the `current view(2D or 3D)`.

- It follows a `lazy and smart style` that mimics `functional programming`.

- In this system, collider positions are `calculated every frame using matrices`, but they are `not pre-converted into Vec2 or Vec3 in advance`.

- Instead, the `Oollision Manager(C_CollisonManager)` converts only the parts of the matrix needed for the current view `when a collision check happens, and stores them` for reuse.

- This helps reduce unnecessary work and `keeps things flexible`.

- `Scale values`, which are mainly `used in OBB checks`, are `not included in this logic` and are `handled separately`.

- To make it faster, `static or pre-made variables` are used inside the manager to skip repeated memory work.

### 9.5. Benefits

- **Clear process**: The steps are always the same based on the collision type.

- **Good performance**: Fast filtering comes first, and detailed checks happen only if needed.

- **Easy to expand**: The enum-based setup makes it simple to add new types or change logic.

- **Clear rules**: The stage sets the rule, and the collision manager only runs the logic.

- **Smart caching**: Only needed data is transformed and cached, and `static variables` make it `faster` by `skipping this pointer` and reusing memory.

- **Cleaner logic flow**: Because the calculations depend on the current view, the engine avoids rigid logic paths and adapts flexibly.

### 9.6. Caution

- Using std::unordered_map requires `careful bucket sizing`.

- `Poor bucket planning` can lead to `performance drops`, especially with a large number of collision pairs.

- **StageManager should not control collision types directly.**

- The collision type must be stored in the `Stage` itself.

- If `StageManager` tries to change or hold this data, it breaks the clean design.

- **The camera is not the same as view type and must never be used for collision logic.**

- DO NOT THINK ABOUT COMBINING TWO POINTERS AS A HASH KEY OR VALUE.

- DO NOT, I FUCKING TRIED SO MANY AND WASTED MY TIME.

---

10. Resource Normalization Design Principles

- Image resources are currently **packed and managed using the custom-built `FL_IMAGE_PACKER` system**

- following a normalized structure. The **initial normalization level is based on the First Normal Form (1NF)**.

- As development progresses and the system evolves, the design allows for **flexible extension to the Second (2NF) or Third Normal Form (3NF)** as needed.

- `FL_IMAGE_PACKER` implements this normalization method for image resources by **separating metadata from binary blocks** and enabling **key-based direct lookup**.

- **All future resource types** (e.g., textures, materials, shaders, sounds) will adopt the same normalization philosophy and be integrated into a **unified packing system**.

---

## 11. Techniques and Rationale Used Here

### 11.1 Yoda Condition Rule

- When comparing against a constant or literal, always place it on the left side.  

- This helps prevent bugs caused by accidental assignment (`=`) in conditionals.

- I didn’t choose to be a Jedi… but I did choose Yoda.

- I don't really know much about Star Wars, but the name has a wise ring to it.

### 11.2 Branch Split Rule

> **"Branch predictability drives speed. Nested ifs lead straight into unpredictability."**

- If a function has 4 or more if or else if statements, and it may add more in the future, then it should be split the logic into separate functions.

- Too many conditions make it hard for the CPU to predict, which can slow things down.

- Splitting into functions makes the code cleaner and easier to update.

- Function call cost is small, but bad branch prediction is expensive.

- To reduce the overhead from branch misprediction, keep `switch-case` structures as `simple` as possible.

- It’s better for SIMD and branch prediction to use value assignment instead of branching.

- For `enum class`, I use `switch branching` instead of `if branching`, to `keep the code style consistent`.

#### Branch Prediction Table

##### Diagram

          [Condition A]
             /    \
         true     false
         /          
   [Condition B]          
     /     \              
 true     false          

##### Overview

| Style             | Compute Cost (cycles) | Branch Misprediction Cost (cycles) | Total Cost (cycles) |
|-------------------|------------------------|-------------------------------------|----------------------|
| Nested `if` (A)   | 325,000                | 64,400                              | 389,400              |
| Flat `else-if` (B)| 325,000                | 26,600                              | 351,600              |

- Both structures execute the same logic.

- However, the **flat `else-if` chain avoids deep branching**, which results in **fewer branch prediction failures**.

- **CPU prediction is critical** for performance in tight loops such as collision checks or update ticks.

- In this test scenario (10,000 iterations), the `else-if` chain saved approximately **37,800 CPU cycles**.

### 11.3 Components Design

- `Components are for data`, `scripts are for logic`.

- I choose to attach scripts directly to objects not manage them globally for making editor-based control and maintenance easier.

- If a component needs to access a value frequently, caching should be considered to minimize `dereference overhead` by `Pointer Chasing` during runtime.

#### Comparison Pointer Chasing Table: Dereference Depth vs Runtime Overhead

| Dereference Depth | Example Access                                                                                  | Pointer Deref. Count | Function Call Count | Inline Optimization Feasibility | Cache Friendliness | Performance Impact | Measured Time (100k runs, sec) |
|-------------------|--------------------------------------------------------------------------------------------------|-----------------------|----------------------|-------------------------------|---------------------|---------------------|-------------------------------|
| 0 (Direct)        | `Vector2 Pos = Vec2_M_Position;`                                                                 | 0                     | 0                    | Very High                     | Excellent           | Minimal             | 0.00243                        |
| 1-Level           | `Vector2 Pos = C_Transform->MF_Get_Position();`                                                  | 1                     | 1                    | Moderate                      | Good                | Slight              | 0.00329                        |
| 2-Level           | `Vector2 Pos = C_Object->MF_Get_Transform()->MF_Get_Position();`                                 | 2                     | 2                    | Low                           | Fair                | Moderate            | 0.00383                        |
| 3-Level           | `Vector2 Pos = C_Component->MF_Get_OwnerObject()->MF_Get_Transform()->MF_Get_Position();`              | 3                     | 3                    | Very Low                      | Poor                | High                | 0.00414                        |

### 11.4 Value Caching

- I Cached a `value as a static member variable` to avoid `repeated work in a loop`.  

- Later, if I work more with `parallel programming`, I may move it `back into the function`.

- If a value is only needed once inside a function, it’s better to create a **stack variable** instead of caching it as static.

- Using **stack variables** for one-time use cuts down overhead and avoids extra memory work.

- I first applied this idea to resource path handling during resource management system development(C_ResoureManager).

- It should be reviewed again when checking the whole codebase later.

#### Overhead Comparison Table: Static vs Member vs Local Variable

| Method               | Memory Location            | Access                           | Creation        | Thread-Safe   | Cache Efficiency   | Example              | Performance (10M ops)   |
|:---------------------|:---------------------------|:---------------------------------|:----------------|:--------------|:-------------------|:---------------------|:------------------------|
| Static variable      | .data / .bss               | Direct (fastest)                 | Once            | No            | High               | static Vector2 temp; | 0.8424 sec              |
| Member-like variable | Heap or stack (via object) | `this` pointer (slightly slower) | Per object      | Yes           | Medium             | this->tempVec;       | 0.8819 sec              |
| Local variable       | Stack frame (per loop)     | Stack allocation (slowest)       | Every iteration | Yes           | Low                | Vector2 temp = ...;  | 3.0636 sec              |

### 11.5 About Memory Layout SoA(Structure of Array) and AoS(Array of Structure)

- Think about for Using Structure of Arrays (SoA) instead of Array of Structures (AoS) when doing repeated math on many vectors, to make the code faster with better cache and SIMD use.

### 11.6 Ternary Operator Rule

- Nested ternary is allowed only inside for or while loops — my personal rule for compactness and clarity.

- Outside loops, I choose if statements for better readability and cache safety.

### 11.7 Using `Getter` function for classfied

- I decide to use getters for other classes' members and access own class's members directly to keep things clear.

### 11.8 About Scale and Rotation Transformation

- The Quaternion Method was chosen due to its significantly faster processing time and protecting Zero Scale problem, and to avoid Gimbal Lock problem.

#### Overhead Comparison Table

| Transformation Method | DirectX Function | Processing Time | Speed Difference |
|----------------------|------------------|-----------------|------------------|
| Quaternion Method     | `XMQuaternionToAxisAngle()` → `XMConvertToDegrees()` | 627 nanoseconds | Reference |
| Matrix Method         | `XMMatrixRotationQuaternion()` → `XMMatrixDecompose()` → `XMConvertToDegrees()` | Approximately 3,637-4,452 nanoseconds | Approximately 5.8-7.1 times slower |

---

## 12. GPU Binding and Shader Register Guidelines

### 12.1 Shader File Format Convention (.fx vs .hlsl)

- Shader source files **must use `.hlsl`** as the standard extension.

- The `.fx` extension is a deprecated legacy format that should be avoided.

### 12.2 Matrix Alignment Rule

- All matrices sent from the CPU must be stored using **row-major layout**.

- Therefore, in HLSL, use the `row_major` keyword to ensure correct memory interpretation.

- This avoids alignment mismatches between `XMFLOAT4X4` (CPU) and `float4x4` (HLSL).

- If you later plan to make the shader cross-platform (e.g., for GLSL), you must switch to `column_major` globally.

---

### 12.3 HLSL Register Types and Limits (HLSL 5.0, DirectX 11)

| Register Type | Prefix | Max Count | DX11 Practical Limit | Notes |
|---------------|--------|-----------|-----------------------|-------|
| Constant Buffer | `b#` | 4096      | 14                    | Use `cbuffer` |
| Texture (SRV)   | `t#` | 128       | 128                   | Includes `Texture2D`, `StructuredBuffer`, etc. |
| Sampler         | `s#` | 16        | 16                    | Used in pixel shaders |
| UAV             | `u#` | 64        | 8 (PS), 64 (CS)       | For compute/output buffers only |

---

### 12.4 Register Slot Design

#### 12.4.1. b#

- **`b0`** : **`Resolution`**

- **`b1`** : **`Time`**

- **`b2`** : **`Transform`**

- **`b3`** : **`Material`**

- **`b10`** : **`Light`**

#### 12.4.2. t#

- **`t0-t9`** : **`Texture`**

- **`t10-t19`** : **`Light`**

- **`t100-t128`** : **`PostProcess`**

#### 12.4.3. s#

- Undecided

#### 12.4.4. u#

- **`u0-u7`** : **`Pixel Shader Only`**

- **`u8-u63`** : **`Compute Shader Only`**

### 12.5 Notes for Portability and Precision

- GPU register slots must be tracked carefully and not exceed the limit.

- HLSL is sensitive to alignment: pad manually if needed to ensure 16-byte alignment inside `cbuffer`.

- UAVs in pixel shaders are rare and limited (8 max), use only when needed.

- When targeting GLSL or Metal, rework layout for column-major and descriptor sets.

---

## 12.5 Rule

- **Use `.hlsl` for all shader source files.**

- **Using `.fx` is banned**, even if only for test files or examples.

- Match the shader stage in the filename (e.g., `PostProcess_VertexShafer.hlsl`, `Basci_PixelShader.hlsl`).

- Maintain a flat, clean naming scheme to simplify shader binding.

- **HLSL doesn't support bool*, so **`BOOL`** data is received as **`uint`**.

---

### 12.5.1. Historical Comparison Table

| Extension | Purpose                        | Framework       | Status         |
|:-----------:|--------------------------------|------------------|----------------|
| `.fx`     | Shader + Graphics State Bundle | FX Framework     | Deprecated  |
| `.hlsl`   | Shader Source Only             | DirectX Native   | Modern Use  |

- The `.fx` format was introduced with **DirectX 9/10** under the **FX Framework**, which allowed developers to bundle shaders with render states (blend, rasterizer, depth, etc.) inside a single script-like `.fx` file using `technique` and `pass` blocks.

- At runtime, developers could use `D3DX11CreateEffectFromFile()` to automatically load and apply these shaders and states with minimal code.

- This approach reduced boilerplate at the time but **sacrificed fine control, performance tuning, and modern flexibility**.

---

### 12.5.2. Reason: `.fx` is `Banned`

- The FX Framework is **deprecated by Microsoft** and is **not supported in DirectX 12**.

- It introduces **unpredictable performance costs**, poor debuggability, and **tight coupling between state and shader logic**.

- Modern engines favor **manual state control**, which offers **better optimization and clean separation** of responsibilities.

- In most cases today, `.fx` is used only out of habit or from old tutorials—not because it is viable.

---

### 12.5.3. Reason: `.hlsl` is `the Standard`

- `.hlsl` is a pure shader source file — it contains no render state logic.

- With this separation, **all graphics pipeline states must be manually bound in C++**.

- This gives **maximum control over performance, memory layout, GPU pipeline structure, and debugging**.

- It also matches the approach used by modern APIs such as **DirectX 11/12**, **Vulkan**, and **Metal**.

---

### 12.5.4. Summary

- `.fx` is a wrapper from an outdated era.

- `.hlsl` is the only format that fits modern low-level graphics programming.

- Abandon `.fx`. Embrace `.hlsl`.

- Write every pipeline by hand. Control every bit.

- That’s what makes it **your engine**, not someone else’s.

---

# Naming Convention for This Practice Solution

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

### HLSL Variable Types
- **`HLSL_DS_`**: Prefix for all structure defined in HLSL.
- **`HLSL_`**: Prefix for all structure defined in HLSL.

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