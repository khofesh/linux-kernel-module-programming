#ifndef CHARDEV_H
#define CHARDEV_H

/* prototypes */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *filp, char __user *buffer,
                           size_t length, loff_t *offset);
static ssize_t device_write(struct file *filp, const char __user *buff, size_t len,
                            loff_t *off);

#endif // CHARDEV_H
