
````markdown
```bash
cd rex_zigbee_stack_library_release/rex_zigbee_stack_library
sudo chmod -R a+x tools
mkdir ninja_build
cd ninja_build
rm -rf ./*
cmake -G Ninja -DTOOLCHAIN_PATH="../tools/toolchain/linux/tc32" ..
````

**Build target `<rex_stack_router_demo>`:**

```bash
# optional, clean first
ninja -t clean rex_stack_router_demo 
ninja rex_stack_router_demo -j$(nproc)
```

**Build all targets:**

```bash
# optional, clean first
ninja -t clean
ninja -j$(nproc)
```

**Output:**

```
File: rex_zigbee_stack_library/build/rex_stack_router_demo/REX_ZB_ROT_On_Off_Demo[20250101].bin
```
