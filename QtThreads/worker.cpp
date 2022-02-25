/**
 ******************************************************************************
 * @file    worker.cpp
 * @author  Copyright (c) 2022,  M.Eng. Robert Ledwig
 * @version V1.0.0
 * @date    22-June-2021
 * @brief   Worker module.
 *
 * This File is the source file of the worker class.
 *
 ******************************************************************************
 */

#include "worker.hpp"
#include <iostream>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
Worker::Worker(QObject* parent) : QObject(parent)
{
}

Worker::~Worker() 
{
}

void Worker::quit()
{
    qInfo() << this << "Quitting" << QThread::currentThread();

    emit finished();

    /* terminate current thread */
    QThread::currentThread()->exit();
}

void Worker::produce()
{
    if (objectName() == "FIFO1")
    {
        int number = 0;

        /* wait for incoming commands from terminal */
        std::cout << "Please enter number:\n";
        std::cin >> number;

        if (number == 0)
        {
            /* quit FIFO1 */
            quit();
        }
        else
        {
            /* send terminal value to FIFO2 */
            emit produced(number);
        }
    }
}

void Worker::consume(int value)
{
    if (objectName() == "FIFO1")
    {
        /* FIFO1 receives multiplied result from FIFO2 and prints it to terminal. */
        qInfo() << this << "result value:" << value << QThread::currentThread();

        /* produce again */
        produce();
    }
    else
    {
        /* FIFO2 consumes incoming value from FIFO1, multiplies it and sends it back. */
        int result = 0;
        const int factor = 2;

        qInfo() << this << "consuming input value:" << value << QThread::currentThread();

        result = multiplyNumber(value, factor);

        emit produced(result);
    }
}

int Worker::multiplyNumber(int number, const int& factor)
{
    int result = number * factor;

    return result;
}