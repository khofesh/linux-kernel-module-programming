/**
 * @file stop.c
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

void cleanup_module(void)
{
    pr_info("short is the life of a kernel module\n");
}

MODULE_LICENSE("GPL");
