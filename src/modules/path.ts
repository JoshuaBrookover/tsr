// TODO: error checking

export function isAbsolute(path: string) {
	return unix.isAbsolute(path);
}

export namespace unix {
	export function isAbsolute(path: string) {
		return path.length > 0 && path[0] == '/';
	}
}
