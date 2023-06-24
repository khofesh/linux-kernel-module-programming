/**
 * @file start.c
 * @author your name (you@domain.com)
 * @brief illustration of multi filed modules
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void)
{
    pr_info("hello world, the kernel speaking\n");

    return 0;
}

MODULE_LICENSE("GPL");