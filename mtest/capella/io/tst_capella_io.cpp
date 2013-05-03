//=============================================================================
//  MuseScore
//  Music Composition & Notation
//  $Id:$
//
//  Copyright (C) 2013 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#include <QtTest/QtTest>
#include "mtest/testutils.h"
#include "libmscore/score.h"
#include "mscore/preferences.h"

#define DIR QString("capella/io/")

//---------------------------------------------------------
//   TestCapellaIO
//---------------------------------------------------------

class TestCapellaIO : public QObject, public MTest
      {
      Q_OBJECT

      void capReadTest(const char* file);
      void capxReadTest(const char* file);

private slots:
      void initTestCase();

      // The list of Capella regression tests
      // Currently failing tests are commented out and annotated with the failure reason
      // To extract the list in a shell scipt use:
      // cat tst_capella_io.cpp | grep "{ <test>" | awk -F\" '{print $2}'
      // where <test> is capReadTest or capxReadTest

      void capTest1() { capReadTest("test1"); }
      void capTest2() { capReadTest("test2"); }
      // void capTest3() { capReadTest("test3"); } // generates spurious natural accidental
      // void capTest4() { capReadTest("test4"); } // generates spurious natural accidental
      // void capTest5() { capReadTest("test5"); } // generates spurious natural accidental
      // void capTest6() { capReadTest("test6"); } // generates spurious natural accidental
      // void capTest7() { capReadTest("test7"); } // generates different (incorrect ?) l1 and l2 values in beams
      void capTest8() { capReadTest("test8"); }
      void capxTest1() { capxReadTest("test1"); }
      void capxTest2() { capxReadTest("test2"); }
      // void capxTest3() { capxReadTest("test3"); } // generates spurious natural accidental
      // void capxTest4() { capxReadTest("test4"); } // generates spurious natural accidental
      // void capxTest5() { capxReadTest("test5"); } // generates spurious natural accidental
      // void capxTest6() { capxReadTest("test6"); } // generates spurious natural accidental
      // void capxTest7() { capxReadTest("test7"); } // generates different (incorrect ?) l1 and l2 values in beams
      void capxTestPianoG4G5() { capxReadTest("testPianoG4G5"); }
      void capxTestScaleC4C5() { capxReadTest("testScaleC4C5"); }
      // void capxTestTuplet1() { capxReadTest("testTuplet1"); } // generates different (incorrect ?) l1 and l2 values in beams
      };

//---------------------------------------------------------
//   initTestCase
//---------------------------------------------------------

void TestCapellaIO::initTestCase()
      {
      initMTest();
      }

//---------------------------------------------------------
//   capReadTest
//   read a Capella file, write to a MuseScore file and verify against reference
//---------------------------------------------------------

void TestCapellaIO::capReadTest(const char* file)
      {
      Score* score = readScore(DIR + file + ".cap");
      QVERIFY(score);
      score->doLayout();
      QVERIFY(saveCompareScore(score, QString("%1.cap.mscx").arg(file),
                               DIR + QString("%1.cap-ref.mscx").arg(file)));
      delete score;
      }

//---------------------------------------------------------
//   capxReadTest
//   read a CapellaXML file, write to a MuseScore file and verify against reference
//---------------------------------------------------------

void TestCapellaIO::capxReadTest(const char* file)
      {
      Score* score = readScore(DIR + file + ".capx");
      QVERIFY(score);
      score->doLayout();
      QVERIFY(saveCompareScore(score, QString("%1.capx.mscx").arg(file),
                               DIR + QString("%1.capx-ref.mscx").arg(file)));
      delete score;
      }

QTEST_MAIN(TestCapellaIO)
#include "tst_capella_io.moc"