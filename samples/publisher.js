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

//Callbacks
function startCB(errorCode) {
    console.log('JS APP startCB');
}

function stopCB(errorCode) {
    console.log('JS APP stopCallback ');
}

function errorCB(errorCode) {
    console.log('JS APP errorCallback ');
}

//EZMQ Event
function getProtoBufEvent() {
    var ezmqEvent = new ezmq.EZMQEvent();
    ezmqEvent.setDevice('device');
    ezmqEvent.setCreated(10);
    ezmqEvent.setModified(20);
    ezmqEvent.setID('id');
    ezmqEvent.setPushed(10);
    ezmqEvent.setOrigin(20);

    // Reading 1
    var ezmqReading = new ezmq.EZMQReading(ezmqEvent);
    ezmqReading.setName('reading1');
    ezmqReading.setValue('10');
    ezmqReading.setCreated(25);
    ezmqReading.setDevice('device');
    ezmqReading.setModified(20);
    ezmqReading.setID('id1');
    ezmqReading.setOrigin(25);
    ezmqReading.setPushed(1);

    // Reading 2
    var ezmqReading2 = new ezmq.EZMQReading(ezmqEvent);
    ezmqReading2.setName('reading2');
    ezmqReading2.setValue('20');
    ezmqReading2.setCreated(30);
    ezmqReading2.setDevice('device');
    ezmqReading2.setModified(20);
    ezmqReading2.setID('id2');
    ezmqReading2.setOrigin(25);
    ezmqReading2.setPushed(1);

    return ezmqEvent;
}

//Print options
function printError() {
    console.log('Re-run the application as shown in below examples: \n');
    console.log('  (1) For publishing without topic: ');
    console.log('       $ node publisher -port 5562\n');
    console.log('  (2) For publishing without topic[Secured]:');
    console.log('       $ node publisher -port 5562 -secured 1\n');
    console.log('  (3) For publishing with topic: ');
    console.log('       $ node publisher -port 5562 -t topic1\n');
    console.log('  (4) For publishing with topic [Secured]: ');
    console.log('       $ node publisher -port 5562 -t topic1 -secured 1\n');
    process.exit();
}

//Process command line arguments
var argc = process.argv.length;
if (argc != 4 && argc != 6 && argc != 8) {
    printError();
}

var n = 2;
var port;
var topic;
var isSecured = 0;
while (n < argc) {
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
        console.log('isSecured  : ' + isSecured);
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
console.log('EZMQ initialize [Result]: ' + result);

var ezmqPub = new ezmq.EZMQPublisher(port, startCB, stopCB, errorCB);

if (isSecured) {
    try {
        var severPrivatekey = "";
        result = ezmqPub.setServerPrivateKey(severPrivatekey);
    } catch (err) {
        console.log('setServerPrivateKey [exception]:  ' + err.message);
        process.exit();
    }
    if (result !== ezmq.EZMQErrorCode.EZMQ_OK) {
        console.log('setServerPrivateKey failed');
        process.exit();
    }
}

result = ezmqPub.start();
if (result !== ezmq.EZMQErrorCode.EZMQ_OK) {
    console.log('Publisher start failed');
    process.exit();
}
console.log('Publisher start [Result]: ' + result);

var protoEvent = getProtoBufEvent();

// This delay is added to prevent ZeroMQ first packet drop during
// initial connection of publisher and subscriber.
sleep(1);

for (i = 0; i < 15; i++) {
    if (typeof topic !== 'string') {
        console.log(
            'Published event[Protobuf]:  ' +
            (i + 1) +
            ' [Result]: ' +
            ezmqPub.publish(protoEvent)
        );
    } else {
        console.log(
            'Published event[Protobuf]:  ' +
            (i + 1) +
            ' [Result]: ' +
            ezmqPub.publish(protoEvent, topic)
        );
    }
    sleep(1);
}

console.log('Publisher stop [Result]: ' + ezmqPub.stop());
