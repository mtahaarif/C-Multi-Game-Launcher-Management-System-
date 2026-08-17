# Gameboy Multi-Game Launcher

A Win32 desktop application project, built with Visual Studio and the native Windows API (`<windows.h>`), created as a **Fundamentals of Programming** course project during the 2nd semester of a Bachelor of Computer Engineering degree.

> **Note on project status:** This repository currently contains the unmodified Visual Studio **"Windows Desktop Application" wizard template** (see [Current State vs. Intended Scope](#current-state-vs-intended-scope) below) rather than the SFML/console-based multi-game launcher described in the original project brief. This document describes exactly what is present in the source tree today, and outlines what remains to be built to reach the originally intended scope.

---

## Table of Contents

- [Overview](#overview)
- [Current State vs. Intended Scope](#current-state-vs-intended-scope)
- [Repository Structure](#repository-structure)
- [Architecture](#architecture)
  - [Application Entry Point](#application-entry-point)
  - [Window Registration](#window-registration)
  - [Instance Initialization](#instance-initialization)
  - [Message Loop](#message-loop)
  - [Window Procedure](#window-procedure)
  - [About Dialog](#about-dialog)
- [Resources](#resources)
  - [Resource Symbols (Resource.h)](#resource-symbols-resourceh)
  - [Menu](#menu)
  - [Accelerator Table](#accelerator-table)
  - [Dialog: About Box](#dialog-about-box)
  - [String Table](#string-table)
  - [Icons](#icons)
- [Build System](#build-system)
  - [Project File (.vcxproj)](#project-file-vcxproj)
  - [Build Configurations](#build-configurations)
  - [Compiler / Linker Settings](#compiler--linker-settings)
- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
  - [Using Visual Studio IDE](#using-visual-studio-ide)
  - [Using MSBuild from the Command Line](#using-msbuild-from-the-command-line)
- [Running the Application](#running-the-application)
- [File-by-File Reference](#file-by-file-reference)
- [Known Issues / Housekeeping](#known-issues--housekeeping)
- [Roadmap: Reaching the Intended "Multi-Game Launcher" Scope](#roadmap-reaching-the-intended-multi-game-launcher-scope)
- [License](#license)

---

## Overview

The project is set up as a standard **Win32 GUI application** (not a console app, not MFC, not using any external graphics library at present). It uses:

- The native **Win32 API** (`windows.h`) for window creation, message handling, and dialogs.
- A classic **Windows resource script** (`.rc`) for the menu, accelerator table, icons, dialog, and string table.
- **MSBuild / Visual Studio project files** (`.vcxproj`, `.vcxproj.filters`, `.vcxproj.user`) targeting the **v143 (Visual Studio 2022) toolset**.
- Unicode character set (`wWinMain`, `WCHAR`, `LoadStringW`, `RegisterClassExW`).

At present the application does nothing beyond what the Visual Studio wizard scaffolds automatically: it opens a blank window with a `File` / `Help` menu, an `Exit` command, and an `About` dialog box. There is no game logic, no rendering loop beyond `WM_PAINT` (which currently does nothing), and no SFML dependency wired into the project.

## Current State vs. Intended Scope

The one-paragraph project description (originally the entire README) states:

> "Developed a game launcher in C++ combining SFML graphics with raw Console Buffer Manipulation for high-performance text rendering. Implemented matrix rotation algorithms for Tetris and a custom physics engine for Flappy Bird using cursor manipulation logic."

None of the following are present anywhere in the current source tree:

| Claimed feature | Status |
|---|---|
| SFML graphics integration | **Not present** — no SFML headers, libraries, NuGet/vcpkg references, or linker settings for SFML exist in `GUI Application.vcxproj`. |
| Console Screen Buffer manipulation (`SetConsoleCursorPosition`, `WriteConsoleOutput`, etc.) | **Not present** — the app is a `WINDOWS` subsystem GUI app, not a console app (`SubSystem` = `Windows` in every build configuration), and no console-buffer code exists. |
| Tetris implementation (matrix rotation) | **Not present** — no Tetris-related source files, matrices, or piece-rotation logic exist. |
| Flappy Bird implementation (physics engine) | **Not present** — no Flappy Bird-related source files or physics/gravity code exist. |
| A "launcher" screen for selecting between games | **Not present** — `WndProc` only handles `About` and `Exit` menu commands; `WM_PAINT` is an empty stub. |

What **is** present is the raw scaffolding a game (or any Win32 app) would be built on top of: a working message pump, a window class, a menu/accelerator/about-dialog resource set, and a build system already configured for both `Win32`/`x64` and `Debug`/`Release`. In other words, this is the **starting skeleton**, not the finished launcher. See [Roadmap](#roadmap-reaching-the-intended-multi-game-launcher-scope) for what would need to be added to match the project description.

## Repository Structure

```
-Gameboy-Multi-Game-Launcher/
├── GUI Application.cpp            # Application entry point, WinMain, WndProc, message loop
├── GUI Application.h              # Minimal app header (pulls in Resource.h)
├── GUI Application.ico            # Main application icon (32-bit, multi-resolution)
├── GUI Application.rc             # Windows resource script (menu, dialog, strings, icons)
├── GUI Application.vcxproj        # MSBuild project file (Visual Studio 2022 / v143 toolset)
├── GUI Application.vcxproj.filters# Solution Explorer virtual-folder groupings for VS
├── GUI Application.vcxproj.user   # Per-user IDE settings (debugger, etc.) — machine-specific
├── framework.h                    # Precompiled-style umbrella header (windows.h, CRT headers)
├── Resource.h                     # Numeric IDs for every resource (menu items, dialog, icons…)
├── targetver.h                    # Defines the minimum supported Windows platform via SDKDDKVer.h
├── small.ico                      # Small (taskbar/title-bar) variant of the application icon
├── RCa25372                       # Stray temporary file left behind by the RC compiler (see below)
└── README.md                      # This file
```

## Architecture

The application follows the exact structure generated by the Visual Studio **"Windows Desktop Application"** project wizard for a native Win32 GUI app. All logic lives in a single translation unit, [`GUI Application.cpp`](GUI%20Application.cpp).

### Application Entry Point

```cpp
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPWSTR lpCmdLine,
                       _In_ int nCmdShow)
```

`wWinMain` is the Unicode entry point used instead of `main()`/`WinMain()` for GUI subsystem apps built with wide-character strings. It:

1. Loads two localizable strings from the `.rc` string table into global buffers:
   - `szTitle` ← `IDS_APP_TITLE` ("GUI Application") — used as the window's title bar text.
   - `szWindowClass` ← `IDC_GUIAPPLICATION` ("GUIAPPLICATION") — used as the registered window class name.
2. Registers the window class via `MyRegisterClass`.
3. Creates and shows the main window via `InitInstance`.
4. Loads the accelerator table (`IDC_GUIAPPLICATION` `ACCELERATORS` resource).
5. Runs the classic Win32 **message loop**, translating accelerator keystrokes before dispatching ordinary messages.
6. Returns the `wParam` of the `WM_QUIT` message as the process exit code.

### Window Registration

`MyRegisterClass(HINSTANCE hInstance)` fills out a `WNDCLASSEXW` structure and registers it with `RegisterClassExW`:

- `lpfnWndProc` → `WndProc` (see below).
- `hIcon` / `hIconSm` → loaded from `IDI_GUIAPPLICATION` / `IDI_SMALL` icon resources.
- `hCursor` → the system arrow cursor (`IDC_ARROW`).
- `hbrBackground` → the standard window background brush (`COLOR_WINDOW+1`).
- `lpszMenuName` → `IDC_GUIAPPLICATION`, binding the `MENU` resource to every window of this class.
- `style` → `CS_HREDRAW | CS_VREDRAW`, so the window is fully redrawn whenever it's resized horizontally or vertically.

### Instance Initialization

`InitInstance(HINSTANCE hInstance, int nCmdShow)`:

- Stores `hInstance` in the module-global `hInst`, so other functions (e.g. `About`, `MyRegisterClass`) can access it without passing it around.
- Creates the main top-level window with `CreateWindowW`, using `WS_OVERLAPPEDWINDOW` style (title bar, system menu, minimize/maximize/close buttons, resizable border) and default size/position (`CW_USEDEFAULT`).
- Calls `ShowWindow` and `UpdateWindow` to display and paint the window immediately.
- Returns `FALSE` (aborting startup) if window creation fails.

### Message Loop

```cpp
while (GetMessage(&msg, nullptr, 0, 0))
{
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
```

Standard blocking Win32 message pump. `GetMessage` blocks until a message arrives (or `WM_QUIT` is posted, at which point it returns `0` and the loop exits). `TranslateAccelerator` intercepts keystrokes that match the loaded accelerator table (currently only `Alt+?` / `Alt+/` → About) before they're translated/dispatched as ordinary keyboard messages.

### Window Procedure

`WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)` handles three messages:

| Message | Behavior |
|---|---|
| `WM_COMMAND` | Dispatches on the low word of `wParam` (the control/menu ID). Handles `IDM_ABOUT` (opens the About dialog via `DialogBox`) and `IDM_EXIT` (calls `DestroyWindow`). Anything else falls through to `DefWindowProc`. |
| `WM_PAINT` | Calls `BeginPaint`/`EndPaint` with no drawing in between — currently a no-op placeholder (`// TODO: Add any drawing code that uses hdc here...`). This is where all game/launcher rendering would eventually go, or be replaced by a rendering backend (e.g. SFML's own window/render loop, GDI, or console buffer writes). |
| `WM_DESTROY` | Calls `PostQuitMessage(0)`, which posts `WM_QUIT` and causes the message loop in `wWinMain` to terminate. |
| *(default)* | Forwarded to `DefWindowProc` for standard OS-provided behavior. |

### About Dialog

`About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)` is a modal dialog procedure registered for the `IDD_ABOUTBOX` dialog resource:

- On `WM_INITDIALOG`, does nothing beyond returning `TRUE` (accepting default focus).
- On `WM_COMMAND` with `IDOK` or `IDCANCEL` (i.e., the OK button or Esc/close), calls `EndDialog` to close the modal dialog and return control to `WndProc`.

## Resources

All UI resources are declared in [`GUI Application.rc`](GUI%20Application.rc) and given symbolic names in [`Resource.h`](Resource.h).

### Resource Symbols (Resource.h)

| Symbol | Value | Purpose |
|---|---|---|
| `IDS_APP_TITLE` | 103 | String: main window title ("GUI Application") |
| `IDR_MAINFRAME` | 128 | Icon reference used inside the About dialog |
| `IDD_GUIAPPLICATION_DIALOG` | 102 | Reserved dialog ID (unused by current resources) |
| `IDD_ABOUTBOX` | 103 | The About dialog template |
| `IDM_ABOUT` | 104 | Menu/accelerator command: show About box |
| `IDM_EXIT` | 105 | Menu command: exit the application |
| `IDI_GUIAPPLICATION` | 107 | Main (large) application icon |
| `IDI_SMALL` | 108 | Small application icon (title bar / taskbar) |
| `IDC_GUIAPPLICATION` | 109 | Shared ID for the window class name string, the menu, and the accelerator table |
| `IDC_MYICON` | 2 | Legacy/unused icon control ID |
| `IDC_STATIC` | -1 | Standard "no specific ID" marker for static dialog controls |

### Menu

Bound to every window of class `IDC_GUIAPPLICATION`:

```
File
  Exit                     → IDM_EXIT
Help
  About ...                → IDM_ABOUT
```

### Accelerator Table

| Key | Command |
|---|---|
| `Alt+?` | `IDM_ABOUT` |
| `Alt+/` | `IDM_ABOUT` |

### Dialog: About Box

`IDD_ABOUTBOX` — a fixed-size (170×62 DLU), modal, system-menu dialog containing:

- The application icon (`IDR_MAINFRAME`).
- Static text: "GUI Application, Version 1.0"
- Static text: "Copyright (c) 2023"
- An **OK** default push-button (`IDOK`).

### String Table

| ID | Value |
|---|---|
| `IDC_GUIAPPLICATION` | `"GUIAPPLICATION"` (window class name) |
| `IDS_APP_TITLE` | `"GUI Application"` (window title) |

### Icons

- [`GUI Application.ico`](GUI%20Application.ico) — main icon, referenced as `IDI_GUIAPPLICATION`.
- [`small.ico`](small.ico) — small icon variant, referenced as `IDI_SMALL`.

Both are declared in the `.rc` file with the icon of lowest resource ID listed first, which is what Windows uses to determine the icon shown for the executable in File Explorer.

## Build System

### Project File (.vcxproj)

[`GUI Application.vcxproj`](GUI%20Application.vcxproj) is an MSBuild project (`VCProjectVersion` 16.0, i.e. Visual Studio 2019/2022-compatible format) with:

- `RootNamespace`: `GUIApplication`
- `Keyword`: `Win32Proj` (native, non-MFC/ATL desktop app)
- `WindowsTargetPlatformVersion`: `10.0` (latest installed Windows 10/11 SDK)
- `PlatformToolset`: `v143` (Visual Studio 2022's MSVC toolset)

### Build Configurations

Four configuration/platform combinations are defined:

| Configuration | Platform |
|---|---|
| Debug | Win32 (x86) |
| Release | Win32 (x86) |
| Debug | x64 |
| Release | x64 |

All four produce an `Application` (`ConfigurationType = Application`, i.e. a `.exe`), use the **Unicode** character set, and target the **Windows** GUI subsystem (`SubSystem = Windows`, meaning the exe has no console window by default).

### Compiler / Linker Settings

- **Warning level**: Level 3 in all configurations.
- **SDL checks**: enabled (`SDLCheck = true`) — Microsoft's basic Security Development Lifecycle static checks.
- **Conformance mode**: enabled (`ConformanceMode = true`) — stricter standards-conformant parsing.
- **Preprocessor definitions**:
  - Debug: `WIN32` (Win32 only); `_DEBUG`; `_WINDOWS`
  - Release: `WIN32` (Win32 only); `NDEBUG`; `_WINDOWS`
- **Release-only optimizations**: `FunctionLevelLinking`, `IntrinsicFunctions`, `WholeProgramOptimization`, `EnableCOMDATFolding`, `OptimizeReferences`.
- **Debug info**: generated in every configuration (`GenerateDebugInformation = true`), including Release, for easier post-mortem debugging.

Item groups declare the following build inputs:

- `ClInclude`: `framework.h`, `GUI Application.h`, `Resource.h`, `targetver.h`
- `ClCompile`: `GUI Application.cpp`
- `ResourceCompile`: `GUI Application.rc`
- `Image`: `GUI Application.ico`, `small.ico`

## Prerequisites

- **Windows 10/11**
- **Visual Studio 2022** (Community, Professional, or Enterprise) with the **"Desktop development with C++"** workload installed, which provides:
  - The MSVC v143 x86/x64 build tools
  - A Windows 10/11 SDK
  - MSBuild
- No third-party libraries (e.g. SFML) are currently required to build, since none are referenced by the project.

## Building the Project

### Using Visual Studio IDE

1. Open `GUI Application.vcxproj` directly in Visual Studio 2022 (or generate/open a `.sln` that references it).
2. Select a configuration/platform from the toolbar, e.g. **Debug | x64** or **Release | x64**.
3. Build via **Build → Build Solution** (`Ctrl+Shift+B`).
4. Run via **Debug → Start Debugging** (`F5`) or **Start Without Debugging** (`Ctrl+F5`).

### Using MSBuild from the Command Line

From a **Developer Command Prompt for VS 2022** (or `Developer PowerShell`):

```powershell
msbuild "GUI Application.vcxproj" /p:Configuration=Release /p:Platform=x64
```

Valid `Configuration` values: `Debug`, `Release`.
Valid `Platform` values: `Win32`, `x64`.

The resulting executable is placed under a generated `x64\Release\` (or equivalent) output folder alongside the project.

## Running the Application

Launch the built `GUI Application.exe`. You'll see:

- An empty window titled **"GUI Application"**.
- A **File** menu with **Exit**.
- A **Help** menu with **About ...**, which opens a small modal dialog showing the app name, version, and copyright, dismissible via **OK**.

There is currently no in-window content, game selection UI, or playable game — see the [Roadmap](#roadmap-reaching-the-intended-multi-game-launcher-scope) below.

## File-by-File Reference

| File | Description |
|---|---|
| [`GUI Application.cpp`](GUI%20Application.cpp) | All application logic: `wWinMain`, `MyRegisterClass`, `InitInstance`, `WndProc`, `About`. |
| [`GUI Application.h`](GUI%20Application.h) | Tiny header that just `#include`s `resource.h`; included by `GUI Application.cpp`. |
| [`framework.h`](framework.h) | Precompiled/umbrella header: pulls in `targetver.h`, defines `WIN32_LEAN_AND_MEAN`, includes `<windows.h>` and core CRT headers (`stdlib.h`, `malloc.h`, `memory.h`, `tchar.h`). |
| [`targetver.h`](targetver.h) | Includes `<SDKDDKVer.h>` to target the highest Windows platform available, per Microsoft's standard template. |
| [`Resource.h`](Resource.h) | Auto-generated numeric IDs for every resource symbol used by both the `.cpp` and `.rc` files. Marked `//{{NO_DEPENDENCIES}}`, meaning it's normally regenerated by the Visual Studio Resource Editor rather than hand-edited. |
| [`GUI Application.rc`](GUI%20Application.rc) | Windows resource script defining the icons, menu, accelerator table, About dialog, and string table (see [Resources](#resources)). |
| [`GUI Application.ico`](GUI%20Application.ico) / [`small.ico`](small.ico) | Multi-resolution icon files used for the app/taskbar icon. |
| [`GUI Application.vcxproj`](GUI%20Application.vcxproj) | MSBuild project file — build configurations, compiler/linker settings, source file list (see [Build System](#build-system)). |
| [`GUI Application.vcxproj.filters`](GUI%20Application.vcxproj.filters) | Purely cosmetic: groups files into Solution Explorer virtual folders ("Header Files", "Source Files", "Resource Files"). Doesn't affect the actual build. |
| [`GUI Application.vcxproj.user`](GUI%20Application.vcxproj.user) | Per-developer, machine-local IDE settings (e.g. debugger working directory). Not meaningful to other checkouts and typically excluded from version control. |
| `RCa25372` | Stray leftover **temporary file from the RC (resource) compiler** — see [Known Issues](#known-issues--housekeeping). |
| [`README.md`](README.md) | This documentation file. |

## Known Issues / Housekeeping

- **`RCa25372` should not be committed.** It's a transient, UTF-16-encoded intermediate file the Visual Studio Resource Compiler (`rc.exe`) writes to expand `#include`s in `GUI Application.rc` before compiling it into a `.res`. Its embedded `#line` directives reveal the original author's local path (`E:\Documents\2nd semester\Programming\Final Project\GUI Application\...`), confirming it's machine-generated build output rather than source. It should be deleted from the repo and ignored going forward.
- **No `.gitignore`.** Because there's no ignore file, build output directories (`Debug/`, `Release/`, `x64/`, `.vs/`, `*.obj`, `*.res`, `*.ilk`, `*.pdb`, etc.) and the machine-specific `.vcxproj.user` file are all at risk of being committed accidentally in future changes.
- **`WM_PAINT` is an empty stub.** No drawing occurs; the window currently just shows the default window background.
- **`IDD_GUIAPPLICATION_DIALOG` (102) is declared but unused** — no dialog template with that ID exists in the `.rc` file. Harmless, but a leftover from the wizard template.
- **Copyright year is stale** ("Copyright (c) 2023") relative to the current date.

## Roadmap: Reaching the Intended "Multi-Game Launcher" Scope

Based on the original project description, the following would need to be implemented on top of this skeleton:

1. **Add SFML** to the project (via vcpkg or manual SDK linking: include/lib paths, `sfml-graphics`, `sfml-window`, `sfml-system` link libraries, and the required runtime DLLs alongside the executable).
2. **Build a launcher screen** — either an SFML render window or additional Win32 controls — that lets the user pick between the available games (e.g. Tetris, Flappy Bird).
3. **Console buffer text renderer** — a module wrapping the Windows Console API (`GetStdHandle(STD_OUTPUT_HANDLE)`, `SetConsoleCursorPosition`, `WriteConsoleOutputW`/`WriteConsoleOutputCharacterW`) for fast, flicker-free text-mode rendering, likely used by one or both games instead of/alongside SFML.
4. **Tetris module**: board grid data structure, tetromino shapes, and matrix-rotation logic (e.g. rotating a piece's cell coordinates via a rotation matrix or precomputed rotation states), line-clear detection, scoring, gravity/drop timing, and input handling.
5. **Flappy Bird module**: a custom physics loop (gravity acceleration applied to the bird's vertical velocity/position each tick), scrolling pipe obstacles, collision detection, and cursor/keyboard-driven "flap" input.
6. **Game loop integration** with the existing Win32 message pump — likely replacing the blocking `GetMessage` loop with a `PeekMessage`-based loop (or a separate SFML event loop) so games can render continuously rather than only in response to window messages.
7. **Packaging**: ensure SFML runtime DLLs and any game asset files (sprites, fonts) ship alongside the built executable.
8. **`.gitignore`** covering VS/MSBuild build artifacts, and removal of the stray `RCa25372` file.

## License

No license file is currently present in this repository. All rights are reserved by the author unless a license is added.
