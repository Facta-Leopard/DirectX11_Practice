# This Practice Solution has the Naming Convention.  
  
## in Codebase,  
---  
### Use the 'CP' Prefix for Object Wrapping by ComPtr class.  
  
### Use the 'SP' Prefix for Object Wrapping by shared_ptr class.  
  
### Use the 'P' Prefix for the Pointer.  
  
### Use the 'R' Prefix for the Refference.  
  
### Use the 'C' Prefix for Class.  
  
### Use the 'M' Prefix for Member Variables or Methods.  
  
### Use the 'F' Prefix for Functions or Methods.  
  
### Use the 'H' Prefix for WINDOWS HANDLE.  
  
### Use the 'D' Prefix for DirectX Class.  
---  
## Example,  
---  
### 'CPMD_Device' Means Member Variable'ID3D11Device' Wrapping by 'ComPtr'  
#### class C_Device {ComPtr<ID3D11Device>			CPMD_Device}