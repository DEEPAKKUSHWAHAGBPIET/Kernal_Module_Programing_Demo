### Output:
```
![output_syscalls](https://github.com/user-attachments/assets/32fc9ecb-7d5e-4b6c-a8c1-8326bcabd687)

```

## User Space
```
Runs unprivileged code (applications: bash, vim, python).

Access to kernel and hardware only via system calls (e.g., open(), read()).

Faults in user space usually only kill the offending process.

Uses standard C library (libc) and system APIs.

Examples: editing files, running programs, network clients.

```

## Kernel Space
````
Runs privileged OS code (kernel core, device drivers, file systems).

Has full access to hardware and all memory.

Bugs can crash or hang the whole machine (kernel panic).

No libc: use kernel APIs (printk(), kmalloc(), copy_from_user()).

Runs in a different CPU mode (privileged), and different memory mapping.

Modules run inside the kernel address space and can register callbacks, handle interrupts, or provide system services.
````
