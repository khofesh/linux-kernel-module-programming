# The Linux Kernel Module programming Guide

## strace

```shell
sudo dnf install strace
```

## a backup copy of the makefile

```shell
cp /lib/modules/`uname -r`/build/Makefile linux-`uname -r`
```

## SELinux in enforcing mode

The issue you are facing is most likely related to the permissions set by SELinux. SELinux is a security mechanism used in some Linux distributions, including Fedora, to enforce mandatory access control policies.

In enforcing mode, SELinux might be preventing the write operation to the `/sys/kernel/mymodule/myvariable` file. To resolve this issue, you can try the following options:

1. Use `sudo tee`:

   ```
   echo "32" | sudo tee /sys/kernel/mymodule/myvariable
   ```

   The `tee` command is a utility that reads from standard input and writes to standard output and files simultaneously. Using `sudo tee` allows you to write to the file with the necessary root privileges.

2. Temporarily disable SELinux enforcement:

   ```
   sudo setenforce 0
   sudo echo "32" > /sys/kernel/mymodule/myvariable
   sudo setenforce 1
   ```

   The `setenforce` command is used to change SELinux modes. Setting it to `0` disables enforcement temporarily, allowing you to perform the write operation. However, keep in mind that disabling SELinux can impact system security, so it's generally recommended to enable it again after you're done.

3. Adjust SELinux file contexts and permissions:

   ```
   sudo chcon -t sysfs_t /sys/kernel/mymodule/myvariable
   sudo echo "32" > /sys/kernel/mymodule/myvariable
   ```

   The `chcon` command is used to change the SELinux security context of files. By changing the file context to `sysfs_t`, you might grant the necessary permissions to write to the file. However, this approach might not work if the SELinux policy explicitly prohibits writing to that file.

It's worth noting that modifying system files and kernel variables should be done with caution, as it can have unintended consequences. Make sure you have a good understanding of the implications and ensure that any changes you make align with your system's requirements.

# References

- https://sysprog21.github.io/lkmpg/
- https://github.com/sysprog21/lkmpg
- https://strace.io/
- Understanding the Linux Kernel, Third Edition 3rd Edition
- https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/Documentation/kbuild/modules.rst
- https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/Documentation/admin-guide/devices.txt
- ioctl numbers - https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/Documentation/userspace-api/ioctl/ioctl-number.rst
