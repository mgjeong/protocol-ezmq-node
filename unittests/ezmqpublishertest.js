var assert = require('assert');
var ezmq = require('../');
var protoEvent = require('./ezmqtestutils.js');

function startCB(errorCode) {}

function stopCB(errorCode) {}

function errorCB(errorCode) {}

var ezmqAPI = new ezmq.EZMQAPI();
ezmqAPI.initialize();
var port = 5562;
var ezmqPub = new ezmq.EZMQPublisher(port, startCB, stopCB, errorCB);

describe('#start()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqPub.start(), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#publish()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqPub.publish(protoEvent()), ezmq.EZMQErrorCode.EZMQ_OK);
        var array = new Uint8Array(4);
        var ezmqByteData = new ezmq.EZMQByteData(array, 4);
        assert.equal(ezmqPub.publish(ezmqByteData), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#publishOnTopic()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(
            ezmqPub.publish(protoEvent(), 'topic'),
            ezmq.EZMQErrorCode.EZMQ_OK
        );
        var array = new Uint8Array(4);
        var ezmqByteData = new ezmq.EZMQByteData(array, 4);
        assert.equal(
            ezmqPub.publish(ezmqByteData, 'topic'),
            ezmq.EZMQErrorCode.EZMQ_OK
        );
    });
});

describe('#publishOnTopicList()', function() {
    it('should return EZMQ_OK', function() {
        var topicList = ['Topic1', 'Topic2'];
        assert.equal(
            ezmqPub.publish(protoEvent(), topicList),
            ezmq.EZMQErrorCode.EZMQ_OK
        );
        var array = new Uint8Array(4);
        var ezmqByteData = new ezmq.EZMQByteData(array, 4);
        assert.equal(
            ezmqPub.publish(ezmqByteData, topicList),
            ezmq.EZMQErrorCode.EZMQ_OK
        );
    });
});

describe('#getPort()', function() {
    it('should return 5562', function() {
        assert.equal(ezmqPub.getPort(), port);
    });
});

describe('#stop()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqPub.stop(), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});
