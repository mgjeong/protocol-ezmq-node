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

#include "EZMQByteData.h"

#include "nezmqsubscriber.h"
#include "nezmqevent.h"
#include "nezmqbytedata.h"

using namespace v8;

namespace nezmq
{
    typedef struct
    {
        NEZMQSubscriber* nSubscriber; // Class object needs for callback
        EZMQMessage *ezmqMessage;
        std::string messageTopic;
        EZMQContentType contentType;
    }SubCBData;

    NAN_MODULE_INIT(NEZMQSubscriber::Init)
    {
        // Prepare constructor template
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NEZMQSubscriber").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "start", Start);
        Nan::SetPrototypeMethod(tpl, "subscribe", Subscribe);
        Nan::SetPrototypeMethod(tpl, "subscribeOnTopic", SubscribeOnTopic);
        Nan::SetPrototypeMethod(tpl, "subscribeOnList", SubscribeOnList);
        Nan::SetPrototypeMethod(tpl, "unSubscribe", UnSubscribe);
        Nan::SetPrototypeMethod(tpl, "unSubscribeOnTopic", UnSubscribeOnTopic);
        Nan::SetPrototypeMethod(tpl, "unSubscribeOnList", UnSubscribeOnList);

        Nan::SetPrototypeMethod(tpl, "stop", Stop);
        Nan::SetPrototypeMethod(tpl, "getIp", GetIp);
        Nan::SetPrototypeMethod(tpl, "getPort", GetPort);

        constructor().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NEZMQSubscriber").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NEZMQSubscriber::NewInstance()
    {
        v8::Local<v8::Function> cons = Nan::New(constructor());
        return Nan::NewInstance(cons).ToLocalChecked();
    }

    NEZMQSubscriber::NEZMQSubscriber() : Nan::ObjectWrap()
    {
    }
    NEZMQSubscriber::~NEZMQSubscriber()
    {

    }

    void  NEZMQSubscriber::NEZMQCreateNative(std::string ip, int port)
    {
        nativeHandle =  new ezmq::EZMQSubscriber(ip, port, std::bind(NEZMQSubscriber::subCallback, std::placeholders::_1, this),
                                                                                      std::bind(NEZMQSubscriber::subTopicCallback, std::placeholders::_1,
                                                                                      std::placeholders::_2, this));


        uvLoop = uv_default_loop();
        int result = uv_async_init(uvLoop, &uvAsyncHandle, NEZMQSubscriber::uvAsynCallback);
        std::cout <<"Addon uv_async_init [result]: "<< result<<std::endl;
    }

    void NEZMQSubscriber::uvAsynCallback(uv_async_t* handle)
    {
        SubCBData *data =  (SubCBData *)static_cast<SubCBData*>(handle->data);

        //call js application callback
        Nan::HandleScope scope;
        Local<Object> addonEvent;
        if(EZMQ_CONTENT_TYPE_PROTOBUF == data->contentType)
        {
            addonEvent =  NEZMQEvent::NewInstance();
            NEZMQEvent* unwrappedEvent = ObjectWrap::Unwrap<NEZMQEvent>(addonEvent);
            unwrappedEvent->nativeHandle = (Event *)data->ezmqMessage;
        }
        else if(EZMQ_CONTENT_TYPE_BYTEDATA == data->contentType)
        {
            v8::Local<v8::Value> argv[] {Nan::Null()};
            addonEvent =  NEZMQByteData::NewInstance(0, argv);
            NEZMQByteData* unwrappedEvent = ObjectWrap::Unwrap<NEZMQByteData>(addonEvent);
            unwrappedEvent->nativeHandle = (EZMQByteData *)data->ezmqMessage;
        }
        else
        {
            std::cout<<"Not supported type"<<std::endl;
            return;
        }

        if ((data->messageTopic).length() < 1)
        {
            const unsigned argc = 1;
            v8::Local<v8::Value> argv[argc] = { addonEvent  };
            ((data ->nSubscriber)->jsSubCallback).Call(1, argv);
        }
        else
        {
            const unsigned argc = 2;
            v8::Local<v8::Value> topic = (Nan::New((data->messageTopic).c_str())).ToLocalChecked();
            v8::Local<v8::Value> argv[argc] = { topic, addonEvent  };
            ((data ->nSubscriber)->jsSubTopicCallback).Call(2, argv);
        }

        std::unique_lock<std::mutex> lock((data ->nSubscriber)->subMutex);
        ((data ->nSubscriber)->subCV).notify_all();
    }

    void NEZMQSubscriber::subCallback(const EZMQMessage &message,  NEZMQSubscriber *obj)
    {
        SubCBData *cbData = new SubCBData();
        cbData->contentType =  message.getContentType();
        if(EZMQ_CONTENT_TYPE_PROTOBUF == cbData->contentType)
        {
            cbData->ezmqMessage =  (Event *)dynamic_cast<const Event*>(&message);
        }
        else if(EZMQ_CONTENT_TYPE_BYTEDATA == cbData->contentType)
        {
            cbData->ezmqMessage =  (EZMQByteData *)dynamic_cast<const EZMQByteData*>(&message);
        }
        else
        {
            std::cout<<"Not supported type"<<std::endl;
            return;
        }
        cbData->nSubscriber = obj;
        (obj->uvAsyncHandle).data = cbData;
        int result =   uv_async_send(&(obj->uvAsyncHandle));
        std::unique_lock<std::mutex> lock(obj->subMutex);
        (obj->subCV).wait(lock);
    }

    void NEZMQSubscriber::subTopicCallback(std::string topic,  const EZMQMessage &message, NEZMQSubscriber *obj)
    {
        SubCBData *cbData = new SubCBData();
        cbData->contentType =  message.getContentType();

        if(EZMQ_CONTENT_TYPE_PROTOBUF == cbData->contentType)
        {
            cbData->ezmqMessage =  (Event *)dynamic_cast<const Event*>(&message);
        }
        else if(EZMQ_CONTENT_TYPE_BYTEDATA == cbData->contentType)
        {
            cbData->ezmqMessage =  (EZMQByteData *)dynamic_cast<const EZMQByteData*>(&message);
        }
        else
        {
            std::cout<<"Not supported type"<<std::endl;
            return;
        }

        cbData->nSubscriber = obj;
        cbData->messageTopic = topic;
        (obj->uvAsyncHandle).data = cbData;
        int result =   uv_async_send(&(obj->uvAsyncHandle));
        std::unique_lock<std::mutex> lock(obj->subMutex);
        (obj->subCV).wait(lock);
    }

    NAN_METHOD(NEZMQSubscriber::New)
    {
        // Invoked as constructor: `new NEZMQSubscriber(...)`
        if (info.IsConstructCall())
        {
            //Get IP
            Local<String> str = Local<String>::Cast(info[0]);
            String::Utf8Value utfValue(str);

            //Get Port
            int port = info[1]->IsUndefined() ? 0 : info[1]->NumberValue();

            NEZMQSubscriber* obj = new NEZMQSubscriber();

            //Get Callbacks
            const v8::Local<v8::Function> subCallback = Nan::To<v8::Function>(info[2]).ToLocalChecked();
            (obj->jsSubCallback).Reset(subCallback);

            const v8::Local<v8::Function> subTopicCallback = Nan::To<v8::Function>(info[3]).ToLocalChecked();
            (obj->jsSubTopicCallback).Reset(subTopicCallback);

            obj->NEZMQCreateNative(*utfValue, port);

            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
        else
        {
        }
    }

    NAN_METHOD(NEZMQSubscriber::Start)
    {
        NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->start()));
    }

