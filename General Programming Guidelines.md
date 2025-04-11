# General Programming Guidelines

---

Components are for data, scripts are for logic.

I chose to attach scripts directly to objects not manage them globally for making editor-based control and maintenance easier.

---

## 1. Class Member Declaration Order

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

7. **Clone method**  (if applicable)
   - Example: `MF_Clone()` for duplicating the instance.

8. **Callback functions** (if applicable)
   - Functions acting as callbacks should follow the naming convention `MF_CallBack_`. The name should end with `MF_CallBack_` to indicate its role as a callback function. This ensures clarity in identifying callback-specific logic.

9. **Abstract methods (`virtual`)**  (if applicable)
   - All pure virtual functions declared here.

10. **Binding-related** methods (if applicable)
   - Functions related to GPU register bindings, such as `MF_Bind()`, `MF_Bind()`, and so on.

11. **Initialization and frame-based methods**  (if applicable)
   - `MF_Initialize()`, `MF_Prepare()`,  
     followed by `MF_Progress()`, `MF_Update()`, `MF_Tick()`.

12. **Getters and Setters**  
    - For all Getters and Setters, use the inline keyword to optimize performance, reduce function call overhead, and maintain the naming convention `MF_GetX()` and `MF_SetY()`.

13. **Attach and Detach functions**
    - Functions to attach or detach elements or components should follow the naming convention `MF_Attach_` and `MF_Detach_`.

14. **Public/Internal methods**  
    - Main logic and behavior functions.

15. **Modularized private/internal methods**  (if applicable)
    - Small helper methods and decomposed logic units.

16. **Template methods** (if applicable)
    - Declare all function templates at the end of the class definition.

### it is important to maintain clear separation based on access specifiers.

- For example, if there are multiple public members within the public section, or if there are redundant members in the protected or private sections, each section should still be clearly separated.

- Even in cases of redundancy, ensure that access specifiers are used clearly to maintain consistency and readability in the class structure.

---

## 2. Scale Handling Guidelines

### 2.1. Negative Scale Values
- When using **negative scale values**, exercise caution, particularly when interacting with libraries or systems that rely on positional data (e.g., physics engines, collision detection). Negative scales may lead to unexpected behaviors such as flipped geometries or incorrect transformations.

### 2.2. Zero Scale Values
- **Scale values of 0** can lead to issues such as rendering failures or incorrect matrix transformations. It is recommended to either **clamp** the scale to a small positive value or implement **exception handling** to prevent these errors. This ensures that objects with scale set to 0 do not cause unexpected behavior in the system.

### 2.3. Scale of 1
- A **scale of 1** indicates that the object maintains its **original size**, with **no influence** from parent object scaling. This is useful for cases where independent scaling is desired or to preserve an object's original dimensions in the scene.

---

## 3. General Guidelines for Transformations

- **World transformation matrices** should be updated consistently when position, rotation, or scale changes.
- Handle transformations separately for rendering and physics calculations, ensuring proper synchronization between the two.
- Always ensure that transformations are applied in the correct order (usually Scale → Rotation → Translation).

## 4. Key Considerations

- Maintain separation of concerns when handling transformations, ensuring that each system (rendering, physics, etc.) has access to the required data without interference.
- Regularly update and validate transformation matrices to avoid discrepancies during gameplay or simulation.