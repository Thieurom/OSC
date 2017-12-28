/**
 * Programming Project
 * Linux Kernel Modules
 */


#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/list.h>


struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);


/* This function is called when the module is loaded. */
int simple_init(void)
{

    struct birthday *p1, *p2, *p3, *p4, *p5; 
    struct birthday *ptr;

    printk(KERN_INFO "Loading Module\n");

    /* Create 5 struct birthday instances */
    p1 = kmalloc(sizeof(*p1), GFP_KERNEL);
    p1->day = 1;
    p1->month = 8;
    p1->year = 2001;
    INIT_LIST_HEAD(&p1->list);

    p2 = kmalloc(sizeof(*p2), GFP_KERNEL);
    p2->day = 2;
    p2->month = 9;
    p2->year = 2002;
    INIT_LIST_HEAD(&p2->list);

    p3 = kmalloc(sizeof(*p3), GFP_KERNEL);
    p3->day = 3;
    p3->month = 10;
    p3->year = 2003;
    INIT_LIST_HEAD(&p3->list);

    p4 = kmalloc(sizeof(*p4), GFP_KERNEL);
    p4->day = 4;
    p4->month = 11;
    p4->year = 2004;
    INIT_LIST_HEAD(&p4->list);

    p5 = kmalloc(sizeof(*p5), GFP_KERNEL);
    p5->day = 5;
    p5->month = 12;
    p5->year = 2005;
    INIT_LIST_HEAD(&p5->list);

    /* Add to birthday_list */
    list_add_tail(&p1->list, &birthday_list);
    list_add_tail(&p2->list, &birthday_list);
    list_add_tail(&p3->list, &birthday_list);
    list_add_tail(&p4->list, &birthday_list);
    list_add_tail(&p5->list, &birthday_list);

    /* Output contents of elements */
    list_for_each_entry(ptr, &birthday_list, list) {
        printk(KERN_INFO "...loaded birthday: %i/%i/%i\n", ptr->month, ptr->day, ptr->year);
    }

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    struct birthday *ptr, *next;

    printk(KERN_INFO "Removing Module\n");

    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        printk(KERN_INFO "birthday: %i/%i/%i", ptr->month, ptr->day, ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
        printk(KERN_INFO " ...removed.\n");
    }
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
