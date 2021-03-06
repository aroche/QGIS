# -*- coding: utf-8 -*-
"""QGIS Unit tests for QgsLayerDefinition

.. note:: This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
"""
__author__ = 'Hugo Mercier'
__date__ = '07/01/2016'
__copyright__ = 'Copyright 2016, The QGIS Project'
# This will get replaced with a git SHA1 when you do a git archive
__revision__ = '$Format:%H$'

import qgis

from qgis.core import (QGis,
                       QgsProject,
                       QgsMapLayerRegistry,
                       QgsLayerDefinition
                       )

from utilities import (TestCase, unittest, getQgisTestApp, unitTestDataPath)

from PyQt4.QtCore import QVariant
from PyQt4.QtXml import QDomDocument

QGISAPP, CANVAS, IFACE, PARENT = getQgisTestApp()
TEST_DATA_DIR = unitTestDataPath()


class TestQgsLayerDefinition(TestCase):

    def testDependency(self):
        inDoc = """
        <maplayers>
        <maplayer>
          <id>layerB</id>
          <layerDependencies>
            <layer id="layerA"/>
          </layerDependencies>
        </maplayer>
        <maplayer>
          <id>layerA</id>
        </maplayer>
        </maplayers>"""
        doc = QDomDocument("testdoc")
        doc.setContent(inDoc)
        dep = QgsLayerDefinition.DependencySorter(doc)
        nodes = dep.sortedLayerNodes()
        self.assertTrue(not dep.hasCycle())
        self.assertTrue(not dep.hasMissingDependency())
        self.assertEqual(nodes[0].firstChildElement("id").text(), "layerA")
        self.assertEqual(nodes[1].firstChildElement("id").text(), "layerB")

    def testMissingDependency(self):
        inDoc = """
        <maplayers>
        <maplayer>
          <id>layerB</id>
          <layerDependencies>
            <layer id="layerA"/>
          </layerDependencies>
        </maplayer>
        <maplayer>
          <id>layerA</id>
          <layerDependencies>
            <layer id="layerC"/>
          </layerDependencies>
        </maplayer>
        </maplayers>"""
        doc = QDomDocument("testdoc")
        doc.setContent(inDoc)
        dep = QgsLayerDefinition.DependencySorter(doc)
        nodes = dep.sortedLayerNodes()
        self.assertTrue(not dep.hasCycle())
        self.assertTrue(dep.hasMissingDependency())

    def testCyclicDependency(self):
        inDoc = """
        <maplayers>
        <maplayer>
          <id>layerB</id>
          <layerDependencies>
            <layer id="layerA"/>
          </layerDependencies>
        </maplayer>
        <maplayer>
          <id>layerA</id>
          <layerDependencies>
            <layer id="layerB"/>
          </layerDependencies>
        </maplayer>
        </maplayers>"""
        doc = QDomDocument("testdoc")
        doc.setContent(inDoc)
        dep = QgsLayerDefinition.DependencySorter(doc)
        nodes = dep.sortedLayerNodes()
        self.assertTrue(dep.hasCycle())

    def testVectorAndRaster(self):
        # Load a simple QLR containing a vector layer and a raster layer.
        QgsMapLayerRegistry.instance().removeAllMapLayers()
        layers = QgsMapLayerRegistry.instance().mapLayers()
        self.assertEqual(len(layers), 0)

        (result, errMsg) = QgsLayerDefinition.loadLayerDefinition(TEST_DATA_DIR + '/vector_and_raster.qlr', QgsProject.instance().layerTreeRoot())
        self.assertTrue(result)

        layers = QgsMapLayerRegistry.instance().mapLayers()
        self.assertEqual(len(layers), 2)
        QgsMapLayerRegistry.instance().removeAllMapLayers()

if __name__ == '__main__':
    unittest.main()
