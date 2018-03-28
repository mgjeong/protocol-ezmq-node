var assert = require('assert');
var ezmq = require('../');

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

module.exports = getProtoBufEvent;
