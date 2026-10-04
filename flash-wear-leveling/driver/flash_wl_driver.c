#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "flash_wl"
#define BUFFER_SIZE 100

static dev_t dev_number;
static struct cdev flash_cdev;
static struct class *flash_class;

static int flash_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "flash_wl: Device opened\n");
    return 0;
}

static int flash_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "flash_wl: Device closed\n");
    return 0;
}

static ssize_t flash_write(struct file *file,
                           const char __user *user_buffer,
                           size_t count,
                           loff_t *offset)
{
    char buffer[BUFFER_SIZE];

    if (count >= BUFFER_SIZE)
        count = BUFFER_SIZE - 1;

    if (copy_from_user(buffer, user_buffer, count))
        return -EFAULT;

    buffer[count] = '\0';

    printk(KERN_INFO "flash_wl: Data received: %s\n", buffer);

    return count;
}

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = flash_open,
    .release = flash_release,
    .write = flash_write
};

static int __init flash_driver_init(void)
{
    int result;

    printk(KERN_INFO "flash_wl: Driver loading\n");

    result = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);

    if (result < 0)
    {
        printk(KERN_ALERT "flash_wl: Failed to allocate device number\n");
        return result;
    }

    cdev_init(&flash_cdev, &fops);

    result = cdev_add(&flash_cdev, dev_number, 1);

    if (result < 0)
    {
        unregister_chrdev_region(dev_number, 1);
        return result;
    }

    flash_class = class_create(DEVICE_NAME);

    if (IS_ERR(flash_class))
    {
        cdev_del(&flash_cdev);
        unregister_chrdev_region(dev_number, 1);
        return PTR_ERR(flash_class);
    }

    device_create(
        flash_class,
        NULL,
        dev_number,
        NULL,
        DEVICE_NAME
    );

    printk(KERN_INFO "flash_wl: Driver loaded successfully\n");

    return 0;
}

static void __exit flash_driver_exit(void)
{
    device_destroy(flash_class, dev_number);
    class_destroy(flash_class);

    cdev_del(&flash_cdev);
    unregister_chrdev_region(dev_number, 1);

    printk(KERN_INFO "flash_wl: Driver unloaded\n");
}

module_init(flash_driver_init);
module_exit(flash_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Satyam");
MODULE_DESCRIPTION("Flash Memory Wear-Leveling Character Device Driver");
