/***************************************************************************
  qgslayertreeutils.h
  --------------------------------------
  Date                 : May 2014
  Copyright            : (C) 2014 by Martin Dobias
  Email                : wonder dot sk at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSLAYERTREEUTILS_H
#define QGSLAYERTREEUTILS_H

#include <qnamespace.h>
#include <QList>
#include <QPair>

class QDomElement;
class QDomDocument;
class QStringList;

class QgsLayerTreeNode;
class QgsLayerTreeGroup;
class QgsLayerTreeLayer;
class QgsMapLayer;

/**
 * Assorted functions for dealing with layer trees.
 *
 * @note added in 2.4
 */
class CORE_EXPORT QgsLayerTreeUtils
{
  public:

    //! Try to load layer tree from \verbatim <legend> \endverbatim tag from project files from QGIS 2.2 and below
    static bool readOldLegend( QgsLayerTreeGroup* root, const QDomElement& legendElem );
    //! Try to load custom layer order from \verbatim <legend> \endverbatim tag from project files from QGIS 2.2 and below
    static bool readOldLegendLayerOrder( const QDomElement& legendElem, bool& hasCustomOrder, QStringList& order );
    //! Return \verbatim <legend> \endverbatim tag used in QGIS 2.2 and below
    static QDomElement writeOldLegend( QDomDocument& doc, QgsLayerTreeGroup* root, bool hasCustomOrder, const QStringList& order );

    //! Convert Qt::CheckState to QString
    static QString checkStateToXml( Qt::CheckState state );
    //! Convert QString to Qt::CheckState
    static Qt::CheckState checkStateFromXml( const QString& txt );

    //! Return true if any of the layers is editable
    static bool layersEditable( const QList<QgsLayerTreeLayer*>& layerNodes );
    //! Return true if any of the layers is modified
    static bool layersModified( const QList<QgsLayerTreeLayer*>& layerNodes );

    //! Remove layer nodes that refer to invalid layers
    static void removeInvalidLayers( QgsLayerTreeGroup* group );

    //! Remove subtree of embedded groups and replaces it with a custom property embedded-visible-layers
    static void replaceChildrenOfEmbeddedGroups( QgsLayerTreeGroup* group );

    //! @note not available in python bindings
    static void updateEmbeddedGroupsProjectPath( QgsLayerTreeGroup* group );

    //! get invisible layers
    static QStringList invisibleLayerList( QgsLayerTreeNode *node );

    //! Set the expression filter of a legend layer
    static void setLegendFilterByExpression( QgsLayerTreeLayer& layer, const QString& expr, bool enabled = true );
    //! Return the expression filter of a legend layer
    static QString legendFilterByExpression( const QgsLayerTreeLayer& layer, bool* enabled = nullptr );
    //! Test if one of the layers in a group has an expression filter
    static bool hasLegendFilterExpression( const QgsLayerTreeGroup& group );

    //! Insert a QgsMapLayer just below another one
    //! @param group the tree group where layers are (can be the root group)
    //! @param refLayer the reference layer
    //! @param layerToInsert the new layer to insert just below the reference layer
    //! @returns the new tree layer
    static QgsLayerTreeLayer* insertLayerBelow( QgsLayerTreeGroup* group, const QgsMapLayer* refLayer, QgsMapLayer* layerToInsert );
};

#endif // QGSLAYERTREEUTILS_H
