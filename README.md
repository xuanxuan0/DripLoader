# DripLoader (PoC)
![msbuild](https://github.com/xinbailu/DripLoader/actions/workflows/msbuild.yml/badge.svg)

Evasive shellcode loader for bypassing event-based injection detection, without necessarily suppressing event collection (still added direct syscalls, just so I don't have to deal with AV). The project is aiming to highlight limitations of event-driven injection identification, and show the need for more advanced memory scanning and smarter local agent software inventories in EDR.

## DripLoader evades common EDRs by:
- using the most risky APIs possible like `NtAllocateVirtualMemory` and `NtCreateThreadEx`
- blending in with call arguments to create events that vendors are forced to drop or log&ignore due to volume
- avoiding multi-event correlation by introducing delays 

## What does DripLoader do
- Identifies a base address suitable for our payload
- Reserves enough `AllocationGranularity` (64kB) sized, `NO_ACCESS` memory segments at the base address
- Loops over those
    - Allocating `PageSize` (4kB) sized, writable segments
    - Writing shellcode
    - Reprotecting as `RX`
- Overwrites prologue of one `ntdll` function in the remote process memory space with a `jmp` to our base
- Drops a thread on that trampoline 

I'll explain the thinking behind each step in a blog post comming end of the week.

## And so
- It's able to fully bypass many EDR injection detections, including Defender ATP. 
- Bypasses simple thread-centric scanners like `Get-InjectedThread`. Persisting within a process is another story, and this is up to the payload author. 
- It is `sRDI`-compatible, but if your payload creates another local thread you will lose the benefit of thread start address in `ntdll`.

To test it out of the box
- compile/download
- XOR your binary shellcode blob file with default key 0x08, name it `blob.bin`
- place both files in the same directory 
- run it and follow the prompts or ./DripLoader.exe <target_pid> <delay_per_step_ms>

I attached an example `MessageBox` blob for your pleasure, be aware though it's size is unrealistically small for a payload.

![driploader](https://user-images.githubusercontent.com/32537788/116470458-bc5f4e00-a873-11eb-9fca-42e277f6a3eb.png)

ASCII arts are essential for tools like this to work
![image](https://user-images.githubusercontent.com/32537788/116482174-eb31f000-a884-11eb-844d-9db69cdbe20d.png)

