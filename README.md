# null-widget

A Windows API and C++ based Windows widget application.

> Currently, it renders a draggable code-customizable clock widget.
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

### 1. Font mismatch due to local fonts
  - Since I used locally downloaded fonts, these fonts are local to only me and not on your device.
  - This will cause error while compilation itself, as the fonts will be not found on your system.
  - Or if you ran the binary, well, that's UB (maybe Windows will use the default font?)
  - A fix for this is being worked on and will be available soon
  - For now, you can download the three fonts from [here](https://fonts.google.com/specimen/Urbanist), [here](https://fonts.google.com/specimen/Doto) and [here](https://fonts.google.com/specimen/Kode+Mono). They are cool fonts to have anyway.

### 2. Lack of Cross-Compiler Support
  - Yea... only Clang++ is truly supported, if it works on others then, do let me know.
  - Will provide cross-compiler compilation if I feel like it.
  
### 3. No `Close Widget` option
 - Yes, there is no option to directly close the widget.
 - For now, you can close the widget by killing the executable from the task manager; it will be named "null-widget"
 - This issue is being worked on as you read this
 
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
