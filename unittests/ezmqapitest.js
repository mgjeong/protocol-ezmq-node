var assert = require('assert');
var ezmq = require('../');

describe('#initialize()', function() {
    it('should return EZMQ_OK', function() {
        var ezmqAPI = new ezmq.EZMQAPI();
        assert.equal(ezmqAPI.initialize(), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#terminate()', function() {
    it('should return EZMQ_OK', function() {
        var ezmqAPI = new ezmq.EZMQAPI();
        assert.equal(ezmqAPI.initialize(), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqAPI.terminate(), ezmq.EZMQErrorCode.EZMQ_OK);
    });
});

describe('#getstatus()', function() {
    it('should return ezmq service current status', function() {
        var ezmqAPI = new ezmq.EZMQAPI();
        assert.equal(ezmqAPI.initialize(), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqAPI.getStatus(), ezmq.EZMQStatusCode.EZMQ_INITAILIZED);
        assert.equal(ezmqAPI.terminate(), ezmq.EZMQErrorCode.EZMQ_OK);
        assert.equal(ezmqAPI.getStatus(), ezmq.EZMQStatusCode.EZMQ_TERMINATED);
    });
});
