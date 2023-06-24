# The Linux Kernel Module programming Guide

## strace

```shell
sudo dnf install strace
```

## a backup copy of the makefile

```shell
cp /lib/modules/`uname -r`/build/Makefile linux-`uname -r`
```

# References
- https://sysprog21.github.io/lkmpg/
- https://github.com/sysprog21/lkmpg
- https://strace.io/
- Understanding the Linux Kernel, Third Edition 3rd Edition
- https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/Documentation/kbuild/modules.rst
- https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/Documentation/admin-guide/devices.txt
