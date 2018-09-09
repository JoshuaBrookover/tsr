var __util = {};
__util.stringify = function(obj, indent) {
	indent = indent || 0;
	var str = '';
	function ind(offset) {
		offset = offset || 0;
		return '  '.repeat(indent + offset);
	}
	if (typeof obj == 'function') {
		str += '[Function]';
	} else if (Array.isArray(obj)) {
		if (indent > 2) {
			str += '[Array]';
		} else {
			str += '[';
			var first = true;
			for (var i = 0; i < obj.length; ++i) {
				if (!first) str += ', ';
				first = false;
				str += __util.stringify(obj[i]);
			}
			str += ']';
			if (str.length > 50) {
				str = '';
				str += '[';
				first = true;
				for (var i = 0; i < obj.length; ++i) {
					if (!first) str += ',';
					first = false;
					str += '\n' + ind(1) + __util.stringify(obj[i]);
				}
				if (!first) str += '\n' + ind();
				str += ']';
			}
		}
	} else if (typeof obj == 'object') {
		if (indent > 2) {
			str += '[Object]';
		} else {
			str += '{';
			var first = true;
			for (var key in obj) {
				if (!first) str += ',';
				first = false;
				str += '\n' + ind(1) + key + ': ' + __util.stringify(obj[key], indent + 1);
			}
			if (!first) str += '\n' + ind();
			str += '}';
		}
	} else if (typeof obj == 'string') {
		return '"' + obj + '"';
	} else {
		return String(obj);
	}
	return str;
}
__util.format = function() {
	var str = '';
	var allPrimitive = true;
	for (var i = 0; i < arguments.length; ++i) {
		if (typeof arguments[i] == "function" || typeof arguments[i] == "object") {
			allPrimitive = false;
			break;
		}
	}
	for (var i = 0; i < arguments.length; ++i) {
		str += allPrimitive ? String(arguments[i]) : __util.stringify(arguments[i]);
		if (i != arguments.length - 1) {
			str += ' ';
		}
	}
	return str;
}
