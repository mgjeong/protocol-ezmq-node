var assert = require('assert');
var ezmq = require('../');

var ezmqEvent = new ezmq.EZMQEvent();
var ezmqReading = new ezmq.EZMQReading(ezmqEvent);

describe('#readingID()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqReading.setID('id'), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqReading.getID(), 'id');
    });
});

describe('#readingCreated()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqReading.setCreated(10), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqReading.getCreated(), 10);
    });
});

describe('#readingModified()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqReading.setModified(20), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqReading.getModified(), 20);
    });
});

describe('#readingOrigin()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqReading.setOrigin(20), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqReading.getOrigin(), 20);
    });
});

describe('#readingPushed()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqReading.setPushed(10), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqReading.getPushed(), 10);
    });
});

describe('#readingDevice()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqEvent.setDevice('device'), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqEvent.getDevice(), 'device');
    });
});

describe('#readingName()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqReading.setName('id'), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqReading.getName(), 'id');
    });
});

describe('#readingValue()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqReading.setValue('id'), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqReading.getValue(), 'id');
    });
});
