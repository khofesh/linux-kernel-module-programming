# SELinux in enforcing mode

```shell
[fahmad@ryzen hello-sysfs]$  make
...
[fahmad@ryzen hello-sysfs]$  sudo ../../insmod.sh hello-sysfs.ko
[sudo] password for fahmad:
[fahmad@ryzen hello-sysfs]$  sudo lsmod | grep hello_sysfs
hello_sysfs            16384  0
[fahmad@ryzen hello-sysfs]$  cat /sys/kernel/mymodule/myvariable
cat: /sys/kernel/mymodule/myvariable: Permission denied
[fahmad@ryzen hello-sysfs]$  sudo cat /sys/kernel/mymodule/myvariable
0
[fahmad@ryzen hello-sysfs]$  sudo echo "32" > /sys/kernel/mymodule/myvariable
bash: /sys/kernel/mymodule/myvariable: Permission denied
[fahmad@ryzen hello-sysfs]$  ls -lh /sys/kernel/mymodule/myvariable
-rw-rw----. 1 root root 4.0K Jul  1 10:05 /sys/kernel/mymodule/myvariable
[fahmad@ryzen hello-sysfs]$  echo "32" | sudo tee /sys/kernel/mymodule/myvariable
[sudo] password for fahmad:
32
[fahmad@ryzen hello-sysfs]$  sudo cat /sys/kernel/mymodule/myvariable
32
[fahmad@ryzen hello-sysfs]$  sudo rmmod hello_sysfs
```
