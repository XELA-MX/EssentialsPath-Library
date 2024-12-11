# EssentialsPath-Library

A cross-platform C++ library for accessing essential system paths and managing file operations.

## Features

- Access common system directories (Documents, Downloads, Desktop, etc.)
- Cross-platform support for Windows and Unix-like systems
- Multiple return type options (std::filesystem::path, std::string, const char*)
- Simple and intuitive API
- Header-only implementation


## Requirements

- C++17 or later
- Windows: MinGW with ole32, uuid, and shell32 libraries
- Unix-like systems: Standard C++ compiler



## Usage

```cpp
#include "EPaths.h"

// Get path as std::filesystem::path (default)
auto docPath = getFolderPath(FolderType::DOCUMENTS);

// Get path as string
std::string downloads = getFolderPath<std::string>(FolderType::DOWNLOADS);

// Get path as const char*
const char* desktop = getFolderPath<const char*>(FolderType::DESKTOP);
```


EPath offers a unified interface for accessing important system locations and performing file operations, making it easier for developers to manage file system tasks in their projects.
