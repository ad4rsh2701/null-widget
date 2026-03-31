# null-widget
![Status](https://img.shields.io/badge/status-alpha-orange)
![Version](https://img.shields.io/github/v/release/ad4rsh2701/null-widget?include_prereleases&label=latest%20pre-release)

A Windows API and C++ based Windows widget application.

---

## Installation

You can install `null-widget` by compiling the project files, or by downloading and
running the binaries present in release and running them.

Strictly for Windows, obviously.

To compile, run
```bash
  git clone https://github.com/ad4rsh2701/null-widget
  cd null-widget

  cmake -G "Ninja" -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build
```
For development, always use `-DCMAKE_BUILD_TYPE=Debug` flag while building.

> `null-widget` successfully compiles using the `llvm clang` compiler, I cannot garuntee if it will compile using other compilers like GCC or MSVC ...yet.

And to close the widget, you will need to manually kill the exe from the taskbar :P

---

## Features.. I guess?

A nifty little floating window on your screen with Day and Time. What more could you possibly need?

- Low memory usage
- Multiple fonts support
- To-Do integration (Soon)

---
## Known Issues

### 1. Lack of Cross-Compiler Support
  - Yea... only Clang++ is truly supported, if it works on others then, do let me know.
  - Will provide cross-compiler compilation if I feel like it.

Please refere the [Issues](https://github.com/ad4rsh2701/null-widget/issues) section for latest issues
 
 ---
 
 ## FAQs
 
 1. Why? 
    - I felt like it, and actually, the main idea is to integrate my tasks present in my `todo.txt` to be displayed in that widget in some form.
    - I have a general idea of the concept, and with this, the implementation too, so working towards that.
 2. Why not switch to Linux?
    - Good Question
 3. Is this AI-generated or AI-assisted?
    - No, it's not AI generated, however, AI was used to get answers to questions like *"why does WM_CREATE expand to integer 2 and what does it do?"* or *"what is  `lpfnWndProc`??!"*.
    - AI was also used to create a basic template/idea code at the start, which is present [here](./.notes/archive/old.cpp) if you want to check it out, I obviously had no idea of this Macro abomination called WindowsAPI
