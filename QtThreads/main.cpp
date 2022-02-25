/**
 ******************************************************************************
 * @file    main.cpp
 * @author  Copyright (c) 2022,  M.Eng. Robert Ledwig
 * @version V1.0.0
 * @date    22-June-2021
 * @brief   main function.
 *
 * This File is the source file of the main function.
 * 
 * This is an thread example of producing and consuming values in a threadsafe
 * environment using signals in Qt.
 *
 ******************************************************************************
 */

 /* Includes ------------------------------------------------------------------*/
#include <QCoreApplication>
#include <QThread>
#include "worker.hpp"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QThread thread1;
    QThread thread2;

    Worker worker1;
    Worker worker2;

    /* assign threads to instances of the class */
    worker1.moveToThread(&thread1);
    worker2.moveToThread(&thread2);

    thread1.setObjectName("Thread1");
    thread2.setObjectName("Thread2");
    worker1.setObjectName("FIFO1");
    worker2.setObjectName("FIFO2");

    /* connect the signals with the functions of the instances of the worker class. */

    /* after thread1 has been started, worker1 will produce. */
    /* after worker1 has produced, worker2 will consume. */
    /* after worker2 has produced, worker1 will consume the result. */
    /* after worker1 has finished, worker2 will finish as well. */

    QObject::connect(&thread1, &QThread::started, &worker1, &Worker::produce);

    /* put information in a queued connection Qt5 */
    QObject::connect(&worker1, &Worker::produced, &worker2, &Worker::consume, Qt::QueuedConnection);
    QObject::connect(&worker2, &Worker::produced, &worker1, &Worker::consume, Qt::QueuedConnection);
    QObject::connect(&worker1, &Worker::finished, &worker2, &Worker::quit, Qt::QueuedConnection);

    /* start the threads */
    thread1.start();
    thread2.start();

    return a.exec();
}