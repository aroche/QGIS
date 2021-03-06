/***************************************************************************
     testqgsgdalprovider.cpp
     --------------------------------------
    Date                 : March 2015
    Copyright            : (C) 2015 by Nyall Dawson
    Email                : nyall.dawson@gmail.com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QStringList>
<<<<<<< HEAD
#include <QObject>
=======
>>>>>>> upstream/master
#include <QApplication>
#include <QFileInfo>
#include <QDir>

//qgis includes...
#include <qgis.h>
#include <qgsapplication.h>
#include <qgsproviderregistry.h>
#include <qgsrasterdataprovider.h>
#include <qgsrectangle.h>

/** \ingroup UnitTests
 * This is a unit test for the gdal provider
 */
class TestQgsGdalProvider : public QObject
{
    Q_OBJECT

  private slots:
    void initTestCase();// will be called before the first testfunction is executed.
    void cleanupTestCase();// will be called after the last testfunction was executed.
    void init() {}// will be called before each testfunction is executed.
    void cleanup() {}// will be called after every testfunction.

    void scaleDataType(); //test resultant data types for int raster with float scale (#11573)
    void warpedVrt(); //test loading raster which requires a warped vrt

  private:
    QString mTestDataDir;
    QString mReport;
};

//runs before all tests
void TestQgsGdalProvider::initTestCase()
{
  // init QGIS's paths - true means that all path will be inited from prefix
  QgsApplication::init();
  QgsApplication::initQgis();

<<<<<<< HEAD
  mTestDataDir = QString( TEST_DATA_DIR ) + QDir::separator(); //defined in CmakeLists.txt
=======
  mTestDataDir = QString( TEST_DATA_DIR ) + '/'; //defined in CmakeLists.txt
>>>>>>> upstream/master
  mReport = "<h1>GDAL Provider Tests</h1>\n";
}

//runs after all tests
void TestQgsGdalProvider::cleanupTestCase()
{
  QgsApplication::exitQgis();
<<<<<<< HEAD
  QString myReportFile = QDir::tempPath() + QDir::separator() + "qgistest.html";
=======
  QString myReportFile = QDir::tempPath() + "/qgistest.html";
>>>>>>> upstream/master
  QFile myFile( myReportFile );
  if ( myFile.open( QIODevice::WriteOnly | QIODevice::Append ) )
  {
    QTextStream myQTextStream( &myFile );
    myQTextStream << mReport;
    myFile.close();
  }
}

void TestQgsGdalProvider::scaleDataType()
{
<<<<<<< HEAD
  QString rasterWithOffset = QString( TEST_DATA_DIR ) + QDir::separator() +  "int_raster_with_scale.tif";
=======
  QString rasterWithOffset = QString( TEST_DATA_DIR ) + "/int_raster_with_scale.tif";
>>>>>>> upstream/master
  QgsDataProvider* provider = QgsProviderRegistry::instance()->provider( "gdal", rasterWithOffset );
  QgsRasterDataProvider* rp = dynamic_cast< QgsRasterDataProvider* >( provider );
  QVERIFY( rp );
  //raster is an integer data type, but has a scale < 1, so data type must be float
  QCOMPARE( rp->dataType( 1 ), QGis::Float32 );
  QCOMPARE( rp->srcDataType( 1 ), QGis::Float32 );
<<<<<<< HEAD
=======
  delete provider;
>>>>>>> upstream/master
}

void TestQgsGdalProvider::warpedVrt()
{
<<<<<<< HEAD
  QString raster = QString( TEST_DATA_DIR ) + QDir::separator() +  "requires_warped_vrt.tif";
=======
  QString raster = QString( TEST_DATA_DIR ) + "/requires_warped_vrt.tif";
>>>>>>> upstream/master
  QgsDataProvider* provider = QgsProviderRegistry::instance()->provider( "gdal", raster );
  QgsRasterDataProvider* rp = dynamic_cast< QgsRasterDataProvider* >( provider );
  QVERIFY( rp );

  qDebug() << "x min: " << rp->extent().xMinimum();
  qDebug() << "x max: " << rp->extent().xMaximum();
  qDebug() << "y min: " << rp->extent().yMinimum();
  qDebug() << "y max: " << rp->extent().yMaximum();

  QVERIFY( qgsDoubleNear( rp->extent().xMinimum(), 2058589, 1 ) );
  QVERIFY( qgsDoubleNear( rp->extent().xMaximum(), 3118999, 1 ) );
  QVERIFY( qgsDoubleNear( rp->extent().yMinimum(), 2281355, 1 ) );
  QVERIFY( qgsDoubleNear( rp->extent().yMaximum(), 3129683, 1 ) );
<<<<<<< HEAD
=======
  delete provider;
>>>>>>> upstream/master
}

QTEST_MAIN( TestQgsGdalProvider )
#include "testqgsgdalprovider.moc"
