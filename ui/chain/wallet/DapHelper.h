/*
 * Authors:
 * Dmitriy A. Gearasimov <gerasimov.dmitriy@demlabs.net>
 * Demlabs Limited  https://demlabs.net
 * CellFrame       https://cellframe.net
 * Sources         https://gitlab.demlabs.net/cellframe
 * Copyright  (c) 2017-2020
 * All rights reserved.

 This file is part of CellFrame SDK the open source project

    CellFrame SDK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CellFrame SDK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with any CellFrame SDK based project.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <QObject>
#include <QSystemSemaphore>
#include <QSharedMemory>

class DapHelper : public QObject
{
    Q_OBJECT
    
    /// Standart constructor.
    explicit DapHelper(QObject *parent = nullptr);
    
public:
    // Realization of a singleton
    DapHelper(const DapHelper&) = delete;
    DapHelper& operator= (const DapHelper &) = delete;
    /// Get an instance of a class.
    /// @return Instance of a class.
    static DapHelper &getInstance();
    
    /// Check for the existence of a running instance of the program.
    /// @param systemSemaphore Semaphore for blocking shared resource.
    /// @param memmoryApp Shared memory.
    /// @param memmoryAppBagFix Shared memory for Linux system features.
    /// @return If the application is running, it returns three, otherwise false.
    bool checkExistenceRunningInstanceApp(QSystemSemaphore& systemSemaphore, QSharedMemory &memmoryApp, QSharedMemory &memmoryAppBagFix);
};
