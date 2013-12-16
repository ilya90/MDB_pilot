#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/sysfs.h>
#include <linux/proc_fs.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <asm/segment.h>
#include <linux/buffer_head.h>

#define DEVICE_NAME "gps"
#define CLASS_NAME "gps_class"

#define STATUS_BUFFER_SIZE 200
#define USER_BUFFER_SIZE 200

static int cnt = 0;

struct generic_device_structure {
	dev_t devt;
	struct cdev cdev;
	struct device* dev;
	struct class* class;
	struct semaphore sem;
	dev_t dev_t;
	int major;
	int minor;
	char *status;
};

static struct generic_device_structure gps_dev;

struct file *f = NULL;
/* Creates segment to interact with userspace file*/
mm_segment_t fs;

static int gps_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "IN OPEN FUNCTION\n");
	return 0;
}

static ssize_t gps_read(struct file *filp, const char *user_buff, size_t count, loff_t *offp)
{
	char buf[512];
	char res[512];
	int status = 0;
	printk(KERN_INFO "IN READ FUNCTION\n");
	f = filp_open("/dev/ttyO3", O_RDONLY, 0);
    	if(f == NULL)
        	printk(KERN_ALERT "file_open error!!.\n");
	else{
		// Get current segment descriptor
		fs = get_fs();
		// Set segment descriptor associated to kernel space
		set_fs(get_ds());

		f->f_op->read(f, buf, 512, &f->f_pos);

		// Restore segment descriptor
		set_fs(fs);
		printk(KERN_INFO "buf:%s\n",buf);
		printk(KERN_INFO "Read finished\n");
	}
/*	if(buf[cnt]=="\0") {*/
/*		copy_to_user(user_buff, &buf[cnt], 1);*/
/*		status = 1;*/
/*		cnt++;*/
/*	}*/
/*	else {*/
/*		status = 0;*/
/*		cnt=0;	*/
/*	}*/
	
    	return status;
}

static struct file_operations gps_fops =
{
	.owner 	      =	THIS_MODULE,
	.open         = gps_open,
	.read	      = gps_read,
};

static ssize_t sculld_show_dev(struct device *ddev,
                                struct device_attribute *attr,
                               char *buf){
        return 0;
}
 
static DEVICE_ATTR(gps, S_IRUGO, sculld_show_dev, NULL);

static int __init gps_init_cdev(void)
{
	int error;

	gps_dev.devt = MKDEV(0, 0);

	// Allocate region
	error = alloc_chrdev_region(&gps_dev.devt, 0, 1, DEVICE_NAME);
	if (error < 0) {
		printk(KERN_ALERT "MDB GPS read: alloc_chrdev_region() failed: error = %d \n", error);
		return -1;
	}

	// Assign File operations
	cdev_init(&gps_dev.cdev, &gps_fops);
	gps_dev.cdev.owner = THIS_MODULE;

	// Add device
	error = cdev_add(&gps_dev.cdev, gps_dev.devt, 1);
	if (error) {
		printk(KERN_ALERT "MDB GPS read: cdev_add() failed: error = %d\n", error);
		unregister_chrdev_region(gps_dev.devt, 1);
		return -1;
	}	

	return 0;
}

static int __init gps_init_class(void)
{
	gps_dev.class = class_create(THIS_MODULE, DEVICE_NAME);

	if (!gps_dev.class) {
		printk(KERN_ALERT "MDB GPS read: class_create(i2c) failed\n");
		return -1;
	}

	if (!device_create(gps_dev.class, NULL, gps_dev.devt,NULL, DEVICE_NAME)) {
		class_destroy(gps_dev.class);
		return -1;
	}

	return 0;
}

static int __init gps_init(void)
{
	printk(KERN_INFO "\n");
	printk(KERN_INFO "Initializing MDB GPS Read driver\n");
	printk(KERN_INFO "\n");

	int error;
	// allocate memory for device structure
	memset(&gps_dev, 0, sizeof(struct generic_device_structure));

	// set semaphore
	sema_init(&gps_dev.sem, 1);

	// initialize characther device
	if (gps_init_cdev() < 0) {
		return -1;
	}

	if (gps_init_class() < 0) {
		cdev_del(&gps_dev.cdev);
		unregister_chrdev_region(gps_dev.devt, 1);
		return -1;
	}

	error = device_create_file(gps_dev.dev, &dev_attr_gps);
	if(error < 0) {
		printk(KERN_WARNING "dulldev: Error creatinbg device file.\n");
	}


	return 0;
}

static void __exit gps_exit(void)
{
	printk(KERN_INFO "MDB GPS Read driver: exit()\n");

	/* unregister fs (node) in /dev */
	device_remove_file(gps_dev.dev, &dev_attr_gps);
	printk(KERN_INFO "ONE\n");
	/* destroy device */
	device_destroy(gps_dev.class, gps_dev.devt);
	printk(KERN_INFO "TWO\n");
	/* destroy the class */
  	class_destroy(gps_dev.class);
	printk(KERN_INFO "THREE\n");
	cdev_del(&gps_dev.cdev);
	printk(KERN_INFO "FOUR\n");
	/* cleanup_module is never called if registering failed */
	unregister_chrdev_region(gps_dev.dev_t, 1);


	printk(KERN_WARNING "dulldev: Device unregistered\n");
}

module_init(gps_init);
module_exit(gps_exit);

MODULE_AUTHOR("Ilja Fursov <ilfur12@student.sdu.dk");	
MODULE_DESCRIPTION("Test driver"); 
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION("0.1");




