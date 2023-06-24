/**
 * hello-4.c - demonstrates module documentation.
 */
// needed for the macros
#include <linux/init.h>
// needed by all modules
#include <linux/module.h>
// needed for pr_info()
#include <linux/printk.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fahmi");
MODULE_DESCRIPTION("learning linux kernel module");

static int __init init_hello_4(void)
{
    pr_info("hello world 4\n");

    return 0;
}

static void __exit cleanup_hello_4(void)
{
    pr_info("goodbye world 4\n");
}

module_init(init_hello_4);
module_exit(cleanup_hello_4);
