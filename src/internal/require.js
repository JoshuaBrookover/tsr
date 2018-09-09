function require(file) {
	if (typeof global.modules == 'undefined') {
		global.modules = [];
	}
	if (typeof global.modules[file] == 'undefined') {
		global.modules[file] = __require(file);
	}
	return global.modules[file];
}
