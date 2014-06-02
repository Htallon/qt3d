/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "quick3deffect.h"

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Render {

namespace Quick {

Quick3DEffect::Quick3DEffect(Node *parent)
    : Qt3D::Quick::Quick3DNode(parent),
      QAbstractEffect()
{
}

QQmlListProperty<Technique> Quick3DEffect::techniqueList()
{
    return QQmlListProperty<Technique>(this, 0,
                                       &Quick3DEffect::appendTechnique,
                                       &Quick3DEffect::techniqueCount,
                                       &Quick3DEffect::techniqueAt,
                                       &Quick3DEffect::clearTechniqueList);
}

void Quick3DEffect::appendTechnique(QQmlListProperty<Technique> *list, Technique *bar)
{
    QAbstractEffect *eff = qobject_cast<QAbstractEffect*>(list->object);
    if (eff)
        eff->addTechnique(bar);
}

Technique *Quick3DEffect::techniqueAt(QQmlListProperty<Technique> *list, int index)
{
    QAbstractEffect *eff = qobject_cast<QAbstractEffect*>(list->object);
    if (eff)
        return qobject_cast<Technique*>(eff->techniques().at(index));
    return Q_NULLPTR;
}

int Quick3DEffect::techniqueCount(QQmlListProperty<Technique> *list)
{
    QAbstractEffect *eff = qobject_cast<QAbstractEffect*>(list->object);
    if (eff)
        return eff->techniques().count();
    return 0;
}

void Quick3DEffect::clearTechniqueList(QQmlListProperty<Technique> *list)
{
    QAbstractEffect *eff = qobject_cast<QAbstractEffect*>(list->object);
    if (eff) {
        // Ownership of techniques is handled by the QmlEngine so we shouldn't class clearTechniques
        // which deletes techniques
        Q_FOREACH (QAbstractTechnique *tech, eff->techniques())
            eff->removeTechnique(tech);
    }
}

} // Quick

} // Render

} // Qt3D

QT_END_NAMESPACE