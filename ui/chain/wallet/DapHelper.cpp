#include "DapHelper.h"

DapHelper::DapHelper(QObject *parent) : QObject(parent)
{
    
}

DapHelper &DapHelper::getInstance()
{
    static DapHelper instance;
    return instance;
}

/// Check for the existence of a running instance of the program.
/// @param systemSemaphore Semaphore for blocking shared resource.
/// @param memmoryApp Shared memory.
/// @param memmoryAppBagFix Shared memory for Linux system features.
/// @return If the application is running, it returns three, otherwise false.
bool DapHelper::checkExistenceRunningInstanceApp(QSystemSemaphore& systemSemaphore, QSharedMemory &memmoryApp, QSharedMemory &memmoryAppBagFix)
{
    systemSemaphore.acquire();
    
    if(memmoryAppBagFix.attach())
    {
        memmoryAppBagFix.detach();
    }
    
    bool isRunning {false};
    
    if (memmoryApp.attach())
    {
        isRunning = true;
    }
    else
    {
        memmoryApp.create(1);
        isRunning = false;
    }
    
    systemSemaphore.release();
    
    return isRunning;
}
