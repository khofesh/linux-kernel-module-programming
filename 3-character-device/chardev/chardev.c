/**
 * @file chardev.c
 * @author your name (you@domain.com)
 * @brief creates a read-only char device that says how many time
 * you have read from the dev file
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <linux/atomic.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
// for sprintf()
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
// for get_user and put_user
#include <linux/uaccess.h>

#include <asm/errno.h>

#include "chardev.h"

#define SUCCESS 0
// dev name as it appears in /proc/devices
#define DEVICE_NAME "chardev"
// max length of the message from the device
#define BUF_LEN 80

/* global variables are declared as static, so are global within the file. */

// major number assigned to our device driver
static int major;

enum
{
    CDEV_NOT_USED = 0,
    CDEV_EXCLUSIVE_OPEN = 1,
};

/* is device open? used to prevent multiple access to device */
static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED);

// the msg the device will give when asked
static char msg[BUF_LEN + 1];

static struct class *cls;

static struct file_operations chardev_fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};

static int __init chardev_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &chardev_fops);

    if (major < 0)
    {
        pr_alert("registering char device failed with %d\n", major);

        return major;
    }

    pr_info("i was assigned major number %d.\n", major);

    cls = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    pr_info("device created on /dev/%s\n", DEVICE_NAME);

    return SUCCESS;
}

static void __exit chardev_exit(void)
{
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);

    // unregister the device
    unregister_chrdev(major, DEVICE_NAME);
}

/* methods */

/**
 * @brief called when a process tries to open the device file,
 * like "sudo cat /dev/chardev"
 */
static int device_open(struct inode *inode, struct file *file)
{
    static int counter = 0;

    if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN))
    {
        return -EBUSY;
    }

    sprintf(msg, "I already told %d times hello world!\n", counter++);
    try_module_get(THIS_MODULE);

    return SUCCESS;
}

/**
 * @brief called when a process closes the device file.
 *
 * @return int
 */
static int device_release(struct inode *inode, struct file *file)
{
    // we're now ready for our next caller
    atomic_set(&already_open, CDEV_NOT_USED);

    /**
     * @brief decrement the usage count, or else once you opened the file,
     * you will never get rid of the module.
     */
    module_put(THIS_MODULE);

    return SUCCESS;
}

/**
 * @brief called when a process, which already opened the dev file,
 * attempts to read from it.
 *
 * @param filp see include/linux/fs.h
 * @param buffer buffer to fill with data
 * @param length length of the buffer
 * @param offset
 * @return ssize_t
 */
static ssize_t device_read(struct file *filp, char __user *buffer,
                           size_t length, loff_t *offset)
{
    // number of bytes actually written to the buffer
    int bytes_read = 0;
    const char *msg_ptr = msg;

    if (!*(msg_ptr + *offset))
    {
        // reset the offset
        *offset = 0;
        // signify end of file
        return 0;
    }

    msg_ptr += *offset;

    // actually put the data into the buffer
    while (length && *msg_ptr)
    {
        /* The buffer is in the user data segment, not the kernel
         * segment so "*" assignment won't work. We have to use
         * put_user which copies data from the kernel data segment to
         * the user data segment.
         */
        put_user(*(msg_ptr++), buffer++);
        length--;
        bytes_read++;
    }

    *offset += bytes_read;

    // most read functions return the number of bytes put into the buffer.
    return bytes_read;
}

/**
 * @brief called when a process writes to dev file:
 * echo "hi" > /dev/hello
 *
 * @param filp
 * @param buff
 * @param len
 * @param off
 * @return ssize_t
 */
static ssize_t device_write(struct file *filp, const char __user *buff, size_t len,
                            loff_t *off)
{
    pr_alert("sorry, this operation is not supported.\n");
    return -EINVAL;
}

module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
