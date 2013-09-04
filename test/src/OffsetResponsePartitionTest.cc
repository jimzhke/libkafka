///////////////////////////////////////////////////////////////////////////
//
// libkafka - C/C++ client for Apache Kafka v0.8+
//
// David Tompkins -- 8/8/2013
// tompkins@adobe_dot_com
//
///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2013 Adobe Systems Incorporated. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////

#include <string>
#include <gtest/gtest.h>
#include "BaseTest.h"

namespace {

  class OffsetResponsePartitionTest : public BaseTest {
    protected:

      OffsetResponsePartitionTest() { }
      virtual ~OffsetResponsePartitionTest() { }
      virtual void SetUp() { } 
      virtual void TearDown() { }
  };

  TEST_F(OffsetResponsePartitionTest, Constructor) {

    OffsetResponsePartition *orp1 = createOffsetResponsePartition();
    EXPECT_NE(orp1, (void*)0);
    orp1->packet = new Packet();
    unsigned char * message = orp1->toWireFormat();
    int size = orp1->getWireFormatSize(true);
    EXPECT_EQ(orp1->packet->getSize(), size);

    orp1->packet->resetForReading();
    OffsetResponsePartition *orp2 = new OffsetResponsePartition(orp1->packet);

    EXPECT_NE(orp2, (void*)0);
    EXPECT_EQ(orp2->packet->getSize(), orp1->packet->getSize());
    EXPECT_EQ(orp2->partition, orp1->partition);
    EXPECT_EQ(orp2->errorCode, orp1->errorCode);
    EXPECT_EQ(orp2->offsetArraySize, orp1->offsetArraySize);
    // TODO: need to compare contents

    delete orp1->packet;
    delete orp1;
    delete orp2;
  }

}  // namespace