#include <linux/module.h>        // 核心模块头文件
#include <linux/fs.h>            // 文件系统头文件
#include <linux/cdev.h>          // 字符设备头文件
#include <linux/device.h>        // 设备模型头文件
#include <linux/gpio.h>          // GPIO子系统头文件[reference:0]
#include <linux/uaccess.h>       // 用户空间数据访问头文件
#include <linux/errno.h>         // 错误码头文件

#define DEVICE_NAME "gpioled"    // 设备名称
#define LED_GPIO 18              // 根据之前的确认，GPIO编号为18

static dev_t dev_num;            // 设备号
static struct cdev led_cdev;     // 字符设备结构体
static struct class *led_class;  // 设备类
static struct device *led_device;

// 驱动写操作：从用户空间接收指令，控制LED亮/灭[reference:1]
static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos) {
    char cmd;

    // 从用户空间安全地拷贝数据[reference:2]
    if (copy_from_user(&cmd, buf, 1)) {
        return -EFAULT;
    }

    // 根据指令设置GPIO电平
    // '1' 点亮LED, '0' 熄灭LED
    if (cmd == '0') {
        gpio_set_value(LED_GPIO, 0);
        printk(KERN_INFO "gpioled: LED OFF\n");
    } else if (cmd == '1') {
        gpio_set_value(LED_GPIO, 1);
        printk(KERN_INFO "gpioled: LED ON\n");
    } else {
        return -EINVAL;
    }

    return count;
}

// 文件操作结构体[reference:3][reference:4]
static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write,
};

// 模块初始化函数
static int __init led_init(void) {
    int ret;

    // 1. 动态申请GPIO
    if (!gpio_is_valid(LED_GPIO)) {
        printk(KERN_ERR "gpioled: Invalid GPIO %d\n", LED_GPIO);
        return -ENODEV;
    }
    ret = gpio_request(LED_GPIO, "led_gpio");
    if (ret) {
        printk(KERN_ERR "gpioled: Failed to request GPIO %d\n", LED_GPIO);
        return ret;
    }
    // 设置为输出模式，初始状态为低电平（熄灭LED）
    ret = gpio_direction_output(LED_GPIO, 0);
    if (ret) {
        printk(KERN_ERR "gpioled: Failed to set GPIO direction\n");
        gpio_free(LED_GPIO);
        return ret;
    }

    // 2. 动态分配字符设备号[reference:5]
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "gpioled: Failed to allocate device number\n");
        gpio_free(LED_GPIO);
        return ret;
    }

    // 3. 初始化并添加字符设备到内核
    cdev_init(&led_cdev, &led_fops);
    led_cdev.owner = THIS_MODULE;
    ret = cdev_add(&led_cdev, dev_num, 1);
    if (ret) {
        printk(KERN_ERR "gpioled: Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1);
        gpio_free(LED_GPIO);
        return ret;
    }

    // 4. 创建设备类和设备节点，这样加载后/dev下会自动出现设备文件
    led_class = class_create(THIS_MODULE, "led_class");
    if (IS_ERR(led_class)) {
        printk(KERN_ERR "gpioled: Failed to create class\n");
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        gpio_free(LED_GPIO);
        return PTR_ERR(led_class);
    }

    led_device = device_create(led_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(led_device)) {
        printk(KERN_ERR "gpioled: Failed to create device\n");
        class_destroy(led_class);
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        gpio_free(LED_GPIO);
        return PTR_ERR(led_device);
    }

    printk(KERN_INFO "gpioled: Driver loaded. Control LED with: echo '1' > /dev/%s (ON), echo '0' > /dev/%s (OFF)\n", DEVICE_NAME, DEVICE_NAME);
    return 0;
}

// 模块卸载函数
static void __exit led_exit(void) {
    // 按照相反的顺序释放所有资源[reference:6]
    device_destroy(led_class, dev_num);
    class_destroy(led_class);
    cdev_del(&led_cdev);
    unregister_chrdev_region(dev_num, 1);
    gpio_free(LED_GPIO);
    printk(KERN_INFO "gpioled: Driver unloaded.\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wang");
MODULE_DESCRIPTION("A simple GPIO LED driver for RK3506");