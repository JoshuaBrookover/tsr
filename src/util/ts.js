var ts = module.exports;
function nyi(fn) {
	print('Not yet implemented: ' + fn);
}
ts.sys = {
	args: [],
	newLine: '\n',
	useCaseSensitiveFileNames: false,
	debugMode: false,
	write: nyi.bind(null, 'ts.sys.write'),
	readFile: nyi.bind(null, 'ts.sys.readFile'),
	writeFile: nyi.bind(null, 'ts.sys.writeFile'),
	watchFile: nyi.bind(null, 'ts.sys.watchFile'),
	watchDirectory: nyi.bind(null, 'ts.sys.watchDirectory'),
	resolvePath: nyi.bind(null, 'ts.sys.resolvePath'),
	fileExists: nyi.bind(null, 'ts.sys.fileExists'),
	directoryExists: nyi.bind(null, 'ts.sys.directoryExists'),
	createDirectory: nyi.bind(null, 'ts.sys.createDirectory'),
	getExecutingFilePath: nyi.bind(null, 'ts.sys.getExecutingFilePath'),
	getCurrentDirectory: nyi.bind(null, 'ts.sys.getCurrentDirectory'),
	getDirectories: nyi.bind(null, 'ts.sys.getDirectories'),
	getEnvironmentVariable: nyi.bind(null, 'ts.sys.getEnvironmentVariable'),
	readDirectory: nyi.bind(null, 'ts.sys.readDirectory'),
	getModifiedTime: nyi.bind(null, 'ts.sys.getModifiedTime'),
	createHash: nyi.bind(null, 'ts.sys.createHash'),
	getMemoryUsage: nyi.bind(null, 'ts.sys.getMemoryUsage'),
	getFileSize: nyi.bind(null, 'ts.sys.getFileSize'),
	exit: nyi.bind(null, 'ts.sys.exit'),
	realpath: nyi.bind(null, 'ts.sys.realpath'),
	tryEnableSourceMapsForHost: nyi.bind(null, 'ts.sys.tryEnableSourceMapsForHost'),
	setTimeout: nyi.bind(null, 'ts.sys.setTimeout'),
	clearTimeout: nyi.bind(null, 'ts.sys.clearTimeout')
};
function transpile(input) {
	return ts.transpileModule(input, {
		compilerOptions: {},
		moduleName: 'asdf',
		reportDiagnostics: true
	}).outputText;
}
