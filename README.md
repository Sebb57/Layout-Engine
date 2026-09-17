# Layout-Engine

## Compilation

### lib only

```bash
cmake -B build -DBUILD_TEST_APP=OFF
cmake --build build
````

### lib + test main

```bash
cmake -B build -DBUILD_TEST_APP=ON
cmake --build build
./build/layout-test
```
