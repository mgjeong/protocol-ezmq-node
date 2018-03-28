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

#include "nezmqreading.h"

using namespace v8;

namespace nezmq
{
    NAN_MODULE_INIT(NEZMQReading::Init)
    {
        // Prepare constructor template
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NEZMQReading").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "getID", GetID);
        Nan::SetPrototypeMethod(tpl, "getCreated", GetCreated);
        Nan::SetPrototypeMethod(tpl, "getModified", GetModified);
        Nan::SetPrototypeMethod(tpl, "getOrigin", GetOrigin);
        Nan::SetPrototypeMethod(tpl, "getPushed", GetPushed);
        Nan::SetPrototypeMethod(tpl, "getName", GetName);
        Nan::SetPrototypeMethod(tpl, "getValue", GetValue);
        Nan::SetPrototypeMethod(tpl, "getDevice", GetDevice);

        Nan::SetPrototypeMethod(tpl, "setID", SetID);
        Nan::SetPrototypeMethod(tpl, "setCreated", SetCreated);
        Nan::SetPrototypeMethod(tpl, "setModified", SetModified);
        Nan::SetPrototypeMethod(tpl, "setOrigin", SetOrigin);
        Nan::SetPrototypeMethod(tpl, "setPushed", SetPushed);
        Nan::SetPrototypeMethod(tpl, "setName", SetName);
        Nan::SetPrototypeMethod(tpl, "setValue", SetValue);
        Nan::SetPrototypeMethod(tpl, "setDevice", SetDevice);

        constructor1().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NEZMQReading").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NEZMQReading::NewInstance(int argc, v8::Local<v8::Value> argv[])
    {
        v8::Local<v8::Function> cons = Nan::New(constructor1());
        return Nan::NewInstance(cons, argc, argv).ToLocalChecked();
    }

    NEZMQReading::NEZMQReading(NEZMQEvent *eventObj): Nan::ObjectWrap()
    {
        if(NULL != eventObj)
        {
            nativeHandle =  (eventObj->nativeHandle)->add_reading();
        }
        else
        {

        }
    }

    NEZMQReading::~NEZMQReading()
    {

    }

    NAN_METHOD(NEZMQReading::New)
    {
         if (info.IsConstructCall())
        {
            // Invoked as constructor: `new NEZMQReading(...)`
            NEZMQEvent* eventObj = NULL;
            if(info.Length() > 0)
            {
               eventObj = Nan::ObjectWrap::Unwrap<NEZMQEvent>(info[0].As<Object>());
            }

            NEZMQReading* obj = new NEZMQReading(eventObj);
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
        else
        {
        }
    }

    NAN_METHOD(NEZMQReading::GetID)
    {
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->id()).c_str())).ToLocalChecked());
    }

    NAN_METHOD(NEZMQReading::GetCreated)
    {
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->created()));
    }

    NAN_METHOD(NEZMQReading::GetModified)
    {
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->modified()));
    }

    NAN_METHOD(NEZMQReading::GetOrigin)
    {
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->origin()));
    }

    NAN_METHOD(NEZMQReading::GetPushed)
    {
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->pushed()));
    }

    NAN_METHOD(NEZMQReading::GetName)
    {
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->name()).c_str())).ToLocalChecked());
    }

    NAN_METHOD(NEZMQReading::GetValue)
    {
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->value()).c_str())).ToLocalChecked());
    }

    NAN_METHOD(NEZMQReading::GetDevice)
    {
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->device()).c_str())).ToLocalChecked());
    }

    NAN_METHOD(NEZMQReading::SetID)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(str);
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        (obj->nativeHandle)->set_id(*utfValue);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQReading::SetCreated)
    {
        long value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        (obj->nativeHandle)->set_created(value);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQReading::SetModified)
    {
        long value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        (obj->nativeHandle)->set_modified(value);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQReading::SetOrigin)
    {
        long value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        (obj->nativeHandle)->set_origin(value);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQReading::SetPushed)
    {
        long value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        (obj->nativeHandle)->set_pushed(value);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQReading::SetName)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(str);

        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        (obj->nativeHandle)->set_name(*utfValue);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQReading::SetValue)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(str);

        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        (obj->nativeHandle)->set_value(*utfValue);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQReading::SetDevice)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(str);

        NEZMQReading* obj = ObjectWrap::Unwrap<NEZMQReading>(info.Holder());
        (obj->nativeHandle)->set_device(*utfValue);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }
}

