var assert = require('assert');
var ezmq = require('../');
var protoEvent = require('./ezmqtestutils.js');

var ezmqEvent = new ezmq.EZMQEvent();

describe('#eventGetContentType()', function() {
    it('should return Protouf event as type', function() {
        assert.equal(
            ezmqEvent.getContentType(),
            ezmq.EZMQContentType.EZMQ_CONTENT_TYPE_PROTOBUF
        );
    });
});

describe('#eventDevice()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqEvent.setDevice('device'), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqEvent.getDevice(), 'device');
    });
});

describe('#eventCreated()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqEvent.setCreated(10), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqEvent.getCreated(), 10);
    });
});

describe('#eventModified()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqEvent.setModified(20), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqEvent.getModified(), 20);
    });
});

describe('#eventID()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqEvent.setID('id'), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqEvent.getID(), 'id');
    });
});

describe('#eventPushed()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqEvent.setPushed(10), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqEvent.getPushed(), 10);
    });
});

describe('#eventOrigin()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqEvent.setOrigin(20), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqEvent.getOrigin(), 20);
    });
});

describe('#eventGetReadingCount()', function() {
    it('should return zero as reading count', function() {
        assert.equal(ezmqEvent.getReadingCount(), 0);
    });
});

describe('#eventGetReading()', function() {
    it('should return zero null as return value', function() {
        assert.equal(ezmqEvent.getReading(0), undefined);
        var event = protoEvent();
        var reading = event.getReading(0);
        assert.equal(reading.getOrigin(), 25);
    });
});