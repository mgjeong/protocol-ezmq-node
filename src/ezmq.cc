/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

#include <nan.h>

#include "nezmqapi.h"
#include "nezmqevent.h"
#include "nezmqreading.h"
#include "nezmqbytedata.h"
#include "nezmqpublisher.h"
#include "nezmqsubscriber.h"

using namespace Nan;

namespace nezmq
{
    static NAN_MODULE_INIT(CreateNodeEZMQ)
    {
        nezmq::NEZMQAPI::Init(target);
        nezmq::NEZMQEvent::Init(target);
        nezmq::NEZMQReading::Init(target);
        nezmq::NEZMQByteData::Init(target);
        nezmq::NEZMQPublisher::Init(target);
        nezmq::NEZMQSubscriber::Init(target);
    }
}

extern "C" NAN_MODULE_INIT(init)
{
    nezmq::CreateNodeEZMQ(target);
}

NODE_MODULE(ezmq, init)

