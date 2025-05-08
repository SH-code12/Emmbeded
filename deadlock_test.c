#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static DEFINE_MUTEX(mutex1);
static DEFINE_MUTEX(mutex2);

static struct task_struct *thread1;
static struct task_struct *thread2;

static int thread_fn1(void *data)
{
    mutex_lock(&mutex1);
    msleep(100); // sleep to allow the second thread to run
    mutex_lock(&mutex2);

    mutex_unlock(&mutex2);
    mutex_unlock(&mutex1);

    return 0;
}

static int thread_fn2(void *data)
{
    mutex_lock(&mutex2);
    msleep(100); // sleep to allow the first thread to run
    mutex_lock(&mutex1);

    mutex_unlock(&mutex1);
    mutex_unlock(&mutex2);

    return 0;
}

static int __init lockdep_test_init(void)
{
    pr_info("Lockdep Test Module Loaded\n");

    thread1 = kthread_run(thread_fn1, NULL, "thread1");
    thread2 = kthread_run(thread_fn2, NULL, "thread2");

    return 0;
}

static void __exit lockdep_test_exit(void)
{
    pr_info("Lockdep Test Module Unloaded\n");
}

module_init(lockdep_test_init);
module_exit(lockdep_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shahd Mohamed Elnassag");
MODULE_DESCRIPTION("Lockdep Deadlock Detection Test");

