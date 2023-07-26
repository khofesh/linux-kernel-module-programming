/**
 * hello-1.c - the simplest kernel module.
 */
#include <linux/module.h> // required for all modules
// /usr/src/kernels/6.3.12-200.fc38.x86_64/include/linux
#include <linux/printk.h>

int init_module()
{
    pr_info("hello world 1.\n");

    return 0;
}

void cleanup_module()
{
    pr_info("goodby world 1.\n");
}

MODULE_LICENSE("GPL");
