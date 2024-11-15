## Performance test of copy and move constructors on simple example

Tested classes: [HeavyToCopy](https://github.com/AlekseyLapunov/Practise_cpp/blob/main/Move-Constructors-Perf-Test/Move-Constructors-Perf-Test/src/heavy_to_copy.hpp#L4) & [HeavyToCopy_Move](https://github.com/AlekseyLapunov/Practise_cpp/blob/main/Move-Constructors-Perf-Test/Move-Constructors-Perf-Test/src/heavy_to_copy.hpp#L24), where the second one has implemented move-constructors and the first does not.

One of tests output executed in release mode (x64 platform):

![HTC-Move/HTC-Copy Ratio = 3.56](https://github.com/AlekseyLapunov/Practise_cpp/blob/main/Move-Constructors-Perf-Test/_.png "Screenshot")
