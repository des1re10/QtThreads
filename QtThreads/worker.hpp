/**
 ******************************************************************************
 * @file    worker.hpp
 * @author  Copyright (c) 2022,  M.Eng. Robert Ledwig
 * @version V1.0.0
 * @date    22-June-2021
 * @brief   Worker module.
 *
 * This File is the header file of the worker class.
 * 
 * This class contains the implementation for a worker that is capable
 * of consuming and producing data in a threadsafe environment via signals
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#pragma once

/* Includes ------------------------------------------------------------------*/
#include <QObject>
#include <QThread>
#include <QDebug>
#include <string>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
* @class Worker
*
* Worker class definition
*
*/
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject* parent = nullptr);
    ~Worker();

signals:

    /**
     * @fn Worker::produced();
     * @brief produced signal
     * @param[in] value value that has been produced
     * @retval None
     */
    void produced(int value);

    /**
     * @fn Worker::finished();
     * @brief finished signal
     * @param  None
     * @retval None
     */
    void finished();

public slots:

    /**
     * @fn Worker::quit();
     * @brief quit the current worker and corresponding thread
     * @param  None
     * @retval None
     */
    void quit();

    /**
     * @fn Worker::produce();
     * @brief produce something
     * @param  None
     * @retval None
     */
    void produce();

    /**
     * @fn Worker::consume(int value);
     * @brief consume an incoming value
     * @param[in] value value that will be consumed
     * @retval None
     */
    void consume(int value);

    /**
     * @fn Worker::multiplyNumber(int value, const int& factor);
     * @brief mutiply number with a factor
     * @param[in] value value that will be multiplied with a factor
     * @param[in] factor factor for the multiplication
     * @retval [out] int result of the multiplication
     */
    int multiplyNumber(int value, const int& factor);

private:
};