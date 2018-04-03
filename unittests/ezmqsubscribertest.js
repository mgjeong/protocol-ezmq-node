var assert = require('assert');
var ezmq = require('../');
var protoEvent = require('./ezmqtestutils.js');

function subCallback(ezmqEvent) {}

function subTopicCallback(topic, ezmqEvent) {}

var ezmqAPI = new ezmq.EZMQAPI();
ezmqAPI.initialize();
var ip = 'localhost';
var port = 5562;
var ezmqSub = new ezmq.EZMQSubscriber(ip, port, subCallback, subTopicCallback);

describe('#start()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqSub.start(), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#subscribe()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqSub.subscribe(), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#subscribeOnTopic()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqSub.subscribe('topic'), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#subscribeOnTopicList()', function() {
    it('should return EZMQ_OK', function() {
        var topicList = ['Topic1', 'Topic2'];
        assert.equal(ezmqSub.subscribe(topicList), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#unSubscribe()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqSub.unSubscribe(), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#unSubscribeOnTopic()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqSub.unSubscribe('topic'), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#unSubscribeOnTopicList()', function() {
    it('should return EZMQ_OK', function() {
        var topicList = ['Topic1', 'Topic2'];
        assert.equal(
            ezmqSub.unSubscribe(topicList),
            ezmq.EZMQErrorCode.EZMQ_OK
        );
    });
});

describe('#getIp()', function() {
    it('should return 5562', function() {
        assert.equal(ezmqSub.getIp(), ip);
    });
});

describe('#getPort()', function() {
    it('should return 5562', function() {
        assert.equal(ezmqSub.getPort(), port);
    });
});

describe('#stop()', function() {
    it('should return EZMQ_OK', function() {
        assert.equal(ezmqSub.stop(), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});
