/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QT3D_TASK_P_H
#define QT3D_TASK_P_H

#include "qaspectjobmanager.h"

#include <QtCore/QtGlobal>
#include <QtCore/QThread>
#include <QtCore/QSharedPointer>
#include <QtCore/QWaitCondition>

QT_BEGIN_NAMESPACE

namespace Qt3D {

class JobRunner;
class DependencyHandler;

class TaskInterface
{
public:
    virtual ~TaskInterface();

    virtual void run(QSharedPointer<TaskInterface> self, JobRunner *jr) = 0;
    virtual void run() = 0;

    virtual void setDependencyHandler(DependencyHandler *) = 0;
    virtual DependencyHandler *dependencyHandler() = 0;

    virtual int id() = 0;
    virtual void setId(int id) = 0;
};

class AspectTask : public TaskInterface
{
public:
    AspectTask();
    ~AspectTask();

    int id() Q_DECL_OVERRIDE { return m_id; }
    void setId(int id) Q_DECL_OVERRIDE { m_id = id; }

    void setDependencyHandler(DependencyHandler *handler) Q_DECL_OVERRIDE;
    DependencyHandler *dependencyHandler() Q_DECL_OVERRIDE;

public:
    QSharedPointer<QAspectJob> m_job;

protected:
    void run(QSharedPointer<TaskInterface> self, JobRunner *jr) Q_DECL_OVERRIDE;
    void run() Q_DECL_OVERRIDE;

private:
    DependencyHandler *m_dependencyHandler;
    int m_id; // For testing purposes for now
};

class SynchronizedTask : public TaskInterface
{
public:
    explicit SynchronizedTask(QAbstractAspectJobManager::JobFunction func, void *arg,
                              QAtomicInt *atomicCount);
    ~SynchronizedTask();

    int id() Q_DECL_OVERRIDE { return m_id; }
    void setId(int id) Q_DECL_OVERRIDE { m_id = id; }

    void setDependencyHandler(DependencyHandler *handler) Q_DECL_OVERRIDE;
    DependencyHandler *dependencyHandler() Q_DECL_OVERRIDE;

protected:
    void run(QSharedPointer<TaskInterface> self, JobRunner *jr) Q_DECL_OVERRIDE;
    void run() Q_DECL_OVERRIDE;

private:
    QAbstractAspectJobManager::JobFunction m_func;
    void *m_arg;
    QAtomicInt *m_atomicCount;

    int m_id;
};

} // namespace Qt3D

QT_END_NAMESPACE

#endif // QT3D_TASK_P_H

