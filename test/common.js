function argTypeAssertionError(i, typeStr) {
  return new RegExp('Argument ' + (i + 1) + ' must be ' + typeStr);
}
module.exports = {
  ERR_MUST_USE_NEW: /Cannot instantiate without new/,
  ERR_INVALID_ARGUMENTS: /Invalid arguments/,
  ERR_NOT_IMPLEMENTED: /Not implemented/,
  numberArgAssertionError: function(i) {
    return argTypeAssertionError(i, 'a number');
  },
  stringArgAssertionError: function(i) {
    return argTypeAssertionError(i, 'a string');
  },
  functionArgAssertionError: function(i) {
    return argTypeAssertionError(i, 'a function');
  },
  argcAssertionError: function(count, actual) {
    return new RegExp('Expected ' + count + ' arguments, but got ' + actual);
  },
  argcMinAssertionError: function(min, actual) {
    return new RegExp('Expected at least ' + min + ' arguments, but got ' + actual);
  },
  argcRangeAssertionError: function(min, max, actual) {
    return new RegExp('Expected ' + min + '-' + max + ' arguments, but got ' + actual);
  }
};
