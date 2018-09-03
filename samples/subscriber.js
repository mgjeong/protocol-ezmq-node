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

var ezmq = require('../');

function sleep(seconds) {
    var e = new Date().getTime() + seconds * 1000;
    while (new Date().getTime() <= e) {}
}

function printProtoEvent(ezmqEvent) {
    console.log('--------------------------------------');
    console.log('Device:  ' + ezmqEvent.getDevice());
    console.log('Readings:  ' + ezmqEvent.getReadingCount());

    for (i = 0; i < ezmqEvent.getReadingCount(); i++) {
        var ezmqReading = ezmqEvent.getReading(i);
        console.log('Name:  ' + ezmqReading.getName());
        console.log('Value:  ' + ezmqReading.getValue());
    }
    console.log('--------------------------------------');
}

function printByteData(ezmqByteData) {
    var length = ezmqByteData.getLength();
    var byteData = ezmqByteData.getByteData();
    console.log('Byte Data length :  ' + length);
    for (i = 0; i < length; i++) {
        console.log('data: ' + byteData[i]);
    }
}

//Callbacks
function subCallback(ezmqEvent) {
    console.log('App subCallback');
    var contentType = ezmqEvent.getContentType();
    if (ezmq.EZMQContentType.EZMQ_CONTENT_TYPE_PROTOBUF == contentType) {
        console.log('Content type:  Protobuf');
        printProtoEvent(ezmqEvent);
    } else if (ezmq.EZMQContentType.EZMQ_CONTENT_TYPE_BYTEDATA == contentType) {
        console.log('Content type:  Byte Data');
        printByteData(ezmqEvent);
    }
}

function subTopicCallback(topic, ezmqEvent) {
    console.log('subTopicCallback [Topic]:  ' + topic);
    var contentType = ezmqEvent.getContentType();
    if (ezmq.EZMQContentType.EZMQ_CONTENT_TYPE_PROTOBUF == contentType) {
        console.log('Content type:  Protobuf');
        printProtoEvent(ezmqEvent);
    } else if (ezmq.EZMQContentType.EZMQ_CONTENT_TYPE_BYTEDATA == contentType) {
        console.log('Content type:  Byte Data');
        printByteData(ezmqEvent);
    }
}

//Print options
function printError() {
    console.log('Re-run the application as shown in below examples: \n');
    console.log('  (1) For subscribing without topic: ');
    console.log('       $ node subscriber -ip 192.168.0.1 -port 5562\n');
    console.log('  (2) For subscribing without topic [Secured]: ');
    console.log('       $ node subscriber -ip 192.168.0.1 -port 5562 -secured 1\n');
    console.log('  (3) For subscribing with topic: ');
    console.log('       $ node subscriber -ip 192.168.0.1 -port 5562 -t topic1\n');
    console.log('  (4) For subscribing with topic [Secured]: ');
    console.log('       $ node subscriber -ip 192.168.0.1 -port 5562 -t topic1 -secured 1');
    process.exit();
}

//Process command line arguments
var argc = process.argv.length;
if (argc != 6 && argc != 8 && argc != 10) {
    printError();
}

var n = 2;
var ip;
var port;
var topic;
var isSecured = 0;
while (n < argc) {
    if ('-ip' === process.argv[n]) {
        ip = process.argv[n + 1];
        console.log('Given IP: ' + ip);
        n = n + 2;
    }
    if ('-port' === process.argv[n]) {
        port = process.argv[n + 1];
        console.log('Given Port: ' + port);
        n = n + 2;
    } else if ('-t' === process.argv[n]) {
        topic = process.argv[n + 1];
        console.log('Topic is : ' + topic);
        n = n + 2;
    } else if ('-secured' === process.argv[n]) {
        isSecured = process.argv[n + 1];
        console.log('isSecured : ' + isSecured);
        n = n + 2;
    } else {
        printError();
    }
}

//Initialize ezmq service
var ezmqAPI = new ezmq.EZMQAPI();
var result = ezmqAPI.initialize();
if (result !== ezmq.EZMQErrorCode.EZMQ_OK) {
    console.log('EZMQ initialize failed');
    process.exit();
}
console.log('EZMQ Initailize [Result] : ' + result);

var ezmqSub = new ezmq.EZMQSubscriber(ip, port, subCallback, subTopicCallback);

if (isSecured) {
    try {
        var clientSecretKey = "ZB1@RS6Kv^zucova$kH(!o>tZCQ.<!Q)6-0aWFmW";
        var clientPublicKey = "-QW?Ved(f:<::3d5tJ$[4Er&]6#9yr=vha/caBc(";
        result = ezmqSub.setClientKeys(clientSecretKey, clientPublicKey);
        if (result !== ezmq.EZMQErrorCode.EZMQ_OK) {
            console.log('setClientKeys failed');
            process.exit();
        }
        var serverPublicKey = "tXJx&1^QE2g7WCXbF.$$TVP.wCtxwNhR8?iLi&S<";
        result = ezmqSub.setServerPublicKey(serverPublicKey);
        if (result !== ezmq.EZMQErrorCode.EZMQ_OK) {
            console.log('setServerPublicKey failed');
            process.exit();
        }
    } catch (err) {
        console.log('set key [exception]:  ' + err.message);
        process.exit();
    }
}

result = ezmqSub.start();
if (result !== ezmq.EZMQErrorCode.EZMQ_OK) {
    console.log('Subscriber start failed');
    process.exit();
}
console.log('Subscriber start [Result]: ' + result);

if (typeof topic !== 'string') {
    console.log('Subscribe  [Result]: ' + ezmqSub.subscribe());
} else {
    console.log('Subscribe [Result]: ' + ezmqSub.subscribe(topic));
}

//To prevent program from exit
var waitTill = new Date(new Date().getTime() + 3 * 1000);
while (waitTill > new Date()) {}
