```shell
[fahmad@ryzen hello-5]$ sudo insmod hello-5.ko mystring="bebop" myintarray=-1
[sudo] password for fahmad:
[fahmad@ryzen hello-5]$ sudo dmesg -t | tail -7
myshort is a short integer: 1
myint is an integer: 420
mylong is a long integer: 9999
mystring is a string: bebop
myintarray[0] = -1
myintarray[1] = 420
got 1 arguments for myintarray.
[fahmad@ryzen hello-5]$ sudo rmmod hello_5
[fahmad@ryzen hello-5]$ sudo dmesg -t | tail -1
goodbye world 5

[fahmad@ryzen hello-5]$  sudo insmod hello-5.ko mystring="verylongstringhere" myintarray=-1,-1
[fahmad@ryzen hello-5]$  sudo dmesg -t | tail -7
myshort is a short integer: 1
myint is an integer: 420
mylong is a long integer: 9999
mystring is a string: verylongstringhere
myintarray[0] = -1
myintarray[1] = -1
got 2 arguments for myintarray.

```
