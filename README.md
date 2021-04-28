# DripLoader (PoC)
Evasive shellcode loader for bypassing event-based injection detection, without necessarily suppressing event collection (still added direct syscalls, just coz I can).

The project is aiming to highlight limitations of event-driven injection identification, and show the need for more advanced memory scanning in EDR software.

## DripLoader evades common EDRs by:
- blending in by generating only common CRT and allocation events which vendors are forced to drop by default
- avoiding multi-event correlation by introducing delays in execution

## What does DripLoader do
- Identifies a base address suitable for our payload
- Reserves enough AllocationGranularity (64kB) sized, NO_ACCESS memory segments at the base address
- Loops over those
    - Allocating PageSize (4kB) sized, writable segments
    - Writing shellcode
    - Reprotecting as RX
- Overwrites prologue of one ntdll function in the remote process memory space with a jmp to our base
- Drops a thread on that trampoline 

It's able to bypass Defender VM allocation alerting, and others. I'll explain the thinking behind each step in a blog post comming end of the week.

