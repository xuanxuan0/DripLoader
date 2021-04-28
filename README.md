# DripLoader (PoC)
Evasive shellcode loader for bypassing event-based injection detection, without necessarily suppressing event collection (still added direct syscalls, just coz I can).

The project is aiming to highlight limitations of event-driven injection identification, and show the need for more advanced memory scanning in EDR software.

## DripLoader evades common EDRs by:
- using the most risky APIs possible like `NtAllocateVirtualMemory` and ``NtCreateThreadEx
- blending with call arguments, vendors are forced to drop most by default, or log but can't detect
- avoiding multi-event correlation by introducing delays 

## What does DripLoader do
- Identifies a base address suitable for our payload
- Reserves enough `AllocationGranularity` (64kB) sized, `NO_ACCESS` memory segments at the base address
- Loops over those
    - Allocating `PageSize` (4kB) sized, writable segments
    - Writing shellcode
    - Reprotecting as RX
- Overwrites prologue of one ntdll function in the remote process memory space with a jmp to our base
- Drops a thread on that trampoline 

It's able to bypass Defender VM allocation alerting, and others. I'll explain the thinking behind each step in a blog post comming end of the week.

![driploader](https://user-images.githubusercontent.com/32537788/116470458-bc5f4e00-a873-11eb-9fca-42e277f6a3eb.png)
