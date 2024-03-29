/**
 * hello-2.c - demonstrating the module_init() and module_exit() macros.
 * this is preferred over using init_module() and cleanup_module().
 */
// needed for the macros
#include <linux/init.h>
// needed by all modules
#include <linux/module.h>
// needed for pr_info()
#include <linux/printk.h>

static int __init hello_2_init(void)
{
    pr_info("hello world 2\n");

    return 0;
}

static void __exit hello_2_exit(void)
{
    pr_info("goodbye world 2\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);

MODULE_LICENSE("GPL");
