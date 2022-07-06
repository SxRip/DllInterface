# DllInterface
## The simple interface for working with DLL in dynamic style.

### You can take this from "Module" folder.

### In the project exists 2 solution for demonstration the class work

For compilation: 
* Go to Project Properties ->
  * Configuration properties -> Additionally
  * Character set -> Use multibyte encoding

The class implemented with map (module name and own module).

Methods:
```
size
clear
pop_back
get_func
pop_front
push_back
```

# get_func

get_func it's a template method. He has 2 implementations wich takes the function prototype: typedef TYPE (*TYPENAME)(PARAMETERS);
Explame: typedef bool (*KillProcess)(const std::string&);

## CODE EXPLAME:
```
typedef bool (*KillProcess)(const std::string&);

KillProcess pfnKillProcess = modules.get_func<KillProcess>("KillProcess", "exmplamedll.dll");
```

# Syntax

```
template <class _Ty>
_Ty get_func(const char* functionName, const char* dllName) noexcept;


template <class _Ty>
_Ty get_func(const char* functionName) noexcept;
```

## FIRST METHOD:
```
template <class _Ty>
_Ty get_func(const char* functionName, const char* dllName) noexcept;
```

## Parameters
[in] functionName

Type: const char*

A const char pointer that contains a name of the function.


[in] dllName

Type: const char*

A const char pointer that contains a path to the dll.

## Return value
Type: _Ty

If the method succeeds, the return value is pointer to the function from the dll.
If the method fails, the return value is nullptr (NULL).

## SECOND METHOD:

```
template <class _Ty>
_Ty get_func(const char* functionName) noexcept;
```

## Parameters
[in] functionName

Type: const char*

A const char pointer that contains a name of the function.

## Return value
Type: _Ty

If the method succeeds, the return value is pointer to the function from the dll.
If the method fails, the return value is nullptr (NULL).


# push_back

push_back has 3 implementations wich takes the HMODULE, const char* and HMODULE, const char*.

# Syntax

```
void push_back(const char* dllName, HMODULE& dllInfo) noexcept;

bool push_back(const char* dllName) noexcept;
  
void push_back(HMODULE& dllInfo) noexcept;
```

FIRST METHOD:

```
void push_back(const char* dllName, HMODULE& dllInfo) noexcept;
```

## Parameters
[in] dllName

Type: const char*

A const char pointer that contains a name of the dll.


[in] dllInfo

Type: HMODULE&

A reference that contains the initialized HMODULE object.

## WHAT DOES THIS METHOD DO?
Type: void

This method add the dll name and initialized HMODULE object to map object in the class.


SECOND METHOD:

```
bool push_back(const char* dllName) noexcept;
```

## Parameters
[in] dllName

Type: const char*

A const char pointer that contains a name of the dll.

## return value
Type: bool

If the method succeeds, the return value is true and add the initialized object and a dll path to map object in the class.
If the method fails, the return value is false. 


THIRD METHOD:

```
void push_back(HMODULE& dllInfo) noexcept;
```

## Parameters
[in] dllInfo

Type: HMODULE&

A reference that contains the initialized HMODULE object.

## WHAT DOES THIS METHOD DO?
Type: void

If the method succeeds, the return value is true and add the initialized object and a dll path to map object in the class.
If the method fails, the return value is false. 



# Remarks about push_back
⚠You can use the second method (get_func), when you have already added dll through push_back methods, or first method get_func(const char*, const char*). 

When you call second method without pasting the dll name - the class trying to find this function in already added modules.


