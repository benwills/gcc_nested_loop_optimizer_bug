This is an example of a possible bug in the GCC-12 compiler when nesting loops
and reading past the end of array bounds.

When compiling with -O2 or -O3, and there are _reads_ (no writes)
past the end of the tokens array, `i > iEnd` is never triggered,
and the program eventually segfaults.

Compiling without optimizations or with -O1 appears to compile
and execute correctly. Compiling with -O2 or -O3 results in segfaults.

To run this on your system:
$ git clone git@github.com:benwills/gcc_nested_loop_optimizer_bug.git
$ cd gcc_nested_loop_optimizer_bug
$ chmod a+x buildExec.sh
$ ./buildExec.sh

When it runs, it will loop through the various optimization levels and pipe
the output to `output.ON.txt` where N is the optimization level.

Also important: the way this loop is designed, it it is logically incorrect.
The `i <= iEnd` should be `i < iEnd`. When this is changed, the program
runs as desired with all optimization levels.

So it may be important to note that this error occurs on logically-incorrect
code.

My system is running gcc-12:

$ gcc-12 -v
Using built-in specs.
COLLECT_GCC=gcc-12
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/12/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:amdgcn-amdhsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 12.1.0-2ubuntu1~22.04' --with-bugurl=file:///usr/share/doc/gcc-12/README.Bugs --enable-languages=c,ada,c++,go,d,fortran,objc,obj-c++,m2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-12 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --enable-libphobos-checking=release --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --enable-cet --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-12-sZcx2y/gcc-12-12.1.0/debian/tmp-nvptx/usr,amdgcn-amdhsa=/build/gcc-12-sZcx2y/gcc-12-12.1.0/debian/tmp-gcn/usr --enable-offload-defaulted --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 12.1.0 (Ubuntu 12.1.0-2ubuntu1~22.04) 
