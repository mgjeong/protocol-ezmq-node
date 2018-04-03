/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2018 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include "nezmqevent.h"
#include "nezmqreading.h"

using namespace v8;

namespace nezmq
{
    NAN_MODULE_INIT(NEZMQEvent::Init)
    {
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NEZMQEvent").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "getContentType", GetContentType);
        Nan::SetPrototypeMethod(tpl, "getID", GetID);
        Nan::SetPrototypeMethod(tpl, "getCreated", GetCreated);
        Nan::SetPrototypeMethod(tpl, "getModified", GetModified);
        Nan::SetPrototypeMethod(tpl, "getOrigin", GetOrigin);
        Nan::SetPrototypeMethod(tpl, "getPushed", GetPushed);
        Nan::SetPrototypeMethod(tpl, "getDevice", GetDevice);
        Nan::SetPrototypeMethod(tpl, "getReadingCount", GetReadingCount);
        Nan::SetPrototypeMethod(tpl, "getReading", GetReading);

        Nan::SetPrototypeMethod(tpl, "setID", SetID);
        Nan::SetPrototypeMethod(tpl, "setCreated", SetCreated);
        Nan::SetPrototypeMethod(tpl, "setModified", SetModified);
        Nan::SetPrototypeMethod(tpl, "setOrigin", SetOrigin);
        Nan::SetPrototypeMethod(tpl, "setPushed", SetPushed);
        Nan::SetPrototypeMethod(tpl, "setDevice", SetDevice);

        constructor().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NEZMQEvent").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NEZMQEvent::NewInstance()
    {
        v8::Local<v8::Function> cons = Nan::New(constructor());
        return Nan::NewInstance(cons).ToLocalChecked();
    }

    NEZMQEvent::NEZMQEvent() : Nan::ObjectWrap()
    {
        nativeHandle =  new Event();
    }

    NEZMQEvent::~NEZMQEvent()  { }

    v8::Local<v8::Object> NEZMQEvent::createReadingInstance(Reading *reading)
    {
        v8::Local<v8::Value> argv1[] {Nan::Null()};
        Local<Object> addonReading =  NEZMQReading::NewInstance(0, argv1);
        NEZMQReading* unwrappedReading = ObjectWrap::Unwrap<NEZMQReading>(addonReading);
        unwrappedReading->nativeHandle = reading;
        return addonReading;
    }

    NAN_METHOD(NEZMQEvent::New)
    {
        if (info.IsConstructCall())
        {
            // Invoked as constructor: `new NEZMQEvent(...)`
            NEZMQEvent* obj = new NEZMQEvent();
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
        else
        {
        }
    }

    NAN_METHOD(NEZMQEvent::GetContentType)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->getContentType()));
    }

    NAN_METHOD(NEZMQEvent::GetID)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->id()).c_str())).ToLocalChecked());
    }

    NAN_METHOD(NEZMQEvent::GetCreated)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->created()));
    }

    NAN_METHOD(NEZMQEvent::GetModified)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->modified()));
    }

    NAN_METHOD(NEZMQEvent::GetOrigin)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->origin()));
    }

    NAN_METHOD(NEZMQEvent::GetPushed)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->pushed()));
    }

    NAN_METHOD(NEZMQEvent::GetDevice)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->device()).c_str())).ToLocalChecked());
    }

    NAN_METHOD(NEZMQEvent::GetReadingCount)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->reading_size()));
    }

    NAN_METHOD(NEZMQEvent::GetReading)
    {
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        int index = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        Reading *nativeReading = (obj->nativeHandle)->mutable_reading(index);
        info.GetReturnValue().Set(obj->createReadingInstance(nativeReading));
    }

    NAN_METHOD(NEZMQEvent::SetID)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(str);

        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        (obj->nativeHandle)->set_id(*utfValue);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQEvent::SetCreated)
    {
        long value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        (obj->nativeHandle)->set_created(value);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQEvent::SetModified)
    {
        long value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        (obj->nativeHandle)->set_modified(value);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQEvent::SetOrigin)
    {
        long value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        (obj->nativeHandle)->set_origin(value);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQEvent::SetPushed)
    {
        long value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        (obj->nativeHandle)->set_pushed(value);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }

    NAN_METHOD(NEZMQEvent::SetDevice)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(str);

        NEZMQEvent* obj = ObjectWrap::Unwrap<NEZMQEvent>(info.Holder());
        (obj->nativeHandle)->set_device(*utfValue);
        info.GetReturnValue().Set(Nan::New<Integer>(0));
    }
}