    NAN_METHOD(NEZMQSubscriber::Subscribe)
    {
       NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
       info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->subscribe()));
    }

    NAN_METHOD(NEZMQSubscriber::SubscribeOnTopic)
    {
       NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        Local<String> topic = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(topic);
       info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->subscribe(*utfValue)));
    }

    NAN_METHOD(NEZMQSubscriber::SubscribeOnList)
    {
       NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        Local<Array> topicList = Local<Array>::Cast(info[0]);
        unsigned int length = topicList->Length();
        std::list<std::string> nativeList;
        for (unsigned int i = 0; i < length; i++)
        {
            Local<String> str = Local<String>::Cast(topicList->Get(i));
            String::Utf8Value utfValue(str);
            nativeList.push_back(*utfValue);
        }
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->subscribe(nativeList)));
    }

    NAN_METHOD(NEZMQSubscriber::UnSubscribe)
    {
        NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->unSubscribe()));
    }

    NAN_METHOD(NEZMQSubscriber::UnSubscribeOnTopic)
    {
        NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        Local<String> topic = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(topic);
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->unSubscribe(*utfValue)));
    }

    NAN_METHOD(NEZMQSubscriber::UnSubscribeOnList)
    {
       NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        Local<Array> topicList = Local<Array>::Cast(info[0]);
        unsigned int length = topicList->Length();
        std::list<std::string> nativeList;
        for (unsigned int i = 0; i < length; i++)
        {
            Local<String> str = Local<String>::Cast(topicList->Get(i));
            String::Utf8Value utfValue(str);
            nativeList.push_back(*utfValue);
        }
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->unSubscribe(nativeList)));
    }

    NAN_METHOD(NEZMQSubscriber::Stop)
    {
        NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        uv_unref((uv_handle_t*)(&(obj->uvAsyncHandle)));
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->stop()));
    }

    NAN_METHOD(NEZMQSubscriber::GetIp)
    {
        NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->getIp()).c_str())).ToLocalChecked());
    }

    NAN_METHOD(NEZMQSubscriber::GetPort)
    {
        NEZMQSubscriber* obj = ObjectWrap::Unwrap<NEZMQSubscriber>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->getPort()));
    }

   // TODO libuv stop

}


