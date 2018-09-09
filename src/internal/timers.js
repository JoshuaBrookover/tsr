function setImmediate(fn) {
	// TODO: validate arguments
	__setTimer(fn, 1, 0);
}

function setTimeout(fn, ms) {
	// TODO: validate arguments
	ms = ms || 0;
	if (ms <= 0) ms = 1;
	return __setTimer(fn, ms, 0);
}

function setInterval(fn, ms) {
	// TODO: validate arguments
	ms = ms || 0;
	if (ms <= 0) ms = 1;
	return __setTimer(fn, ms, ms);
}

function clearTimeout(timer) {
	// TODO: validate arguments
	__clearTimer(timer);
}

function clearInterval(timer) {
	// TODO: validate arguments
	__clearTimer(timer);
}
