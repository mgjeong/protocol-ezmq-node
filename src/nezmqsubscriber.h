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

#ifndef NEZMQ_SUBSCRIBER_H
#define NEZMQ_SUBSCRIBER_H

#include <condition_variable>
#include <memory>
#include <nan.h>
#include "uv.h"

#include "EZMQSubscriber.h"

using namespace Nan;
using namespace ezmq;
using namespace v8;

namespace nezmq
{
    class NEZMQSubscriber : public Nan::ObjectWrap
    {
        public:
            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance();

            //callback functions
            static void uvAsynCallback(uv_async_t* handle);
            static void subCallback(const EZMQMessage &event,  NEZMQSubscriber *obj);
            static void subTopicCallback(std::string topic,  const EZMQMessage &event, NEZMQSubscriber *pointer);

        private:
            explicit NEZMQSubscriber();
            void NEZMQCreateNative(std::string ip, int port);
            ~NEZMQSubscriber();

            static NAN_METHOD(New);
            static NAN_METHOD(SetClientKeys);
            static NAN_METHOD(SetServerPublicKey);
            static NAN_METHOD(Start);
            static NAN_METHOD(Subscribe);
            static NAN_METHOD(SubscribeOnTopic);
            static NAN_METHOD(SubscribeOnList);
            static NAN_METHOD(SubscribeWithIPPort);
            static NAN_METHOD(UnSubscribe);
            static NAN_METHOD(UnSubscribeOnTopic);
            static NAN_METHOD(UnSubscribeOnList);
            static NAN_METHOD(Stop);
            static NAN_METHOD(GetIp);
            static NAN_METHOD(GetPort);

            static inline Nan::Persistent<v8::Function> & constructor()
            {
                static Nan::Persistent<v8::Function> constructor;
                return constructor;
            }

            ezmq::EZMQSubscriber *nativeHandle;
            Nan::Callback jsSubCallback;
            Nan::Callback jsSubTopicCallback;
            uv_async_t uvAsyncHandle;
            uv_loop_t* uvLoop;
            std::mutex subMutex;
            std::condition_variable subCV;
    };
}
#endif //NEZMQ_SUBSCRIBER_H



