# ngircd Stack/Heap Fix Summary

## Problem
ngircd was showing warnings:
```
STACK USING 524 UNUSED HEAP
STACK USING 518 HEAP
STACK USING 670 HEAP
```

This indicated the stack was growing dangerously close to (or into) the heap space, risking memory corruption.

## Root Cause
1. **Large stack buffers**: `READBUFFER_LEN` (2048 bytes) in conn.c creates large stack-allocated arrays
2. **Insufficient stack size**: Previous stack size of 4KB (0x1000) was too small
3. **Deep call chains**: Function calls add overhead on top of local variables

When stack usage reached 670 bytes remaining before hitting heap, it meant only ~3.3KB of stack was being used, but local buffers alone were 2KB.

## Solution Applied

### Changes to `build-elks-ngircd.sh`:

**Before:**
```bash
--stack 0x1000 --heap 0x4000
# Stack: 4KB, Heap: 16KB
```

**After:**
```bash
--stack 0x2000 --heap 0x3000
# Stack: 8KB, Heap: 12KB  
```

### Why These Values:

1. **Stack doubled to 8KB (0x2000)**:
   - Accommodates 2048-byte buffers
   - Provides headroom for function calls
   - Prevents stack overflow into heap

2. **Heap reduced to 12KB (0x3000)**:
   - ELKS has 64KB data segment limit
   - Total = Stack (8KB) + Heap (12KB) + Static Data (~44KB) ≈ 64KB
   - Larger heap (16KB+ or 24KB) caused "default data segment exceeds maximum size" error

## Memory Layout (ELKS 64KB limit)

```
|------------------|
|  Static Data     |  ~44 KB
|  (globals, BSS)  |
|------------------|
|  Heap (malloc)   |  12 KB (0x3000)
|  grows up ↑      |
|------------------|
|  Stack           |   8 KB (0x2000)
|  grows down ↓    |
|------------------|
   Total: ~64 KB
```

## Expected Result

After rebuild, ngircd should:
- ✅ No longer show "STACK USING X HEAP" warnings
- ✅ Have sufficient stack space for 2KB buffers + overhead
- ✅ Have enough heap for dynamic allocations
- ✅ Fit within ELKS 64KB data segment limit

## Build Command

```bash
cd /home/arduino/elks/ngircd-broken-elks
./build-elks-ngircd.sh clean
./build-elks-ngircd.sh
```

Output: `build-elks/bin/ngircd.os2` (211KB)

## Testing

Deploy the new ngircd.os2 to ELKS and run it. The stack warnings should no longer appear.

## Files Modified

1. `build-elks-ngircd.sh` - Updated ewlink parameters
2. `ELKS_PORT_CHANGES.txt` - Documented the changes
