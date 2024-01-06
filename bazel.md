# Some notes on adding bazel

## But before that, after I've added bazel support (for fun, but also convenience)

I've found that it was already done - at least once - https://github.com/search?q=%22ftxui.build%22&ref=opensearch&type=code
https://github.com/search?q=%22ftxui.build%22&ref=opensearch&type=code

I've also found some cool projects this way, so all good!

In any case, I'm doing this more for my own education, but it might end up being useful.

## Changes

On Windows, FTXUI requires UNICODE (-DUNICODE, -D_UNICODE). I haven't spoken to the author about this (Arthur), but it could be that specific "W" function, instead of "A" is needed (e.g. CreateFileW vs CreateFileA).
I wanted to remove this define, as if this was the only use case, we can simply switch to explicitly the "W" function. Some findings:

After building with bazel (`bazel build //...`), and going to the (default) bazel folder, then using `llvm-nm` to dump obj files and looking for all undefined (" U "), also dll imports ("__imp_"), and ignore any C++ symbols,
i've found this:

C:\Users\dstanev\_bazel_dstanev\2taz4d3b\execroot\_main\bazel-out\x64_windows-fastbuild\bin\src\_objs>llvm-nm dom\*.obj component\*.obj screen\*.obj | grep " U " | grep __imp_ | grep -v "@" | sort | uniq
         U __imp__beginthreadex
         U __imp__invalid_parameter_noinfo_noreturn
         U __imp__wassert
         U __imp_ceilf
         U __imp_cosf
         U __imp_fmodf
         U __imp_GetConsoleMode
         U __imp_GetConsoleScreenBufferInfo
         U __imp_getenv
         U __imp_GetNumberOfConsoleInputEvents
         U __imp_GetStdHandle
         U __imp_powf
         U __imp_ReadConsoleInputW
         U __imp_SetConsoleCP
         U __imp_SetConsoleMode
         U __imp_SetConsoleOutputCP
         U __imp_signal
         U __imp_sinf
         U __imp_sqrtf
         U __imp_terminate
         U __imp_WaitForSingleObject

There is only one function -> `__imp_ReadConsoleInputW` that needs UNICODE. Actually the function `ReadConsoleInput` is a macro, which with -DUNICODE gets defined to `ReadConsoleInputW`, so I guess that's all it's needed!