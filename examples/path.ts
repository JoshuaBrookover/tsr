import * as path from 'path';
let paths = [
	'/usr/local',
	'hello.txt'
];
for (let p of paths) {
	console.log(p + ' is absolute? ' + path.isAbsolute(p));
}
